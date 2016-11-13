//******************************************************************************
///
/// @file patches/glow.cpp
///
/// This module implements most of the MegaPOV glow patch.
///
/// @author Chris Huff (original MegaPOV implementation)
/// @author Christoph Lipka (UberPOV port)
///
/// @copyright
/// @parblock
///
/// UberPOV Raytracer version 1.37.
/// Portions Copyright 2013-2016 Christoph Lipka.
///
/// UberPOV 1.37 is an experimental unofficial branch of POV-Ray 3.7, and is
/// subject to the same licensing terms and conditions.
///
/// ----------------------------------------------------------------------------
///
/// Persistence of Vision Ray Tracer ('POV-Ray') version 3.7.
/// Copyright 1991-2016 Persistence of Vision Raytracer Pty. Ltd.
///
/// POV-Ray is free software: you can redistribute it and/or modify
/// it under the terms of the GNU Affero General Public License as
/// published by the Free Software Foundation, either version 3 of the
/// License, or (at your option) any later version.
///
/// POV-Ray is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
/// GNU Affero General Public License for more details.
///
/// You should have received a copy of the GNU Affero General Public License
/// along with this program.  If not, see <http://www.gnu.org/licenses/>.
///
/// ----------------------------------------------------------------------------
///
/// POV-Ray is based on the popular DKB raytracer version 2.12.
/// DKBTrace was originally written by David K. Buck.
/// DKBTrace Ver 2.0-2.12 were written by David K. Buck & Aaron A. Collins.
///
/// @endparblock
///
//******************************************************************************

// Unit header file must be the first file included within POV-Ray *.cpp files (pulls in config)
#include "patches/glow.h"
// This file also implements code declared in multiple other locations.
#include "parser/parser.h"

#include "core/material/warp.h"
#include "core/scene/scenedata.h"

// this must be the last file included
#include "base/povdebug.h"

#if PATCH_MEGAPOV_GLOW

namespace pov
{

//******************************************************************************

Glow::Glow() :
    center(0,0,0),
    colour(RGBColour(1,1,1)),
    glowType(1),
    size(1),
    cutoffRadius(0),
    fadePower(1),
    warps()
{}

//------------------------------------------------------------------------------

Glow::Glow (const Glow& o) :
    center(o.center),
    colour(o.colour),
    glowType(o.glowType),
    size(o.size),
    cutoffRadius(o.cutoffRadius),
    fadePower(o.fadePower),
    warps()
{
    Copy_Warps (warps, o.warps);
}

//------------------------------------------------------------------------------

void Glow::Transform (const TRANSFORM* trans)
{
    MTransPoint (center, center, trans);
}

//******************************************************************************

void Parser::Parse_Glow ()
{
    Glow* glow = new Glow();
    Parse_Glow (glow);
    sceneData->glows.push_back (glow);
}

//------------------------------------------------------------------------------

void Parser::Parse_Glow (LightSource* pLightSource)
{
    Glow* glow = new Glow;
    glow->colour = pLightSource->colour;
    glow->center = pLightSource->Center;
    Parse_Glow (glow);
    sceneData->glows.push_back (glow);
    pLightSource->glows.push_back (glow);
}

//------------------------------------------------------------------------------

void Parser::Parse_Glow (GlowPtr pGlow)
{
    MATRIX Matrix;
    int Warped = false;
    TRANSFORM Trans;
    TRANSFORM Temp_Trans;
    Vector3d Local_Vector;

    MIdentity (Trans.matrix);
    MIdentity (Trans.inverse);

    Parse_Begin();

    EXPECT

        CASE(SIZE_TOKEN)
            pGlow->size = Parse_Float();
        END_CASE

        CASE(RADIUS_TOKEN)
            pGlow->cutoffRadius = Parse_Float();
        END_CASE

        CASE(FADE_POWER_TOKEN)
            pGlow->fadePower = Parse_Float();
        END_CASE

        CASE(TYPE_TOKEN)
            pGlow->glowType = (int)Parse_Float();
            if (pGlow->glowType < 0 || pGlow->glowType > 3)
                Error("Unknown glow type.");
        END_CASE

        CASE(LOCATION_TOKEN)
            Parse_Vector (pGlow->center);
        END_CASE

        CASE(COLOUR_TOKEN)
            Parse_Colour (pGlow->colour);
        END_CASE

        CASE (WARP_TOKEN)
            Parse_Warp (pGlow->warps);
        END_CASE

        CASE (TRANSLATE_TOKEN)
            Parse_Vector (Local_Vector);
            Compute_Translation_Transform (&Temp_Trans, Local_Vector);
            Compose_Transforms (&Trans, &Temp_Trans);
        END_CASE

        CASE (ROTATE_TOKEN)
            Parse_Vector (Local_Vector);
            Compute_Rotation_Transform (&Temp_Trans, Local_Vector);
            Compose_Transforms (&Trans, &Temp_Trans);
        END_CASE

        CASE (SCALE_TOKEN)
            Parse_Scale_Vector (Local_Vector);
            Compute_Scaling_Transform (&Temp_Trans, Local_Vector);
            Compose_Transforms (&Trans, &Temp_Trans);
        END_CASE

        CASE (MATRIX_TOKEN)
            Parse_Matrix (Matrix);
            Compute_Matrix_Transform (&Temp_Trans, Matrix);
            Compose_Transforms (&Trans, &Temp_Trans);
        END_CASE

        CASE (TRANSFORM_TOKEN)
            Parse_Transform (&Temp_Trans);
            Compose_Transforms (&Trans, &Temp_Trans);
        END_CASE

        OTHERWISE
            UNGET
            EXIT
        END_CASE

    END_EXPECT

    Parse_End();

    pGlow->Transform (&Trans);
}

//******************************************************************************

void Trace::ComputeGlows (LightColour& colour, const Intersection& isect, const BasicRay& ray)
{
    for (GlowList::iterator i = sceneData->glows.begin(); i != sceneData->glows.end(); ++i)
        ComputeGlow (colour, isect, ray, **i);
}

//------------------------------------------------------------------------------

void Trace::ComputeGlow (LightColour& colour, const Intersection& isect, const BasicRay& ray, const Glow& glow)
{
    Vector3d    pt;             // point on plane perpendicular to ray and passing through glow
    Vector3d    lightDir;       // direction of glow source
    DBL depth = isect.Depth;    // distance to intersection
    DBL scattering = 0;
    DBL cosA;                   // cosine of the angle between the ray and the direction of the glow source
    DBL dist;

    /* cosA Computing */
    lightDir = ray.Origin - glow.center;
    cosA = dot (lightDir, ray.Direction);

    /* d0 Computing */
    pt = ray.Origin + ray.Direction * -cosA;
    if(!glow.warps.empty())
        Warp_EPoint (pt, pt, glow.warps);

    pt -= glow.center;
    dist = pt.length();
    if(glow.cutoffRadius == 0 || dist < glow.cutoffRadius)
    {
        // scattered energy integration along ray
        switch(glow.glowType)
        {
            case 0: // A model, I(d) = 1/d^2
                {
                    dist /= glow.size;
                    scattering = (atan((depth+cosA)/dist) - atan(cosA/dist))/dist;
                }
                break;

            case 1: // B model, I(d) = 1/(d^2+1)
                {
                    DBL d0 = pt.lengthSqr();
                    DBL denom = sqrt (d0 + 1) / glow.size;
                    if (depth >= MAX_DISTANCE) // Optimization
                        scattering = (M_PI_2 - atan(cosA/denom))/denom;
                    else
                        scattering = (atan((depth+cosA)/denom) - atan(cosA/denom))/denom;
                }
                break;

            case 2: // exp() falloff
                {
                    if(cosA < 0)
                        scattering = exp(-dist/glow.size);
                }
                break;

            case 3: // Cosine falloff
                {
                    DBL d = dist/glow.size;
                    if(d < 1 && cosA < 0)
                        scattering = sin(max(0.0, 1-d)*M_PI_2);
                }
                break;
        }
        if (glow.fadePower != 1)
        {
            if(glow.fadePower == 2)
                scattering *= scattering;
            else
                scattering = pow(scattering, glow.fadePower);
        }
        colour += glow.colour * scattering;
    }
}

//******************************************************************************

void TransformGlows (GlowList& glows, const TRANSFORM* trans)
{
    for (GlowList::iterator i = glows.begin(); i != glows.end(); ++i)
        (*i)->Transform (trans);
}

//------------------------------------------------------------------------------

void DeleteGlows (GlowList& glows)
{
    for (GlowList::iterator i = glows.begin(); i != glows.end(); ++i)
        delete *i;
}

//------------------------------------------------------------------------------

void CopyGlows (GlowList& newGlows, GlowList& oldGlows)
{
    newGlows.reserve (oldGlows.size());
    for (GlowList::iterator i = oldGlows.begin(); i != oldGlows.end(); ++i)
        newGlows.push_back(new Glow(**i));
}

//******************************************************************************

}

#endif // PATCH_MEGAPOV_GLOW

//******************************************************************************
///
/// @file parser/patch.cpp
///
/// @todo   What's in here?
///
/// @copyright
/// @parblock
///
/// UberPOV Raytracer version 1.37.
/// Copyright 2013-2016 Christoph Lipka.
///
/// UberPOV is free software: you can redistribute it and/or modify
/// it under the terms of the GNU Affero General Public License as
/// published by the Free Software Foundation, either version 3 of the
/// License, or (at your option) any later version.
///
/// UberPOV is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
/// GNU Affero General Public License for more details.
///
/// You should have received a copy of the GNU Affero General Public License
/// along with this program.  If not, see <http://www.gnu.org/licenses/>.
///
/// ---------------------------------------------------------------------------
///
/// UberPOV is based on the popular Persistence of Vision Ray Tracer
/// ('POV-Ray') version 3.7, Copyright 1991-2013 Persistence of Vision
/// Raytracer Pty. Ltd.
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

// configparser.h must always be the first POV file included in the parser (pulls in platform config)
#include "parser/configparser.h"
#include "parser/patch.h"

#include "base/stringutilities.h"

// this must be the last file included
#include "base/povdebug.h"

namespace pov
{

typedef struct {
    const char* name;
    float       version;
} Patch_Data;

// List of patches supported by this branch
static const Patch_Data patch_data[] = {
    { "upov",                         137.00 }, // UberPOV version number

    { "upov-blink",                     0.90 }, // UberPOV-style blink keyword
    { "upov-file_time",                 0.90 }, // UberPOV-style file_time function
    { "upov-light_source-max_distance", 0.80 }, // UberPOV-style distance-based cutoff of light sources
    { "upov-lommel_seeliger",           0.90 }, // UberPOV-style support for Lommel-Seeliger diffuse shading model
    { "upov-oren_nayar",                0.10 }, // UberPOV-style support for Oren-Nayar diffuse shading model
#if EXPERIMENTAL_UPOV_PERSISTENT
    { "upov-persistent",                0.20 }, // UberPOV-style persistent data between animation frames
#endif
    { "upov-radiosity-no_cache",        0.10 }, // UberPOV-style bypass of radiosity caching mechanism to implement stochastic diffuse
    { "upov-read-text",                 1.00 }, // UberPOV-style plaintext reading
    { "upov-reflection-roughness",      0.90 }, // UberPOV-style blurred reflections
    { "wfpokorny-density_file-refine",  1.10 }, // density_file centering and new exponential blobbing interpolations.

    /*
    { "upov-backscatter",               0.10 }, // UberPOV-style support for backscattering (cat's eye effect)
    { "upov-finish",                    0.10 }, // UberPOV-style alternative finish syntax
    { "upov-halo",                      0.10 }, // UberPOV-style support for backside illumination halos
    { "upov-sky_sphere",                0.10 }, // UberPOV sky sphere improvements
    { "John Doe's Patch",               1.01 },
    */
    { NULL,                             0.99 }, // end of file, and version number of the patch providing the "#patch" directive and "patch()" function
};

unsigned int GetPatchVersion(char* patchName)
{
    for (const Patch_Data* p = patch_data; ; ++ p)
    {
        if (p->name == NULL)
        {
            if (patchName == NULL)
                return p->version * 100 + 0.5;
            else
                return 0;
        }
        if ((patchName != NULL) && (pov_base::pov_stricmp(patchName, p->name) == 0))
            return (unsigned int)(p->version * 100 + 0.5);
    }
}

} // end of pov namespace

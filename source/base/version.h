//******************************************************************************
///
/// @file base/version.h
///
/// Version information.
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

#ifndef POVRAY_BASE_VERSION_H
#define POVRAY_BASE_VERSION_H

#include "base/configbase.h"
#include "base/branch.h"
#include "base/build.h"

// POV-Ray version and copyright message macros

#define POV_RAY_COPYRIGHT "Copyright 1991-2016 Persistence of Vision Raytracer Pty. Ltd."
#define OFFICIAL_VERSION_STRING "3.7.1"
#define OFFICIAL_VERSION_NUMBER 371

#define POV_RAY_PRERELEASE "x.colour.8883362"

#define POV_RAY_EDITOR_VERSION "3.7.0"

#ifdef BRANCH_NAME

    #if POV_RAY_IS_OFFICIAL == 1
    #error "A branch build cannot be an official POV-Ray build."
    #endif

    #ifdef POV_RAY_PRERELEASE
    #define POV_RAY_VERSION OFFICIAL_VERSION_STRING "-" POV_RAY_PRERELEASE
    #else
    #define POV_RAY_VERSION OFFICIAL_VERSION_STRING
    #endif

    #define POV_RAY_IS_BRANCH 1

    #if STANDALONE_BUILD == 1
    #define STANDALONE_VER ".stalone"
    #define REGCURRENT_VERSION BRANCH_FULL_VERSION
    #else
    #define STANDALONE_VER ""
    #define REGCURRENT_VERSION POV_RAY_VERSION "-" BRANCH_NAME "-" BRANCH_FULL_VERSION
    #endif

#else

    #if (POV_RAY_IS_AUTOBUILD == 1) && ((POV_RAY_IS_OFFICIAL == 1) || (POV_RAY_IS_SEMI_OFFICIAL == 1))
    #ifdef POV_RAY_PRERELEASE
    #define POV_RAY_VERSION OFFICIAL_VERSION_STRING "-" POV_RAY_PRERELEASE "+" POV_RAY_AUTOBUILD_ID
    #else
    #define POV_RAY_VERSION OFFICIAL_VERSION_STRING "+" POV_RAY_AUTOBUILD_ID
    #endif
    #elif (POV_RAY_IS_OFFICIAL == 1)
    #ifdef POV_RAY_PRERELEASE
    #define POV_RAY_VERSION OFFICIAL_VERSION_STRING "-" POV_RAY_PRERELEASE
    #else
    #define POV_RAY_VERSION OFFICIAL_VERSION_STRING
    #endif
    #else
    #ifdef POV_RAY_PRERELEASE
    #define POV_RAY_VERSION OFFICIAL_VERSION_STRING "-" POV_RAY_PRERELEASE ".unofficial"
    #else
    #define POV_RAY_VERSION OFFICIAL_VERSION_STRING "-unofficial"
    #endif
    #endif

    #define BRANCH_NAME                 "POV-Ray"
    #define BRANCH_FULL_NAME            "Persistence of Vision Raytracer(tm)"
    #define BRANCH_MAINTAINER           "the POV-Ray Team"
    #define BRANCH_CONTACT              "http://www.povray.org"
    #define BRANCH_VERSION              OFFICIAL_VERSION
    #define BRANCH_FULL_VERSION         POV_RAY_VERSION
    #define BRANCH_COPYRIGHT            POV_RAY_COPYRIGHT
    #define BRANCH_BUILD_IS_OFFICIAL    POV_RAY_IS_OFFICIAL
    #define POV_RAY_IS_BRANCH           0

    #define STANDALONE_VER ""
    #define REGCURRENT_VERSION POV_RAY_VERSION

#endif

#endif // POVRAY_BASE_VERSION_H

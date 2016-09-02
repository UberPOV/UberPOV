//******************************************************************************
///
/// @file base/branch.h
///
/// This file contains preprocessor defines specifying details of this branch.
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
/// ('POV-Ray') version 3.7, Copyright 1991-2015 Persistence of Vision
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

#ifndef POVRAY_BRANCH_H
#define POVRAY_BRANCH_H

#include "base/configbase.h"
#include "base/build.h"

#define BRANCH_NAME             "UberPOV"
#define BRANCH_FULL_NAME        "UberPOV Raytracer"
#define BRANCH_MAINTAINER       "Christoph Lipka"
#define BRANCH_CONTACT          "http://www.lipka-koeln.de"
#define BRANCH_VERSION          "1.37.1.1"
#define BRANCH_COPYRIGHT        "Copyright 2013-2016 Christoph Lipka."
#define BRANCH_PRERELEASE       "alpha.8767927"

/// Primary developers of this branch, in alphabetical order.
/// Comma-separated list of strings, e.g.
///
///     #define BRANCH_DEVELOPERS "John Doe", "Frank N. Furter", "R. Daneel Olivaw"
///
#define BRANCH_DEVELOPERS       "Christoph Lipka"

/// Additional contributors to this branch, in alphabetical order.
/// Comma-separated list of strings, e.g.
///
///     #define BRANCH_CONTRIBUTORS "John Doe", "Frank N. Furter", "R. Daneel Olivaw"
///
/// Leave undefined if there are no additional contributors.
///
#define BRANCH_CONTRIBUTORS     "Christian Froeschlin"


#if STANDALONE_BUILD == 1
    // This is a build for standalone operation without (or independent of) an official POV-Ray installation,
    // so we're using our own registry key, directory and ini file names.

    #define BRANCH_INI  "uberpov.ini"

    #define REGKEY      "UberPOV"
    #define REGVERKEY   "v1.37"

    #define PATHKEY     "UberPOV"
    #define PATHVERKEY  "v1.37"

#else
    // This is a build for piggyback operation alongside an official POV-Ray installation,
    // so we're using the same registry key, directory and ini file names as official POV-Ray.

    #define BRANCH_INI  "povray.ini"

    #define REGKEY      "POV-Ray"
    #define REGVERKEY   "v3.7"

    #define PATHKEY     "POV-Ray"
    #define PATHVERKEY  "v3.7"

#endif


#ifdef BRANCH_PRERELEASE
#define BRANCH_FULL_VERSION BRANCH_VERSION "-" BRANCH_PRERELEASE
#else
#define BRANCH_FULL_VERSION BRANCH_VERSION
#endif

#endif // POVRAY_BRANCH_H

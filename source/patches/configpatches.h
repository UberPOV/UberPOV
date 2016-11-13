//******************************************************************************
///
/// @file patches/configpatches.h
///
/// This header file defines all types that can be configured by platform
/// specific code for unofficial patches. It further allows insertion of
/// platform specific function prototypes making use of those types.
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

#ifndef POVRAY_PATCHES_CONFIGPATCHES_H
#define POVRAY_PATCHES_CONFIGPATCHES_H

#include "syspovconfigpatches.h"

//******************************************************************************
///
/// @name Ports of MegaPOV Patches
///
/// The following macros enable patches ported from MegaPOV.
///
/// @{

/// @def PATCH_MEGAPOV
/// Define as zero to disable all MegaPOV patch ports not explicitly enabled.
///
#ifndef PATCH_MEGAPOV
    #define PATCH_MEGAPOV 1
#endif

/// @def PATCH_MEGAPOV_GLOW
/// Define as zero to disable the port of the MegaPOV `glow` patch.
///
#ifndef PATCH_MEGAPOV_GLOW
    #define PATCH_MEGAPOV_GLOW PATCH_MEGAPOV
#endif

/// @}
///
//******************************************************************************
///
/// @name Patches With Notable Limitations
///
/// The following macros enable patches which have known noteworthy limitations.
///
/// @{

/// @def EXPERIMENTAL_UPOV_PERSISTENT
/// Experimental patch providing a mechanism to persist data between frames in an animation.
/// Kudos to Christian Froeschlin, who published the basis for this patch on the povray.unofficial.patches newsgroup.
///
/// @note     This patch will also persist data between successive renders in a GUI.
///           Currently, no mechanism has been implemented to force cleanup of persistent data from the GUI.
///           Cleanup from SDL can be achieved using the @c #undef statement.
///
/// @warning  This patch requires parsing to be single-threaded.
///
#ifndef EXPERIMENTAL_UPOV_PERSISTENT
    #define EXPERIMENTAL_UPOV_PERSISTENT 1
#endif

/// @}
///
//******************************************************************************
///
/// @name Debug Settings.
///
/// The following settings enable or disable certain debugging aids, such as run-time sanity checks
/// or additional log output.
///
/// Unless noted otherwise, a non-zero integer will enable the respective debugging aids, while a
/// zero value will disable them.
///
/// It is recommended that system-specific configurations leave these settings undefined in release
/// builds, in which case they will default to @ref POV_DEBUG unless noted otherwise.
///
/// @{

/// @def POV_PATCHES_DEBUG
/// Enable run-time sanity checks for unofficial patches.
///
/// Define as non-zero integer to enable, or zero to disable.
///
#ifndef POV_PATCHES_DEBUG
    #define POV_PATCHES_DEBUG POV_DEBUG
#endif

/// @}
///
//******************************************************************************
///
/// @name Non-Configurable Macros
///
/// The following macros are configured automatically at compile-time; they cannot be overridden by
/// system-specific configuration.
///
/// @{

#if POV_PATCHES_DEBUG
    #define POV_PATCH_ASSERT(expr) POV_ASSERT_HARD(expr)
#else
    #define POV_PATCH_ASSERT(expr) POV_ASSERT_DISABLE(expr)
#endif

/// @}
///
//******************************************************************************

#endif // POVRAY_PATCHES_CONFIGPATCHES_H

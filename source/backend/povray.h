//******************************************************************************
///
/// @file backend/povray.h
///
/// This file contains the interface to initialise and terminate all
/// POV-Ray threads. Beyond the functions in this file, no other
/// functions need to be called to run POV-Ray.
/// Rendering is controlled by the classes provided in the frontend
/// files.
///
/// This file also contains version information strings.
///
/// @copyright
/// @parblock
///
/// UberPOV Raytracer version 1.37.
/// Portions Copyright 2013-2015 Christoph Lipka.
///
/// UberPOV 1.37 is an experimental unofficial branch of POV-Ray 3.7, and is
/// subject to the same licensing terms and conditions.
///
/// ----------------------------------------------------------------------------
///
/// Persistence of Vision Ray Tracer ('POV-Ray') version 3.7.
/// Copyright 1991-2014 Persistence of Vision Raytracer Pty. Ltd.
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

/// @file
/// @todo   Maybe we want to move the version information stuff to a separate file,
///         preferably in the `base` directory.

#ifndef POVRAY_BACKEND_POVRAY_H
#define POVRAY_BACKEND_POVRAY_H

// Please put everything that isn't a preprocessor directive in this
// file into SKIP_COMPLEX_OPTOUT_H sections like the one below! [trf]
#ifndef SKIP_COMPLEX_OPTOUT_H

#include "base/build.h"
#include "base/branch.h"
#include "base/povms.h"
#include <boost/thread.hpp>
#include <boost/function.hpp>

/**
 *  This function does essential initialisation that is required before
 *  POV-Ray can be used. It also starts the main render thread that
 *  receives and processes all messages received from the frontend.
 *  @param  addr  If not NULL, backend address on return.
 *  @return       Pointer to the thread resource created.
 */
boost::thread *povray_init(const boost::function0<void>& threadExit, POVMSAddress *addr = NULL);

/**
 *  This function shuts down the main render thread and after it has
 *  been called, all memory allocated by POV-Ray has been freed and
 *  all threads created by POV-Ray have been terminated.
 */
void povray_terminate();

/**
 *  Returns true if the main thread has terminated. It will return
 *  false if the main thread is not running because it has not yet
 *  been started.
 */
bool povray_terminated();

#endif // SKIP_COMPLEX_OPTOUT_H

#define DAYS(n)         (86400 * n)

// POV-Ray version and copyright message macros

#define POV_RAY_COPYRIGHT "Copyright 1991-2015 Persistence of Vision Raytracer Pty. Ltd."
#define OFFICIAL_VERSION_STRING "3.7.1"
#define OFFICIAL_VERSION_NUMBER 371
#define OFFICIAL_VERSION_NUMBER_HEX 0x0371

#define POV_RAY_PRERELEASE "alpha.7974983"

#define POV_RAY_EDITOR_VERSION "3.7.0"


#ifdef BRANCH_NAME

#if POV_RAY_IS_OFFICIAL == 1
#error A branch build cannot be an official POV-Ray build.
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

#if POV_RAY_IS_OFFICIAL == 1
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


#if POV_RAY_IS_OFFICIAL == 1

#ifdef DISTRIBUTION_MESSAGE_2
#undef DISTRIBUTION_MESSAGE_2
#endif

#define DISTRIBUTION_MESSAGE_1 "This is an official version prepared by the POV-Ray Team. See the"
#define DISTRIBUTION_MESSAGE_2 "documentation on how to contact the authors or visit us on the"
#define DISTRIBUTION_MESSAGE_3 "internet at http://www.povray.org/\n"

#elif BRANCH_BUILD_IS_OFFICIAL == 1

#define DISTRIBUTION_MESSAGE_1 "This is a branch of POV-Ray " POV_RAY_VERSION " maintained by "
#define DISTRIBUTION_MESSAGE_2 BRANCH_MAINTAINER " (" BRANCH_CONTACT ")."
#define DISTRIBUTION_MESSAGE_3 "The POV-Ray Team(tm) is not responsible for supporting this version.\n"

#else

#ifndef BUILT_BY
#error Please complete the BUILT_BY definition in source/base/build.h
#endif

#define DISTRIBUTION_MESSAGE_1 "This is an unofficial version compiled by:"
#define DISTRIBUTION_MESSAGE_2 BUILT_BY
#if POV_RAY_IS_BRANCH
#define DISTRIBUTION_MESSAGE_3 "Neither the POV-Ray Team(tm) nor the " BRANCH_NAME " maintainers are responsible for supporting this version.\n"
#else
#define DISTRIBUTION_MESSAGE_3 "The POV-Ray Team(tm) is not responsible for supporting this version.\n"
#endif

#endif

#define DISCLAIMER_MESSAGE_1 "This is free software; see the source for copying conditions.  There is NO"
#define DISCLAIMER_MESSAGE_2 "warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE."

#endif // POVRAY_BACKEND_POVRAY_H

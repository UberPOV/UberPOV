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

#ifndef POVRAY_BACKEND_POVRAY_H
#define POVRAY_BACKEND_POVRAY_H

#include "base/build.h"
#include "base/branch.h"
#include <boost/thread.hpp>
#include <boost/function.hpp>

#include "povms/povmscpp.h"

#include "base/version.h"

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

#define DAYS(n)         (86400 * n)

// POV-Ray version and copyright message macros

#if POV_RAY_IS_OFFICIAL == 1

#if POV_RAY_IS_AUTOBUILD == 1
#define DISTRIBUTION_MESSAGE_1 "This is an official automated build authorized by the POV-Ray Team."
#else // POV_RAY_IS_AUTOBUILD
#define DISTRIBUTION_MESSAGE_1 "This is an official version prepared by the POV-Ray Team."
#endif // POV_RAY_IS_AUTOBUILD
#define DISTRIBUTION_MESSAGE_2 "See the documentation on how to contact the authors or visit us"
#define DISTRIBUTION_MESSAGE_3 "on the internet at http://www.povray.org/\n"

#elif POV_RAY_IS_SEMI_OFFICIAL == 1

#if POV_RAY_IS_AUTOBUILD == 1
#define DISTRIBUTION_MESSAGE_1 "This is an automated development build authorized by:"
#else // POV_RAY_IS_AUTOBUILD
#define DISTRIBUTION_MESSAGE_1 "This is a development version compiled by:"
#endif // POV_RAY_IS_AUTOBUILD
#define DISTRIBUTION_MESSAGE_2 BUILT_BY
#define DISTRIBUTION_MESSAGE_3 "The POV-Ray Team does not officially support this version.\n"

#elif BRANCH_BUILD_IS_OFFICIAL == 1

#define DISTRIBUTION_MESSAGE_1 "This is a branch of POV-Ray " POV_RAY_VERSION " maintained by "
#define DISTRIBUTION_MESSAGE_2 BRANCH_MAINTAINER " (" BRANCH_CONTACT ")."
#define DISTRIBUTION_MESSAGE_3 "The POV-Ray Team(tm) is not responsible for supporting this version.\n"

#else

#ifndef BUILT_BY
#error "Please complete the BUILT_BY definition in source/base/build.h"
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

#if (POV_RAY_IS_OFFICIAL == 1) && (POV_RAY_IS_AUTOBUILD != 1)
#define POV_RAY_HAS_OFFICIAL_FEATURES 1
#else
#define POV_RAY_HAS_OFFICIAL_FEATURES 0
#endif

#endif // POVRAY_BACKEND_POVRAY_H

/*******************************************************************************
 * syspovconfig_posix.h
 *
 * This file contains Unix flavor-specific defines for compiling the VFE
 * on generic POSIX-conformant Unix systems.
 *
 * ---------------------------------------------------------------------------
 * Persistence of Vision Ray Tracer ('POV-Ray') version 3.7.
 * Copyright 1991-2013 Persistence of Vision Raytracer Pty. Ltd.
 *
 * POV-Ray is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * POV-Ray is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * ---------------------------------------------------------------------------
 * POV-Ray is based on the popular DKB raytracer version 2.12.
 * DKBTrace was originally written by David K. Buck.
 * DKBTrace Ver 2.0-2.12 were written by David K. Buck & Aaron A. Collins.
 * ---------------------------------------------------------------------------
 * $File: //depot/clipka/upov/vfe/unix/syspovconfig_posix.h $
 * $Revision: #1 $
 * $Change: 6157 $
 * $DateTime: 2013/12/02 16:43:38 $
 * $Author: clipka $
 *******************************************************************************/

#ifndef __SYSPOVCONFIG_POSIX_H__
#define __SYSPOVCONFIG_POSIX_H__

#include <unistd.h>

#if defined(_POSIX_V6_LPBIG_OFFBIG) || defined(_POSIX_V6_LP64_OFF64) || defined(_POSIX_V6_ILP32_OFFBIG)
	// off_t is at least 64 bits
	#define lseek64(handle,offset,whence) lseek(handle,offset,whence)
#elif defined(_POSIX_V6_ILP32_OFF32)
	// off_t is 32 bits
	// Comment-out the following line to proceed anyway.
	#error Image size will be limited to approx. 100 Megapixels. Proceed at your own risk.
	#define lseek64(handle,offset,whence) lseek(handle,offset,whence)
#else
	// Unable to detect off_t size at compile-time; comment-out the following line to proceed anyway.
	#error Image size may be limited to approx. 100 Megapixels. Proceed at your own risk.
	#define lseek64(handle,offset,whence) lseek(handle,offset,whence)
#endif

#if defined(_POSIX_V6_LPBIG_OFFBIG) || defined(_POSIX_V6_LP64_OFF64)
	// long is at least 64 bits.
	#define POV_LONG long
#elif defined(_POSIX_V6_ILP32_OFFBIG) || defined(_POSIX_V6_ILP32_OFF32)
	// long is 32 bits.
	#define POV_LONG long long
#else
	// Unable to detect long size at compile-time, assuming less than 64 bits.
	#define POV_LONG long long
#endif

// TODO - the TLS stuff is just copied from the Linux settings; someone needs to check universal POSIX compatibility.
#define DECLARE_THREAD_LOCAL_PTR(ptrType, ptrName)                __thread ptrType *ptrName
#define IMPLEMENT_THREAD_LOCAL_PTR(ptrType, ptrName, ignore)      __thread ptrType *ptrName
#define GET_THREAD_LOCAL_PTR(ptrName)                             (ptrName)
#define SET_THREAD_LOCAL_PTR(ptrName, ptrValue)                   (ptrName = ptrValue)

#endif

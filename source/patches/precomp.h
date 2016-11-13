//******************************************************************************
///
/// @file patches/precomp.h
///
/// Precompiled header for inofficial patches of POV-Ray.
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

/// @file
/// @note
/// @parblock
///     This header file is _not_ explicitly included in any source file (except @ref patches/precomp.cpp
///     which is designed to allow for precompiling this header in the first place). To use
///     precompiled headers, you will therefore have to make your build environment automatically
///     inject this header at the start of every source file.
///
///     The rationale behind this is to keep the set of headers included in each source file at an
///     absolute minimum when precompiled headers are _not_ used.
/// @endparblock

// Module config header file must be the first file included within POV-Ray unit header files
#include "patches/configpatches.h"

// C++ variants of standard C header files
#include <cassert>
#include <cctype>
#include <cfloat>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

// Standard C++ header files
#include <algorithm>
#include <exception>
#include <list>
#include <map>
#include <new>
#include <set>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

// Boost header files
#include <boost/bind.hpp>
#include <boost/format.hpp>
#include <boost/function.hpp>
#include <boost/functional/hash/hash.hpp>
#include <boost/scoped_array.hpp>
#include <boost/scoped_ptr.hpp>
#if POV_MULTITHREADED
#include <boost/thread.hpp>
#include <boost/thread/condition.hpp>
#endif
#include <boost/tr1/memory.hpp>
#include <boost/unordered_map.hpp>


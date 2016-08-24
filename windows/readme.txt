------------------------------------------------------------------------

UberPOV Raytracer version 1.37.
Portions Copyright 2013-2016 Christoph Lipka.

UberPOV 1.37 is an experimental unofficial branch of POV-Ray 3.7, and is
subject to the same licensing terms and conditions.

------------------------------------------------------------------------

Persistence of Vision Ray Tracer ('POV-Ray') version 3.7.
Copyright 1991-2013 Persistence of Vision Raytracer Pty. Ltd.

POV-Ray is free software: you can redistribute it and/or modify it under
the terms of the GNU Affero General Public License as published by the
Free Software Foundation, either version 3 of the License, or (at your
option) any later version.

POV-Ray is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public
License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program. If not, see http://www.gnu.org/licenses/

------------------------------------------------------------------------

$File: //depot/clipka/upov/windows/readme.txt $
$Revision: #3 $
$Change: 6009 $
$DateTime: 2013/08/21 19:29:03 $
$Author: clipka $

------------------------------------------------------------------------

=======================================
Building the UberPOV for Windows source
=======================================


About this document
-------------------

This document does not attempt to explain how UberPOV works or how to
make modifications to it. Some of the internals of UberPOV are highly
complex; if you wish to gain a better understanding of that topic,
please follow the link provided on the source code page mentioned below.
This document is intended only to assist you in getting the UberPOV
source code built using an officially supported compiler on Win32 or
Win64. Furthermore, no attempt is made to cover advanced subjects such
as profile-guided optimization (though we will point out that the latter
is definitely worthwhile, if you have the time and patience).

Assistance
----------

Please use the POV-Ray unofficial patches support group at
http://news.povray.org/povray.unofficial.patches  or
news://news.povray.org/povray.unofficial.patches. This group provides the best
means for support with relation to this subject.

=========
Compilers
=========

Visual Studio 2010 and 2012
---------------------------

Currently the only officially supported means of building the Windows
version of UberPOV is via the provided Visual Studio 2010 project (you
can also use it with VS 2012) with a full version of Visual Studio and
the compilers provided with it or with the platform SDK.

The Visual Studio 2010 project is located in the "windows/vs10"
subdirectory.

Visual Studio 2015
------------------

The Visual Studio 2010 projects should also build fine in Visual Studio 2015
after automatic conversion, as has been tested with the Visual Studio 2015
Community edition.

Earlier Versions of Visual Studio
---------------------------------

Note that versions of Visual Studio prior to 8.0 (VS 2005) are not
supported at all and furthermore *will not work*. The code in UberPOV
1.37 requires a reasonably up-to-date C++ compiler and STL, and earlier
versions of VC++ are not compatible. VS 2005 /may/ work but as it is not
used or tested against we do not recommend it. VS2008 /should/ work as
it was used for a portion of the development process of POV 3.7. In
either case you will need to generate suitable project files, which is
not as simple as just dropping all the source files into a new project
and hitting F7. Please closely study the options applied to each project
in the VS2010 solution if you wish to try to backport the projects.


Visual Studio Express
---------------------

The express editions have been reported to work in building 32-bit executables
but this is not officially supported, and additionally takes some effort to get
set up. It is recommended to first try building POV-Ray 3.7, of which UberPOV
1.37 is an unofficial branch; a source distribution package of POV-Ray for
Windows can be obtained from http://www.povray.org; once you are successful in
building POV-Ray, it should be easy to adapt your build process to UberPOV.


Other Compilers
---------------

In order to build UberPOV with any other compiler, it is recommended to first
try building POV-Ray 3.7, of which UberPOV 1.37 is an unofficial branch;
a source distribution package of POV-Ray for Windows can be obtained from
http://www.povray.org; once you are successful in building POV-Ray, it should
be easy to adapt your build process to UberPOV.


===========
Build Steps
===========

 1. Make sure you have a working copy of the appropriate release binary
    installed. This ensures that the appropriate registry settings and
    support files are present. If you don't do this, your compiled code
    will probably not work on your machine.

 2. Open |windows\vs10\uberpov.sln| in Visual Studio 2010/2012. Set
    'Windows Targets > GUI' as the start-up project if it is not already
    selected. Then, select the 'Generic POV-Ray > povbackend' project
    and expand 'Backend Headers', then open the file |'povray.h'| listed
    within it. Please set |DISTRIBUTION_MESSAGE_2| to your real name to
    make unofficial versions distinguishable from each other. Remove the
    |#error| directive afterwards to proceed with the build. Note that
    if you do not do this you will get compile errors.

    By default, the GUI project is built, and the Console project is
    excluded. If you wish to generate a simple console version of
    UberPOV, please modify the configuration as needed, edit
    vfe\win\syspovconfig.h to enable the definition of _CONSOLE as noted
    therein, and build.

    *Note:* The windows console project is intended to be a simple
    example of how to use the VFE library to make a console version of
    UberPOV with /minimal code/. It is */not/* intended to be a
    fully-featured console build of POV. If you wish to make a more
    comprehensive console version that runs on windows, please use the
    unix version as a guide - it uses the same principles (as it is also
    linked with VFE) but has more features.

 3. Once you have taken whatever steps are needed as set out above,
    select your desired build (e.g. Win32 release - anything except
    SSE2|x64), hit F7, and wait. We recommend that you read the rest of
    this document while you are waiting.

    If all goes well, you should end up with the UberPOV for Windows
    executable. All 32-bit binaries should end up in
    |windows\vs10\bin32|, and the 64-bit ones should be in
    |windows\vs10\bin64|.

    Note: if you are building a DEBUG version of UberPOV, be aware that
    the executable will attempt to load the debug version of POV-Ray's
    editor DLLs. In this case, if you want the editor to be available in
    the GUI, copy the standard editor DLLs that come with the official
    POV-Ray 3.7 distribution to their debug equivalent names (e.g. copy
    |cmedit32.dll| to |cmedit32d.dll|, etc).

    Note that the copied |cmedit32.dll| will still attempt to load
    |povcmax32.dll| (i.e. the non-debug version), so it's not necessary
    to copy |povcmax32.dll| to its debug equivalent. The same goes for
    |povcmax64.dll|.

NB: you should never attempt to build the 'x64 SSE2' configuration (if it
is present): apart from the fact that this is by default excluded from
the build in the configuration manager, it simply won't work. The only
reason it is there at all is that Visual Studio insists on cloning the
Win32 SSE2 project every time it updates the solution file, no matter
how hard we try to get rid of it. SSE2 is always enabled for x64 targets
(it can't be turned off as it's a standard feature of all x64 CPU's) and
thus the x64 release project is all that is needed.


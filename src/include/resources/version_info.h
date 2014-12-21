/*
RustyCoder

Copyright (C) 2012-2014 Chak Wai Yuan

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#define MACRO_STRINGIFY(s) #s
#define MACRO_EXPANDED_STRINGIFY(s) MACRO_STRINGIFY(s)

/** Change version numbers only before release */

/** Increment this number when there are huge feature changes */
#define VERSION_MAJOR               1

/** Increment this number when there are feature additions */
#define VERSION_MINOR               0

/** Increment this number when there are bug fixes and minor improvements */
#define VERSION_REVISION            0

/** Change this to number of commits on the master branch before release */
#define VERSION_BUILD               26

#define VER_FILEVERSION            VERSION_MAJOR,VERSION_MINOR,VERSION_REVISION,VERSION_BUILD
#define VER_FILEVERSION_STR        MACRO_EXPANDED_STRINGIFY(VERSION_MAJOR) "." \
                                   MACRO_EXPANDED_STRINGIFY(VERSION_MINOR) "." \
                                   MACRO_EXPANDED_STRINGIFY(VERSION_REVISION) "." \
                                   MACRO_EXPANDED_STRINGIFY(VERSION_BUILD) "\0"

#define VER_PRODUCTVERSION         VER_FILEVERSION
#define VER_PRODUCTVERSION_STR     VER_FILEVERSION_STR

#define VER_PRODUCTNAME_STR        "RustyCoder"
#define VER_FILEDESCRIPTION_STR    "RustyCoder"
#define VER_ORIGINALFILENAME_STR   VER_PRODUCTNAME_STR ".exe"
#define VER_INTERNALNAME_STR       VER_ORIGINALFILENAME_STR
#define VER_COPYRIGHT_STR          "Copyright (C) 2012-2014 Chak Wai Yuan"

#ifdef _DEBUG
#define VER_FILEFLAGS              VS_FF_DEBUG
#else
#define VER_FILEFLAGS              0
#endif

#define VER_FILEOS                 VOS_NT
#define VER_FILETYPE               VFT_APP

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

#ifndef GUI_FILE_EXTENSION_FILTERS_H
#define GUI_FILE_EXTENSION_FILTERS_H

#include "stdafx.h"

class FileExtensionFilters
{
    public:
        static const COMDLG_FILTERSPEC input_audio_format_filters[22];
        static const COMDLG_FILTERSPEC input_profile_format_filters[3];
};

#endif
/*
RustyCoder

Copyright (C) 2012-2015 Chak Wai Yuan

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

#include "stdafx.h"
#include "file_dialog.h"

unsigned int rusty::controls::FileDialog::GetSelectedFileTypeIndex(IFileDialog *save_file_dialog)
{
    unsigned int selected_file_type_index;

    ASSERT_METHOD(save_file_dialog->GetFileTypeIndex(&selected_file_type_index), == , S_OK);

    return selected_file_type_index - 1u;
}
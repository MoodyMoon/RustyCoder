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

#include "stdafx.h"
#include "save_file_dialog.h"

SaveFileDialog::SaveFileDialog(HWND hWndParent, const COMDLG_FILTERSPEC * const rgFilterSpec, unsigned int cFileTypes, FileDialogEvents *events)
{
    assert(hWndParent != nullptr); //owner cannot be null. Dialog must block.

    METHOD_ASSERT(CoCreateInstance(CLSID_FileSaveDialog, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd)), >= , 0);

    if(events != nullptr)
    {
        events->SetData(this);

        FileDialogEvents *file_dialog_events = events;

        file_dialog_events->QueryInterface(IID_PPV_ARGS(&pfde));
        file_dialog_events->Release();

        METHOD_ASSERT(pfd->Advise(pfde, &dwCookie), == , S_OK);
    }

    unsigned long flags;

    METHOD_ASSERT(pfd->GetOptions(&flags), >= , 0);

    METHOD_ASSERT(pfd->SetOptions(flags | FOS_FORCEFILESYSTEM | FOS_DONTADDTORECENT), >= , 0);

    METHOD_ASSERT(pfd->SetFileTypes(cFileTypes, rgFilterSpec), >= , 0);

    if((pfd->Show(hWndParent)) == S_OK)
    {
        IShellItem *ppsi;
        got_result = (SUCCEEDED((pfd->GetResult(&ppsi))) == TRUE);
        assert(got_result);

        wchar_t *ppszName;

        METHOD_ASSERT(ppsi->GetDisplayName(SIGDN_DESKTOPABSOLUTEEDITING, &ppszName), >=, 0);
        output_file_full_path = ppszName;
        CoTaskMemFree(ppszName);

        METHOD_ASSERT(ppsi->GetDisplayName(SIGDN_NORMALDISPLAY, &ppszName), >=, 0);
        output_file_name_extension = ppszName;
        CoTaskMemFree(ppszName);

        METHOD_ASSERT(ppsi->Release(), == , 1ul);
    }
}

bool SaveFileDialog::HasResult(void)
{
    return got_result;
}

std::wstring SaveFileDialog::GetFile(RustyFile::File flag)
{
    assert(got_result);

    switch(flag)
    {
        case RustyFile::File::FULL_PATH:
            return output_file_full_path;
        case RustyFile::File::NAME_AND_EXTENSION:
            return output_file_name_extension;
        default:
            return RustyFile::GetFile(output_file_full_path, flag);
    }
}

SaveFileDialog::~SaveFileDialog(void)
{
    if(pfde != nullptr)
    {
        METHOD_ASSERT(pfd->Unadvise(dwCookie), == , S_OK);

        pfde->Release();
    }

    METHOD_ASSERT(pfd->Release(), == , 0ul);
}
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
#include "save_file_dialog.h"

rusty::controls::SaveFileDialog::SaveFileDialog(HWND hWndParent, const COMDLG_FILTERSPEC * const rgFilterSpec, unsigned int cFileTypes, FileDialogEvents *events)
{
    assert(hWndParent != nullptr); //owner cannot be null. Dialog must block.

    ASSERT_METHOD(CoCreateInstance(CLSID_FileSaveDialog, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd)), >= , 0);

    if(events != nullptr)
    {
        events->SetData(this);

        FileDialogEvents *file_dialog_events = events;

        file_dialog_events->QueryInterface(IID_PPV_ARGS(&pfde));
        file_dialog_events->Release();

        ASSERT_METHOD(pfd->Advise(pfde, &dwCookie), == , S_OK);
    }

    unsigned long flags;

    ASSERT_METHOD(pfd->GetOptions(&flags), >= , 0);

    ASSERT_METHOD(pfd->SetOptions(flags | FOS_FORCEFILESYSTEM | FOS_DONTADDTORECENT), >= , 0);

    ASSERT_METHOD(pfd->SetFileTypes(cFileTypes, rgFilterSpec), >= , 0);

    if((pfd->Show(hWndParent)) == S_OK)
    {
        IShellItem *ppsi;
        got_result = (SUCCEEDED((pfd->GetResult(&ppsi))) == TRUE);
        assert(got_result);

        wchar_t *ppszName;

        ASSERT_METHOD(ppsi->GetDisplayName(SIGDN_FILESYSPATH, &ppszName), >= , 0);
        file_path = ppszName;
        CoTaskMemFree(ppszName);

        selected_file_type_index = FileDialog::GetSelectedFileTypeIndex(pfd);

        ASSERT_METHOD(ppsi->Release(), == , 1ul);
    }
}

bool rusty::controls::SaveFileDialog::HasResult(void)
{
    return got_result;
}

boost::filesystem::path rusty::controls::SaveFileDialog::GetFile()
{
    assert(got_result);

    return file_path;
}

unsigned int rusty::controls::SaveFileDialog::GetSelectedFileTypeIndex()
{
    return selected_file_type_index;
}

rusty::controls::SaveFileDialog::~SaveFileDialog(void)
{
    if(pfde != nullptr)
    {
        ASSERT_METHOD(pfd->Unadvise(dwCookie), == , S_OK);

        pfde->Release();
    }

    ASSERT_METHOD(pfd->Release(), == , 0ul);
}
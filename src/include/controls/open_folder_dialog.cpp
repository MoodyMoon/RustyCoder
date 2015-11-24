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
#include "open_folder_dialog.h"

rusty::controls::OpenFolderDialog::OpenFolderDialog(HWND hWndParent, FileDialogEvents *events)
{
    assert(hWndParent != nullptr); //owner cannot be null. Dialog must block.

    ASSERT_METHOD(CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd)), >= , 0);

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

    ASSERT_METHOD(pfd->SetOptions(flags | FOS_PICKFOLDERS | FOS_FORCEFILESYSTEM | FOS_PATHMUSTEXIST | FOS_DONTADDTORECENT), >= , 0);

    if((pfd->Show(hWndParent)) == S_OK)
    {
        IShellItem *ppsi;
        got_result = (SUCCEEDED((pfd->GetResult(&ppsi))) == TRUE);
        assert(got_result);

        wchar_t *ppszName;

        ASSERT_METHOD(ppsi->GetDisplayName(SIGDN_FILESYSPATH, &ppszName), >= , 0);
        folder_path = ppszName;
        folder_path.append("\\");
        CoTaskMemFree(ppszName);
    }
}

bool rusty::controls::OpenFolderDialog::HasResult(void)
{
    return got_result;
}

boost::filesystem::path rusty::controls::OpenFolderDialog::GetFolder()
{
    assert(got_result);

    return folder_path;
}

rusty::controls::OpenFolderDialog::~OpenFolderDialog(void)
{
    if(pfde != nullptr)
    {
        ASSERT_METHOD(pfd->Unadvise(dwCookie), == , S_OK);

        pfde->Release();
    }

    ASSERT_METHOD(pfd->Release(), == , 0ul);
}
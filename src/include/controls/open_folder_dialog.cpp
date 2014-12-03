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
#include "open_folder_dialog.h"

OpenFolderDialog::OpenFolderDialog(HWND hWndParent, FileDialogEvents *events)
{
    assert(hWndParent != nullptr); //owner cannot be null. Dialog must block.

    METHOD_ASSERT(CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd)), >= , 0);

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

    METHOD_ASSERT(pfd->SetOptions(flags | FOS_PICKFOLDERS | FOS_FORCEFILESYSTEM | FOS_PATHMUSTEXIST | FOS_DONTADDTORECENT), >= , 0);

    if((pfd->Show(hWndParent)) == S_OK)
    {
        IShellItem *ppsi;
        got_result = (SUCCEEDED((pfd->GetResult(&ppsi))) == TRUE);
        assert(got_result);

        wchar_t *ppszName;

        METHOD_ASSERT(ppsi->GetDisplayName(SIGDN_DESKTOPABSOLUTEEDITING, &ppszName), >= , 0);
        output_folder_path = ppszName;
        CoTaskMemFree(ppszName);
    }
}

bool OpenFolderDialog::HasResult(void)
{
    return got_result;
}

std::wstring OpenFolderDialog::GetFolder()
{
    assert(got_result);

    return output_folder_path;
}

OpenFolderDialog::~OpenFolderDialog(void)
{
    if(pfde != nullptr)
    {
        METHOD_ASSERT(pfd->Unadvise(dwCookie), == , S_OK);

        pfde->Release();
    }

    METHOD_ASSERT(pfd->Release(), == , 0ul);
}
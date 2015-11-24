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
#include "open_file_dialog.h"

rusty::controls::OpenFileDialog::OpenFileDialog(HWND hWndParent, const COMDLG_FILTERSPEC * const rgFilterSpec, unsigned int cFileTypes, bool multi_select, FileDialogEvents *events)
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

    ASSERT_METHOD(pfd->SetOptions(flags | FOS_FORCEFILESYSTEM | (multi_select ? FOS_ALLOWMULTISELECT : 0x0) | FOS_FILEMUSTEXIST | FOS_DONTADDTORECENT), >= , 0);

    ASSERT_METHOD(pfd->SetFileTypes(cFileTypes, rgFilterSpec), >= , 0);

    if((pfd->Show(hWndParent)) == S_OK)
    {
        got_result = (SUCCEEDED((pfd->GetResults(&ppenum))) == TRUE);
        assert(got_result);
    }
}

bool rusty::controls::OpenFileDialog::HasResult(void)
{
    return got_result;
}

boost::filesystem::path rusty::controls::OpenFileDialog::GetFile(unsigned long dwIndex)
{
    assert(got_result);

    IShellItem *ppsi = nullptr;

    boost::filesystem::path file_path;

    GetResult(&ppsi, dwIndex);

    wchar_t *ppszName;
    ASSERT_METHOD(ppsi->GetDisplayName(SIGDN_FILESYSPATH, &ppszName), >= , 0);
    file_path = ppszName;
    CoTaskMemFree(ppszName);

    DestroyResult(ppsi);

    return file_path;
}

unsigned long rusty::controls::OpenFileDialog::GetResultCount(void)
{
    assert(got_result);

    unsigned long result_count;
    ASSERT_METHOD(ppenum->GetCount(&result_count), == , S_OK);
    return result_count;
}

void rusty::controls::OpenFileDialog::GetResult(IShellItem **ppsi, int dwIndex)
{
    ASSERT_METHOD(ppenum->GetItemAt(dwIndex, ppsi), >= , 0);
}

void rusty::controls::OpenFileDialog::DestroyResult(IShellItem *ppsi)
{
    ASSERT_METHOD(ppsi->Release(), == , 0ul);
}

rusty::controls::OpenFileDialog::~OpenFileDialog()
{
    if(pfde != nullptr)
    {
        ASSERT_METHOD(pfd->Unadvise(dwCookie), == , S_OK);

        pfde->Release();
    }

    if(got_result)
        ppenum->Release();

    ASSERT_METHOD(pfd->Release(), == , 0ul);
}
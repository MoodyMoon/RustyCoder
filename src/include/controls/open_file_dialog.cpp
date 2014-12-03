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
#include "open_file_dialog.h"

OpenFileDialog::OpenFileDialog(HWND hWndParent, const COMDLG_FILTERSPEC * const rgFilterSpec, unsigned int cFileTypes, bool multi_select, FileDialogEvents *events)
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

    METHOD_ASSERT(pfd->GetOptions(&flags), >=, 0);

    METHOD_ASSERT(pfd->SetOptions(flags | FOS_FORCEFILESYSTEM | (multi_select ? FOS_ALLOWMULTISELECT : 0x0) | FOS_FILEMUSTEXIST | FOS_DONTADDTORECENT), >=, 0);

    METHOD_ASSERT(pfd->SetFileTypes(cFileTypes, rgFilterSpec), >= , 0);

    if((pfd->Show(hWndParent)) == S_OK)
    {
        got_result = (SUCCEEDED((pfd->GetResults(&ppenum))) == TRUE);
        assert(got_result);
    }
}

bool OpenFileDialog::HasResult(void)
{
    return got_result;
}

std::wstring OpenFileDialog::GetFile(RustyFile::File flag)
{
    return GetFile(0ul, flag);
}

std::wstring OpenFileDialog::GetFile(unsigned long dwIndex, RustyFile::File flag)
{
    assert(got_result);

    IShellItem *ppsi = nullptr;

    std::wstring display_name;

    GetResult(&ppsi, dwIndex);

    switch(flag)
    {
        case RustyFile::File::FULL_PATH:
        {
            wchar_t *ppszName;
            GetFullPath(ppsi, &ppszName);
            display_name = ppszName;
            CoTaskMemFree(ppszName);
            break;
        }
        case RustyFile::File::NAME_AND_EXTENSION:
        {
            wchar_t *ppszName;
            GetFileNameExtension(ppsi, &ppszName);
            display_name = ppszName;
            CoTaskMemFree(ppszName);
            break;
        }
        case RustyFile::File::PATH_AND_NAME:
        case RustyFile::File::PATH:
        case RustyFile::File::NAME:
        case RustyFile::File::EXTENSION:
        {
            wchar_t *ppszName;
            GetFullPath(ppsi, &ppszName);
            display_name = ppszName;
            CoTaskMemFree(ppszName);
            display_name = RustyFile::GetFile(display_name, flag);
            break;
        }
    }

    DestroyResult(ppsi);

    return display_name;
}

unsigned long OpenFileDialog::GetResultCount(void)
{
    assert(got_result);

    unsigned long result_count;
    METHOD_ASSERT(ppenum->GetCount(&result_count), == , S_OK);
    return result_count;
}

void OpenFileDialog::GetResult(IShellItem **ppsi, int dwIndex)
{
    METHOD_ASSERT(ppenum->GetItemAt(dwIndex, ppsi), >=, 0);
}

void OpenFileDialog::DestroyResult(IShellItem *ppsi)
{
    METHOD_ASSERT(ppsi->Release(), ==, 0ul);
}

void OpenFileDialog::GetFileNameExtension(IShellItem *ppsi, wchar_t **ppszName)
{
    METHOD_ASSERT(ppsi->GetDisplayName(SIGDN_NORMALDISPLAY, ppszName), >= , 0);
}

void OpenFileDialog::GetFullPath(IShellItem *ppsi, wchar_t **ppszName)
{
    METHOD_ASSERT(ppsi->GetDisplayName(SIGDN_DESKTOPABSOLUTEEDITING, ppszName), >=, 0);
}

OpenFileDialog::~OpenFileDialog()
{
    if(pfde != nullptr)
    {
        METHOD_ASSERT(pfd->Unadvise(dwCookie), ==, S_OK);

        pfde->Release();
    }

    if(got_result)
        ppenum->Release();

    METHOD_ASSERT(pfd->Release(), == , 0ul);
}
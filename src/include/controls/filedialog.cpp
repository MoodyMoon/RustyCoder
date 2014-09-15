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
#include "FileDialog.h"

OpenFileDialog::OpenFileDialog(HWND hWndParent, const COMDLG_FILTERSPEC * const rgFilterSpec, unsigned int cFileTypes)
{
    assert(hWndParent != nullptr); //owner cannot be null. Dialog must block.

    if(CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd)) < 0)
        throw GuiGenericException("OpenFileDialog", GetLastError(), WindowsUtilities::UTF8_Encode(WindowsUtilities::GetErrorMessage(GetLastError())).c_str());

    unsigned long flags;

    if(pfd->GetOptions(&flags) < 0)
        throw GuiGenericException("OpenFileDialog", GetLastError(), WindowsUtilities::UTF8_Encode(WindowsUtilities::GetErrorMessage(GetLastError())).c_str());

    if(pfd->SetOptions(flags | FOS_FORCEFILESYSTEM | FOS_ALLOWMULTISELECT | FOS_FILEMUSTEXIST | FOS_DONTADDTORECENT) < 0)
        throw GuiGenericException("OpenFileDialog", GetLastError(), WindowsUtilities::UTF8_Encode(WindowsUtilities::GetErrorMessage(GetLastError())).c_str());

    if(pfd->SetFileTypes(cFileTypes, rgFilterSpec) < 0)
        throw GuiGenericException("OpenFileDialog", GetLastError(), WindowsUtilities::UTF8_Encode(WindowsUtilities::GetErrorMessage(GetLastError())).c_str());

    if((pfd->Show(hWndParent)) == S_OK)
    {
        got_result = (SUCCEEDED((pfd->GetResults(&ppenum))) == TRUE);
        if(!got_result)
            throw GuiGenericException("OpenFileDialog", GetLastError(), WindowsUtilities::UTF8_Encode(WindowsUtilities::GetErrorMessage(GetLastError())).c_str());
    }
}

bool OpenFileDialog::HasResult(void)
{
    return got_result;
}

std::wstring OpenFileDialog::GetFile(unsigned long dwIndex, File flag)
{
    //Original ref_count of IShellItem is 1
    IShellItem *ppsi = nullptr;

    std::wstring display_name;

    GetResult(&ppsi, dwIndex);

    switch(flag)
    {
        case FULL_PATH:
        {
            wchar_t *ppszName = nullptr;
            GetFullPath(ppsi, &ppszName);
            display_name = ppszName;
            CoTaskMemFree(ppszName);
            break;
        }
        case NAME_AND_EXTENSION:
        {
            wchar_t *ppszName = nullptr;
            GetFileNameExtension(ppsi, &ppszName);
            display_name = ppszName;
            CoTaskMemFree(ppszName);
            break;
        }
        case PATH_AND_NAME:
        {
            wchar_t *ppszName = nullptr;
            GetFullPath(ppsi, &ppszName);
            display_name = ppszName;
            CoTaskMemFree(ppszName);
            std::wstring display_name2;
            display_name2 = display_name.substr(0u, display_name.rfind(L'\\') + 1u);
            std::wstring::size_type pos1 = display_name.rfind(L'\\') + 1u, pos2;
            display_name = display_name.substr(pos1, display_name.npos - pos1);
            pos1 = display_name.rfind(L'.');
            if(pos1 != display_name.npos)
            {
                pos2 = display_name.find(L' ', pos1 + 1u);
                if(pos2 == display_name.npos)
                    display_name = display_name.substr(0, pos1);
            }
            display_name = display_name2.append(display_name);
            break;
        }
        case PATH:
        {
            wchar_t *ppszName = nullptr;
            GetFullPath(ppsi, &ppszName);
            display_name = ppszName;
            CoTaskMemFree(ppszName);
            display_name = display_name.substr(0u, display_name.rfind(L'\\') + 1u);
            break;
        }
        case NAME:
        {
            wchar_t *ppszName = nullptr;
            GetFullPath(ppsi, &ppszName);
            display_name = ppszName;
            CoTaskMemFree(ppszName);
            std::wstring::size_type pos1 = display_name.rfind(L'\\') + 1u, pos2;
            display_name = display_name.substr(pos1, display_name.npos - pos1);
            pos1 = display_name.rfind(L'.');
            if(pos1 != display_name.npos)
            {
                pos2 = display_name.find(L' ', pos1 + 1u);
                if(pos2 == display_name.npos)
                    display_name = display_name.substr(0, pos1);
            }
            break;
        }
        case EXTENSION:
        {
            wchar_t *ppszName = nullptr;
            GetFullPath(ppsi, &ppszName);
            display_name = ppszName;
            CoTaskMemFree(ppszName);
            std::wstring::size_type pos1 = display_name.rfind(L'\\') + 1u, pos2;
            display_name = display_name.substr(pos1, display_name.npos - pos1);
            pos1 = display_name.rfind(L'.');
            if(pos1 != display_name.npos)
            {
                pos2 = display_name.find(L' ', pos1 + 1u);
                if(pos2 == display_name.npos)
                    display_name = display_name.substr(pos1, display_name.npos);
                else
                    display_name.clear();
            }
            else
                display_name.clear();
            break;
        }
    }

    DestroyResult(ppsi);

    return display_name;
}

OpenFileDialog::~OpenFileDialog(void)
{
    if(got_result)
    {
        ref_count = ppenum->Release();
        ppenum = nullptr;
    }

    METHOD_ASSERT(pfd->Release(), ==, 0ul);
    pfd = nullptr;
}

void OpenFileDialog::GetResult(IShellItem **ppsi, int dwIndex)
{
    if(ppenum->GetItemAt(dwIndex, ppsi) < 0)
        throw GuiGenericException("OpenFileDialog", GetLastError(), WindowsUtilities::UTF8_Encode(WindowsUtilities::GetErrorMessage(GetLastError())).c_str());
}

void OpenFileDialog::DestroyResult(IShellItem *ppsi)
{
    if(ppsi->Release() != 0ul)
        throw GuiGenericException("OpenFileDialog", GetLastError(), WindowsUtilities::UTF8_Encode(WindowsUtilities::GetErrorMessage(GetLastError())).c_str());
}

void OpenFileDialog::GetFileNameExtension(IShellItem *ppsi, wchar_t **ppszName)
{
    if(ppsi->GetDisplayName(SIGDN_NORMALDISPLAY, ppszName) < 0)
        throw GuiGenericException("OpenFileDialog", GetLastError(), WindowsUtilities::UTF8_Encode(WindowsUtilities::GetErrorMessage(GetLastError())).c_str());
}

void OpenFileDialog::GetFullPath(IShellItem *ppsi, wchar_t **ppszName)
{
    if(ppsi->GetDisplayName(SIGDN_DESKTOPABSOLUTEEDITING, ppszName) < 0)
        throw GuiGenericException("OpenFileDialog", GetLastError(), WindowsUtilities::UTF8_Encode(WindowsUtilities::GetErrorMessage(GetLastError())).c_str());
}
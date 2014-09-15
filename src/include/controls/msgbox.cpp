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
#include "msgbox.h"

void MsgBox::Show(const std::string lpText, HWND hWnd, const char * const lpCaption, unsigned int uType)
{
    if(MessageBoxA(hWnd, lpText.c_str(), lpCaption, uType) == 0)
        throw GuiGenericException("MsgBox", GetLastError(), WindowsUtilities::UTF8_Encode(WindowsUtilities::GetErrorMessage(GetLastError())).c_str());
}

void MsgBox::Show(const std::wstring lpText, HWND hWnd, const wchar_t * const lpCaption, unsigned int uType)
{
    if(MessageBoxW(hWnd, lpText.c_str(), lpCaption, uType) == 0)
        throw GuiGenericException("MsgBox", GetLastError(), WindowsUtilities::UTF8_Encode(WindowsUtilities::GetErrorMessage(GetLastError())).c_str());
}

void MsgBox::Show(const char * const lpText, HWND hWnd, const char * const lpCaption, unsigned int uType)
{
    if(MessageBoxA(hWnd, lpText, lpCaption, uType) == 0)
        throw GuiGenericException("MsgBox", GetLastError(), WindowsUtilities::UTF8_Encode(WindowsUtilities::GetErrorMessage(GetLastError())).c_str());
}

void MsgBox::Show(const wchar_t * const lpText, HWND hWnd, const wchar_t * const lpCaption, unsigned int uType)
{
    if(MessageBoxW(hWnd, lpText, lpCaption, uType) == 0)
        throw GuiGenericException("MsgBox", GetLastError(), WindowsUtilities::UTF8_Encode(WindowsUtilities::GetErrorMessage(GetLastError())).c_str());
}
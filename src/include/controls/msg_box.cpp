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
#include "msg_box.h"

void rusty::controls::MsgBox::Show(const int value, HWND hWnd, const char * const lpCaption, unsigned int uType)
{
    ASSERT_METHOD(MessageBoxA(hWnd, std::to_string(value).c_str(), lpCaption, uType), != , 0);
}

void rusty::controls::MsgBox::Show(const long value, HWND hWnd, const char * const lpCaption, unsigned int uType)
{
    ASSERT_METHOD(MessageBoxA(hWnd, std::to_string(value).c_str(), lpCaption, uType), != , 0);
}

void rusty::controls::MsgBox::Show(const long long value, HWND hWnd, const char * const lpCaption, unsigned int uType)
{
    ASSERT_METHOD(MessageBoxA(hWnd, std::to_string(value).c_str(), lpCaption, uType), != , 0);
}

void rusty::controls::MsgBox::Show(const unsigned value, HWND hWnd, const char * const lpCaption, unsigned int uType)
{
    ASSERT_METHOD(MessageBoxA(hWnd, std::to_string(value).c_str(), lpCaption, uType), != , 0);
}

void rusty::controls::MsgBox::Show(const unsigned long value, HWND hWnd, const char * const lpCaption, unsigned int uType)
{
    ASSERT_METHOD(MessageBoxA(hWnd, std::to_string(value).c_str(), lpCaption, uType), != , 0);
}

void rusty::controls::MsgBox::Show(const unsigned long long value, HWND hWnd, const char * const lpCaption, unsigned int uType)
{
    ASSERT_METHOD(MessageBoxA(hWnd, std::to_string(value).c_str(), lpCaption, uType), != , 0);
}

void rusty::controls::MsgBox::Show(const float value, HWND hWnd, const char * const lpCaption, unsigned int uType)
{
    ASSERT_METHOD(MessageBoxA(hWnd, std::to_string(value).c_str(), lpCaption, uType), != , 0);
}

void rusty::controls::MsgBox::Show(const double value, HWND hWnd, const char * const lpCaption, unsigned int uType)
{
    ASSERT_METHOD(MessageBoxA(hWnd, std::to_string(value).c_str(), lpCaption, uType), != , 0);
}

void rusty::controls::MsgBox::Show(const long double value, HWND hWnd, const char * const lpCaption, unsigned int uType)
{
    ASSERT_METHOD(MessageBoxA(hWnd, std::to_string(value).c_str(), lpCaption, uType), != , 0);
}

void rusty::controls::MsgBox::Show(const std::string lpText, HWND hWnd, const char * const lpCaption, unsigned int uType)
{
    ASSERT_METHOD(MessageBoxA(hWnd, lpText.c_str(), lpCaption, uType), != , 0);
}

void rusty::controls::MsgBox::Show(const std::wstring lpText, HWND hWnd, const wchar_t * const lpCaption, unsigned int uType)
{
    ASSERT_METHOD(MessageBoxW(hWnd, lpText.c_str(), lpCaption, uType), != , 0);
}

void rusty::controls::MsgBox::Show(const char * const lpText, HWND hWnd, const char * const lpCaption, unsigned int uType)
{
    ASSERT_METHOD(MessageBoxA(hWnd, lpText, lpCaption, uType), != , 0);
}

void rusty::controls::MsgBox::Show(const wchar_t * const lpText, HWND hWnd, const wchar_t * const lpCaption, unsigned int uType)
{
    ASSERT_METHOD(MessageBoxW(hWnd, lpText, lpCaption, uType), != , 0);
}
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

#ifndef CONTROLS_MSGBOX_H
#define CONTROLS_MSGBOX_H

class MsgBox
{
    public:
        MsgBox(const MsgBox &) = delete;
        MsgBox & operator=(const MsgBox &) = delete;

        static void Show(const int value, HWND hWnd = nullptr, const char * const lpCaption = "RustyCoder", unsigned int uType = MB_OK);
        static void Show(const long value, HWND hWnd = nullptr, const char * const lpCaption = "RustyCoder", unsigned int uType = MB_OK);
        static void Show(const long long value, HWND hWnd = nullptr, const char * const lpCaption = "RustyCoder", unsigned int uType = MB_OK);
        static void Show(const unsigned value, HWND hWnd = nullptr, const char * const lpCaption = "RustyCoder", unsigned int uType = MB_OK);
        static void Show(const unsigned long value, HWND hWnd = nullptr, const char * const lpCaption = "RustyCoder", unsigned int uType = MB_OK);
        static void Show(const unsigned long long value, HWND hWnd = nullptr, const char * const lpCaption = "RustyCoder", unsigned int uType = MB_OK);
        static void Show(const float value, HWND hWnd = nullptr, const char * const lpCaption = "RustyCoder", unsigned int uType = MB_OK);
        static void Show(const double value, HWND hWnd = nullptr, const char * const lpCaption = "RustyCoder", unsigned int uType = MB_OK);
        static void Show(const long double value, HWND hWnd = nullptr, const char * const lpCaption = "RustyCoder", unsigned int uType = MB_OK);
        static void Show(const std::string lpText, HWND hWnd = nullptr, const char * const lpCaption = "RustyCoder", unsigned int uType = MB_OK);
        static void Show(const std::wstring lpText, HWND hWnd = nullptr, const wchar_t * const lpCaption = L"RustyCoder", unsigned int uType = MB_OK);
        static void Show(const char * const lpText, HWND hWnd = nullptr, const char * const lpCaption = "RustyCoder", unsigned int uType = MB_OK);
        static void Show(const wchar_t * const lpText, HWND hWnd = nullptr, const wchar_t * const lpCaption = L"RustyCoder", unsigned int uType = MB_OK);
};

#endif
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
#include "profile_form.h"

ProfileForm::ProfileForm(HINSTANCE hInstance, HWND hWndParent, std::unique_ptr<ProfileForm> &me) : hInstance(hInstance), me(&me)
{
    window.reset(new Window(hInstance, this, L"ProfileForm", L"Profile", hWndParent, WS_EX_DLGMODALFRAME, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_VISIBLE, -1, -1, CW_USEDEFAULT, CW_USEDEFAULT, 450, 550, true));
}

LRESULT ProfileForm::HandleEvent(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_NCDESTROY:
            me->reset();
            break;
        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return 0ull;
}
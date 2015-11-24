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
#include "numeric_up_down.h"

rusty::controls::NumericUpDown::NumericUpDown(HINSTANCE hInstance, HWND hWndParent, uintptr_t hMenu, HWND hWndBuddy, int lower_bound, int upper_bound, unsigned long dwExStyle, unsigned long dwStyle) : Window(hInstance, UPDOWN_CLASS, nullptr, hWndParent, dwExStyle, dwStyle, hMenu, 0, 0, 0, 0, true), lower_bound(lower_bound), upper_bound(upper_bound)
{
    SendMessage(hWnd, UDM_SETBUDDY, reinterpret_cast<WPARAM>(hWndBuddy), 0);

    assert(lower_bound <= upper_bound);

    SendMessage(hWnd, UDM_SETRANGE32, static_cast<WPARAM>(lower_bound), static_cast<LPARAM>(upper_bound));
}

int rusty::controls::NumericUpDown::GetPosition(void)
{
    BOOL valid;
    int position = static_cast<int>(SendMessage(hWnd, UDM_GETPOS32, 0, reinterpret_cast<LPARAM>(&valid)));
    assert(valid == TRUE);

    return position;
}

int rusty::controls::NumericUpDown::GetLowerBound(void)
{
    return lower_bound;
}

int rusty::controls::NumericUpDown::GetUpperBound(void)
{
    return upper_bound;
}

void rusty::controls::NumericUpDown::SetPosition(int value)
{
    SendMessage(hWnd, UDM_SETPOS32, 0, static_cast<LPARAM>(value));
}
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

#ifndef CONTROLS_PANEL_H
#define CONTROLS_PANEL_H

class Panel : public Window
{
    public:
        Panel(const Panel &) = delete;
        Panel & operator=(const Panel &) = delete;

        Panel(HINSTANCE hInstance, EventHandlerInterface *event_handler, ControlHandle *parent_handle, const wchar_t * const lpClassName, int hMenu, int x, int y, int nWidth, int nHeight, DWORD dwExStyle = WS_EX_LEFT, DWORD dwStyle = WS_BORDER | WS_CHILD | WS_VISIBLE, bool set_cursor = true);
        Panel(HINSTANCE hInstance, EventHandlerInterface *event_handler, HWND hWndParent, const wchar_t * const lpClassName, int hMenu, int x, int y, int nWidth, int nHeight, DWORD dwExStyle = WS_EX_LEFT, DWORD dwStyle = WS_BORDER | WS_CHILD | WS_VISIBLE, bool set_cursor = true);
};

#endif
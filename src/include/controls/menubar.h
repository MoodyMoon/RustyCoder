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

#ifndef CONTROLS_MENUBAR_H
#define CONTROLS_MENUBAR_H

class MenuBar
{
    private:
        HMENU root_menu = nullptr;

    public:
        MenuBar(const MenuBar &) = delete;
        MenuBar & operator=(const MenuBar &) = delete;

        MenuBar(void);

        MenuHandle CreateSubMenu(const wchar_t * const lpNewItem, MenuHandle * const parent_menu);
        void CreateMenuItem(const wchar_t * const lpNewItem, unsigned int uIDNewItem, MenuHandle &parent_menu);
        void Attach(HWND hWnd);
        std::wstring GetMenuText(MenuHandle &menu, unsigned int uItem);

        ~MenuBar(void);
};

#endif
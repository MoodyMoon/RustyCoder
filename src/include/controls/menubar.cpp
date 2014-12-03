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
#include "menubar.h"

MenuBar::MenuBar(void)
{
    root_menu = CreateMenu();
    assert(root_menu != nullptr);
}

HMENU MenuBar::CreateSubMenu(const wchar_t * const lpNewItem, HMENU parent_menu)
{
    HMENU sub_menu;
    sub_menu = CreatePopupMenu();
    assert(sub_menu != nullptr);

    HMENU menu;
    if(parent_menu == nullptr)
        menu = root_menu;
    else
        menu = parent_menu;

    METHOD_ASSERT(AppendMenu(menu, MF_STRING | MF_POPUP, reinterpret_cast<unsigned int>(sub_menu), lpNewItem), !=, 0);

    return sub_menu;
}

void MenuBar::CreateMenuItem(const wchar_t * const lpNewItem, unsigned int uIDNewItem, HMENU parent_menu)
{
    if(parent_menu == nullptr)
        parent_menu = root_menu;

    METHOD_ASSERT(AppendMenu(parent_menu, MF_STRING, uIDNewItem, lpNewItem), != , 0);
}

void MenuBar::Attach(HWND hWnd)
{
    METHOD_ASSERT(SetMenu(hWnd, root_menu), !=, 0);
}

std::wstring MenuBar::GetMenuText(HMENU menu, unsigned int uItem)
{
    MENUITEMINFO info;
    info.cbSize = sizeof(MENUITEMINFO);
    info.fMask = MIIM_STRING;
    info.dwTypeData = nullptr;

    METHOD_ASSERT(GetMenuItemInfo(menu, uItem, TRUE, &info), !=, 0);

    unsigned int buffer_size = ++info.cch;
    wchar_t *buffer = new (std::nothrow) wchar_t[buffer_size];
    if(buffer == nullptr)
        throw MemoryAllocationException("MenuBar");

    info.dwTypeData = buffer;

    METHOD_ASSERT(GetMenuItemInfo(menu, uItem, TRUE, &info), != , 0);

    std::wstring menu_text(buffer);
    delete[] buffer;

    return menu_text;
}

MenuBar::~MenuBar(void)
{
    if(IsMenu(root_menu))
        METHOD_ASSERT(DestroyMenu(root_menu), != , 0);
}
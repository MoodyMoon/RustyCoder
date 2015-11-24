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
#include "menu_bar.h"

rusty::controls::MenuBar::MenuBar(void)
{
    root_menu = CreateMenu();
    assert(root_menu != nullptr);
}

HMENU rusty::controls::MenuBar::CreateSubMenu(const wchar_t * const lpNewItem, HMENU parent_menu)
{
    HMENU sub_menu;
    sub_menu = CreatePopupMenu();
    assert(sub_menu != nullptr);

    HMENU menu;
    if(parent_menu == nullptr)
        menu = root_menu;
    else
        menu = parent_menu;

    ASSERT_METHOD(AppendMenu(menu, MF_STRING | MF_POPUP, reinterpret_cast<uintptr_t>(sub_menu), lpNewItem), != , 0);

    return sub_menu;
}

void rusty::controls::MenuBar::CreateMenuItem(const wchar_t * const lpNewItem, unsigned int uIDNewItem, HMENU parent_menu)
{
    if(parent_menu == nullptr)
        parent_menu = root_menu;

    ASSERT_METHOD(AppendMenu(parent_menu, MF_STRING, uIDNewItem, lpNewItem), != , 0);
}

void rusty::controls::MenuBar::Attach(HWND hWnd)
{
    ASSERT_METHOD(SetMenu(hWnd, root_menu), != , 0);
}

std::wstring rusty::controls::MenuBar::GetMenuText(HMENU menu, unsigned int uItem)
{
    MENUITEMINFO info;
    info.cbSize = sizeof(MENUITEMINFO);
    info.fMask = MIIM_STRING;
    info.dwTypeData = nullptr;

    ASSERT_METHOD(GetMenuItemInfo(menu, uItem, TRUE, &info), != , 0);

    unsigned int buffer_size = ++info.cch;
    wchar_t *buffer = new (std::nothrow) wchar_t[buffer_size];
    if(buffer == nullptr)
        throw core::MemoryAllocationException("MenuBar");

    info.dwTypeData = buffer;

    ASSERT_METHOD(GetMenuItemInfo(menu, uItem, TRUE, &info), != , 0);

    std::wstring menu_text(buffer);
    delete[] buffer;

    return menu_text;
}

rusty::controls::MenuBar::~MenuBar(void)
{
    if(IsMenu(root_menu))
        ASSERT_METHOD(DestroyMenu(root_menu), != , 0);
}
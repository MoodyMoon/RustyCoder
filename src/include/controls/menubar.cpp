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
    if(root_menu == FALSE)
        throw GuiGenericException("MenuBar", GetLastError(), WindowsUtilities::UTF8_Encode(WindowsUtilities::GetErrorMessage(GetLastError())).c_str());
}

MenuHandle MenuBar::CreateSubMenu(const wchar_t * const lpNewItem, MenuHandle * const parent_menu)
{
    MenuHandle sub_menu;
    sub_menu.handle = CreatePopupMenu();
    if(sub_menu.handle == nullptr)
        throw GuiGenericException("MenuBar", GetLastError(), WindowsUtilities::UTF8_Encode(WindowsUtilities::GetErrorMessage(GetLastError())).c_str());
    
    MenuHandle menu;
    if(parent_menu == nullptr)
        menu.handle = root_menu;
    else
        menu.handle = parent_menu->handle;

    if(AppendMenu(menu.handle, MF_STRING | MF_POPUP, reinterpret_cast<unsigned int>(sub_menu.handle), lpNewItem) == 0)
        throw GuiGenericException("MenuBar", GetLastError(), WindowsUtilities::UTF8_Encode(WindowsUtilities::GetErrorMessage(GetLastError())).c_str());

    return sub_menu;
}

void MenuBar::CreateMenuItem(const wchar_t * const lpNewItem, unsigned int uIDNewItem, MenuHandle &parent_menu)
{
    if(parent_menu.handle == nullptr)
        parent_menu.handle = root_menu;

    if(AppendMenu(parent_menu.handle, MF_STRING, uIDNewItem, lpNewItem) == 0)
        throw GuiGenericException("MenuBar", GetLastError(), WindowsUtilities::UTF8_Encode(WindowsUtilities::GetErrorMessage(GetLastError())).c_str());
}

void MenuBar::Attach(HWND hWnd)
{
    if(SetMenu(hWnd, root_menu) == 0)
        throw GuiGenericException("MenuBar", GetLastError(), WindowsUtilities::UTF8_Encode(WindowsUtilities::GetErrorMessage(GetLastError())).c_str());
}

std::wstring MenuBar::GetMenuText(MenuHandle &menu, unsigned int uItem)
{
    MENUITEMINFO info;
    info.cbSize = sizeof(MENUITEMINFO);
    info.fMask = MIIM_STRING;
    info.dwTypeData = nullptr;

    if(GetMenuItemInfo(menu.handle, uItem, TRUE, &info) == 0)
        throw GuiGenericException("MenuBar", GetLastError(), WindowsUtilities::UTF8_Encode(WindowsUtilities::GetErrorMessage(GetLastError())).c_str());

    unsigned int buffer_size = ++info.cch;
    wchar_t *buffer = new (std::nothrow) wchar_t[buffer_size];
    if(buffer == nullptr)
        throw MemoryAllocationException("MenuBar");

    info.dwTypeData = buffer;

    if(GetMenuItemInfo(menu.handle, uItem, TRUE, &info) == 0)
        throw GuiGenericException("MenuBar", GetLastError(), WindowsUtilities::UTF8_Encode(WindowsUtilities::GetErrorMessage(GetLastError())).c_str());

    std::wstring menu_text(buffer);
    delete[] buffer;

    return menu_text;
}

MenuBar::~MenuBar(void)
{
    if(IsMenu(root_menu))
        METHOD_ASSERT(DestroyMenu(root_menu), != , 0);
}
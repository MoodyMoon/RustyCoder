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
#include "combo_box.h"

ComboBox::ComboBox(HINSTANCE hInstance, HWND hWndParent, int hMenu, int x, int y, int nWidth, Type combo_box_type, unsigned long dwExStyle, unsigned long dwStyle) : Window(hInstance, WC_COMBOBOX, nullptr, hWndParent, dwExStyle, dwStyle | combo_box_type, reinterpret_cast<HMENU>(hMenu), x, y, nWidth, Window::GetClientBottom(hWndParent) - x, true) {}

unsigned int ComboBox::GetItemCount(void)
{
    return ComboBox_GetCount(hWnd);
}

bool ComboBox::IsSelectedItem(void)
{
    return ComboBox_GetCurSel(hWnd) != CB_ERR;
}

unsigned int ComboBox::GetSelectedItemIndex(void)
{
    assert(ComboBox_GetCurSel(hWnd) != CB_ERR);
    return ComboBox_GetCurSel(hWnd);
}

bool ComboBox::HasItemData(unsigned int index)
{
    return ComboBox_GetItemData(hWnd, index) != CB_ERR;
}

LPARAM ComboBox::GetItemData(unsigned int index)
{
    assert(ComboBox_GetItemData(hWnd, index) != CB_ERR);
    return ComboBox_GetItemData(hWnd, index);
}

void ComboBox::SelectItem(unsigned int index)
{
    int text_length = ComboBox_GetLBTextLen(hWnd, index);

    std::unique_ptr<wchar_t> text(new wchar_t[text_length + 1]);
    METHOD_ASSERT(ComboBox_GetLBText(hWnd, index, text.get()), >=, 0);

    METHOD_ASSERT(ComboBox_SelectString(hWnd, index, text.get()), >=, 0);
}

void ComboBox::SelectItem(int start_index, const wchar_t *text)
{
    METHOD_ASSERT(ComboBox_SelectString(hWnd, start_index, text), >=, 0);
}

void ComboBox::AppendItem(const wchar_t *text)
{
    METHOD_ASSERT(ComboBox_AddString(hWnd, text), >=, 0);
}

void ComboBox::AppendItem(const wchar_t *text, LPARAM data)
{
    int index = ComboBox_AddString(hWnd, text);
    assert(index >= 0);

    SetItemData(index, data);
}

void ComboBox::SetItemData(unsigned int index, LPARAM data)
{
    METHOD_ASSERT(ComboBox_SetItemData(hWnd, index, data), !=, CB_ERR);
}

void ComboBox::InsertItem(unsigned int index, const wchar_t *text)
{
    METHOD_ASSERT(ComboBox_InsertString(hWnd, index, text), >=, 0);
}

void ComboBox::InsertItem(unsigned int index, const wchar_t *text, LPARAM data)
{
    METHOD_ASSERT(ComboBox_InsertString(hWnd, index, text), >=, 0);

    SetItemData(index, data);
}

void ComboBox::RemoveItem(unsigned int index)
{
    METHOD_ASSERT(ComboBox_DeleteString(hWnd, index), !=, CB_ERR);
}

void ComboBox::RemoveAllItems(void)
{
    ComboBox_ResetContent(hWnd);
}
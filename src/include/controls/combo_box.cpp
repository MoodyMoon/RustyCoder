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
#include "combo_box.h"

rusty::controls::ComboBox::ComboBox(HINSTANCE hInstance, HWND hWndParent, uintptr_t hMenu, int x, int y, int nWidth, Type combo_box_type, unsigned long dwExStyle, unsigned long dwStyle) : Window(hInstance, WC_COMBOBOX, nullptr, hWndParent, dwExStyle, dwStyle | static_cast<unsigned long>(combo_box_type), hMenu, x, y, nWidth, Window::GetClientBottom(hWndParent) - x, true) {}

unsigned int rusty::controls::ComboBox::GetSelectedItemIndex(void)
{
    assert(ComboBox_GetCurSel(hWnd) != CB_ERR);
    return ComboBox_GetCurSel(hWnd);
}

LPARAM rusty::controls::ComboBox::GetItemData(unsigned int index)
{
    assert(ComboBox_GetItemData(hWnd, index) != CB_ERR);
    return ComboBox_GetItemData(hWnd, index);
}

unsigned int rusty::controls::ComboBox::GetItemCount(void)
{
    return ComboBox_GetCount(hWnd);
}

std::wstring rusty::controls::ComboBox::GetItemText(unsigned int index)
{
    std::unique_ptr<wchar_t> item_text;

    int item_text_length = ComboBox_GetLBTextLen(hWnd, index);

    assert(item_text_length != CB_ERR);

    item_text.reset(new wchar_t[item_text_length + 1]);

    ASSERT_METHOD(ComboBox_GetLBText(hWnd, index, item_text.get()), !=, CB_ERR);

    return item_text.get();
}

bool rusty::controls::ComboBox::HasSelectedItems(void)
{
    return ComboBox_GetCurSel(hWnd) != CB_ERR;
}

bool rusty::controls::ComboBox::HasItemData(unsigned int index)
{
    return ComboBox_GetItemData(hWnd, index) != CB_ERR;
}

void rusty::controls::ComboBox::SelectItem(unsigned int index)
{
    int text_length = ComboBox_GetLBTextLen(hWnd, index);

    std::unique_ptr<wchar_t> text(new wchar_t[text_length + 1]);
    ASSERT_METHOD(ComboBox_GetLBText(hWnd, index, text.get()), >=, CB_ERR);

    ASSERT_METHOD(ComboBox_SelectString(hWnd, index, text.get()), >=, CB_ERR);
}

void rusty::controls::ComboBox::SelectItem(int start_index, const wchar_t *text)
{
    ASSERT_METHOD(ComboBox_SelectString(hWnd, start_index, text), >=, CB_ERR);
}

void rusty::controls::ComboBox::SelectItem(int start_index, LPARAM data)
{
    unsigned int item_count = GetItemCount();

    for(++start_index; start_index < item_count; ++start_index)
    {
        if(GetItemData(start_index) == data)
        {
            SelectItem(start_index);
        }
    }
}

void rusty::controls::ComboBox::AppendItem(const wchar_t *text)
{
    ASSERT_METHOD(ComboBox_AddString(hWnd, text), >=, 0);
}

void rusty::controls::ComboBox::AppendItem(const wchar_t *text, LPARAM data)
{
    int index = ComboBox_AddString(hWnd, text);
    assert(index >= 0);

    SetItemData(index, data);
}

void rusty::controls::ComboBox::SetItemData(unsigned int index, LPARAM data)
{
    ASSERT_METHOD(ComboBox_SetItemData(hWnd, index, data), !=, CB_ERR);
}

void rusty::controls::ComboBox::InsertItem(unsigned int index, const wchar_t *text)
{
    ASSERT_METHOD(ComboBox_InsertString(hWnd, index, text), >=, 0);
}

void rusty::controls::ComboBox::InsertItem(unsigned int index, const wchar_t *text, LPARAM data)
{
    ASSERT_METHOD(ComboBox_InsertString(hWnd, index, text), >=, 0);

    SetItemData(index, data);
}

void rusty::controls::ComboBox::RemoveItem(unsigned int index)
{
    ASSERT_METHOD(ComboBox_DeleteString(hWnd, index), !=, CB_ERR);
}

void rusty::controls::ComboBox::RemoveAllItems(void)
{
    ComboBox_ResetContent(hWnd);
}
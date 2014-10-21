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
#include "list_view.h"

ListView::ListView(HINSTANCE hInstance, HWND hWndParent, int x, int y, int nWidth, int nHeight, int hMenu, DWORD dwExStyle, DWORD dwStyle) : Window(hInstance, WC_LISTVIEW, nullptr, hWndParent, hMenu, x, y, nWidth, nHeight, dwExStyle, dwStyle)
{

}

void ListView::GetColumnText(unsigned int index, wchar_t *text, size_t text_size)
{
    LVCOLUMN column;
    column.mask = LVCF_TEXT;
    column.pszText = text;
    column.cchTextMax = text_size;

    METHOD_ASSERT(ListView_GetColumn(hWnd, index, &column), ==, TRUE);
}

void ListView::EditColumnText(unsigned int index, wchar_t *text, size_t text_size)
{
    LVCOLUMN column;
    column.mask = LVCF_TEXT;
    column.pszText = text;
    column.cchTextMax = text_size;

    METHOD_ASSERT(ListView_SetColumn(hWnd, index, &column), ==, TRUE);
}

void ListView::InsertColumn(unsigned int column_width, unsigned int index, wchar_t *text, size_t text_size)
{
    LVCOLUMN column;
    column.mask = LVCF_WIDTH | LVCF_TEXT;
    column.cx = column_width;
    column.pszText = text;
    column.cchTextMax = text_size;

    METHOD_ASSERT(ListView_InsertColumn(hWnd, index, &column), !=, -1);
}

void ListView::RemoveColumn(unsigned int index)
{
    METHOD_ASSERT(ListView_DeleteColumn(hWnd, index), ==, TRUE);
}

unsigned int ListView::GetRowCount(void)
{
    return ListView_GetItemCount(hWnd);
}

void ListView::InsertRow(unsigned int index)
{
    LVITEM item;
    item.mask = 0u;
    item.iItem = index;
    item.iSubItem = 0;

    METHOD_ASSERT(ListView_InsertItem(hWnd, &item), !=, -1);
}

void ListView::GetCellText(unsigned int column_index, unsigned int row_index, wchar_t **text, size_t text_size)
{
    LVITEM item;
    item.mask = LVIF_TEXT;
    item.iItem = row_index;
    item.iSubItem = column_index;
    item.pszText = (*text);
    item.cchTextMax = text_size;

    METHOD_ASSERT(ListView_GetItem(hWnd, &item), != , -1);
}

void ListView::EditCellText(unsigned int column_index, unsigned int row_index, wchar_t *text, size_t text_size)
{
    LVITEM item;
    item.mask = LVIF_TEXT;
    item.iItem = row_index;
    item.iSubItem = column_index;
    item.pszText = text;
    item.cchTextMax = text_size;

    METHOD_ASSERT(ListView_SetItem(hWnd, &item), != , -1);
}

void ListView::RemoveRow(unsigned int index)
{
    METHOD_ASSERT(ListView_DeleteItem(hWnd, index), ==, TRUE);
}

void ListView::RemoveAllRows(void)
{
    METHOD_ASSERT(ListView_DeleteAllItems(hWnd), == , TRUE);
}
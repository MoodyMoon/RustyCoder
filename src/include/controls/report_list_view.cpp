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
#include "report_list_view.h"

rusty::controls::ReportListView::ReportListView(HINSTANCE hInstance, HWND hWndParent, uintptr_t hMenu, int x, int y, int nWidth, int nHeight, unsigned long dwExStyle, unsigned long dwStyle, bool grid_lines, bool double_buffer, bool full_row_select, bool column_reorder) : Window(hInstance, WC_LISTVIEW, nullptr, hWndParent, dwExStyle, dwStyle, hMenu, x, y, nWidth, nHeight, false)
{
    if(double_buffer)
        ListView_SetExtendedListViewStyleEx(hWnd, LVS_EX_DOUBLEBUFFER, LVS_EX_DOUBLEBUFFER);

    if(full_row_select)
        ListView_SetExtendedListViewStyleEx(hWnd, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);

    if(grid_lines)
        ListView_SetExtendedListViewStyleEx(hWnd, LVS_EX_GRIDLINES, LVS_EX_GRIDLINES);

    if(column_reorder)
        ListView_SetExtendedListViewStyleEx(hWnd, LVS_EX_HEADERDRAGDROP, LVS_EX_HEADERDRAGDROP);
}

void rusty::controls::ReportListView::GetColumnText(unsigned int index, wchar_t *text_buffer, size_t text_buffer_size)
{
    LVCOLUMN column;
    column.mask = LVCF_TEXT;
    column.pszText = text_buffer;
    column.cchTextMax = static_cast<int>(text_buffer_size);

    ASSERT_METHOD(ListView_GetColumn(hWnd, index, &column), == , TRUE);
}

void rusty::controls::ReportListView::SetColumnText(unsigned int index, const wchar_t *text)
{
    LVCOLUMN column;
    column.mask = LVCF_TEXT;
    column.pszText = const_cast<wchar_t *>(text);

    ASSERT_METHOD(ListView_SetColumn(hWnd, index, &column), == , TRUE);
}

void rusty::controls::ReportListView::InsertColumn(unsigned int column_width, unsigned int index, const wchar_t *text)
{
    LVCOLUMN column;
    column.mask = LVCF_WIDTH | (text == nullptr ? 0x0 : LVCF_TEXT);
    column.cx = column_width;

    if(text != nullptr)
        column.pszText = const_cast<wchar_t *>(text);

    ASSERT_METHOD(ListView_InsertColumn(hWnd, index, &column), != , -1);
}

void rusty::controls::ReportListView::RemoveColumn(unsigned int index)
{
    ASSERT_METHOD(ListView_DeleteColumn(hWnd, index), == , TRUE);
}

unsigned int rusty::controls::ReportListView::GetRowCount(void)
{
    return ListView_GetItemCount(hWnd);
}

unsigned int rusty::controls::ReportListView::GetRowUniqueId(unsigned int index)
{
    return ListView_MapIndexToID(hWnd, index);
}

unsigned int rusty::controls::ReportListView::GetRowIndex(unsigned int id)
{
    return ListView_MapIDToIndex(hWnd, id);
}

void rusty::controls::ReportListView::AppendRow(const wchar_t * text, void * data)
{
    unsigned int row_count = GetRowCount();

    InsertRow(row_count, text, data);
}

void rusty::controls::ReportListView::InsertRow(unsigned int index, const wchar_t *text, void *data)
{
    LVITEM item;
    item.mask = LVFIF_TEXT;

    if(data != nullptr)
    {
        item.mask = LVIF_PARAM;
        item.lParam = reinterpret_cast<LPARAM>(data);
    }

    item.iItem = index;
    item.iSubItem = 0;
    item.pszText = const_cast<wchar_t *>(text);

    ASSERT_METHOD(ListView_InsertItem(hWnd, &item), != , -1);
}

void rusty::controls::ReportListView::GetCellText(unsigned int column_index, unsigned int row_index, wchar_t **text_buffer, size_t text_buffer_size)
{
    LVITEM item;
    item.mask = LVIF_TEXT;
    item.iItem = row_index;
    item.iSubItem = column_index;
    item.pszText = *text_buffer;
    item.cchTextMax = static_cast<int>(text_buffer_size);

    ASSERT_METHOD(ListView_GetItem(hWnd, &item), != , -1);
}

void rusty::controls::ReportListView::SetCellText(unsigned int column_index, unsigned int row_index, const wchar_t *text)
{
    LVITEM item;
    item.mask = LVIF_TEXT;
    item.iItem = row_index;
    item.iSubItem = column_index;
    item.pszText = const_cast<wchar_t *>(text);

    ASSERT_METHOD(ListView_SetItem(hWnd, &item), != , -1);
}

void rusty::controls::ReportListView::RemoveRow(unsigned int index)
{
    ASSERT_METHOD(ListView_DeleteItem(hWnd, index), == , TRUE);
}

void rusty::controls::ReportListView::RemoveAllRows()
{
    ASSERT_METHOD(ListView_DeleteAllItems(hWnd), == , TRUE);
}

unsigned int rusty::controls::ReportListView::GetSelectedItemsCount()
{
    return ListView_GetSelectedCount(hWnd);
}

int rusty::controls::ReportListView::GetNextSelectedItem(unsigned int iStart)
{
    return ListView_GetNextItem(hWnd, static_cast<int>(iStart) - 1, LVNI_SELECTED);
}

bool rusty::controls::ReportListView::HasSelectedItems()
{
    return (ListView_GetNextItem(hWnd, -1, LVNI_SELECTED) > -1);
}
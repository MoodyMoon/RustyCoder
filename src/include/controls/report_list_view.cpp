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
#include "report_list_view.h"

ReportListView::ReportListView(HINSTANCE hInstance, HWND hWndParent, int hMenu, int x, int y, int nWidth, int nHeight, unsigned long dwExStyle, unsigned long dwStyle, bool grid_lines, bool double_buffer, bool full_row_select, bool column_reorder) : Window(hInstance, WC_LISTVIEW, nullptr, hWndParent, dwExStyle, dwStyle, reinterpret_cast<HMENU>(hMenu), x, y, nWidth, nHeight, false)
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

void ReportListView::GetColumnText(unsigned int index, wchar_t *text_buffer, size_t text_buffer_size)
{
    LVCOLUMN column;
    column.mask = LVCF_TEXT;
    column.pszText = text_buffer;
    column.cchTextMax = static_cast<int>(text_buffer_size);

    METHOD_ASSERT(ListView_GetColumn(hWnd, index, &column), ==, TRUE);
}

void ReportListView::SetColumnText(unsigned int index, const wchar_t *text)
{
    LVCOLUMN column;
    column.mask = LVCF_TEXT;
    column.pszText = const_cast<wchar_t *>(text);

    METHOD_ASSERT(ListView_SetColumn(hWnd, index, &column), ==, TRUE);
}

void ReportListView::InsertColumn(unsigned int column_width, unsigned int index, const wchar_t *text)
{
    LVCOLUMN column;
    column.mask = LVCF_WIDTH | LVCF_TEXT;
    column.cx = column_width;
    column.pszText = const_cast<wchar_t *>(text);

    METHOD_ASSERT(ListView_InsertColumn(hWnd, index, &column), !=, -1);
}

void ReportListView::RemoveColumn(unsigned int index)
{
    METHOD_ASSERT(ListView_DeleteColumn(hWnd, index), ==, TRUE);
}

unsigned int ReportListView::GetRowCount(void)
{
    return ListView_GetItemCount(hWnd);
}

unsigned int ReportListView::GetRowUniqueId(unsigned int index)
{
    return ListView_MapIndexToID(hWnd, index);
}

unsigned int ReportListView::GetRowIndex(unsigned int id)
{
    return ListView_MapIDToIndex(hWnd, id);
}

void ReportListView::InsertRow(unsigned int index, const wchar_t *text, void *data)
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

    METHOD_ASSERT(ListView_InsertItem(hWnd, &item), !=, -1);
}

void ReportListView::GetCellText(unsigned int column_index, unsigned int row_index, wchar_t **text_buffer, size_t text_buffer_size)
{
    LVITEM item;
    item.mask = LVIF_TEXT;
    item.iItem = row_index;
    item.iSubItem = column_index;
    item.pszText = *text_buffer;
    item.cchTextMax = static_cast<int>(text_buffer_size);

    METHOD_ASSERT(ListView_GetItem(hWnd, &item), != , -1);
}

void ReportListView::SetCellText(unsigned int column_index, unsigned int row_index, const wchar_t *text)
{
    LVITEM item;
    item.mask = LVIF_TEXT;
    item.iItem = row_index;
    item.iSubItem = column_index;
    item.pszText = const_cast<wchar_t *>(text);

    METHOD_ASSERT(ListView_SetItem(hWnd, &item), != , -1);
}

void ReportListView::RemoveRow(unsigned int index)
{
    METHOD_ASSERT(ListView_DeleteItem(hWnd, index), ==, TRUE);
}

void ReportListView::RemoveAllRows()
{
    METHOD_ASSERT(ListView_DeleteAllItems(hWnd), == , TRUE);
}

unsigned int ReportListView::GetSelectedItemsCount()
{
    return ListView_GetSelectedCount(hWnd);
}

int ReportListView::GetNextSelectedItem(unsigned int iStart)
{
    return ListView_GetNextItem(hWnd, static_cast<int>(iStart) - 1, LVNI_SELECTED);
}

bool ReportListView::HasSelectedItems()
{
    return (ListView_GetNextItem(hWnd, -1, LVNI_SELECTED) > -1);
}
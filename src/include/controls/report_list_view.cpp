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

ReportListView::ReportListView(HINSTANCE hInstance, HWND hWndParent, int x, int y, int nWidth, int nHeight, int hMenu, bool grid_lines, bool sort_column, bool single_select, bool double_buffer, bool full_row_select, bool column_reorder) : Window(hInstance, WC_LISTVIEW, nullptr, hWndParent, hMenu, x, y, nWidth, nHeight, (double_buffer ? LVS_EX_DOUBLEBUFFER : 0x0) | (full_row_select ? LVS_EX_FULLROWSELECT : 0x0) | (grid_lines ? LVS_EX_GRIDLINES : 0x0) | (column_reorder ? LVS_EX_HEADERDRAGDROP : 0x0), (sort_column ? 0x0 : LVS_NOSORTHEADER) | LVS_REPORT | (single_select ? LVS_SINGLESEL : 0x0) | WS_BORDER | WS_CLIPCHILDREN | WS_CHILD | WS_VISIBLE) {}

void ReportListView::GetColumnText(unsigned int index, wchar_t *text, size_t text_size)
{
    LVCOLUMN column;
    column.mask = LVCF_TEXT;
    column.pszText = text;
    column.cchTextMax = static_cast<int>(text_size);

    METHOD_ASSERT(ListView_GetColumn(hWnd, index, &column), ==, TRUE);
}

void ReportListView::EditColumnText(unsigned int index, const wchar_t *text, size_t text_size)
{
    LVCOLUMN column;
    column.mask = LVCF_TEXT;
    column.pszText = const_cast<wchar_t *>(text);
    column.cchTextMax = static_cast<int>(text_size);

    METHOD_ASSERT(ListView_SetColumn(hWnd, index, &column), ==, TRUE);
}

void ReportListView::InsertColumn(unsigned int column_width, unsigned int index, const wchar_t *text, size_t text_size)
{
    LVCOLUMN column;
    column.mask = LVCF_WIDTH | LVCF_TEXT;
    column.cx = column_width;
    column.pszText = const_cast<wchar_t *>(text);
    column.cchTextMax = static_cast<int>(text_size);

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

void ReportListView::InsertRow(unsigned int index)
{
    LVITEM item;
    item.mask = 0u;
    item.iItem = index;
    item.iSubItem = 0;

    METHOD_ASSERT(ListView_InsertItem(hWnd, &item), !=, -1);
}

void ReportListView::GetCellText(unsigned int column_index, unsigned int row_index, wchar_t **text, size_t text_size)
{
    LVITEM item;
    item.mask = LVIF_TEXT;
    item.iItem = row_index;
    item.iSubItem = column_index;
    item.pszText = (*text);
    item.cchTextMax = static_cast<int>(text_size);

    METHOD_ASSERT(ListView_GetItem(hWnd, &item), != , -1);
}

void ReportListView::EditCellText(unsigned int column_index, unsigned int row_index, const wchar_t *text, size_t text_size)
{
    LVITEM item;
    item.mask = LVIF_TEXT;
    item.iItem = row_index;
    item.iSubItem = column_index;
    item.pszText = const_cast<wchar_t *>(text);
    item.cchTextMax = static_cast<int>(text_size);

    METHOD_ASSERT(ListView_SetItem(hWnd, &item), != , -1);
}

void ReportListView::RemoveRow(unsigned int index)
{
    METHOD_ASSERT(ListView_DeleteItem(hWnd, index), ==, TRUE);
}

void ReportListView::RemoveAllRows(void)
{
    METHOD_ASSERT(ListView_DeleteAllItems(hWnd), == , TRUE);
}

unsigned int ReportListView::GetSelectedItemsCount(void)
{
    return ListView_GetSelectedCount(hWnd);
}

int ReportListView::GetNextSelectedItem(int iStart)
{
    return ListView_GetNextItem(hWnd, iStart, LVNI_ALL);
}
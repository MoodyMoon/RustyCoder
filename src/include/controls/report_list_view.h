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

#ifndef CONTROLS_REPORT_LIST_VIEW_H
#define CONTROLS_REPORT_LIST_VIEW_H

#include "window.h"

namespace rusty
{
namespace controls
{
class ReportListView : public Window
{
    public:
        ReportListView(const ReportListView &) = delete;
        ReportListView & operator=(const ReportListView &) = delete;

        ReportListView(HINSTANCE hInstance, HWND hWndParent, uintptr_t hMenu, int x, int y, int nWidth, int nHeight, unsigned long dwExStyle = WS_EX_LEFT, unsigned long dwStyle = LVS_REPORT | LVS_SINGLESEL | WS_CHILD | WS_VISIBLE, bool grid_lines = false, bool double_buffer = true, bool full_row_select = true, bool column_reorder = true);

        void GetColumnText(unsigned int index, wchar_t *text_buffer, size_t text_buffer_size);
        void SetColumnText(unsigned int index, const wchar_t *text);
        void InsertColumn(unsigned int column_width, unsigned int index, const wchar_t *text);
        void RemoveColumn(unsigned int index);

        unsigned int GetRowCount(void);
        unsigned int GetRowUniqueId(unsigned int index);
        unsigned int GetRowIndex(unsigned int id);
        void AppendRow(const wchar_t *text, void *data);
        void InsertRow(unsigned int index, const wchar_t *text, void *data);
        void GetCellText(unsigned int column_index, unsigned int row_index, wchar_t **text_buffer, size_t text_buffer_size);
        void SetCellText(unsigned int column_index, unsigned int row_index, const wchar_t *text);
        void RemoveRow(unsigned int index);
        void RemoveAllRows(void);

        unsigned int GetSelectedItemsCount(void);
        int GetNextSelectedItem(unsigned int iStart = 0);
        bool HasSelectedItems(void);

        virtual ~ReportListView(void) {}
};
}
}

#endif
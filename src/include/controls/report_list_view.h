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

#ifndef CONTROLS_REPORT_LIST_VIEW_H
#define CONTROLS_REPORT_LIST_VIEW_H

class ReportListView : public Window
{
    public:
        ReportListView(const ReportListView &) = delete;
        ReportListView & operator=(const ReportListView &) = delete;

        ReportListView(HINSTANCE hInstance, HWND hWndParent, int x, int y, int nWidth, int nHeight, int hMenu, bool grid_lines = false, bool sort_column = true, bool single_select = false, bool double_buffer = true, bool full_row_select = true, bool column_reorder = false);

        void GetColumnText(unsigned int index, wchar_t *text, size_t text_size);
        void EditColumnText(unsigned int index, const wchar_t *text, size_t text_size);
        void InsertColumn(unsigned int column_width, unsigned int index, const wchar_t *text, size_t text_size);
        void RemoveColumn(unsigned int index);

        unsigned int GetRowCount(void);
        void InsertRow(unsigned int index);
        void GetCellText(unsigned int column_index, unsigned int row_index, wchar_t **text, size_t text_size);
        void EditCellText(unsigned int column_index, unsigned int row_index, const wchar_t *text, size_t text_size);
        void RemoveRow(unsigned int index);
        void RemoveAllRows(void);

        unsigned int GetSelectedItemsCount(void);
        int GetNextSelectedItem(int iStart);
};

#endif
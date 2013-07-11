#include "listview.h"

ListView::ListView(HWND hwnd_mainwin)
{
    hwnd = CreateWindowEx(WS_EX_WINDOWEDGE, WC_LISTVIEW, L"", WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_EDITLABELS, 0, 0, 700, 200, hwnd_mainwin, (HMENU)ID_LISTVIEW1, GetModuleHandle(nullptr), nullptr);
}

void ListView::set_column(int column_index, std::wstring column_name)
{
    LVCOLUMN temp_col;
    temp_col.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
    temp_col.fmt = LVCFMT_LEFT;
    temp_col.cx = 180;
    temp_col.pszText = const_cast<wchar_t*>(column_name.c_str());
    temp_col.cchTextMax = 30;
    temp_col.iSubItem = column_index;
    ListView_InsertColumn(hwnd, 0, &temp_col);
}
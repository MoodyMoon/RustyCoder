#include "listview.h"

HWND ListView::hwnd = nullptr;

void ListView::set_handle(HWND hwnd_listview)
{
    hwnd = hwnd_listview;
}

void ListView::set_column(int column_index, std::wstring column_name)
{
    LVCOLUMN temp_col;
    temp_col.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
    temp_col.fmt = LVCFMT_LEFT;
    temp_col.cx = 180;
    temp_col.pszText = const_cast<wchar_t*>(column_name.c_str());
    temp_col.cchTextMax = 30;
    temp_col.iSubItem = 0;
    ListView_InsertColumn(hwnd, column_index, &temp_col);
}

/*
void ListView::dispose(void)
{
    if(!DestroyWindow(ListView::hwnd))
        std::cout << "Fail to destroy ListView" << std::endl;
    else
        std::cout << "Successfully destroyed ListView" << std::endl;
}

void ListView::exists(void)
{
    if(IsWindow(ListView::hwnd))
        std::cout << "ListView exists!" << std::endl;
    else
        std::cout << "ListView does not exists!" << std::endl;
}
*/
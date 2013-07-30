#include "listview.h"

void ListView::set_column(const HWND hwnd, const int column_index, const std::wstring column_name, const int col_width)
{
    LVCOLUMN new_col;
    new_col.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
    new_col.fmt = LVCFMT_LEFT;
    new_col.cx = col_width;
    new_col.pszText = const_cast<wchar_t*>(column_name.c_str());
    new_col.cchTextMax = 30;
    new_col.iSubItem = 0;
    ListView_InsertColumn(hwnd, column_index, &new_col);
}

void ListView::set_item(const HWND hwnd, const std::wstring items[])
{
    LVITEM new_item;
    const int item_count = ListView_GetItemCount(hwnd);
    new_item.mask = LVIF_TEXT;
    new_item.iItem = item_count;
    new_item.iSubItem = 0;
    new_item.pszText = const_cast<wchar_t*>(items[0].c_str());
    
    ListView_InsertItem(hwnd, &new_item);

    for(int i = 1; i <= 2; ++i)
    {
        new_item.iSubItem = i;
        new_item.pszText = const_cast<wchar_t*>(items[i].c_str());
        ListView_SetItem(hwnd, &new_item);
    }

    new_item.iSubItem = 4;
    new_item.pszText = const_cast<wchar_t*>(items[3].c_str());
    ListView_SetItem(hwnd, &new_item);
}

void ListView::set_ex_styles(const HWND hwnd, const long styles)
{
    ListView_SetExtendedListViewStyleEx(hwnd, styles, styles);
}

void ListView::remove_all_items(const HWND hwnd)
{
    ListView_DeleteAllItems(hwnd);
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
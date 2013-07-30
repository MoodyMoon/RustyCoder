#ifndef CTRL_LISTVIEW_H
#define CTRL_LISTVIEW_H

#include <string>

#include <windows.h>
#include <commctrl.h>

#include "res/resource.h"

class ListView
{
    public:
        static void set_column(const HWND hwnd, const int column_index, const std::wstring column_name, const int col_width);
        static void set_item(const HWND hwnd, const std::wstring items[]);
        static void set_ex_styles(const HWND hwnd, const long styles);
        static void remove_all_items(const HWND hwnd);
        /*
        static void dispose(void);
        static void exists(void);
        */
};

#endif
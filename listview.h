#ifndef CTRL_LISTVIEW_H
#define CTRL_LISTVIEW_H

#include <string>

#include <windows.h>
#include <commctrl.h>

#include "res/resource.h"

class ListView
{
    public:
        static void set_column(HWND hwnd, int column_index, std::wstring column_name, int col_width);
        static void set_item(HWND hwnd, const std::wstring items[]);
        static void set_ex_styles(HWND hwnd, long styles);
        static void remove_all_items(HWND hwnd);
        /*
        static void dispose(void);
        static void exists(void);
        */
};

#endif
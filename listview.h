#ifndef CTRL_LISTVIEW_H
#define CTRL_LISTVIEW_H

#include <string>

#include <windows.h>
#include <commctrl.h>

#include "res/resource.h"

class ListView
{
    private:
        static HWND hwnd;
    public:
        static void set_handle(HWND hwnd_mainwin);
        static void set_column(int column_index, std::wstring column_name);
        /*
        static void dispose(void);
        static void exists(void);
        */
};

#endif
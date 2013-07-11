#ifndef CTRL_LISTVIEW_H
#define CTRL_LISTVIEW_H

#include <string>

#include <windows.h>
#include <commctrl.h>

#include "res/resource.h"

class ListView
{
    private:
        HWND hwnd = nullptr;
    public:
        ListView(HWND hwnd_mainwin);
        void set_column(int column_index, std::wstring column_name);
};

#endif
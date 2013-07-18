#ifndef FILEDIALOG_H
#define FILEDIALOG_H

#include <string>
#include <iostream>
#include <windows.h>

class FileDialog
{
    public:
        void open_file_dialog(HWND hwnd);
};

#endif
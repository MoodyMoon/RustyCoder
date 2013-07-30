#ifndef FILEDIALOG_H
#define FILEDIALOG_H

#include <vector>

#include <windows.h>

#include "main_event.h"

class FileDialog
{
    private:
        std::vector<std::wstring> file_paths;

        void set_vector_element(const wchar_t fullpath[]);
        void set_vector_element(const wchar_t path[], const wchar_t filename[]);
    public:
        FileDialog(const HWND hwnd);
        std::vector<std::wstring>& get_file_paths(void);
        void print_all_paths(void);
};

#endif

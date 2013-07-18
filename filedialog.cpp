#include "filedialog.h"

void FileDialog::open_file_dialog(HWND hwnd)
{
    wchar_t buffer[70000] = {'\x0000'};

    OPENFILENAME open_file;
    memset(&open_file, 0, sizeof(OPENFILENAME));
    open_file.lStructSize = sizeof(OPENFILENAME);
    open_file.hwndOwner = hwnd;
    open_file.lpstrFile = buffer;
    open_file.nMaxFile = sizeof(buffer);
    open_file.Flags = OFN_ALLOWMULTISELECT | OFN_DONTADDTORECENT | OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_READONLY;

    GetOpenFileName(&open_file);
    /*
    std::cout << sizeof(buffer);
    MessageBox(nullptr, buffer, L"Testing", MB_OK);

    bool nullfirst = false;
    bool nullsecond = false;
    std::wstring abd = L"0";
    for(int index = 0; index <= 100; ++index)
    {
        if(buffer[index] == '\0')
            MessageBox(nullptr, abd.c_str(), L"Testing", MB_OK);
        else
            abd.append(buffer[index]);
    }
    */
}

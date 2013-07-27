#include "main_event.h"

MainEvent::OS MainEvent::main_os_is_supported(void)
{
    OSVERSIONINFOEX osver;
    memset(&osver, 0, sizeof(OSVERSIONINFOEX));
    osver.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

    if(GetVersionEx(reinterpret_cast<LPOSVERSIONINFO>(&osver)))
    {
        if(osver.wProductType == VER_NT_WORKSTATION && osver.dwMajorVersion >= 5 && osver.dwMajorVersion <= 6)
        {
            if(osver.dwMajorVersion == 5 && osver.dwMinorVersion >= 1)
                return WIN_XP;
            else if(osver.dwMajorVersion == 6 && osver.dwMinorVersion <= 2)
                return WIN_VISTA_OR_LATER;
        }
    }
    return OS_NOT_SUPPORTED;
}

void MainEvent::main_on_create(HWND hwnd)
{
    INITCOMMONCONTROLSEX initctrl;
    initctrl.dwICC = ICC_LISTVIEW_CLASSES;
    InitCommonControlsEx(&initctrl);

    NONCLIENTMETRICS ncm;
    ncm.cbSize = sizeof(NONCLIENTMETRICS);
    SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncm, 0);
    HFONT hfont = CreateFontIndirect(&ncm.lfMessageFont);

    HMENU menu, menu_file_add, menu_file_dummy;

    menu = CreateMenu();
    menu_file_add = CreatePopupMenu();
    menu_file_dummy = CreatePopupMenu();

    AppendMenu(menu, MF_STRING | MF_POPUP, reinterpret_cast<unsigned int>(menu_file_add), L"File");
    AppendMenu(menu_file_add, MF_STRING, ID_MENU1_FILE_ADD, L"&Add files");
    AppendMenu(menu_file_add, MF_STRING | MF_POPUP, reinterpret_cast<unsigned int>(menu_file_dummy), L"&Dummy");
    AppendMenu(menu_file_dummy, MF_STRING, ID_MENU1_FILE_DUMMY, L"&Dummy");
    AppendMenu(menu_file_add, MF_STRING, ID_MENU1_FILE_EXIT, L"E&xit");

    SetMenu(hwnd, menu);

    HWND listview1;
    listview1 = CreateWindow(WC_LISTVIEW, L"", WS_BORDER | WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SHOWSELALWAYS, 0, 0, MAIN_CLIENT_WIDTH - 16, 387, hwnd, reinterpret_cast<HMENU>(ID_LISTVIEW1), GetModuleHandle(nullptr), nullptr);
    ListView::set_ex_styles(listview1, LVS_EX_BORDERSELECT | LVS_EX_DOUBLEBUFFER | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
    ListView::set_column(listview1, 0, L"File name", 250);
    ListView::set_column(listview1, 1, L"File size", 70);
    ListView::set_column(listview1, 2, L"File format", 70);
    ListView::set_column(listview1, 3, L"Output format", 70);
    ListView::set_column(listview1, 4, L"File directory", 250);
    ListView::set_column(listview1, 5, L"Output directory", 250);
    ListView::set_column(listview1, 6, L"Profile", 70);

    HWND button1;
    button1 = CreateWindowEx(WS_EX_WINDOWEDGE, L"BUTTON", L"^", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 5, 392, 25, 25, hwnd, reinterpret_cast<HMENU>(ID_BUTTON1), GetModuleHandle(nullptr), nullptr);
    SendMessage(button1, WM_SETFONT, reinterpret_cast<WPARAM>(hfont), MAKELPARAM(FALSE, 0));

    HWND button2;
    button2 = CreateWindowEx(WS_EX_WINDOWEDGE, L"BUTTON", L"^", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 35, 392, 25, 25, hwnd, reinterpret_cast<HMENU>(ID_BUTTON2), GetModuleHandle(nullptr), nullptr);
    SendMessage(button2, WM_SETFONT, reinterpret_cast<WPARAM>(hfont), MAKELPARAM(FALSE, 0));

    HWND button3;
    button3 = CreateWindowEx(WS_EX_WINDOWEDGE, L"BUTTON", L"V", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 65, 392, 25, 25, hwnd, reinterpret_cast<HMENU>(ID_BUTTON3), GetModuleHandle(nullptr), nullptr);
    SendMessage(button3, WM_SETFONT, reinterpret_cast<WPARAM>(hfont), MAKELPARAM(FALSE, 0));

    HWND button4;
    button4 = CreateWindowEx(WS_EX_WINDOWEDGE, L"BUTTON", L"V", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 95, 392, 25, 25, hwnd, reinterpret_cast<HMENU>(ID_BUTTON4), GetModuleHandle(nullptr), nullptr);
    SendMessage(button4, WM_SETFONT, reinterpret_cast<WPARAM>(hfont), MAKELPARAM(FALSE, 0));

    HWND button5;
    button5 = CreateWindowEx(WS_EX_WINDOWEDGE, L"BUTTON", L"D", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, MAIN_CLIENT_WIDTH - 46, 392, 25, 25, hwnd, reinterpret_cast<HMENU>(ID_BUTTON5), GetModuleHandle(nullptr), nullptr);
    SendMessage(button5, WM_SETFONT, reinterpret_cast<WPARAM>(hfont), MAKELPARAM(FALSE, 0));

    HWND button6;
    button6 = CreateWindowEx(WS_EX_WINDOWEDGE, L"BUTTON", L"...", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, MAIN_CLIENT_WIDTH - 46, 423, 25, 22, hwnd, reinterpret_cast<HMENU>(ID_BUTTON6), GetModuleHandle(nullptr), nullptr);
    SendMessage(button6, WM_SETFONT, reinterpret_cast<WPARAM>(hfont), MAKELPARAM(FALSE, 0));

    HWND button7;
    button7 = CreateWindowEx(WS_EX_WINDOWEDGE, L"BUTTON", L"S", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, MAIN_CLIENT_WIDTH - 46, 450, 25, 22, hwnd, reinterpret_cast<HMENU>(ID_BUTTON7), GetModuleHandle(nullptr), nullptr);
    SendMessage(button7, WM_SETFONT, reinterpret_cast<WPARAM>(hfont), MAKELPARAM(FALSE, 0));

    HWND label1;
    label1 = CreateWindow(L"STATIC", L"File Destination", WS_CHILD | WS_VISIBLE | SS_LEFTNOWORDWRAP, 10, 426, 82, 20, hwnd, reinterpret_cast<HMENU>(ID_LABEL1), GetModuleHandle(nullptr), nullptr);
    SendMessage(label1, WM_SETFONT, reinterpret_cast<WPARAM>(hfont), MAKELPARAM(FALSE, 0));

    HWND label2;
    label2 = CreateWindow(L"STATIC", L"Arguments", WS_CHILD | WS_VISIBLE | SS_LEFTNOWORDWRAP, 10, 453, 62, 20, hwnd, reinterpret_cast<HMENU>(ID_LABEL2), GetModuleHandle(nullptr), nullptr);
    SendMessage(label2, WM_SETFONT, reinterpret_cast<WPARAM>(hfont), MAKELPARAM(FALSE, 0));

    HWND textbox1;
    textbox1 = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", nullptr, WS_TABSTOP | WS_VISIBLE | WS_CHILD, 97, 423, 603, 22, hwnd, reinterpret_cast<HMENU>(ID_TEXTBOX1), GetModuleHandle(nullptr), nullptr);
    SendMessage(textbox1, WM_SETFONT, reinterpret_cast<WPARAM>(hfont), MAKELPARAM(FALSE, 0));
    SendMessage(textbox1, EM_SETREADONLY, true, 0);

    HWND textbox2;
    textbox2 = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", nullptr, WS_TABSTOP | WS_VISIBLE | WS_CHILD, 97, 450, 603, 22, hwnd, reinterpret_cast<HMENU>(ID_TEXTBOX2), GetModuleHandle(nullptr), nullptr);
    SendMessage(textbox2, WM_SETFONT, reinterpret_cast<WPARAM>(hfont), MAKELPARAM(FALSE, 0));
}

void MainEvent::main_on_getminmaxinfo(LPARAM lParam)
{
    LPMINMAXINFO min_max_size;
    min_max_size = reinterpret_cast<LPMINMAXINFO>(lParam);
    min_max_size->ptMinTrackSize.x = MainEvent::MAIN_CLIENT_WIDTH;
    min_max_size->ptMinTrackSize.y = MainEvent::MAIN_CLIENT_HEIGHT;
}

void MainEvent::main_on_size_sizing(HWND hwnd)
{
    RECT hwnd_coords;
    GetWindowRect(hwnd, &hwnd_coords);

    HWND listview1;
    listview1 = GetDlgItem(hwnd, ID_LISTVIEW1);
    SetWindowPos(listview1, listview1, 0, 0, hwnd_coords.right - hwnd_coords.left - 16, hwnd_coords.bottom - hwnd_coords.top - 148, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_NOZORDER);

    HWND button1;
    button1 = GetDlgItem(hwnd, ID_BUTTON1);
    SetWindowPos(button1, button1, 5, hwnd_coords.bottom - hwnd_coords.top - 143, 25, 25, SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_NOZORDER);

    HWND button2;
    button2 = GetDlgItem(hwnd, ID_BUTTON2);
    SetWindowPos(button2, button2, 35, hwnd_coords.bottom - hwnd_coords.top - 143, 25, 25, SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_NOZORDER);

    HWND button3;
    button3 = GetDlgItem(hwnd, ID_BUTTON3);
    SetWindowPos(button3, button3, 65, hwnd_coords.bottom - hwnd_coords.top - 143, 25, 25, SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_NOZORDER);

    HWND button4;
    button4 = GetDlgItem(hwnd, ID_BUTTON4);
    SetWindowPos(button4, button4, 95, hwnd_coords.bottom - hwnd_coords.top - 143, 25, 25, SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_NOZORDER);

    HWND button5;
    button5 = GetDlgItem(hwnd, ID_BUTTON5);
    SetWindowPos(button5, button5, hwnd_coords.right - hwnd_coords.left - 46, hwnd_coords.bottom - hwnd_coords.top - 143, 25, 25, SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_NOZORDER);

    HWND button6;
    button6 = GetDlgItem(hwnd, ID_BUTTON6);
    SetWindowPos(button6, button6, hwnd_coords.right - hwnd_coords.left - 46, hwnd_coords.bottom - hwnd_coords.top - 112, 25, 22, SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_NOZORDER);

    HWND button7;
    button7 = GetDlgItem(hwnd, ID_BUTTON7);
    SetWindowPos(button7, button7, hwnd_coords.right - hwnd_coords.left - 46, hwnd_coords.bottom - hwnd_coords.top - 85, 25, 22, SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_NOZORDER);

    HWND label1;
    label1 = GetDlgItem(hwnd, ID_LABEL1);
    SetWindowPos(label1, label1, 10, hwnd_coords.bottom - hwnd_coords.top - 109, 82, 20, SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_NOZORDER);

    HWND label2;
    label2 = GetDlgItem(hwnd, ID_LABEL2);
    SetWindowPos(label2, label2, 10, hwnd_coords.bottom - hwnd_coords.top - 82, 62, 20, SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_NOZORDER);

    HWND textbox1;
    textbox1 = GetDlgItem(hwnd, ID_TEXTBOX1);
    SetWindowPos(textbox1, textbox1, 97, hwnd_coords.bottom - hwnd_coords.top - 112, hwnd_coords.right - hwnd_coords.left - 147, 22, SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_NOZORDER);

    HWND textbox2;
    textbox2 = GetDlgItem(hwnd, ID_TEXTBOX2);
    SetWindowPos(textbox2, textbox2, 97, hwnd_coords.bottom - hwnd_coords.top - 85, hwnd_coords.right - hwnd_coords.left - 147, 22, SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_NOZORDER);
}

void MainEvent::button1_on_click(HWND hwnd)
{
    std::thread thread1(start_stream_redirection, hwnd);
    thread1.detach();
}

void MainEvent::button2_on_click(HWND hwnd)
{
    HWND listview1;
    listview1 = GetDlgItem(hwnd, ID_LISTVIEW1);
    ListView::remove_all_items(listview1);
}

void MainEvent::menu_exit_on_click(HWND hwnd)
{
    SendMessage(hwnd, WM_CLOSE, 0, 0);
}

LRESULT MainEvent::main_on_ctlcolorstatic(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HWND handle, textbox1;
    HDC hdc;
    hdc = reinterpret_cast<HDC>(lParam);
    handle = reinterpret_cast<HWND>(lParam);
    textbox1 = GetDlgItem(hwnd, ID_TEXTBOX1);

    if(handle == textbox1)
    {
        SetBkColor(hdc, RGB(255, 255, 255));
        return reinterpret_cast<LRESULT>(GetStockObject(DC_BRUSH));
    }
    else
        return DefWindowProc(hwnd, message, wParam, lParam);
}

void MainEvent::menu_file_add_on_click(HWND hwnd)
{
    FileDialog filedialog1(hwnd);
    std::vector<std::wstring>& file_paths = filedialog1.get_file_paths();
    int file_paths_count = file_paths.size();
    if(file_paths_count > 0)
    {
        HWND listview1;
        listview1 = GetDlgItem(hwnd, ID_LISTVIEW1);
        std::wstring list_items[4];

        SendMessage(listview1, WM_SETREDRAW, false, 0);

        for(int index = 0; index < file_paths_count; ++index)
        {
            list_items[0] = get_file_name(file_paths[index]);
            list_items[1] = long_long_to_wstr(get_file_size(file_paths[index]));
            list_items[2] = get_file_format(file_paths[index]);
            list_items[3] = get_file_directory(file_paths[index]);
            ListView::set_item(listview1, list_items);
        }

        SendMessage(listview1, WM_SETREDRAW, true, 0);
        SendMessage(listview1, WM_PAINT, 0, 0);
    }
}

void MainEvent::start_stream_redirection(HWND hwnd)
{
    HANDLE standard_output_read;
    HANDLE standard_output_write;

    SECURITY_ATTRIBUTES secure_attribute;

    secure_attribute.nLength = sizeof(SECURITY_ATTRIBUTES);
    secure_attribute.bInheritHandle = true;
    secure_attribute.lpSecurityDescriptor = nullptr;

    if(!CreatePipe(&standard_output_read, &standard_output_write, &secure_attribute, 0))
        show_error_msg();

    if(!SetHandleInformation(standard_output_read, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT))
        show_error_msg();

    if(create_child_process(standard_output_write))
        read_from_pipe(hwnd, standard_output_read);

    if(!CloseHandle(standard_output_read))
        show_error_msg();
}

bool MainEvent::create_child_process(HANDLE _standard_output_write)
{
    PROCESS_INFORMATION process_info;
    STARTUPINFO process_startup_info;
    bool bSuccess;

    memset(&process_info, 0, sizeof(PROCESS_INFORMATION));

    memset(&process_startup_info, 0, sizeof(STARTUPINFO));

    process_startup_info.cb = sizeof(STARTUPINFO);
    process_startup_info.hStdOutput = _standard_output_write;
    process_startup_info.hStdError = _standard_output_write;
    process_startup_info.dwFlags |= STARTF_USESTDHANDLES;

    bSuccess = CreateProcess(L"lame.exe",
                             L" \"C:\\abc.mp3\" \"C:\\bcd.mp3\"",               // command line
                             nullptr,                                           // process security attributes
                             nullptr,                                           // primary thread security attributes
                             true,                                              // handles are inherited
                             BELOW_NORMAL_PRIORITY_CLASS | CREATE_NO_WINDOW,    // creation flags
                             nullptr,                                           // use parent's environment
                             nullptr,                                           // use parent's current directory
                             &process_startup_info,                             // STARTUPINFO pointer
                             &process_info);                                    // receives PROCESS_INFORMATION

    if(!CloseHandle(_standard_output_write))
        show_error_msg();

    // If an error occurs, exit the application.
    if(bSuccess)
    {
        CloseHandle(process_info.hProcess);
        CloseHandle(process_info.hThread);
    }
    else
        show_error_msg();
    return bSuccess;
}

void MainEvent::read_from_pipe(HWND hwnd, HANDLE _standard_output_read)
{
    unsigned long bytes_read = 0;
    char output_buffer[80];
    unsigned long text_length;
    HWND textbox1 = GetDlgItem(hwnd, ID_TEXTBOX1);

    while(ReadFile(_standard_output_read, output_buffer, 79, &bytes_read, nullptr))
    {
        text_length = SendMessage(textbox1, WM_GETTEXTLENGTH, 0, 0);
        textbox1_append_text(textbox1, output_buffer, text_length);
        memset(output_buffer, 0, sizeof(output_buffer));
    }
}

void MainEvent::textbox1_append_text(const HWND textbox, char _output_buffer[], unsigned long _text_length)
{
    SetFocus(textbox);
    SendMessage(textbox, EM_SETSEL, _text_length, _text_length);
    if (!SendMessageA(textbox, EM_REPLACESEL, false, reinterpret_cast<LPARAM>(_output_buffer)))
        MessageBox(nullptr, L"Text cannot be changed!", L"Error", MB_OK);
}

std::wstring MainEvent::get_file_name(const std::wstring& file_path)
{
    size_t index = file_path.find_last_of(L'\\');
    if(index != std::string::npos)
        return file_path.substr(index + 1, file_path.length() - 1);
    else
        return nullptr;
}

long long MainEvent::get_file_size(const std::wstring& file_path)
{
    long long size = -1;
    LARGE_INTEGER temp_size;
    HANDLE file = CreateFile(file_path.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if(file != INVALID_HANDLE_VALUE)
        if(GetFileSizeEx(file, &temp_size))
            size = temp_size.QuadPart;
    CloseHandle(file);
    return size;
}

std::wstring MainEvent::get_file_format(const std::wstring& file_path)
{
    size_t index = file_path.find_last_of(L'.');
    if(index != std::string::npos)
        return file_path.substr(index, file_path.length() - 1);
    else
        return nullptr;
}

std::wstring MainEvent::get_file_directory(const std::wstring& file_path)
{
    size_t index = file_path.find_last_of(L'\\');
    if(index != std::string::npos)
        return file_path.substr(0, index);
    else
        return nullptr;
}

std::wstring MainEvent::long_long_to_wstr(long long number)
{
    std::wstringstream temp;
    temp << number;
    return temp.str();
}

void MainEvent::show_error_msg(void)
{
    MessageBox(nullptr, L"Error", L"Error", MB_OK);
}

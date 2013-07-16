/*
    RustyCoder
    http://sourceforge.net/projects/rustycoder/

    Copyright (C) 2012-2013 Chak Wai Yuan

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Version: Major.Minor.Patch+build.number.date
    Version: 0.2.0+build.7.20130716
*/

#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <sstream>
#include <thread>

#include <stdio.h>

#include "listview.h"

HWND hwnd; //This is the handle for our window
const std::wstring szClassName = L"RustyCoder"; //Make the class name into a global variable

const unsigned int MAIN_CLIENT_WIDTH = 750;
const unsigned int MAIN_CLIENT_HEIGHT = 530;

void button1_on_click(void);
void start_stream_redirection(void);
bool create_child_process(HANDLE standard_output_write);
void read_from_pipe(HANDLE standard_output_read);
void show_error_msg(void);
void textbox1_append_text(HWND textbox, char _output_buffer[], unsigned long _text_length);
std::wstring int_to_wstring(int number);

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName.c_str();
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof(WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
    wincl.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wincl.lpszMenuName = MAKEINTRESOURCE(ID_MENU1);
    wincl.cbClsExtra = 0;                       /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                       /* structure or the window instance */

    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH)COLOR_BACKGROUND + 1;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx(&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx(
        0,                                                              /* Extended possibilites for variation */
        wincl.lpszClassName,                                            /* Classname */
        wincl.lpszClassName,                                            /* Title Text */
        WS_OVERLAPPEDWINDOW,                                            /* default window */
        (GetSystemMetrics(SM_CXSCREEN) - MAIN_CLIENT_WIDTH) / 2,        /* Windows decides the position */
        (GetSystemMetrics(SM_CYSCREEN) - MAIN_CLIENT_HEIGHT) / 2,       /* where the window ends up on the screen */
        MAIN_CLIENT_WIDTH,                                              /* The programs width */
        MAIN_CLIENT_HEIGHT,                                             /* and height in pixels */
        HWND_DESKTOP,                                                   /* The window is a child-window to desktop */
        nullptr,                                                        /* No menu */
        hThisInstance,                                                  /* Program Instance handler */
        nullptr                                                         /* No Window Creation data */
        );

    /* Make the window visible on the screen */
    ShowWindow(hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while(GetMessage(&messages, nullptr, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}

/*  This function is called by the Windows function DispatchMessage()  */
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)                  /* handle the messages */
    {
        case WM_CREATE:
        {
            INITCOMMONCONTROLSEX initctrl;
            initctrl.dwICC = ICC_LISTVIEW_CLASSES;
            InitCommonControlsEx(&initctrl);

            NONCLIENTMETRICS ncm;
            ncm.cbSize = sizeof(NONCLIENTMETRICS);
            SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncm, 0);
            HFONT hfont = CreateFontIndirect(&ncm.lfMessageFont);

            HMENU menu_strip1, menu_strip_sub1;
            menu_strip1 = CreateMenu();

            menu_strip_sub1 = CreatePopupMenu();
            AppendMenu(menu_strip_sub1, MF_STRING, ID_MENU1_FILE_EXIT, L"E&xit");
            AppendMenu(menu_strip1, MF_STRING | MF_POPUP, reinterpret_cast<unsigned int>(menu_strip_sub1), L"&File");

            SetMenu(hwnd, menu_strip1);

            HWND listview1;
            listview1 = CreateWindow(WC_LISTVIEW, L"", WS_BORDER | WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SHOWSELALWAYS, 0, 0, MAIN_CLIENT_WIDTH - 16, 387, hwnd, reinterpret_cast<HMENU>(ID_LISTVIEW1), GetModuleHandle(nullptr), nullptr);
            ListView_SetExtendedListViewStyleEx(listview1, LVS_EX_BORDERSELECT | LVS_EX_DOUBLEBUFFER | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES, LVS_EX_BORDERSELECT | LVS_EX_DOUBLEBUFFER | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
            ListView::set_handle(listview1);    //Must set handle before using member functions
            ListView::set_column(0, L"Filename");
            ListView::set_column(1, L"Size");

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
            button6 = CreateWindowEx(WS_EX_WINDOWEDGE, L"BUTTON", L"...", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, MAIN_CLIENT_WIDTH - 46, 422, 25, 22, hwnd, reinterpret_cast<HMENU>(ID_BUTTON6), GetModuleHandle(nullptr), nullptr);
            SendMessage(button6, WM_SETFONT, reinterpret_cast<WPARAM>(hfont), MAKELPARAM(FALSE, 0));

            HWND button7;
            button7 = CreateWindowEx(WS_EX_WINDOWEDGE, L"BUTTON", L"S", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, MAIN_CLIENT_WIDTH - 46, 445, 25, 22, hwnd, reinterpret_cast<HMENU>(ID_BUTTON7), GetModuleHandle(nullptr), nullptr);
            SendMessage(button7, WM_SETFONT, reinterpret_cast<WPARAM>(hfont), MAKELPARAM(FALSE, 0));

            HWND label1;
            label1 = CreateWindow(L"STATIC", L"File Destination", WS_CHILD | WS_VISIBLE | SS_LEFTNOWORDWRAP, 10, 425, 82, 20, hwnd, reinterpret_cast<HMENU>(ID_LABEL1), GetModuleHandle(nullptr), nullptr);
            SendMessage(label1, WM_SETFONT, reinterpret_cast<WPARAM>(hfont), MAKELPARAM(FALSE, 0));

            HWND label2;
            label2 = CreateWindow(L"STATIC", L"Arguments", WS_CHILD | WS_VISIBLE | SS_LEFTNOWORDWRAP, 10, 448, 62, 20, hwnd, reinterpret_cast<HMENU>(ID_LABEL2), GetModuleHandle(nullptr), nullptr);
            SendMessage(label2, WM_SETFONT, reinterpret_cast<WPARAM>(hfont), MAKELPARAM(FALSE, 0));

            HWND textbox1;
            textbox1 = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", nullptr, WS_TABSTOP | WS_VISIBLE | WS_CHILD, 97, 423, 603, 20, hwnd, reinterpret_cast<HMENU>(ID_TEXTBOX1), GetModuleHandle(nullptr), nullptr);
            SendMessage(textbox1, WM_SETFONT, reinterpret_cast<WPARAM>(hfont), MAKELPARAM(FALSE, 0));
            SendMessage(textbox1, EM_SETREADONLY, true, 0);

            HWND textbox2;
            textbox2 = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", nullptr, WS_TABSTOP | WS_VISIBLE | WS_CHILD, 97, 446, 603, 20, hwnd, reinterpret_cast<HMENU>(ID_TEXTBOX2), GetModuleHandle(nullptr), nullptr);
            SendMessage(textbox2, WM_SETFONT, reinterpret_cast<WPARAM>(hfont), MAKELPARAM(FALSE, 0));
            break;
        }
        case WM_GETMINMAXINFO:
        {
            LPMINMAXINFO min_max_size;
            min_max_size = reinterpret_cast<LPMINMAXINFO>(lParam);
            min_max_size->ptMinTrackSize.x = MAIN_CLIENT_WIDTH;
            min_max_size->ptMinTrackSize.y = MAIN_CLIENT_HEIGHT;
            break;
        }
        case WM_SIZE:
        case WM_SIZING:
        {
            RECT hwnd_coords;
            GetWindowRect(hwnd, &hwnd_coords);

            HWND listview1;
            listview1 = GetDlgItem(hwnd, ID_LISTVIEW1);
            SetWindowPos(listview1, listview1, 0, 0, hwnd_coords.right - hwnd_coords.left - 16, 387, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_NOZORDER);

            HWND button5;
            button5 = GetDlgItem(hwnd, ID_BUTTON5);
            SetWindowPos(button5, button5, hwnd_coords.right - hwnd_coords.left - 46, 392, 25, 25, SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_NOZORDER);

            HWND button6;
            button6 = GetDlgItem(hwnd, ID_BUTTON6);
            SetWindowPos(button6, button6, hwnd_coords.right - hwnd_coords.left - 46, 422, 25, 22, SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_NOZORDER);

            HWND button7;
            button7 = GetDlgItem(hwnd, ID_BUTTON7);
            SetWindowPos(button7, button7, hwnd_coords.right - hwnd_coords.left - 46, 445, 25, 22, SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_NOZORDER);

            HWND textbox1;
            textbox1 = GetDlgItem(hwnd, ID_TEXTBOX1);
            SetWindowPos(textbox1, textbox1, 97, 423, hwnd_coords.right - hwnd_coords.left - 147, 20, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_NOZORDER);

            HWND textbox2;
            textbox2 = GetDlgItem(hwnd, ID_TEXTBOX2);
            SetWindowPos(textbox2, textbox2, 97, 446, hwnd_coords.right - hwnd_coords.left - 147, 20, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_NOZORDER);
            break;
        }
        case WM_COMMAND:
        {
            switch(LOWORD(wParam))
            {
                case ID_BUTTON1:
                    switch(HIWORD(wParam))
                    {
                        case BN_CLICKED:
                        {
                            button1_on_click();
                            break;
                        }
                    }
                    break;
                case ID_MENU1_FILE_EXIT:
                    switch(HIWORD(wParam))
                    {
                        case BN_CLICKED:
                        {
                            SendMessage(hwnd, WM_CLOSE, 0, 0);
                            break;
                        }
                    }
                    break;
            }
            break;
        }
        case WM_CTLCOLORSTATIC:
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
            {
                return DefWindowProc(hwnd, message, wParam, lParam);
            }
            break;
        }
        case WM_DESTROY:
        {
            PostQuitMessage(0);       /* send a WM_QUIT to the message queue */
            break;
        }
        default:                      /* for messages that we don't deal with */
            return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}

void button1_on_click(void)
{
    std::thread thread1(start_stream_redirection);
    thread1.detach();
}

void start_stream_redirection(void)
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
        read_from_pipe(standard_output_read);

    if(!CloseHandle(standard_output_read))
        show_error_msg();
}

bool create_child_process(HANDLE _standard_output_write)
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
                             L" \"C:\\abc.mp3\" \"C:\\bcd.mp3\"",                                    // command line
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

void read_from_pipe(HANDLE _standard_output_read)
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

void textbox1_append_text(HWND textbox, char _output_buffer[], unsigned long _text_length)
{
    SetFocus(textbox);
    SendMessage(textbox, EM_SETSEL, _text_length, _text_length);
    if (!SendMessageA(textbox, EM_REPLACESEL, false, reinterpret_cast<LPARAM>(_output_buffer)))
        MessageBox(nullptr, L"Text cannot be changed!", L"Error", MB_OK);
}

void show_error_msg()
{
    MessageBox(nullptr, L"Error", L"Error", MB_OK);
}

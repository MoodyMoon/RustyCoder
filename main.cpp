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
    Version: 0.2.0+build.6.20130711
*/

#include <iostream>
#include <sstream>
#include <thread>

#include <stdio.h>

#include "listview.h"

HWND hwnd; //This is the handle for our window
const std::wstring szClassName = L"RustyCoder"; //Make the class name into a global variable

const unsigned int MAIN_CLIENT_WIDTH = 800;
const unsigned int MAIN_CLIENT_HEIGHT = 600;

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
            HWND textbox1;
            HWND button1;
            HMENU menu_strip1, menu_strip_sub1;
            ListView listview1(hwnd);
            listview1.set_column(0, L"Filename");
            menu_strip1 = CreateMenu();
            menu_strip_sub1 = CreatePopupMenu();
            AppendMenu(menu_strip_sub1, MF_STRING, ID_MENU1_FILE_EXIT, L"E&xit");
            AppendMenu(menu_strip1, MF_STRING | MF_POPUP, reinterpret_cast<unsigned int>(menu_strip_sub1), L"&File");
            SetMenu(hwnd, menu_strip1);
            ncm.cbSize = sizeof(NONCLIENTMETRICS);
            SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncm, 0);
            HFONT hfont = CreateFontIndirect(&ncm.lfMessageFont);
            textbox1 = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", nullptr, WS_TABSTOP | WS_VSCROLL | WS_VISIBLE | WS_CHILD | ES_AUTOVSCROLL | ES_MULTILINE, 0, 400, 700, 300, hwnd, (HMENU)ID_TEXTBOX1, GetModuleHandle(nullptr), nullptr);
            SendMessage(textbox1, WM_SETFONT, (WPARAM)hfont, MAKELPARAM(FALSE,0));
            button1 = CreateWindowEx(WS_EX_WINDOWEDGE, L"BUTTON", L"Start", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 701, 501, 75, 30, hwnd, (HMENU)ID_BUTTON1, GetModuleHandle(nullptr), nullptr);
            SendMessage(button1, WM_SETFONT, (WPARAM)hfont, MAKELPARAM(FALSE,0));
            break;
        }
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case ID_BUTTON1:
                    switch(HIWORD(wParam))
                    {
                        case BN_CLICKED:
                            button1_on_click();
                            break;
                    }
                    break;
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);       /* send a WM_QUIT to the message queue */
            break;
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

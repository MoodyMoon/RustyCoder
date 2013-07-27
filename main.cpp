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
    Version: 0.3.0+build.9.20130727
*/

#include "main_event.h"

const std::wstring szClassName = L"RustyCoder (Experimental)";
MainEvent::OS MainEvent::supported_os = MainEvent::OS::OS_NOT_SUPPORTED;

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{
    HWND hwnd;               //This is the handle for our window
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    MainEvent::supported_os = MainEvent::main_os_is_supported();

    if(MainEvent::supported_os)
    {
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
        wincl.lpszMenuName = nullptr;
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
            (GetSystemMetrics(SM_CXSCREEN) - MainEvent::MAIN_CLIENT_WIDTH) / 2,        /* Windows decides the position */
            (GetSystemMetrics(SM_CYSCREEN) - MainEvent::MAIN_CLIENT_HEIGHT) / 2,       /* where the window ends up on the screen */
            MainEvent::MAIN_CLIENT_WIDTH,                                              /* The programs width */
            MainEvent::MAIN_CLIENT_HEIGHT,                                             /* and height in pixels */
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
    }
    else
    {
        MessageBox(nullptr, L"OS not supported.", L"Error", MB_OK);
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
            MainEvent::main_on_create(hwnd);
            break;
        }
        case WM_GETMINMAXINFO:
        {
            MainEvent::main_on_getminmaxinfo(lParam);
            break;
        }
        case WM_SIZE:
        case WM_SIZING:
        {
            MainEvent::main_on_size_sizing(hwnd);
            break;
        }
        case WM_COMMAND:
        {
            switch(LOWORD(wParam))
            {
                case ID_BUTTON1:
                {
                    switch(HIWORD(wParam))
                    {
                        case BN_CLICKED:
                        {
                            MainEvent::button1_on_click(hwnd);
                            break;
                        }
                    }
                    break;
                }
                case ID_BUTTON2:
                {
                    switch(HIWORD(wParam))
                    {
                        case BN_CLICKED:
                        {
                            MainEvent::button2_on_click(hwnd);
                            break;
                        }
                    }
                    break;
                }
                case ID_MENU1_FILE_EXIT:
                {
                    switch(HIWORD(wParam))
                    {
                        case BN_CLICKED:
                        {
                            MainEvent::menu_exit_on_click(hwnd);
                            break;
                        }
                    }
                    break;
                }
                case ID_MENU1_FILE_ADD:
                {
                    switch(HIWORD(wParam))
                    {
                        case BN_CLICKED:
                        {
                            MainEvent::menu_file_add_on_click(hwnd);
                            break;
                        }
                    }
                    break;
                }
            }
            break;
        }
        case WM_CTLCOLORSTATIC:
        {
            return MainEvent::main_on_ctlcolorstatic(hwnd, message, wParam, lParam);
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

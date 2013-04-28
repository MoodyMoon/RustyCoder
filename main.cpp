//Author: Chak Wai Yuan
//RustyCoder Version: Major.Minor.Patch+build.number.date
//RustyCoder Version: 0.1.0+build.3.20130422
//http://semver.org/

#include "res/resource.h"
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <sstream>

HWND hwnd; //This is the handle for our window
const std::wstring szClassName = L"Song Randomizer"; //Make the class name into a global variable

const unsigned int MAIN_CLIENT_AREA_WIDTH = 900;
const unsigned int MAIN_CLIENT_AREA_HEIGHT = 600;

void StartProc(void);
bool CreateChildProcess(HANDLE _stdOut_Rd, HANDLE _stdOut_Wr);
void ReadFromPipe(HANDLE _stdOut_Rd);
void showErrorMsg(void);
std::wstring convertInt(int number);

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
    wincl.lpszMenuName = nullptr;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH)COLOR_BACKGROUND + 1;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx(&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx(
        0,                   /* Extended possibilites for variation */
        wincl.lpszClassName,         /* Classname */
        wincl.lpszClassName,       /* Title Text */
        WS_OVERLAPPEDWINDOW, /* default window */
        (GetSystemMetrics(SM_CXSCREEN) - MAIN_CLIENT_AREA_WIDTH) / 2,       /* Windows decides the position */
        (GetSystemMetrics(SM_CYSCREEN) - MAIN_CLIENT_AREA_HEIGHT) / 2,       /* where the window ends up on the screen */
        MAIN_CLIENT_AREA_WIDTH,                 /* The programs width */
        MAIN_CLIENT_AREA_HEIGHT,                 /* and height in pixels */
        HWND_DESKTOP,        /* The window is a child-window to desktop */
        NULL,                /* No menu */
        hThisInstance,       /* Program Instance handler */
        nullptr                 /* No Window Creation data */
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
            NONCLIENTMETRICS ncm;
            ncm.cbSize = sizeof(NONCLIENTMETRICS);
            SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncm, 0);
            HWND textbox1;
            HWND button1;
            HFONT hfont = CreateFontIndirect(&ncm.lfMessageFont);
            textbox1 = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", nullptr, WS_TABSTOP | WS_VSCROLL | WS_VISIBLE | WS_CHILD | ES_AUTOVSCROLL | ES_MULTILINE, 0, 0, 885, 500, hwnd, (HMENU)IDC_TEXTBOX1, GetModuleHandle(nullptr), nullptr);
            SendMessage(textbox1, WM_SETFONT, (WPARAM)hfont, MAKELPARAM(FALSE,0));
            button1 = CreateWindowEx(WS_EX_WINDOWEDGE, L"BUTTON", L"Start", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 0, 501, 75, 30, hwnd, (HMENU)IDC_BUTTON1, GetModuleHandle(nullptr), nullptr);
            SendMessage(button1, WM_SETFONT, (WPARAM)hfont, MAKELPARAM(FALSE,0));
            break;
        }
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case IDC_BUTTON1:
                    switch(HIWORD(wParam))
                    {
                        case BN_CLICKED:
                            StartProc();
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

void StartProc(void)
{
    HANDLE stdOut_Rd;
    HANDLE stdOut_Wr;
    SECURITY_ATTRIBUTES saAttr;
    saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
    saAttr.bInheritHandle = true;
    saAttr.lpSecurityDescriptor = nullptr;

    if(!CreatePipe(&stdOut_Rd, &stdOut_Wr, &saAttr, 0))
        showErrorMsg();

    if(!SetHandleInformation(stdOut_Rd, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT))
        showErrorMsg();

    if(CreateChildProcess(stdOut_Rd, stdOut_Wr))
        ReadFromPipe(stdOut_Rd);

    if(!CloseHandle(stdOut_Rd))
        showErrorMsg();
}

bool CreateChildProcess(HANDLE _stdOut_Rd, HANDLE _stdOut_Wr)
{
    PROCESS_INFORMATION piProcInfo;
    STARTUPINFO siStartInfo;
    bool bSuccess;

    memset(&piProcInfo, 0, sizeof(PROCESS_INFORMATION));

    memset(&siStartInfo, 0, sizeof(STARTUPINFO));

    siStartInfo.cb = sizeof(STARTUPINFO);
    siStartInfo.hStdOutput = _stdOut_Wr;
    siStartInfo.dwFlags |= STARTF_USESTDHANDLES;

    bSuccess = CreateProcess(L"lame.exe",
                             L" --longhelp", // command line
                             nullptr, // process security attributes
                             nullptr, // primary thread security attributes
                             true, // handles are inherited
                             BELOW_NORMAL_PRIORITY_CLASS | CREATE_NO_WINDOW, // creation flags
                             nullptr, // use parent's environment
                             nullptr, // use parent's current directory
                             &siStartInfo, // STARTUPINFO pointer
                             &piProcInfo); // receives PROCESS_INFORMATION

    if(!CloseHandle(_stdOut_Wr))
        showErrorMsg();

    // If an error occurs, exit the application.
    if(bSuccess)
    {
        CloseHandle(piProcInfo.hProcess);
        CloseHandle(piProcInfo.hThread);
    }
    else
        showErrorMsg();
    return bSuccess;
}

void ReadFromPipe(HANDLE _stdOut_Rd)
{
    unsigned long dwRead = 0;
    char chBuf[80];
    int ndx;
    HWND textbox1 = GetDlgItem(hwnd, IDC_TEXTBOX1);
    while(ReadFile(_stdOut_Rd, chBuf, 79, &dwRead, nullptr))
    {
        ndx = GetWindowTextLength(textbox1);
        SetFocus(textbox1);
        SendMessage(textbox1, EM_SETSEL, ndx, ndx);
        if (!SendMessageA(textbox1, EM_REPLACESEL, false, reinterpret_cast<LPARAM>(chBuf)))
            MessageBox(nullptr, L"Text cannot be changed!", L"Error", MB_OK);
        memset(chBuf, 0, sizeof(chBuf));
    }
}

void showErrorMsg()
{
    MessageBox(nullptr, L"Error", L"Error", MB_OK);
}

std::wstring convertInt(int number)
{
    std::wstringstream ss;    //create a stringstream
    ss << number;        //add number to the stream
    return ss.str();     //return a string with the contents of the stream
}

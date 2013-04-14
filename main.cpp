//Author: Chak Wai Yuan
//RustyCoder Version: Major.Minor.Patch+build.number.date
//RustyCoder Version: 0.1.0+build.1.20130413
#include "res/resource.h"
#include <windows.h>
#include <iostream>
#include <sstream>

using namespace std;
/*  Make the class name into a global variable  */
const wstring szClassName = L"Song Randomizer";
const unsigned int MAIN_WIDTH = 900;
const unsigned int MAIN_HEIGHT = 600;
HANDLE g_hChildStd_IN_Rd = NULL;
HANDLE g_hChildStd_IN_Wr = NULL;
HANDLE g_hChildStd_OUT_Rd = NULL;
HANDLE g_hChildStd_OUT_Wr = NULL;
HWND textbox1;
HWND button1;
void StartProc(void);
void CreateChildProcess(void);
void ReadFromPipe(void);
std::wstring convertInt(int number);

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
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
        (static_cast<unsigned int>(GetSystemMetrics(SM_CXSCREEN)) - MAIN_WIDTH) / 2,       /* Windows decides the position */
        (static_cast<unsigned int>(GetSystemMetrics(SM_CYSCREEN)) - MAIN_HEIGHT) / 2,       /* where the window ends up on the screen */
        MAIN_WIDTH,                 /* The programs width */
        MAIN_HEIGHT,                 /* and height in pixels */
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
            // GetDlgItem to get handle of control

            NONCLIENTMETRICS ncm;
            ncm.cbSize = sizeof(NONCLIENTMETRICS);
            SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncm, 0);
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
    SECURITY_ATTRIBUTES saAttr;
    saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
    saAttr.bInheritHandle = TRUE;
    saAttr.lpSecurityDescriptor = NULL;
   if ( ! CreatePipe(&g_hChildStd_OUT_Rd, &g_hChildStd_OUT_Wr, &saAttr, 0) )
      MessageBox(NULL, L"Error", L"Error", MB_OK);

// Ensure the read handle to the pipe for STDOUT is not inherited.

   if ( ! SetHandleInformation(g_hChildStd_OUT_Rd, HANDLE_FLAG_INHERIT, 0) )
      MessageBox(NULL, L"Error", L"Error", MB_OK);

// Create a pipe for the child process's STDIN.

   if (! CreatePipe(&g_hChildStd_IN_Rd, &g_hChildStd_IN_Wr, &saAttr, 0))
      MessageBox(NULL, L"Error", L"Error", MB_OK);

// Ensure the write handle to the pipe for STDIN is not inherited.

   if ( ! SetHandleInformation(g_hChildStd_IN_Wr, HANDLE_FLAG_INHERIT, 0) )
      MessageBox(NULL, L"Error", L"Error", MB_OK);
    CreateChildProcess();
    CloseHandle(g_hChildStd_OUT_Wr);
    ReadFromPipe();
}

// Create a child process that uses the previously created pipes for STDIN and STDOUT.
void CreateChildProcess()
{
   PROCESS_INFORMATION piProcInfo;
   STARTUPINFO siStartInfo;
   BOOL bSuccess = FALSE;

// Set up members of the PROCESS_INFORMATION structure.

   ZeroMemory( &piProcInfo, sizeof(PROCESS_INFORMATION) );

// Set up members of the STARTUPINFO structure.
// This structure specifies the STDIN and STDOUT handles for redirection.

   ZeroMemory( &siStartInfo, sizeof(STARTUPINFO));
   siStartInfo.cb = sizeof(STARTUPINFO);
   siStartInfo.hStdError = g_hChildStd_OUT_Wr;
   siStartInfo.hStdOutput = g_hChildStd_OUT_Wr;
   siStartInfo.hStdInput = g_hChildStd_IN_Rd;
   siStartInfo.dwFlags |= STARTF_USESTDHANDLES;

// Create the child process.

   bSuccess = CreateProcess(L"lame.exe",
      L" \"--longhelp\"",     // command line
      NULL,          // process security attributes
      NULL,          // primary thread security attributes
      TRUE,          // handles are inherited
      0,             // creation flags
      NULL,          // use parent's environment
      NULL,          // use parent's current directory
      &siStartInfo,  // STARTUPINFO pointer
      &piProcInfo);  // receives PROCESS_INFORMATION

   // If an error occurs, exit the application.
   if(!bSuccess)
      MessageBox(NULL, convertInt(bSuccess).c_str(), L"Error", MB_OK);
   else
   {
      // Close handles to the child process and its primary thread.
      // Some applications might keep these handles to monitor the status
      // of the child process, for example.

      CloseHandle(piProcInfo.hProcess);
      CloseHandle(piProcInfo.hThread);
   }
}

void ReadFromPipe(void)
{
    // Read output from the child process's pipe for STDOUT
    // and write to the parent process's pipe for STDOUT.
    // Stop when there is no more data.
    DWORD dwRead;
    CHAR chBuf[80];
    BOOL bSuccess = FALSE;
    while(ReadFile(g_hChildStd_OUT_Rd, chBuf, 79, &dwRead, NULL))
    {
        int ndx = GetWindowTextLength (textbox1);
        SetFocus (textbox1);
        SendMessage (textbox1, EM_SETSEL, (WPARAM)ndx, (LPARAM)ndx);
        if (!SendMessageA(textbox1, EM_REPLACESEL, 0, reinterpret_cast<LPARAM>(chBuf)))
            MessageBox(NULL, L"Text cannot be changed!", L"Error", MB_OK);
        for(unsigned int index = 0; index < 80; index++)
            chBuf[index] = 0;
    }
}

std::wstring convertInt(int number)
{
   wstringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

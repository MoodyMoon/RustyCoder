/*
RustyCoder

Copyright (C) 2012-2014 Chak Wai Yuan

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
*/

#include "stdafx.h"
#include "window.h"

Window::Window(HINSTANCE hInstance, EventHandlerInterface *event_handler, const wchar_t * const lpClassName, const wchar_t * const lpWindowName, int icon_id, int x, int y, int nWidth, int nHeight, int nCmdShow, unsigned long dwExStyle, unsigned long dwStyle, bool set_cursor)
{
    //Create main window
    this->hInstance = hInstance;
    this->lpClassName = lpClassName;

    Window2(icon_id, set_cursor);

    hWnd = CreateWindowEx(dwExStyle, lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, HWND_DESKTOP, nullptr, hInstance, event_handler);
    assert(hWnd != nullptr);

    ShowWindow(hWnd, nCmdShow);
}

Window::Window(HINSTANCE hInstance, EventHandlerInterface *event_handler, const wchar_t * const lpClassName, const wchar_t * const lpWindowName, HWND hWndParent, int hMenu, int icon_id, int x, int y, int nWidth, int nHeight, unsigned long dwExStyle, unsigned long dwStyle, bool set_cursor)
{
    //Create panel
    this->hInstance = hInstance;
    this->lpClassName = lpClassName;

    Window2(icon_id, set_cursor);

    hWnd = CreateWindowEx(dwExStyle, lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, reinterpret_cast<HMENU>(hMenu), hInstance, event_handler);
    assert(hWnd != nullptr);
}

Window::Window(HINSTANCE hInstance, const wchar_t * const lpClassName, const wchar_t * const lpWindowName, HWND hWndParent, int hMenu, int x, int y, int nWidth, int nHeight, unsigned long dwExStyle, unsigned long dwStyle, bool set_default_font)
{
    //Create control
    this->hInstance = hInstance;
    this->lpClassName = lpClassName;

    hWnd = CreateWindowEx(dwExStyle, lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, reinterpret_cast<HMENU>(hMenu), hInstance, nullptr);
    assert(hWnd != nullptr);

    if(set_default_font)
        SetFont(GetDefaultFont());
}

void Window::Window2(int icon_id, bool set_cursor)
{
    WNDCLASSEX wincl;

    wincl.hInstance = hInstance;
    wincl.lpszClassName = lpClassName;
    wincl.lpfnWndProc = GlobalWindowProcedure;
    wincl.style = CS_DBLCLKS;
    wincl.cbSize = sizeof(WNDCLASSEX);

    if(icon_id != -1)
    {
        wincl.hIcon = reinterpret_cast<HICON>(LoadImage(hInstance, MAKEINTRESOURCE(icon_id), IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR | LR_SHARED));
        assert(wincl.hIcon != nullptr);
        wincl.hIconSm = wincl.hIcon;
    }
    else
    {
        wincl.hIcon = nullptr;
        wincl.hIconSm = nullptr;
    }

    wincl.hCursor = nullptr;

    if(set_cursor)
    {
        wincl.hCursor = reinterpret_cast<HCURSOR>(LoadImage(nullptr, MAKEINTRESOURCE(OCR_NORMAL), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR | LR_SHARED));
        assert(wincl.hCursor != nullptr);
    }
    
    wincl.lpszMenuName = nullptr;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;

    wincl.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_BTNFACE + 1);

    METHOD_ASSERT(RegisterClassEx(&wincl), !=, 0);
}

HFONT Window::GetDefaultFont(void)
{
    static HFONT hFont = nullptr;

    if(hFont == nullptr)
    {
        NONCLIENTMETRICS pvParam;
        pvParam.cbSize = sizeof(NONCLIENTMETRICS);

        METHOD_ASSERT(SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &pvParam, 0), != , 0);

        hFont = CreateFontIndirect(&pvParam.lfMessageFont);
        assert(hFont != nullptr);
    }

    return hFont;
}

void Window::SetFont(HFONT hFont, BOOL redraw)
{
    SendMessage(hWnd, WM_SETFONT, reinterpret_cast<WPARAM>(hFont), MAKELPARAM(redraw, 0));
}

void Window::GetWindowRectangle(RECT &rectangle) const
{
    HWND parent = GetAncestor(hWnd, GA_PARENT);

    METHOD_ASSERT(GetWindowRect(hWnd, &rectangle), != , FALSE);

    MapWindowPoints(HWND_DESKTOP, parent, reinterpret_cast<POINT *>(&rectangle), 2);
}

void Window::GetClientRectangle(RECT &rectangle) const
{
    METHOD_ASSERT(GetClientRect(hWnd, &rectangle), != , FALSE);
}

long Window::GetWindowLeft(void) const
{
    RECT rectangle;
    GetWindowRectangle(rectangle);
    return rectangle.left;
}

long Window::GetWindowTop(void) const
{
    RECT rectangle;
    GetWindowRectangle(rectangle);
    return rectangle.top;
}

long Window::GetWindowRight(void) const
{
    RECT rectangle;
    GetWindowRectangle(rectangle);
    return rectangle.right - 1l;
}

long Window::GetWindowBottom(void) const
{
    RECT rectangle;
    GetWindowRectangle(rectangle);
    return rectangle.bottom - 1l;
}

long Window::GetWindowWidth(void) const
{
    RECT rectangle;
    METHOD_ASSERT(GetWindowRect(hWnd, &rectangle), != , FALSE);
    return rectangle.right - rectangle.left;
}

long Window::GetWindowHeight(void) const
{
    RECT rectangle;
    METHOD_ASSERT(GetWindowRect(hWnd, &rectangle), != , FALSE);
    return rectangle.bottom - rectangle.top;
}

long Window::GetClientLeft(void) const
{
    RECT rectangle;
    METHOD_ASSERT(GetClientRect(hWnd, &rectangle), != , FALSE);
    return rectangle.left;
}

long Window::GetClientTop(void) const
{
    RECT rectangle;
    METHOD_ASSERT(GetClientRect(hWnd, &rectangle), != , FALSE);
    return rectangle.top;
}

long Window::GetClientRight(void) const
{
    RECT rectangle;
    METHOD_ASSERT(GetClientRect(hWnd, &rectangle), != , FALSE);
    return rectangle.right - 1l;
}

long Window::GetClientBottom(void) const
{
    RECT rectangle;
    METHOD_ASSERT(GetClientRect(hWnd, &rectangle), != , FALSE);
    return rectangle.bottom - 1l;
}

long Window::GetClientWidth(void) const
{
    RECT rectangle;
    METHOD_ASSERT(GetClientRect(hWnd, &rectangle), != , FALSE);
    return rectangle.right - rectangle.left;
}

long Window::GetClientHeight(void) const
{
    RECT rectangle;
    METHOD_ASSERT(GetClientRect(hWnd, &rectangle), != , FALSE);
    return rectangle.bottom - rectangle.top;
}

void Window::MoveTo(int x, int y, bool bRepaint)
{
    RECT rectangle;
    GetWindowRectangle(rectangle);
    METHOD_ASSERT(MoveWindow(hWnd, x, y, rectangle.right - rectangle.left, rectangle.bottom - rectangle.top, bRepaint ? TRUE : FALSE), !=, 0);
}

void Window::ResizeTo(int nWidth, int nHeight, bool bRepaint)
{
    RECT rectangle;
    GetWindowRectangle(rectangle);
    METHOD_ASSERT(MoveWindow(hWnd, rectangle.left, rectangle.top, nWidth, nHeight, bRepaint ? TRUE : FALSE), !=, 0);
}

void Window::MoveAndResizeTo(int x, int y, int nWidth, int nHeight, bool bRepaint)
{
    METHOD_ASSERT(MoveWindow(hWnd, x, y, nWidth, nHeight, bRepaint ? TRUE : FALSE), !=, 0);
}

HWND Window::GetHandle(void)
{
    return hWnd;
}

void Window::GetWindowRectangle(HWND hWnd, RECT &rectangle)
{
    HWND parent = GetAncestor(hWnd, GA_PARENT);

    METHOD_ASSERT(GetWindowRect(hWnd, &rectangle), != , FALSE);

    MapWindowPoints(HWND_DESKTOP, parent, reinterpret_cast<POINT *>(&rectangle), 2);
}

void Window::GetClientRectangle(HWND hWnd, RECT &rectangle)
{
    METHOD_ASSERT(GetClientRect(hWnd, &rectangle), != , FALSE);
}

long Window::GetWindowLeft(HWND hWnd)
{
    RECT rectangle;
    GetWindowRectangle(hWnd, rectangle);
    return rectangle.left;
}

long Window::GetWindowTop(HWND hWnd)
{
    RECT rectangle;
    GetWindowRectangle(hWnd, rectangle);
    return rectangle.top;
}

long Window::GetWindowRight(HWND hWnd)
{
    RECT rectangle;
    GetWindowRectangle(hWnd, rectangle);
    return rectangle.right - 1l;
}

long Window::GetWindowBottom(HWND hWnd)
{
    RECT rectangle;
    GetWindowRectangle(hWnd, rectangle);
    return rectangle.bottom - 1l;
}

long Window::GetWindowWidth(HWND hWnd)
{
    RECT rectangle;
    METHOD_ASSERT(GetWindowRect(hWnd, &rectangle), != , FALSE);
    return rectangle.right - rectangle.left;
}

long Window::GetWindowHeight(HWND hWnd)
{
    RECT rectangle;
    METHOD_ASSERT(GetWindowRect(hWnd, &rectangle), != , FALSE);
    return rectangle.bottom - rectangle.top;
}

long Window::GetClientLeft(HWND hWnd)
{
    RECT rectangle;
    METHOD_ASSERT(GetClientRect(hWnd, &rectangle), != , FALSE);
    return rectangle.left;
}

long Window::GetClientTop(HWND hWnd)
{
    RECT rectangle;
    METHOD_ASSERT(GetClientRect(hWnd, &rectangle), != , FALSE);
    return rectangle.top;
}

long Window::GetClientRight(HWND hWnd)
{
    RECT rectangle;
    METHOD_ASSERT(GetClientRect(hWnd, &rectangle), != , FALSE);
    return rectangle.right - 1l;
}

long Window::GetClientBottom(HWND hWnd)
{
    RECT rectangle;
    METHOD_ASSERT(GetClientRect(hWnd, &rectangle), != , FALSE);
    return rectangle.bottom - 1l;
}

long Window::GetClientWidth(HWND hWnd)
{
    RECT rectangle;
    METHOD_ASSERT(GetClientRect(hWnd, &rectangle), != , FALSE);
    return rectangle.right - rectangle.left;
}

long Window::GetClientHeight(HWND hWnd)
{
    RECT rectangle;
    METHOD_ASSERT(GetClientRect(hWnd, &rectangle), != , FALSE);
    return rectangle.bottom - rectangle.top;
}

void Window::MoveTo(HWND hWnd, int x, int y, bool bRepaint)
{
    RECT rectangle;
    GetWindowRectangle(hWnd, rectangle);
    METHOD_ASSERT(MoveWindow(hWnd, x, y, rectangle.right - rectangle.left, rectangle.bottom - rectangle.top, bRepaint ? TRUE : FALSE), !=, 0);
}

void Window::ResizeTo(HWND hWnd, int nWidth, int nHeight, bool bRepaint)
{
    RECT rectangle;
    GetWindowRectangle(hWnd, rectangle);
    METHOD_ASSERT(MoveWindow(hWnd, rectangle.left, rectangle.top, nWidth, nHeight, bRepaint ? TRUE : FALSE), !=, 0);
}

void Window::MoveAndResizeTo(HWND hWnd, int x, int y, int nWidth, int nHeight, bool bRepaint)
{
    METHOD_ASSERT(MoveWindow(hWnd, x, y, nWidth, nHeight, bRepaint ? TRUE : FALSE), !=, 0);
}

Window::~Window(void)
{
    if(IsWindow(hWnd))
        METHOD_ASSERT(DestroyWindow(hWnd), == , TRUE);
}
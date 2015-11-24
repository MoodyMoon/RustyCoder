/*
RustyCoder

Copyright (C) 2012-2015 Chak Wai Yuan

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

rusty::controls::Window::Window(HINSTANCE hInstance, EventHandlerInterface *event_handler, const wchar_t * const lpClassName, const wchar_t * const lpWindowName, HWND hWndParent, unsigned long dwExStyle, unsigned long dwStyle, int nCmdShow, int icon_id, int x, int y, int nWidth, int nHeight, bool set_default_cursor) : hInstance(hInstance), lpClassName(lpClassName)
{
    //Create main windows or child windows
    Window2(icon_id, set_default_cursor);

    hWnd = CreateWindowEx(dwExStyle, lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, nullptr, hInstance, event_handler);
    assert(hWnd != nullptr);

    if(nCmdShow != -1)
        ShowWindow(hWnd, nCmdShow);
}

rusty::controls::Window::Window(HINSTANCE hInstance, EventHandlerInterface *event_handler, const wchar_t * const lpClassName, const wchar_t * const lpWindowName, HWND hWndParent, unsigned long dwExStyle, unsigned long dwStyle, uintptr_t hMenu, int icon_id, int x, int y, int nWidth, int nHeight, bool set_default_cursor) : hInstance(hInstance), lpClassName(lpClassName)
{
    //Create panels
    Window2(icon_id, set_default_cursor);

    hWnd = CreateWindowEx(dwExStyle, lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, reinterpret_cast<HMENU>(hMenu), hInstance, event_handler);
    assert(hWnd != nullptr);
}

rusty::controls::Window::Window(HINSTANCE hInstance, const wchar_t * const lpClassName, const wchar_t * const lpWindowName, HWND hWndParent, unsigned long dwExStyle, unsigned long dwStyle, uintptr_t hMenu, int x, int y, int nWidth, int nHeight, bool set_default_font) : hInstance(hInstance), lpClassName(lpClassName)
{
    //Create controls
    hWnd = CreateWindowEx(dwExStyle, lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, reinterpret_cast<HMENU>(hMenu), hInstance, nullptr);
    assert(hWnd != nullptr);

    if(set_default_font)
        SetFont(GetDefaultFont());
}

void rusty::controls::Window::Window2(int icon_id, bool set_default_cursor)
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

    if(set_default_cursor)
    {
        wincl.hCursor = reinterpret_cast<HCURSOR>(LoadImage(nullptr, MAKEINTRESOURCE(OCR_NORMAL), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR | LR_SHARED));
        assert(wincl.hCursor != nullptr);
    }

    wincl.lpszMenuName = nullptr;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;

    wincl.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_BTNFACE + 1);

    ASSERT_METHOD(RegisterClassEx(&wincl), != , 0);
    has_registered_class = true;
}

HFONT rusty::controls::Window::GetDefaultFont(void)
{
    static HFONT hFont = nullptr;

    if(hFont == nullptr)
    {
        NONCLIENTMETRICS pvParam;
        pvParam.cbSize = sizeof(NONCLIENTMETRICS);

        ASSERT_METHOD(SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &pvParam, 0), != , 0);

        hFont = CreateFontIndirect(&pvParam.lfMessageFont);
        assert(hFont != nullptr);
    }

    return hFont;
}

void rusty::controls::Window::SetFont(HFONT hFont, BOOL redraw)
{
    SendMessage(hWnd, WM_SETFONT, reinterpret_cast<WPARAM>(hFont), MAKELPARAM(redraw, 0));
}

void rusty::controls::Window::GetWindowRectangle(RECT &rectangle) const
{
    HWND parent = GetAncestor(hWnd, GA_PARENT);

    ASSERT_METHOD(GetWindowRect(hWnd, &rectangle), != , FALSE);

    MapWindowPoints(HWND_DESKTOP, parent, reinterpret_cast<POINT *>(&rectangle), 2);
}

void rusty::controls::Window::GetClientRectangle(RECT &rectangle) const
{
    ASSERT_METHOD(GetClientRect(hWnd, &rectangle), != , FALSE);
}

long rusty::controls::Window::GetWindowLeft(void) const
{
    RECT rectangle;
    GetWindowRectangle(rectangle);
    return rectangle.left;
}

long rusty::controls::Window::GetWindowTop(void) const
{
    RECT rectangle;
    GetWindowRectangle(rectangle);
    return rectangle.top;
}

long rusty::controls::Window::GetWindowRight(void) const
{
    RECT rectangle;
    GetWindowRectangle(rectangle);
    return rectangle.right - 1l;
}

long rusty::controls::Window::GetWindowBottom(void) const
{
    RECT rectangle;
    GetWindowRectangle(rectangle);
    return rectangle.bottom - 1l;
}

unsigned long rusty::controls::Window::GetWindowWidth(void) const
{
    RECT rectangle;
    ASSERT_METHOD(GetWindowRect(hWnd, &rectangle), != , FALSE);
    return rectangle.right - rectangle.left;
}

unsigned long rusty::controls::Window::GetWindowHeight(void) const
{
    RECT rectangle;
    ASSERT_METHOD(GetWindowRect(hWnd, &rectangle), != , FALSE);
    return rectangle.bottom - rectangle.top;
}

long rusty::controls::Window::GetClientLeft(void) const
{
    RECT rectangle;
    ASSERT_METHOD(GetClientRect(hWnd, &rectangle), != , FALSE);
    return rectangle.left;
}

long rusty::controls::Window::GetClientTop(void) const
{
    RECT rectangle;
    ASSERT_METHOD(GetClientRect(hWnd, &rectangle), != , FALSE);
    return rectangle.top;
}

long rusty::controls::Window::GetClientRight(void) const
{
    RECT rectangle;
    ASSERT_METHOD(GetClientRect(hWnd, &rectangle), != , FALSE);
    return rectangle.right - 1l;
}

long rusty::controls::Window::GetClientBottom(void) const
{
    RECT rectangle;
    ASSERT_METHOD(GetClientRect(hWnd, &rectangle), != , FALSE);
    return rectangle.bottom - 1l;
}

unsigned long rusty::controls::Window::GetClientWidth(void) const
{
    RECT rectangle;
    ASSERT_METHOD(GetClientRect(hWnd, &rectangle), != , FALSE);
    return rectangle.right - rectangle.left;
}

unsigned long rusty::controls::Window::GetClientHeight(void) const
{
    RECT rectangle;
    ASSERT_METHOD(GetClientRect(hWnd, &rectangle), != , FALSE);
    return rectangle.bottom - rectangle.top;
}

void rusty::controls::Window::MoveTo(int x, int y, bool bRepaint)
{
    RECT rectangle;
    GetWindowRectangle(rectangle);
    ASSERT_METHOD(MoveWindow(hWnd, x, y, rectangle.right - rectangle.left, rectangle.bottom - rectangle.top, bRepaint ? TRUE : FALSE), != , 0);
}

void rusty::controls::Window::ResizeTo(int nWidth, int nHeight, bool bRepaint)
{
    RECT rectangle;
    GetWindowRectangle(rectangle);
    ASSERT_METHOD(MoveWindow(hWnd, rectangle.left, rectangle.top, nWidth, nHeight, bRepaint ? TRUE : FALSE), != , 0);
}

void rusty::controls::Window::MoveAndResizeTo(int x, int y, int nWidth, int nHeight, bool bRepaint)
{
    ASSERT_METHOD(MoveWindow(hWnd, x, y, nWidth, nHeight, bRepaint ? TRUE : FALSE), != , 0);
}

HWND rusty::controls::Window::GetHandle(void)
{
    return hWnd;
}

void rusty::controls::Window::GetText(wchar_t *text_buffer, unsigned int text_buffer_size)
{
    ASSERT_METHOD(GetWindowText(hWnd, text_buffer, text_buffer_size), >, 0);
}

void rusty::controls::Window::SetText(const wchar_t *lpString)
{
    ASSERT_METHOD(SetWindowText(hWnd, lpString), != , 0);
}

void rusty::controls::Window::Focus()
{
    ASSERT_METHOD(SetFocus(hWnd), != , NULL);
}

void rusty::controls::Window::Show(WindowState state)
{
    ShowWindow(hWnd, static_cast<int>(state));
}

void rusty::controls::Window::SetRedraw(bool redraw)
{
    SendMessage(hWnd, WM_SETREDRAW, redraw ? TRUE : FALSE, 0);
}

void rusty::controls::Window::Redraw(const RECT *lprcUpdate, HRGN hrgnUpdate, unsigned int flags)
{
    ASSERT_METHOD(RedrawWindow(hWnd, lprcUpdate, hrgnUpdate, flags), != , 0);
}

void rusty::controls::Window::GetWindowRectangle(HWND hWnd, RECT &rectangle)
{
    HWND parent = GetAncestor(hWnd, GA_PARENT);

    ASSERT_METHOD(GetWindowRect(hWnd, &rectangle), != , FALSE);

    MapWindowPoints(HWND_DESKTOP, parent, reinterpret_cast<POINT *>(&rectangle), 2);
}

void rusty::controls::Window::GetClientRectangle(HWND hWnd, RECT &rectangle)
{
    ASSERT_METHOD(GetClientRect(hWnd, &rectangle), != , FALSE);
}

long rusty::controls::Window::GetWindowLeft(HWND hWnd)
{
    RECT rectangle;
    GetWindowRectangle(hWnd, rectangle);
    return rectangle.left;
}

long rusty::controls::Window::GetWindowTop(HWND hWnd)
{
    RECT rectangle;
    GetWindowRectangle(hWnd, rectangle);
    return rectangle.top;
}

long rusty::controls::Window::GetWindowRight(HWND hWnd)
{
    RECT rectangle;
    GetWindowRectangle(hWnd, rectangle);
    return rectangle.right - 1l;
}

long rusty::controls::Window::GetWindowBottom(HWND hWnd)
{
    RECT rectangle;
    GetWindowRectangle(hWnd, rectangle);
    return rectangle.bottom - 1l;
}

unsigned long rusty::controls::Window::GetWindowWidth(HWND hWnd)
{
    RECT rectangle;
    ASSERT_METHOD(GetWindowRect(hWnd, &rectangle), != , FALSE);
    return rectangle.right - rectangle.left;
}

unsigned long rusty::controls::Window::GetWindowHeight(HWND hWnd)
{
    RECT rectangle;
    ASSERT_METHOD(GetWindowRect(hWnd, &rectangle), != , FALSE);
    return rectangle.bottom - rectangle.top;
}

long rusty::controls::Window::GetClientLeft(HWND hWnd)
{
    RECT rectangle;
    ASSERT_METHOD(GetClientRect(hWnd, &rectangle), != , FALSE);
    return rectangle.left;
}

long rusty::controls::Window::GetClientTop(HWND hWnd)
{
    RECT rectangle;
    ASSERT_METHOD(GetClientRect(hWnd, &rectangle), != , FALSE);
    return rectangle.top;
}

long rusty::controls::Window::GetClientRight(HWND hWnd)
{
    RECT rectangle;
    ASSERT_METHOD(GetClientRect(hWnd, &rectangle), != , FALSE);
    return rectangle.right - 1l;
}

long rusty::controls::Window::GetClientBottom(HWND hWnd)
{
    RECT rectangle;
    ASSERT_METHOD(GetClientRect(hWnd, &rectangle), != , FALSE);
    return rectangle.bottom - 1l;
}

unsigned long rusty::controls::Window::GetClientWidth(HWND hWnd)
{
    RECT rectangle;
    ASSERT_METHOD(GetClientRect(hWnd, &rectangle), != , FALSE);
    return rectangle.right - rectangle.left;
}

unsigned long rusty::controls::Window::GetClientHeight(HWND hWnd)
{
    RECT rectangle;
    ASSERT_METHOD(GetClientRect(hWnd, &rectangle), != , FALSE);
    return rectangle.bottom - rectangle.top;
}

void rusty::controls::Window::MoveTo(HWND hWnd, int x, int y, bool bRepaint)
{
    RECT rectangle;
    GetWindowRectangle(hWnd, rectangle);
    ASSERT_METHOD(MoveWindow(hWnd, x, y, rectangle.right - rectangle.left, rectangle.bottom - rectangle.top, bRepaint ? TRUE : FALSE), != , 0);
}

void rusty::controls::Window::ResizeTo(HWND hWnd, int nWidth, int nHeight, bool bRepaint)
{
    RECT rectangle;
    GetWindowRectangle(hWnd, rectangle);
    ASSERT_METHOD(MoveWindow(hWnd, rectangle.left, rectangle.top, nWidth, nHeight, bRepaint ? TRUE : FALSE), != , 0);
}

void rusty::controls::Window::MoveAndResizeTo(HWND hWnd, int x, int y, int nWidth, int nHeight, bool bRepaint)
{
    ASSERT_METHOD(MoveWindow(hWnd, x, y, nWidth, nHeight, bRepaint ? TRUE : FALSE), != , 0);
}

void rusty::controls::Window::GetText(HWND hWnd, wchar_t *text_buffer, unsigned int text_buffer_size)
{
    ASSERT_METHOD(GetWindowText(hWnd, text_buffer, text_buffer_size), >, 0);
}

void rusty::controls::Window::SetText(HWND hWnd, const wchar_t *lpString)
{
    ASSERT_METHOD(SetWindowText(hWnd, lpString), != , 0);
}

void rusty::controls::Window::Focus(HWND hWnd)
{
    ASSERT_METHOD(SetFocus(hWnd), != , NULL);
}

void rusty::controls::Window::Show(HWND hWnd, WindowState state)
{
    ShowWindow(hWnd, static_cast<int>(state));
}

void rusty::controls::Window::SetRedraw(HWND hWnd, bool redraw)
{
    SendMessage(hWnd, WM_SETREDRAW, redraw ? TRUE : FALSE, 0);
}

void rusty::controls::Window::Redraw(HWND hWnd, const RECT *lprcUpdate, HRGN hrgnUpdate, unsigned int flags)
{
    ASSERT_METHOD(RedrawWindow(hWnd, lprcUpdate, hrgnUpdate, flags), != , 0);
}

rusty::controls::Window::~Window(void)
{
    if(IsWindow(hWnd))
        ASSERT_METHOD(DestroyWindow(hWnd), == , TRUE);

    if(has_registered_class)
        ASSERT_METHOD(UnregisterClass(lpClassName, hInstance), != , 0);
}
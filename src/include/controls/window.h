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

#ifndef CONTROLS_WINDOW_H
#define CONTROLS_WINDOW_H

class Window
{
    private:
        HINSTANCE hInstance = nullptr;
        
        const wchar_t * lpClassName = nullptr;

        void CreateChildWindow(HINSTANCE hInstance, EventHandlerInterface *event_handler, const wchar_t * const lpClassName, const wchar_t * const lpWindowName, HWND hWndParent, int hMenu, int icon_id, int x, int y, int nWidth, int nHeight, unsigned long dwExStyle, unsigned long dwStyle, bool set_cursor);
        void CreateControl(HINSTANCE hInstance, const wchar_t * const lpClassName, const wchar_t * const lpWindowName, HWND hWndParent, int hMenu, int x, int y, int nWidth, int nHeight, unsigned long dwExStyle, unsigned long dwStyle);
        void Window2(int icon_id, bool set_cursor);
        

    protected:
        HWND hWnd = nullptr;

    public:
        Window(const Window &) = delete;
        Window & operator=(const Window &) = delete;

        Window(HINSTANCE hInstance, EventHandlerInterface *event_handler, const wchar_t * const lpClassName, const wchar_t * const lpWindowName, int icon_id = -1, int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int nWidth = CW_USEDEFAULT, int nHeight = CW_USEDEFAULT, int ncmdshow = SW_SHOWDEFAULT, unsigned long dwExStyle = WS_EX_LEFT, unsigned long dwStyle = WS_OVERLAPPEDWINDOW, bool set_cursor = true);
        Window(HINSTANCE hInstance, EventHandlerInterface *event_handler, const wchar_t * const lpClassName, const wchar_t * const lpWindowName, ControlHandle *parent_handle, int hMenu, int icon_id = -1, int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int nWidth = CW_USEDEFAULT, int nHeight = CW_USEDEFAULT, unsigned long dwExStyle = WS_EX_LEFT, unsigned long dwStyle = WS_OVERLAPPEDWINDOW | WS_CHILD, bool set_cursor = true);
        Window(HINSTANCE hInstance, EventHandlerInterface *event_handler, const wchar_t * const lpClassName, const wchar_t * const lpWindowName, HWND hWndParent, int hMenu, int icon_id = -1, int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int nWidth = CW_USEDEFAULT, int nHeight = CW_USEDEFAULT, unsigned long dwExStyle = WS_EX_LEFT, unsigned long dwStyle = WS_OVERLAPPEDWINDOW | WS_CHILD, bool set_cursor = true);
        Window(HINSTANCE hInstance, const wchar_t * const lpClassName, const wchar_t * const lpWindowName, ControlHandle *parent_handle, int hMenu, int x, int y, int nWidth, int nHeight, unsigned long dwExStyle, unsigned long dwStyle);
        Window(HINSTANCE hInstance, const wchar_t * const lpClassName, const wchar_t * const lpWindowName, HWND hWndParent, int hMenu, int x, int y, int nWidth, int nHeight, unsigned long dwExStyle, unsigned long dwStyle);

        HFONT GetDefaultFont(void) const;

        void GetWindowRectangle(RECT &rectangle) const;
        void GetClientRectangle(RECT &rectangle) const;
        long GetWindowLeft(void) const;
        long GetWindowTop(void) const;

        /*!
        Right pixels are inclusive
        */
        long GetWindowRight(void) const;

        /*!
        Bottom pixels are inclusive
        */
        long GetWindowBottom(void) const;
        long GetWindowWidth(void) const;
        long GetWindowHeight(void) const;

        long GetClientLeft(void) const;
        long GetClientTop(void) const;

        /*!
        Right pixels are inclusive
        */
        long GetClientRight(void) const;

        /*!
        Bottom pixels are inclusive
        */
        long GetClientBottom(void) const;
        long GetClientWidth(void) const;
        long GetClientHeight(void) const;

        ControlHandle GetHandle(void);

        void MoveTo(int x, int y, bool bRepaint = true);
        void ResizeTo(int nWidth, int nHeight, bool bRepaint = true);
        void MoveAndResizeTo(int x, int y, int nWidth, int nHeight, bool bRepaint = true);

        ~Window(void);
};

#endif
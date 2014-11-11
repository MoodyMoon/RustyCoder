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
        
        bool has_registered_class = false;
        const wchar_t * lpClassName = nullptr;

        void Window2(int icon_id, bool set_default_cursor);

    protected:
        HWND hWnd = nullptr;

    public:
        Window(const Window &) = delete;
        Window & operator=(const Window &) = delete;

        Window(HINSTANCE hInstance, EventHandlerInterface *event_handler, const wchar_t * const lpClassName, const wchar_t * const lpWindowName, HWND hWndParent, unsigned long dwExStyle, unsigned long dwStyle, int nCmdShow = -1, int icon_id = -1, int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int nWidth = CW_USEDEFAULT, int nHeight = CW_USEDEFAULT, bool set_default_cursor = true);
        Window(HINSTANCE hInstance, EventHandlerInterface *event_handler, const wchar_t * const lpClassName, const wchar_t * const lpWindowName, HWND hWndParent, unsigned long dwExStyle, unsigned long dwStyle, HMENU hMenu, int icon_id = -1, int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int nWidth = CW_USEDEFAULT, int nHeight = CW_USEDEFAULT, bool set_default_cursor = true);
        Window(HINSTANCE hInstance, const wchar_t * const lpClassName, const wchar_t * const lpWindowName, HWND hWndParent, unsigned long dwExStyle, unsigned long dwStyle, HMENU hMenu, int x, int y, int nWidth, int nHeight, bool set_default_font);

        static HFONT GetDefaultFont(void);
        void SetFont(HFONT hFont, BOOL redraw = FALSE);

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

        void MoveTo(int x, int y, bool bRepaint = true);
        void ResizeTo(int nWidth, int nHeight, bool bRepaint = true);
        void MoveAndResizeTo(int x, int y, int nWidth, int nHeight, bool bRepaint = true);

        HWND GetHandle(void);

        static void GetWindowRectangle(HWND hWnd, RECT &rectangle);
        static void GetClientRectangle(HWND hWnd, RECT &rectangle);
        static long GetWindowLeft(HWND hWnd);
        static long GetWindowTop(HWND hWnd);

        /*!
        Right pixels are inclusive
        */
        static long GetWindowRight(HWND hWnd);

        /*!
        Bottom pixels are inclusive
        */
        static long GetWindowBottom(HWND hWnd);
        static long GetWindowWidth(HWND hWnd);
        static long GetWindowHeight(HWND hWnd);

        static long GetClientLeft(HWND hWnd);
        static long GetClientTop(HWND hWnd);

        /*!
        Right pixels are inclusive
        */
        static long GetClientRight(HWND hWnd);

        /*!
        Bottom pixels are inclusive
        */
        static long GetClientBottom(HWND hWnd);
        static long GetClientWidth(HWND hWnd);
        static long GetClientHeight(HWND hWnd);

        static void MoveTo(HWND hWnd, int x, int y, bool bRepaint = true);
        static void ResizeTo(HWND hWnd, int nWidth, int nHeight, bool bRepaint = true);
        static void MoveAndResizeTo(HWND hWnd, int x, int y, int nWidth, int nHeight, bool bRepaint = true);

        virtual ~Window(void);
};

#endif
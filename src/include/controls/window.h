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

#ifndef CONTROLS_WINDOW_H
#define CONTROLS_WINDOW_H

#include "event_handler_interface.h"
#include "global_window_procedure.h"

namespace rusty
{
namespace controls
{
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
        enum WindowState : int
        {
            HIDE = SW_HIDE,
            SHOWNORMAL = SW_SHOWNORMAL,
            SHOWMINIMIZED = SW_SHOWMINIMIZED,
            SHOWMAXIMIZED = SW_SHOWMAXIMIZED,
            SHOWNOACTIVATE = SW_SHOWNOACTIVATE,
            SHOW = SW_SHOW,
            MINIMIZE = SW_MINIMIZE,
            SHOWMINNOACTIVE = SW_SHOWMINNOACTIVE,
            SHOWNA = SW_SHOWNA,
            RESTORE = SW_RESTORE,
            SHOWDEFAULT = SW_SHOWDEFAULT,
            FORCEMINIMIZE = SW_FORCEMINIMIZE,
        };

        Window(const Window &) = delete;
        Window & operator=(const Window &) = delete;

        Window(HINSTANCE hInstance, EventHandlerInterface *event_handler, const wchar_t * const lpClassName, const wchar_t * const lpWindowName, HWND hWndParent, unsigned long dwExStyle, unsigned long dwStyle, int nCmdShow = -1, int icon_id = -1, int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int nWidth = CW_USEDEFAULT, int nHeight = CW_USEDEFAULT, bool set_default_cursor = true);
        Window(HINSTANCE hInstance, EventHandlerInterface *event_handler, const wchar_t * const lpClassName, const wchar_t * const lpWindowName, HWND hWndParent, unsigned long dwExStyle, unsigned long dwStyle, uintptr_t hMenu, int icon_id = -1, int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int nWidth = CW_USEDEFAULT, int nHeight = CW_USEDEFAULT, bool set_default_cursor = true);
        Window(HINSTANCE hInstance, const wchar_t * const lpClassName, const wchar_t * const lpWindowName, HWND hWndParent, unsigned long dwExStyle, unsigned long dwStyle, uintptr_t hMenu, int x, int y, int nWidth, int nHeight, bool set_default_font);

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
        unsigned long GetWindowWidth(void) const;
        unsigned long GetWindowHeight(void) const;

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
        unsigned long GetClientWidth(void) const;
        unsigned long GetClientHeight(void) const;

        void MoveTo(int x, int y, bool bRepaint = true);
        void ResizeTo(int nWidth, int nHeight, bool bRepaint = true);
        void MoveAndResizeTo(int x, int y, int nWidth, int nHeight, bool bRepaint = true);

        HWND GetHandle(void);

        void GetText(wchar_t *text_buffer, unsigned int text_buffer_size);
        void SetText(const wchar_t *lpString);

        void Focus(void);
        void Show(WindowState state);

        void SetRedraw(bool redraw);
        void Redraw(const RECT *lprcUpdate = nullptr, HRGN hrgnUpdate = nullptr, unsigned int flags = RDW_ERASE | RDW_FRAME | RDW_INVALIDATE | RDW_ALLCHILDREN);

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
        static unsigned long GetWindowWidth(HWND hWnd);
        static unsigned long GetWindowHeight(HWND hWnd);

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
        static unsigned long GetClientWidth(HWND hWnd);
        static unsigned long GetClientHeight(HWND hWnd);

        static void MoveTo(HWND hWnd, int x, int y, bool bRepaint = true);
        static void ResizeTo(HWND hWnd, int nWidth, int nHeight, bool bRepaint = true);
        static void MoveAndResizeTo(HWND hWnd, int x, int y, int nWidth, int nHeight, bool bRepaint = true);

        static void GetText(HWND hWnd, wchar_t *text_buffer, unsigned int text_buffer_size);
        static void SetText(HWND hWnd, const wchar_t *lpString);

        static void Focus(HWND hWnd);
        static void Show(HWND hWnd, WindowState state);

        static void SetRedraw(HWND hWnd, bool redraw);
        static void Redraw(HWND hWnd, const RECT *lprcUpdate = nullptr, HRGN hrgnUpdate = nullptr, unsigned int flags = RDW_ERASE | RDW_FRAME | RDW_INVALIDATE | RDW_ALLCHILDREN);

        virtual ~Window(void);
};
}
}

#endif
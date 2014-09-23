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

#ifndef CONTROLS_VERTICAL_SPLIT_WINDOW
#define CONTROLS_VERTICAL_SPLIT_WINDOW

class VerticalSplitWindow;

class VerticalSplitWindowEventHandler : public EventHandlerInterface
{
    protected:
        VerticalSplitWindow *split_window = nullptr;
        Panel *left_panel = nullptr;
        HWND left_panel_handle = nullptr;
        Panel *right_panel = nullptr;
        HWND right_panel_handle = nullptr;
        RECT splitter;
        HCURSOR normal_cursor = reinterpret_cast<HCURSOR>(LoadImage(nullptr, MAKEINTRESOURCE(OCR_NORMAL), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR | LR_SHARED));
        HCURSOR size_cursor = reinterpret_cast<HCURSOR>(LoadImage(nullptr, MAKEINTRESOURCE(OCR_SIZEWE), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR | LR_SHARED));
        TRACKMOUSEEVENT track_mouse;

        unsigned int old_splitter_x;
        unsigned int old_mouse_x;
        unsigned int splitter_temp_x;

        const unsigned int splitter_width = 5u;
        bool left_mouse_down = false;

        virtual LRESULT HandleEvent(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    public:
        VerticalSplitWindowEventHandler() = default;
        VerticalSplitWindowEventHandler(const VerticalSplitWindowEventHandler &) = delete;
        VerticalSplitWindowEventHandler & operator=(const VerticalSplitWindowEventHandler &) = delete;
};

class VerticalSplitWindow : public VerticalSplitWindowEventHandler, public Panel
{
    friend class VerticalSplitWindowEventHandler;

    private:
        void VerticalSplitWindow2(unsigned long splitter_position_x);
        void SetLeftPanelToFit(Panel *panel);
        void SetRightPanelToFit(Panel *panel);

    public:
        VerticalSplitWindow(const VerticalSplitWindow &) = delete;
        VerticalSplitWindow & operator=(const VerticalSplitWindow &) = delete;

        VerticalSplitWindow(HINSTANCE hInstance, ControlHandle *parent_handle, const wchar_t * const lpClassName, int hMenu, int x, int y, int nWidth, int nHeight, unsigned long splitter_position_x, DWORD dwExStyle = WS_EX_LEFT, DWORD dwStyle = WS_BORDER | WS_CHILD | WS_VISIBLE);
        VerticalSplitWindow(HINSTANCE hInstance, HWND hWndParent, const wchar_t * const lpClassName, int hMenu, int x, int y, int nWidth, int nHeight, unsigned long splitter_position_x, DWORD dwExStyle = WS_EX_LEFT, DWORD dwStyle = WS_BORDER | WS_CHILD | WS_VISIBLE);

        void SetLeftPanel(Panel *panel);
        void SetRightPanel(Panel *panel);
};

#endif
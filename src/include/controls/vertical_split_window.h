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

#ifndef CONTROLS_VERTICAL_SPLIT_WINDOW_H
#define CONTROLS_VERTICAL_SPLIT_WINDOW_H

#include "event_handler_interface.h"
#include "panel.h"
#include "window.h"

namespace rusty
{
namespace controls
{
class VerticalSplitWindow;

class VerticalSplitWindowEvents : public EventHandlerInterface
{
    public:
        enum class MinWidthPanel : unsigned int
        {
            LEFT,
            RIGHT
        };

    protected:
        VerticalSplitWindow *split_window = nullptr;
        Panel *left_panel = nullptr;
        HWND left_panel_handle = nullptr;
        Panel *right_panel = nullptr;
        HWND right_panel_handle = nullptr;
        RECT splitter;
        HCURSOR normal_cursor = reinterpret_cast<HCURSOR>(LoadImage(nullptr, MAKEINTRESOURCE(OCR_NORMAL), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR | LR_SHARED));
        HCURSOR size_cursor = reinterpret_cast<HCURSOR>(LoadImage(nullptr, MAKEINTRESOURCE(OCR_SIZEWE), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR | LR_SHARED));

        unsigned int old_splitter_x;
        unsigned int old_mouse_x;
        int splitter_temp_x;
        unsigned int splitter_boundary[2];

        const unsigned int splitter_width = 5u;
        bool left_mouse_down = false;
        unsigned int min_width;
        MinWidthPanel panel_set_min_width;
        unsigned int length_from_splitter_x_to_window_right;

        virtual LRESULT HandleEvent(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    public:
        VerticalSplitWindowEvents() = default;
        VerticalSplitWindowEvents(const VerticalSplitWindowEvents &) = delete;
        VerticalSplitWindowEvents & operator=(const VerticalSplitWindowEvents &) = delete;
};

class VerticalSplitWindow : public VerticalSplitWindowEvents, public Panel
{
    friend class VerticalSplitWindowEvents;

    private:
        void UpdatePanelsPositions(void);
        void SetLeftPanelToFit(Panel *panel);
        void SetRightPanelToFit(Panel *panel);

    public:
        VerticalSplitWindow(const VerticalSplitWindow &) = delete;
        VerticalSplitWindow & operator=(const VerticalSplitWindow &) = delete;

        VerticalSplitWindow(HINSTANCE hInstance, const wchar_t * const lpClassName, HWND hWndParent, int hMenu, int x, int y, int nWidth, int nHeight, unsigned long splitter_position_x, unsigned int min_width, MinWidthPanel panel_set_min_width, unsigned long dwExStyle = WS_EX_LEFT, unsigned long dwStyle = WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_BORDER | WS_CHILD | WS_VISIBLE);

        void SetLeftPanel(Panel *panel, bool fit_to_client_area);
        void SetRightPanel(Panel *panel, bool fit_to_client_area);
        void GetSplitterLeftRectangle(RECT &rectangle);
        void GetSplitterRightRectangle(RECT &rectangle);
        unsigned int GetSplitterLeftWidth(void);
        unsigned int GetSplitterRightWidth(void);

        virtual ~VerticalSplitWindow(void) {}
};
}
}

#endif
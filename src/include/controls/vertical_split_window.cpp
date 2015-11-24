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
#include "vertical_split_window.h"

rusty::controls::VerticalSplitWindow::VerticalSplitWindow(HINSTANCE hInstance, const wchar_t * const lpClassName, HWND hWndParent, int hMenu, int x, int y, int nWidth, int nHeight, unsigned long splitter_position_x, unsigned int min_width, MinWidthPanel panel_set_min_width, unsigned long dwExStyle, unsigned long dwStyle) : Panel(hInstance, this, lpClassName, hWndParent, hMenu, x, y, nWidth, nHeight, dwExStyle, dwStyle, false)
{
    assert(nWidth >= 10 && nHeight >= 10);
    assert((splitter_position_x + splitter_width - 1) <= static_cast<unsigned long>(Window::GetClientRight()));

    splitter.left = splitter_position_x;
    splitter.top = Window::GetClientTop();
    splitter.right = splitter_position_x + splitter_width - 1;
    splitter.bottom = Window::GetClientBottom();

    this->panel_set_min_width = panel_set_min_width;

    if(panel_set_min_width == MinWidthPanel::LEFT)
    {
        splitter_boundary[0] = min_width;
        splitter_boundary[1] = static_cast<unsigned int>(Window::GetClientRight()) - splitter_width + 1;
    }
    else
    {
        this->min_width = min_width;
        splitter_boundary[0] = 0u;
        splitter_boundary[1] = static_cast<unsigned int>(Window::GetClientRight()) - splitter_width + 1 - min_width;
        length_from_splitter_x_to_window_right = Window::GetClientRight() - splitter.left;
    }

    split_window = this;
}

void rusty::controls::VerticalSplitWindow::SetLeftPanel(Panel *panel, bool fit_to_client_area)
{
    if(panel == nullptr)
    {
        if(IsWindow(left_panel_handle) == FALSE)
        {
            left_panel = nullptr;
            left_panel_handle = nullptr;
        }
        #ifdef _DEBUG
        else
            assert(false); //prevent caller from setting nullptr if the panel still exists.
        #endif
    }
    else
    {
        if(fit_to_client_area)
            SetLeftPanelToFit(panel);

        left_panel = panel;
        left_panel_handle = panel->GetHandle();
    }
}

void rusty::controls::VerticalSplitWindow::SetRightPanel(Panel *panel, bool fit_to_client_area)
{
    if(panel == nullptr)
    {
        if(IsWindow(right_panel_handle) == FALSE)
        {
            right_panel = nullptr;
            right_panel_handle = nullptr;
        }
        #ifdef _DEBUG
        else
            assert(false); //prevent caller from setting nullptr if the panel still exists.
        #endif
    }
    else
    {
        if(fit_to_client_area)
            SetRightPanelToFit(panel);

        right_panel = panel;
        right_panel_handle = panel->GetHandle();
    }
}

void rusty::controls::VerticalSplitWindow::UpdatePanelsPositions(void)
{
    if(IsWindow(left_panel_handle))
        split_window->SetLeftPanelToFit(left_panel);
    else
    {
        left_panel = nullptr;
        left_panel_handle = nullptr;
    }

    if(IsWindow(right_panel_handle))
        split_window->SetRightPanelToFit(right_panel);
    else
    {
        right_panel = nullptr;
        right_panel_handle = nullptr;
    }
}

void rusty::controls::VerticalSplitWindow::SetLeftPanelToFit(Panel *panel)
{
    RECT rectangle;
    GetSplitterLeftRectangle(rectangle);
    panel->MoveAndResizeTo(rectangle.left, rectangle.top, rectangle.right + 1, rectangle.bottom + 1);
}

void rusty::controls::VerticalSplitWindow::SetRightPanelToFit(Panel *panel)
{
    RECT rectangle;
    GetSplitterRightRectangle(rectangle);
    panel->MoveAndResizeTo(rectangle.left, rectangle.top, rectangle.right - splitter.right, rectangle.bottom + 1);
}

void rusty::controls::VerticalSplitWindow::GetSplitterLeftRectangle(RECT &rectangle)
{
    rectangle.left = 0;
    rectangle.top = 0;
    rectangle.right = splitter.left - 1;
    rectangle.bottom = Window::GetClientBottom();
}

void rusty::controls::VerticalSplitWindow::GetSplitterRightRectangle(RECT &rectangle)
{
    rectangle.left = splitter.right + 1;
    rectangle.top = 0;
    rectangle.right = Window::GetClientRight();
    rectangle.bottom = Window::GetClientBottom();
}

unsigned int rusty::controls::VerticalSplitWindow::GetSplitterLeftWidth(void)
{
    return splitter.left;
}

unsigned int rusty::controls::VerticalSplitWindow::GetSplitterRightWidth(void)
{
    return Window::GetClientRight() - splitter.right;
}

LRESULT rusty::controls::VerticalSplitWindowEvents::HandleEvent(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_LBUTTONDOWN:
        {
            old_splitter_x = splitter.left;
            old_mouse_x = GET_X_LPARAM(lParam);
            SetCapture(hWnd);
            break;
        }
        case WM_MOUSEMOVE:
        {
            SetCursor(size_cursor);

            if(wParam == MK_LBUTTON)
            {
                splitter_temp_x = GET_X_LPARAM(lParam) - old_mouse_x + old_splitter_x;

                splitter_boundary[1] = static_cast<unsigned int>(split_window->GetClientRight()) - splitter_width + 1u - min_width;

                if(splitter_temp_x >= static_cast<int>(splitter_boundary[0]) && splitter_temp_x <= static_cast<int>(splitter_boundary[1]))
                {
                    splitter.left = splitter_temp_x;
                    splitter.right = splitter_temp_x + splitter_width - 1;
                }
                else if(splitter_temp_x < static_cast<int>(splitter_boundary[0]))
                {
                    splitter.left = splitter_boundary[0];
                    splitter.right = splitter.left + splitter_width - 1;
                }
                else
                {
                    splitter.left = static_cast<long>(splitter_boundary[1]);
                    splitter.right = splitter.left + splitter_width - 1;
                }

                if(panel_set_min_width == MinWidthPanel::RIGHT)
                    length_from_splitter_x_to_window_right = split_window->GetClientRight() - splitter.left;

                split_window->UpdatePanelsPositions();
            }
            break;
        }
        case WM_LBUTTONUP:
            ReleaseCapture();
            break;
        case WM_SIZE:
        {
            switch(wParam)
            {
                case SIZE_MAXIMIZED:
                case SIZE_MAXSHOW:
                case SIZE_RESTORED:
                {
                    if(split_window != nullptr)
                    {
                        splitter_boundary[1] = static_cast<unsigned int>(split_window->GetClientRight()) - splitter_width + 1 - min_width;

                        if(splitter.left >= static_cast<int>(splitter_boundary[0]) && splitter.left <= static_cast<int>(splitter_boundary[1]))
                        {
                            if(panel_set_min_width == MinWidthPanel::RIGHT)
                            {
                                splitter.left = split_window->GetClientRight() - static_cast<long>(length_from_splitter_x_to_window_right);
                                if(splitter.left < static_cast<int>(splitter_boundary[0]))
                                    splitter.left = static_cast<int>(splitter_boundary[0]);
                            }

                            splitter.right = splitter.left + splitter_width - 1;
                        }
                        else if(splitter.left < static_cast<int>(splitter_boundary[0]))
                        {
                            splitter.left = splitter_boundary[0];
                            splitter.right = splitter.left + splitter_width - 1;
                        }
                        else
                        {
                            if(panel_set_min_width == MinWidthPanel::RIGHT)
                            {
                                splitter.left = Window::GetClientWidth(hWnd) - static_cast<long>(length_from_splitter_x_to_window_right);
                            }
                            else
                                splitter.left = static_cast<long>(splitter_boundary[1]);
                            splitter.right = splitter.left + splitter_width - 1;
                        }

                        split_window->UpdatePanelsPositions();
                    }
                    break;
                }
            }
            return 0;
        }
        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return 0;
}
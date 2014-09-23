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
#include "vertical_split_window.h"

VerticalSplitWindow::VerticalSplitWindow(HINSTANCE hInstance, ControlHandle *parent_handle, const wchar_t * const lpClassName, int hMenu, int x, int y, int nWidth, int nHeight, unsigned long splitter_position_x, DWORD dwExStyle, DWORD dwStyle) : Panel(hInstance, this, parent_handle, lpClassName, hMenu, x, y, nWidth, nHeight, dwExStyle, dwStyle, false)
{
    VerticalSplitWindow2(splitter_position_x);
}

VerticalSplitWindow::VerticalSplitWindow(HINSTANCE hInstance, HWND hWndParent, const wchar_t * const lpClassName, int hMenu, int x, int y, int nWidth, int nHeight, unsigned long splitter_position_x, DWORD dwExStyle, DWORD dwStyle) : Panel(hInstance, this, hWndParent, lpClassName, hMenu, x, y, nWidth, nHeight, dwExStyle, dwStyle, false)
{
    VerticalSplitWindow2(splitter_position_x);
}

void VerticalSplitWindow::VerticalSplitWindow2(unsigned long splitter_position_x)
{
    if(splitter_position_x < 0 || splitter_position_x >(Window::GetClientRight() + 1 - splitter_width))
        throw GuiGenericException("VerticalSplitWindow", "Splitter is out of client area boundary.");

    splitter.left = splitter_position_x;
    splitter.top = Window::GetClientTop();
    splitter.right = splitter_position_x + splitter_width - 1;
    splitter.bottom = Window::GetClientBottom();

    split_window = this;
}

void VerticalSplitWindow::SetLeftPanel(Panel *panel)
{
    if(panel == nullptr)
    {
        if(IsWindow(left_panel_handle) == FALSE)
        {
            left_panel = nullptr;
            left_panel_handle = nullptr;
        }
        #ifndef NDEBUG
        else
            assert(false); //prevent caller from setting nullptr if the panel still exists.
        #endif
    }
    else
    {
        SetLeftPanelToFit(panel);

        left_panel = panel;
        left_panel_handle = panel->GetHandle().handle;
    }
}

void VerticalSplitWindow::SetRightPanel(Panel *panel)
{
    if(panel == nullptr)
    {
        if(IsWindow(right_panel_handle) == FALSE)
        {
            right_panel = nullptr;
            right_panel_handle = nullptr;
        }
        #ifndef NDEBUG
        else
            assert(false); //prevent caller from setting nullptr if the panel still exists.
        #endif
    }
    else
    {
        SetRightPanelToFit(panel);

        right_panel = panel;
        right_panel_handle = panel->GetHandle().handle;
    }
}

void VerticalSplitWindow::SetLeftPanelToFit(Panel *panel)
{
    long split_window_client_height = Window::GetClientHeight();

    panel->MoveAndResizeTo(0, 0, splitter.left, split_window_client_height);

    if(panel->GetWindowWidth() != splitter.left || panel->GetWindowHeight() != split_window_client_height)
        throw GuiGenericException("VerticalSplitWindow", "Cannot resize left panel.");
}

void VerticalSplitWindow::SetRightPanelToFit(Panel *panel)
{
    long split_window_client_height = Window::GetClientHeight();
    long right_panel_assumed_width = Window::GetClientRight() - splitter.right;

    panel->MoveAndResizeTo(splitter.right + 1, 0, right_panel_assumed_width, split_window_client_height);

    if(panel->GetWindowWidth() != right_panel_assumed_width || panel->GetWindowHeight() != split_window_client_height)
        throw GuiGenericException("VerticalSplitWindow", "Cannot resize left panel.");
}

LRESULT VerticalSplitWindowEventHandler::HandleEvent(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
                splitter_temp_x = old_splitter_x + GET_X_LPARAM(lParam) - old_mouse_x;

                if(splitter_temp_x >= 0 && (splitter_temp_x <= split_window->GetClientRight() - splitter_width - 1))
                {
                    splitter.left = splitter_temp_x;
                    splitter.right = splitter_temp_x + splitter_width - 1;
                }
                else if(splitter_temp_x < 0)
                {
                    splitter.left = 0;
                    splitter.right = splitter.left + splitter_width - 1;
                }
                else
                {
                    splitter.left = split_window->GetClientRight() - splitter_width + 1;
                    splitter.right = split_window->GetClientRight();
                }

                if(IsWindow(left_panel_handle))
                {
                    splitter.left = splitter.left;
                    split_window->SetLeftPanelToFit(left_panel);
                }
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
            break;
        }
        case WM_LBUTTONUP:
            ReleaseCapture();
            break;
        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return 0;
}
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
#include "global_window_procedure.h"

LRESULT CALLBACK GlobalWindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_NCCREATE:
        {
            if(lParam != 0)
            {
                CREATESTRUCT *cs = reinterpret_cast<CREATESTRUCT *>(lParam);
                #ifndef X64
                SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG>(cs->lpCreateParams));
                #else
                SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(cs->lpCreateParams));
                #endif
            }
            return DefWindowProc(hWnd, uMsg, wParam, lParam); /*!< Must return this to to properly setup the window */
            break;
        }
        default:
        {
            #ifndef X64
            LONG address;
            #else
            LONG_PTR address;
            #endif

            address = GetWindowLongPtr(hWnd, GWLP_USERDATA);

            if(address != 0)
            {
                EventHandlerInterface *event_handler = reinterpret_cast<EventHandlerInterface *>(address);
                return event_handler->HandleEvent(hWnd, uMsg, wParam, lParam);
            }
            else
                return DefWindowProc(hWnd, uMsg, wParam, lParam);
        }
    }
}
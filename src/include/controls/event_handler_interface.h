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

#ifndef CONTROLS_EVENT_HANDLER_INTERFACE_H
#define CONTROLS_EVENT_HANDLER_INTERFACE_H

#include "stdafx.h"

namespace rusty
{
namespace controls
{
class EventHandlerInterface
{
    protected:
        EventHandlerInterface(void) = default;

    public:
        EventHandlerInterface(const EventHandlerInterface &) = delete;
        EventHandlerInterface & operator=(const EventHandlerInterface &) = delete;

        virtual LRESULT HandleEvent(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) = 0;

        virtual ~EventHandlerInterface(void) {}
};
}
}

#endif
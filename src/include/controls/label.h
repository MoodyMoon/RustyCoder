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

#ifndef CONTROLS_LABEL_H
#define CONTROLS_LABEL_H

#include "window.h"

namespace rusty
{
namespace controls
{
class Label : public Window
{
    public:
        Label(const Label &) = delete;
        Label & operator=(const Label &) = delete;

        Label(HINSTANCE hInstance, const wchar_t * const lpWindowName, HWND hWndParent, uintptr_t hMenu, int x, int y, int nWidth, int nHeight, unsigned long dwExStyle = WS_EX_LEFT, unsigned long dwStyle = SS_LEFT | SS_LEFTNOWORDWRAP | WS_CLIPSIBLINGS | WS_CHILD | WS_VISIBLE);

        virtual ~Label(void) {}
};
}
}

#endif
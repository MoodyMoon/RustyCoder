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

#ifndef CONTROLS_NUMERIC_UP_DOWN_H
#define CONTROLS_NUMERIC_UP_DOWN_H

#include "window.h"

namespace rusty
{
namespace controls
{
class NumericUpDown : public Window
{
    private:
        int lower_bound;
        int upper_bound;

    public:
        NumericUpDown(const NumericUpDown &) = delete;
        NumericUpDown & operator=(const NumericUpDown &) = delete;

        NumericUpDown(HINSTANCE hInstance, HWND hWndParent, uintptr_t hMenu, HWND hWndBuddy, int lower_bound, int upper_bound, unsigned long dwExStyle = WS_EX_LEFT, unsigned long dwStyle = UDS_ALIGNRIGHT | UDS_ARROWKEYS | UDS_NOTHOUSANDS | UDS_SETBUDDYINT | WS_CLIPSIBLINGS | WS_CHILD | WS_VISIBLE);

        int GetPosition(void);
        int GetLowerBound(void);
        int GetUpperBound(void);
        void SetPosition(int value);
};
}
}

#endif
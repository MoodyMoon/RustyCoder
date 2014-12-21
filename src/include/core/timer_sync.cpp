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
#include "timer_sync.h"

TimerSync::TimerSync(HWND hWnd, UINT_PTR nIDEvent, unsigned int uElapse, bool start_now) : hWndParent(hWnd), nIDEvent(nIDEvent), uElapse(uElapse), started(start_now)
{
    if(start_now)
        METHOD_ASSERT(SetTimer(hWnd, nIDEvent, uElapse, nullptr), !=, 0);
}

void TimerSync::Start(void)
{
    if(!started)
    {
        METHOD_ASSERT(SetTimer(hWndParent, nIDEvent, uElapse, nullptr), !=, 0);
        started = true;
    }
}

void TimerSync::Stop(void)
{
    if(started)
    {
        METHOD_ASSERT(KillTimer(hWndParent, nIDEvent), !=, 0);
        started = false;
    }
}

bool TimerSync::IsStarted(void)
{
    return started;
}

TimerSync::~TimerSync(void)
{
    Stop();
}
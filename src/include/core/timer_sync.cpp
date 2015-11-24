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
#include "timer_sync.h"

std::unordered_map<uintptr_t, rusty::core::TimerSync::CallbackInterface *> rusty::core::TimerSync::timer_callbacks;

rusty::core::TimerSync::TimerSync(CallbackInterface *callback, unsigned int uElapse, bool start_now) : callback(callback), uElapse(uElapse), started(start_now)
{
    assert(callback != nullptr);

    if(start_now)
    {
        id = SetTimer(nullptr, 0u, uElapse, TimerProc);
        ASSERT_METHOD(id, != , 0u);

        timer_callbacks.emplace(id, callback);
    }
}

void rusty::core::TimerSync::Start(void)
{
    if(!started)
    {
        id = SetTimer(nullptr, 0u, uElapse, TimerProc);
        ASSERT_METHOD(id, != , 0u);

        timer_callbacks.emplace(id, callback);

        started = true;
    }
}

void rusty::core::TimerSync::Stop(void)
{
    if(started)
    {
        ASSERT_METHOD(KillTimer(nullptr, id), != , 0);

        timer_callbacks.erase(id);

        started = false;
    }
}

bool rusty::core::TimerSync::IsStarted(void)
{
    return started;
}

void __stdcall rusty::core::TimerSync::TimerProc(HWND /* hwnd */, unsigned int /* uMsg */, uintptr_t idEvent, unsigned long /* dwTime */)
{
    static CallbackInterface *callback;
    callback = timer_callbacks.at(idEvent);
    callback->OnTimerSyncTick();
}

rusty::core::TimerSync::~TimerSync(void)
{
    Stop();
}
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
#include "timer_async.h"

TimerAsync::TimerAsync(const std::chrono::milliseconds interval, TimerAsyncCallbackInterface *callback) : interval(interval), callback(callback) {}

void TimerAsync::StartSync()
{
    timer_lock.Lock();
    if(!started)
    {
        started = true;
        timer_thread.reset(new std::thread(&TimerAsync::RunAsync, this));
    }
    timer_lock.Unlock();
}

void TimerAsync::StopSync()
{
    timer_lock.Lock();
    if(started)
    {
        started = false;
        timer_lock.Unlock();
    }
    else
    {
        timer_lock.Unlock();
        return;
    }

    timer_thread->join();
    timer_thread.reset();
}

bool TimerAsync::IsStartedSync()
{
    timer_lock.Lock();
    bool _started = started;
    timer_lock.Unlock();
    return _started;
}

void TimerAsync::RunAsync()
{
    while(IsStartedSync())
    {
        std::this_thread::sleep_for(interval);
        callback->OnTickAsync();
    }
}

TimerAsync::~TimerAsync()
{
    StopSync();
}
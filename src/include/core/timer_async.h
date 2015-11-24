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

#ifndef CORE_TIMER_ASYNC_H
#define CORE_TIMER_ASYNC_H

#include "critical_section.h"

namespace rusty
{
namespace core
{
class TimerAsync
{
    public:
        class CallbackInterface;

    private:
        bool started = false;

        CriticalSection timer_lock;

        std::unique_ptr<std::thread> timer_thread;

        const std::chrono::milliseconds interval;
        CallbackInterface *callback;

        void RunAsync(void);

    public:
        TimerAsync(const TimerAsync &) = delete;
        TimerAsync & operator=(const TimerAsync &) = delete;

        TimerAsync(const std::chrono::milliseconds interval, CallbackInterface *callback);

        void StartSync(void);
        void StopSync(void);

        bool IsStartedSync(void);

        ~TimerAsync(void);
};

class TimerAsync::CallbackInterface
{
    public:
    CallbackInterface() = default;
    CallbackInterface(const CallbackInterface &) = delete;
    CallbackInterface & operator=(const CallbackInterface &) = delete;

    virtual void OnTimerAsyncTick(void) = 0;
    virtual ~CallbackInterface(void) {}
};
}
}

#endif
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

#ifndef CORE_TIMER_ASYNC_H
#define CORE_TIMER_ASYNC_H

class TimerAsyncCallbackInterface;

class TimerAsync
{
    private:
        bool started = false;

        RustyLock timer_lock;

        std::unique_ptr<std::thread> timer_thread;

        const std::chrono::milliseconds interval;
        TimerAsyncCallbackInterface *callback;

        void RunAsync(void);

    public:
        TimerAsync(const TimerAsync &) = delete;
        TimerAsync & operator=(const TimerAsync &) = delete;

        TimerAsync(const std::chrono::milliseconds interval, TimerAsyncCallbackInterface *callback);

        void StartSync(void);
        void StopSync(void);

        bool IsStartedSync(void);

        ~TimerAsync(void);
};

class TimerAsyncCallbackInterface
{
    public:
        TimerAsyncCallbackInterface() = default;
        TimerAsyncCallbackInterface(const TimerAsyncCallbackInterface &) = delete;
        TimerAsyncCallbackInterface & operator=(const TimerAsyncCallbackInterface &) = delete;

        virtual void OnTickAsync(void) = 0;

        virtual ~TimerAsyncCallbackInterface(void) {}
};

#endif
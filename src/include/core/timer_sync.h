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

#ifndef CORE_TIMER_SYNC_H
#define CORE_TIMER_SYNC_H

namespace rusty
{
namespace core
{
class TimerSync
{
    public:
        class CallbackInterface;

    private:
        CallbackInterface *callback;
        uintptr_t id;
        unsigned int uElapse;
        bool started;

        static std::unordered_map<uintptr_t, CallbackInterface *> timer_callbacks;
        static void __stdcall TimerProc(HWND hwnd, unsigned int uMsg, uintptr_t idEvent, unsigned long dwTime);

    public:
        TimerSync(const TimerSync &) = delete;
        TimerSync & operator=(const TimerSync &) = delete;

        TimerSync(CallbackInterface *callback, unsigned int uElapse, bool start_now);
        void Start(void);
        void Stop(void);
        bool IsStarted(void);
        ~TimerSync(void);
};

class TimerSync::CallbackInterface
{
    public:
        CallbackInterface() = default;
        CallbackInterface(const CallbackInterface &) = delete;
        CallbackInterface & operator=(const CallbackInterface &) = delete;

        virtual void OnTimerSyncTick(void) = 0;

        virtual ~CallbackInterface(void) {}
};
}
}

#endif
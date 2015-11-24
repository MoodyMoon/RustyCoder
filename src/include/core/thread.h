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

#ifndef CORE_THREAD_H
#define CORE_THREAD_H

namespace rusty
{
namespace core
{
class Thread
{
    private:
        HANDLE thread;
        unsigned long id;

        static unsigned long __stdcall ThreadProc(void *callback);

    public:
        enum Priority : int
        {
            IDLE = THREAD_PRIORITY_IDLE,
            LOWEST = THREAD_PRIORITY_LOWEST,
            BELOW_NORMAL = THREAD_PRIORITY_BELOW_NORMAL,
            NORMAL = THREAD_PRIORITY_NORMAL,
            ABOVE_NORMAL = THREAD_PRIORITY_ABOVE_NORMAL,
            HIGHEST = THREAD_PRIORITY_HIGHEST,
            TIME_CRITICAL = THREAD_PRIORITY_TIME_CRITICAL
        };

        class CallbackInterface;

        Thread(const Thread &) = delete;
        Thread & operator=(const Thread &) = delete;

        Thread(CallbackInterface &callback, Priority priority);
        unsigned long GetId(void);
        void SetPriority(Priority priority);
        static void SetBackground(bool background);
        ~Thread(void);
};

class Thread::CallbackInterface
{
    public:
        CallbackInterface() = default;
        CallbackInterface(const CallbackInterface &) = delete;
        CallbackInterface & operator=(const CallbackInterface &) = delete;

        virtual void ThreadDo(void) = 0;
        virtual ~CallbackInterface(void) {}
};
}
}

#endif
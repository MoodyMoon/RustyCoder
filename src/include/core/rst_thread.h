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

#ifndef CORE_RST_THREAD_H
#define CORE_RST_THREAD_H

class RustyThreadCallbackInterface;

class RustyThread
{
    private:
        HANDLE thread;
        unsigned long id;

        RustyThreadCallbackInterface *object;
        void *parameters;

        static DWORD WINAPI Run(void *rusty_thread);

    public:
        enum Priority
        {
            IDLE = THREAD_PRIORITY_IDLE,
            LOWEST = THREAD_PRIORITY_LOWEST,
            BELOW_NORMAL = THREAD_PRIORITY_BELOW_NORMAL,
            NORMAL = THREAD_PRIORITY_NORMAL,
            ABOVE_NORMAL = THREAD_PRIORITY_ABOVE_NORMAL,
            HIGHEST = THREAD_PRIORITY_HIGHEST,
            TIME_CRITICAL = THREAD_PRIORITY_TIME_CRITICAL
        };

        RustyThread(const RustyThread &) = delete;
        RustyThread & operator=(const RustyThread &) = delete;

        RustyThread(RustyThreadCallbackInterface *object, void *parameters, Priority priority);
        unsigned long GetId(void);
        void SetPriority(Priority priority);
        static void SetBackground(bool background);
        ~RustyThread(void);
};

class RustyThreadCallbackInterface
{
    public:
        RustyThreadCallbackInterface() = default;
        RustyThreadCallbackInterface(const RustyThreadCallbackInterface &) = delete;
        RustyThreadCallbackInterface & operator=(const RustyThreadCallbackInterface &) = delete;

        virtual DWORD DoSync(void *lpParameter) = 0;
        virtual ~RustyThreadCallbackInterface(void) {}
};

#endif
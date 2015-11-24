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
#include "thread.h"

rusty::core::Thread::Thread(CallbackInterface &callback, Priority priority)
{
    thread = CreateThread(nullptr, 0u, ThreadProc, &callback, 0u, &id);
    assert(thread != NULL);

    switch(priority)
    {
        case NORMAL:
            break;
        default:
            ASSERT_METHOD(SetThreadPriority(thread, priority), != , 0);
    }
}

unsigned long __stdcall rusty::core::Thread::ThreadProc(void *callback)
{
    CallbackInterface *_callback = static_cast<CallbackInterface *>(callback);
    _callback->ThreadDo();
    return 0ul;
}

unsigned long rusty::core::Thread::GetId(void)
{
    return id;
}

void rusty::core::Thread::SetPriority(Priority priority)
{
    ASSERT_METHOD(SetThreadPriority(thread, static_cast<int>(priority)), != , 0);
}

void rusty::core::Thread::SetBackground(bool background)
{
    ASSERT_METHOD(SetThreadPriority(GetCurrentThread(), background ? THREAD_MODE_BACKGROUND_BEGIN : THREAD_MODE_BACKGROUND_END), != , 0);
}

rusty::core::Thread::~Thread(void)
{
    ASSERT_METHOD(WaitForSingleObject(thread, INFINITE), != , WAIT_FAILED);
    ASSERT_METHOD(CloseHandle(thread), != , 0);
}
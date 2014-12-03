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
#include "rst_thread.h"

RustyThread::RustyThread(RustyThreadCallbackInterface *object, void *parameters, Priority priority) : object(object), parameters(parameters)
{
    thread = CreateThread(nullptr, 0u, Run, this, 0u, &id);
    assert(thread != NULL);

    switch(priority)
    {
        case NORMAL:
            break;
        default:
            METHOD_ASSERT(SetThreadPriority(thread, priority), !=, 0);
    }
}

DWORD WINAPI RustyThread::Run(void *rusty_thread)
{
    RustyThread *_rusty_thread = static_cast<RustyThread *>(rusty_thread);
    return (_rusty_thread->object)->DoSync(_rusty_thread->parameters);
}

unsigned long RustyThread::GetId(void)
{
    return id;
}

void RustyThread::SetPriority(Priority priority)
{
    METHOD_ASSERT(SetThreadPriority(thread, priority), !=, 0);
}

void RustyThread::SetBackground(bool background)
{
    METHOD_ASSERT(SetThreadPriority(GetCurrentThread(), background ? THREAD_MODE_BACKGROUND_BEGIN : THREAD_MODE_BACKGROUND_END), !=, 0);
}

RustyThread::~RustyThread(void)
{
    METHOD_ASSERT(WaitForSingleObject(thread, INFINITE), !=, WAIT_FAILED);
    METHOD_ASSERT(CloseHandle(thread), !=, 0);
}
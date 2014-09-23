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
#include "rst_lock.h"

RustyLock::RustyLock(bool auto_lock_and_unlock) : auto_lock_and_unlock(auto_lock_and_unlock)
{
    InitializeCriticalSection(&lock);
    if(auto_lock_and_unlock)
        Lock();
}

void RustyLock::Lock()
{
    assert(!locked);
    if(!locked)
    {
        EnterCriticalSection(&lock);
        locked = true;
    }
}

void RustyLock::Unlock()
{
    assert(locked);
    if(locked)
    {
        LeaveCriticalSection(&lock);
        locked = false;
    }
}

RustyLock::~RustyLock()
{
    if(!auto_lock_and_unlock)
        Unlock();
    DeleteCriticalSection(&lock);
}

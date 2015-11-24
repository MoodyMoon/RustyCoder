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
#include "critical_section.h"

rusty::core::CriticalSection::CriticalSection()
{
    InitializeCriticalSection(&lock);
}

void rusty::core::CriticalSection::Lock()
{
    EnterCriticalSection(&lock);
}

void rusty::core::CriticalSection::Unlock()
{
    LeaveCriticalSection(&lock);
}

rusty::core::CriticalSection::~CriticalSection()
{
    DeleteCriticalSection(&lock);
}

rusty::core::ManagedCriticalSection::ManagedCriticalSection(CriticalSection &critical_section) : critical_section(&critical_section)
{
    critical_section.Lock();
}

rusty::core::ManagedCriticalSection::~ManagedCriticalSection()
{
    critical_section->Unlock();
}
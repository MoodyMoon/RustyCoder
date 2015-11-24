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

#ifndef CORE_CRITICAL_SECTION_H
#define CORE_CRITICAL_SECTION_H

namespace rusty
{
namespace core
{
/*!
Windows synchronization objects do not ensure threads FIFO behaviour
*/
class CriticalSection
{
    private:
        CRITICAL_SECTION lock;

    public:
        CriticalSection(const CriticalSection &) = delete;
        CriticalSection & operator=(const CriticalSection &) = delete;

        CriticalSection(void);
        void Lock(void);
        void Unlock(void);
        ~CriticalSection(void);
};

class ManagedCriticalSection
{
    private:
        CriticalSection *critical_section;

    public:
        ManagedCriticalSection(const ManagedCriticalSection &) = delete;
        ManagedCriticalSection & operator=(const ManagedCriticalSection &) = delete;

        ManagedCriticalSection(CriticalSection &critical_section);
        ~ManagedCriticalSection(void);
};
}
}

#endif

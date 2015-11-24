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
#include "reader_writer_lock.h"

rusty::core::ReaderWriterLock::ReaderWriterLock()
{
    InitializeSRWLock(&lock);
}

void rusty::core::ReaderWriterLock::ExclusiveLock()
{
    AcquireSRWLockExclusive(&lock);
}

void rusty::core::ReaderWriterLock::ExclusiveUnlock()
{
    ReleaseSRWLockExclusive(&lock);
}

void rusty::core::ReaderWriterLock::SharedLock()
{
    AcquireSRWLockShared(&lock);
}

void rusty::core::ReaderWriterLock::SharedUnlock()
{
    ReleaseSRWLockShared(&lock);
}

rusty::core::ManagedExclusiveReaderWriterLock::ManagedExclusiveReaderWriterLock(ReaderWriterLock &lock) : lock(&lock)
{
    lock.ExclusiveLock();
}

rusty::core::ManagedExclusiveReaderWriterLock::~ManagedExclusiveReaderWriterLock()
{
    lock->ExclusiveUnlock();
}

rusty::core::ManagedSharedReaderWriterLock::ManagedSharedReaderWriterLock(ReaderWriterLock &lock) : lock(&lock)
{
    lock.SharedLock();
}

rusty::core::ManagedSharedReaderWriterLock::~ManagedSharedReaderWriterLock()
{
    lock->SharedUnlock();
}
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

#ifndef CORE_READER_WRITER_LOCK_H
#define CORE_READER_WRITER_LOCK_H

namespace rusty
{
namespace core
{
class ReaderWriterLock
{
    private:
        SRWLOCK lock;

    public:
        ReaderWriterLock(const ReaderWriterLock &) = delete;
        ReaderWriterLock & operator=(const ReaderWriterLock &) = delete;

        ReaderWriterLock(void);
        void ExclusiveLock(void);
        void ExclusiveUnlock(void);
        void SharedLock(void);
        void SharedUnlock(void);
};

class ManagedExclusiveReaderWriterLock
{
    private:
        ReaderWriterLock *lock;

    public:
        ManagedExclusiveReaderWriterLock(const ManagedExclusiveReaderWriterLock &) = delete;
        ManagedExclusiveReaderWriterLock & operator=(const ManagedExclusiveReaderWriterLock &) = delete;

        ManagedExclusiveReaderWriterLock(ReaderWriterLock &lock);
        ~ManagedExclusiveReaderWriterLock(void);
};

class ManagedSharedReaderWriterLock
{
    private:
        ReaderWriterLock *lock;

    public:
        ManagedSharedReaderWriterLock(const ManagedSharedReaderWriterLock &) = delete;
        ManagedSharedReaderWriterLock & operator=(const ManagedSharedReaderWriterLock &) = delete;

        ManagedSharedReaderWriterLock(ReaderWriterLock &lock);
        ~ManagedSharedReaderWriterLock(void);
};
}
}

#endif
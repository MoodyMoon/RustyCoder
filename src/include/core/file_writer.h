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

#ifndef CORE_FILE_WRITER_H
#define CORE_FILE_WRITER_H

#include "common.h"
#include "exception.h"
#include "windows_utilities.h"

namespace rusty
{
namespace core
{
/*!
A wrapper around Windows API. File size larger than 4GB is supported on x86 and x64 platforms.
*/
class FileWriter
{
    private:
        HANDLE file_handle = nullptr;

        uint32_t Write(const unsigned char *buffer, uint32_t valid_byte_count, bool throw_exception, bool *error);

    public:
        enum Access : unsigned long
        {
            EXCLUSIVE_WRITE = 0ul
        };

        enum Create : unsigned long
        {
            OVERWRITE = CREATE_ALWAYS,
            TRUNCATE = TRUNCATE_EXISTING,
            UNTOUCHED = OPEN_EXISTING
        };

        FileWriter(const FileWriter &) = delete;
        FileWriter & operator=(const FileWriter &) = delete;

        /*!
        Create a new file or overwrite the exisiting.
        \param[in] path   Input file path.
        \param[in] access Access exclusivity that restricts writes from other handles.
        \param[in] create Describe how a new file should be created.
        \throw WriteFileException
        */
        FileWriter(const boost::filesystem::path &path, Access access, Create create);

        /*!
        Get the offset relative to the start of the write position.
        \return offset relative to the start of the write position.
        \throw SeekException
        */
        uint64_t Tell(void);

        /*!
        Seek to \c position relative to \c offset.
        \param[in] position Refer to \ref SeekPosition.
        \param[in] offset   An offset relative to \c position.
        \return offset relative to the start of the write position.
        \throw SeekException
        */
        uint64_t Seek(SeekPosition position, int64_t offset);

        /*!
        Write some data to the file.
        \param[in] buffer           Valid data to be be written.
        \param[in] valid_byte_count Size of data to be written.
        \return Valid number of bytes written.
        \throw WriteFileException
        \note <tt>valid_byte_count == 0</tt> will not cause an exception to be thrown.
        */
        uint32_t Write(const unsigned char *buffer, uint32_t valid_byte_count);

        /*!
        Write some data to the file.
        \param[in] buffer           Valid data to be be written.
        \param[in] valid_byte_count Size of data to be written.
        \return Valid number of bytes written.
        \note <tt>valid_byte_count == 0</tt> will not cause an exception to be thrown.
        */
        uint32_t Write(const unsigned char *buffer, uint32_t valid_byte_count, bool &error);

        /*!
        Close the file.
        */
        ~FileWriter(void);
};
}
}

#endif
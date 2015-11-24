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

#ifndef CORE_FILE_READER_H
#define CORE_FILE_READER_H

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
class FileReader
{
    private:
        HANDLE file_handle = nullptr;

        uint64_t GetFileLength(bool throw_exception, bool *error);

        uint64_t Seek(SeekPosition position, int64_t offset, bool throw_exception, bool *error);

        uint32_t Read(unsigned char *buffer, uint32_t valid_byte_count, bool throw_exception, bool *error);

    public:
        enum class Access : unsigned long
        {
            EXCLUSIVE_READ = 0ul,
            SHARE_READ = FILE_SHARE_READ
        };

        enum Attribute : unsigned long
        {
            NONE = 0ul,
            RANDOM = FILE_FLAG_RANDOM_ACCESS,
            SEQUENTIAL = FILE_FLAG_SEQUENTIAL_SCAN
        };

        FileReader(const FileReader &) = delete;
        FileReader & operator=(const FileReader &) = delete;

        /*!
        Open an existing file.
        \param[in] path      Input file path.
        \param[in] access    Access exclusivity that restricts reads from other handles.
        \param[in] attribute Seeking behaviour that affects read performance.
        \throw ReadFileException
        */
        FileReader(const boost::filesystem::path &path, Access access, Attribute attribute);

        /*!
        Get the file size in bytes.
        \return file size in bytes
        \throw ReadFileException
        */
        uint64_t GetFileLength(void);

        /*!
        Get the file size in bytes.
        \param[out] error    Set if \c throw_exception is true and an error has occurred.
        \return file size in bytes
        */
        uint64_t GetFileLength(bool &error);

        /*!
        Get the offset relative to the start of the file.
        \return offset relative to the start of the file.
        \throw SeekException
        */
        uint64_t Tell(void);

        /*!
        Get the offset relative to the start of the file.
        \param[out] error            Set if \c throw_exception is true and an error has occurred.
        \return Offset relative to the start of the file.
        */
        uint64_t Tell(bool &error);

        /*!
        Seek to \c position relative to \c offset.
        \param[in] position Refer to \ref SeekPosition.
        \param[in] offset   An offset relative to \c position.
        \return Offset relative to the start of the file.
        \throw SeekException
        */
        uint64_t Seek(SeekPosition position, int64_t offset);

        /*!
        Seek to \c position relative to \c offset.
        \param[in]  position Refer to \ref SeekPosition.
        \param[in]  offset   An offset relative to \c position.
        \param[out] error    Set if \c throw_exception is true and an error has occurred.
        \return Offset relative to the start of the file.
        */
        uint64_t Seek(SeekPosition position, int64_t offset, bool &error);

        /*!
        Read some data on the file.
        \param[out] buffer           Valid data read will be filled here. This can be \c nullptr if <tt>valid_byte_count == 0u</tt>.
        \param[in]  valid_byte_count Size of data to be read. This can be 0.
        \return Valid number of bytes read.
        \throw ReadFileException
        \note End-of-file will not cause an exception to be thrown.
        */
        uint32_t Read(unsigned char *buffer, uint32_t valid_byte_count);

        /*!
        Read some data on the file.
        \param[out] buffer           Valid data read will be filled here. This can be \c nullptr if <tt>valid_byte_count == 0u</tt>.
        \param[in]  valid_byte_count Size of data to be read. This can be 0.
        \param[out] error            Set if \c throw_exception is true and an error has occurred.
        \return Valid number of bytes read.
        \note End-of-file will not cause an exception to be thrown.
        */
        uint32_t Read(unsigned char *buffer, uint32_t valid_byte_count, bool &error);

        /*!
        Close the file handle.
        */
        ~FileReader(void);
};
}
}

#endif
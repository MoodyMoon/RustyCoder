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

#ifndef CORE_FILE_READER_H
#define CORE_FILE_READER_H

#include <fstream>

/*!
A wrapper around STL ifstream. File size larger than 4GB is supported in both x86 and x64 build using MSVC
*/
class FileReader
{
    private:
        std::string file_path;
        std::ifstream ifs;
        uint64_t file_size;

    public:
        FileReader(const FileReader &) = delete;
        FileReader & operator=(const FileReader &) = delete;

        /*!
        Open an existing file.
        \param[in] file        Input file path.
        \param[in] seek_to_end Insert the pointer to the end of the file instead of the start.
        \throw ReadFileException
        \throw SeekException
        */
        FileReader(const char * const file, bool seek_to_end);
        
        /*!
        Get the file size in bytes.
        */
        uint64_t GetFileLength(void) const noexcept;
        
        /*!
        Seek to \c position relative to \c offset.
        \param[in] position Refer to \ref SeekPosition.
        \param[in] offset   An offset relative to \c position.
        \return offset relative to the start of the file.
        \throw SeekException
        */
        uint64_t Seek(SeekPosition position, int64_t offset);
        
        /*!
        Get the offset relative to the start of the file.
        \return offset relative to the start of the file.
        \throw SeekException
        */
        uint64_t Tell(void);
        
        /*!
        Read some data on the file.
        \param[out] buffer           Valid data read will be filled here.
        \param[in]  valid_byte_count Size of data to be read.
        \return Valid number of bytes read.
        \throw ReadFileException
        \note <tt>read_count == 0</tt> will not cause an exception to be thrown.
        \note End-of-file will cause an exception to be thrown.
        */
        uint32_t Read(char *buffer, uint32_t valid_byte_count);

        /*!
        Close the file.
        */
        ~FileReader(void);
};

#endif
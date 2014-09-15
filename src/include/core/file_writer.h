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

#ifndef CORE_FILE_WRITER_H
#define CORE_FILE_WRITER_H

#include <fstream>

/*!
A wrapper around STL ifstream. File size larger than 4GB is supported in both x86 and x64 build using MSVC
*/
class FileWriter
{
    private:
        std::ofstream ofs;
        uint64_t file_size;

    public:
        FileWriter(const FileWriter &) = delete;
        FileWriter & operator=(const FileWriter &) = delete;

        /*!
        Create a new file or overwrite the exisiting.
        \param[in] file        Input file path.
        \throw WriteFileException
        */
        FileWriter(const char * const file);
        
        /*!
        Seek to \c position relative to \c offset.
        \param[in] position Refer to \ref SeekPosition.
        \param[in] offset   An offset relative to \c position.
        \return offset relative to the start of the write position.
        \throw SeekException
        */
        uint64_t Seek(SeekPosition position, int64_t offset);
        
        /*!
        Get the offset relative to the start of the write position.
        \return offset relative to the start of the write position.
        \throw SeekException
        */
        uint64_t Tell(void);
        
        /*!
        Write some data to the file.
        \param[in] buffer       Valid data to be be written.
        \param[in]  write_count Size of data to be written.
        \return Valid number of bytes written.
        \throw WriteFileException
        \note <tt>write_count == 0</tt> will not cause an exception to be thrown.
        \note End-of-file will not cause an exception to be thrown.
        */
        void Write(const char * const buffer, uint32_t write_count);

        /*!
        Close the file.
        */
        ~FileWriter(void);
};

#endif
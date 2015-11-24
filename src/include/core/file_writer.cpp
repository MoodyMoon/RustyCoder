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
#include "file_writer.h"

rusty::core::FileWriter::FileWriter(const boost::filesystem::path &path, Access access, Create create)
{
    file_handle = CreateFile(path.wstring().c_str(), GENERIC_WRITE, static_cast<unsigned long>(access), nullptr, static_cast<unsigned long>(create), FILE_ATTRIBUTE_NORMAL, nullptr);

    if(file_handle == INVALID_HANDLE_VALUE)
    {
        unsigned int error_code = GetLastError();
        throw ReadFileException("FileWriter", error_code, WindowsUtilities::UTF8_Encode(WindowsUtilities::GetErrorMessage(error_code)).c_str());
    }
}

uint64_t rusty::core::FileWriter::Tell(void)
{
    return Seek(SeekPosition::CURRENT, 0ll);
}

uint64_t rusty::core::FileWriter::Seek(SeekPosition position, int64_t offset)
{
    LARGE_INTEGER seek_distance;
    seek_distance.QuadPart = offset;

    LARGE_INTEGER pointer_position;

    unsigned int _position;

    switch(position)
    {
        case SeekPosition::START:
            _position = FILE_BEGIN;
            if(offset < 0ll)
                throw SeekException("FileWriter", "Unable to seek to position less than 0."); //To prevent Windows from interpreting the offset as an unsigned value when \c FILE_BEGIN is specified.
            break;
        case SeekPosition::CURRENT:
            _position = FILE_CURRENT;
            break;
        case SeekPosition::END:
            _position = FILE_END;
            break;
        default:
            assert(false);
    }

    if(SetFilePointerEx(file_handle, seek_distance, &pointer_position, _position) == 0)
    {
        unsigned int error_code = GetLastError();
        throw SeekException("FileWriter", error_code, WindowsUtilities::UTF8_Encode(WindowsUtilities::GetErrorMessage(error_code)).c_str());
    }

    return pointer_position.QuadPart;
}

uint32_t rusty::core::FileWriter::Write(const unsigned char *buffer, uint32_t valid_byte_count)
{
    return Write(buffer, valid_byte_count, true, nullptr);
}

uint32_t rusty::core::FileWriter::Write(const unsigned char *buffer, uint32_t valid_byte_count, bool &error)
{
    return Write(buffer, valid_byte_count, false, &error);
}

uint32_t rusty::core::FileWriter::Write(const unsigned char *buffer, uint32_t valid_byte_count, bool throw_exception, bool *error)
{
    /* This 0 byte write check is to ensure nothing is written if <tt>valid_byte_count == 0</tt> is given. \c WriteFile handles this differently on different file systems. */
    if(valid_byte_count > 0u)
    {
        unsigned long bytes_written;

        if(WriteFile(file_handle, buffer, valid_byte_count, &bytes_written, nullptr) == FALSE)
        {
            if(throw_exception)
            {
                unsigned int error_code = GetLastError();
                throw WriteFileException("FileWriter", error_code, WindowsUtilities::UTF8_Encode(WindowsUtilities::GetErrorMessage(error_code)).c_str());
            }
            else
            {
                *error = true;
            }
        }
        else if(!throw_exception)
        {
            *error = false;
        }

        #ifdef _DEBUG
        if(!throw_exception && *error == false)
        {
            assert(bytes_written == valid_byte_count);
        }
        #endif

        return bytes_written;
    }
    else if(!throw_exception)
    {
        *error = false;
    }

    return 0ull;
}

rusty::core::FileWriter::~FileWriter()
{
    ASSERT_METHOD(CloseHandle(file_handle), != , 0);
}
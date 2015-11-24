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
#include "file_reader.h"

rusty::core::FileReader::FileReader(const boost::filesystem::path &path, Access access, Attribute attribute)
{
    file_handle = CreateFile(path.wstring().c_str(), GENERIC_READ, static_cast<unsigned long>(access), nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | static_cast<unsigned long>(attribute), nullptr);

    if(file_handle == INVALID_HANDLE_VALUE)
    {
        unsigned int error_code = GetLastError();
        throw ReadFileException("FileReader", error_code, WindowsUtilities::UTF8_Encode(WindowsUtilities::GetErrorMessage(error_code)).c_str());
    }
}

uint64_t rusty::core::FileReader::GetFileLength()
{
    return GetFileLength(true, nullptr);
}

uint64_t rusty::core::FileReader::GetFileLength(bool &error)
{
    return GetFileLength(false, &error);
}

uint64_t rusty::core::FileReader::GetFileLength(bool throw_exception, bool *error)
{
    LARGE_INTEGER file_size;

    if(GetFileSizeEx(file_handle, &file_size) == 0)
    {
        if(throw_exception)
        {
            unsigned int error_code = GetLastError();
            throw ReadFileException("FileReader", error_code, WindowsUtilities::UTF8_Encode(WindowsUtilities::GetErrorMessage(error_code)).c_str());
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

    if(throw_exception || *error == false)
        return file_size.QuadPart;
    else
        return 0ull;
}

uint64_t rusty::core::FileReader::Tell()
{
    return Seek(SeekPosition::CURRENT, 0ll, true, nullptr);
}

uint64_t rusty::core::FileReader::Tell(bool &error)
{
    return Seek(SeekPosition::CURRENT, 0ll, false, &error);
}

uint64_t rusty::core::FileReader::Seek(SeekPosition position, int64_t offset)
{
    return Seek(position, offset, true, nullptr);
}

uint64_t rusty::core::FileReader::Seek(SeekPosition position, int64_t offset, bool &error)
{
    return Seek(position, offset, false, &error);
}

uint64_t rusty::core::FileReader::Seek(SeekPosition position, int64_t offset, bool throw_exception, bool *error)
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
                throw SeekException("FileReader", "Unable to seek to position less than 0."); //To prevent Windows from interpreting the offset as an unsigned value when \c FILE_BEGIN is specified.
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
        if(throw_exception)
        {
            unsigned int error_code = GetLastError();
            throw SeekException("FileReader", error_code, WindowsUtilities::UTF8_Encode(WindowsUtilities::GetErrorMessage(error_code)).c_str());
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

    if(throw_exception || *error == false)
        return pointer_position.QuadPart;
    else
        return 0ull;
}

uint32_t rusty::core::FileReader::Read(unsigned char *buffer, uint32_t valid_byte_count)
{
    return Read(buffer, valid_byte_count, true, nullptr);
}

uint32_t rusty::core::FileReader::Read(unsigned char *buffer, uint32_t valid_byte_count, bool &error)
{
    return Read(buffer, valid_byte_count, false, &error);
}

uint32_t rusty::core::FileReader::Read(unsigned char *buffer, uint32_t valid_byte_count, bool throw_exception, bool *error)
{
    unsigned long bytes_read;

    if(ReadFile(file_handle, buffer, valid_byte_count, &bytes_read, nullptr) == FALSE)
    {
        if(throw_exception)
        {
            unsigned int error_code = GetLastError();
            throw ReadFileException("FileReader", error_code, WindowsUtilities::UTF8_Encode(WindowsUtilities::GetErrorMessage(error_code)).c_str());
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

    return bytes_read;
}

rusty::core::FileReader::~FileReader()
{
    ASSERT_METHOD(CloseHandle(file_handle), !=, 0);
}
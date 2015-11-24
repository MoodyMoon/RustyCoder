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
#include "sndfile.h"

sf_count_t rusty::codecs::SndFile::sf_vio_get_filelen(void *user_data)
{
    core::FileReader *file_reader = static_cast<core::FileReader *>(user_data);

    bool error;
    uint64_t file_length;

    file_length = file_reader->GetFileLength(error);

    if(error)
        return -1;
    else
        return file_length;
}

sf_count_t rusty::codecs::SndFile::sf_vio_seek(sf_count_t offset, int whence, void *user_data)
{
    core::FileReader *file_reader = static_cast<core::FileReader *>(user_data);

    bool error;
    uint64_t position;

    switch(whence)
    {
        case SEEK_SET:
            position = file_reader->Seek(core::SeekPosition::START, offset, error);
            break;
        case SEEK_CUR:
            position = file_reader->Seek(core::SeekPosition::CURRENT, offset, error);
            break;
        case SEEK_END:
            position = file_reader->Seek(core::SeekPosition::END, offset, error);
            break;
        default:
            assert(false);
    }

    if(error)
        return -1;
    else
        return position;
}

sf_count_t rusty::codecs::SndFile::sf_vio_read(void *ptr, sf_count_t count, void *user_data)
{
    core::FileReader *file_reader = static_cast<core::FileReader *>(user_data);

    bool error;
    uint64_t bytes_read;

    bytes_read = file_reader->Read(reinterpret_cast<unsigned char *>(ptr), count, error);

    if(error)
        return -1;
    else
        return bytes_read;
}

sf_count_t rusty::codecs::SndFile::sf_vio_write(const void *ptr, sf_count_t count, void *user_data)
{
    core::FileWriter *file_writer = static_cast<core::FileWriter *>(user_data);

    bool error;
    uint64_t bytes_written;

    bytes_written = file_writer->Write(reinterpret_cast<const unsigned char *>(ptr), count, error);

    if(error)
        return -1;
    else
        return bytes_written;
}

sf_count_t rusty::codecs::SndFile::sf_vio_tell(void *user_data)
{
    core::FileReader *file_reader = static_cast<core::FileReader *>(user_data);

    bool error;
    uint64_t position;

    position = file_reader->Tell(error);

    if(error)
        return -1;
    else
        return position;
}
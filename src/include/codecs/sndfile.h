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

#ifndef CODECS_SNDFILE_H
#define CODECS_SNDFILE_H

#include "../core/common.h"
#include "../core/file_reader.h"
#include "../core/file_writer.h"
#include "sndfile_decoder.h"
#include "sndfile_encoder.h"

namespace rusty
{
namespace codecs
{
class SndFile
{
    public:
        SndFile() = delete;
        SndFile(const SndFile &) = delete;
        SndFile & operator=(const SndFile &) = delete;

        static sf_count_t sf_vio_get_filelen(void *user_data);
        static sf_count_t sf_vio_seek(sf_count_t offset, int whence, void *user_data);
        static sf_count_t sf_vio_read(void *ptr, sf_count_t count, void *user_data);
        static sf_count_t sf_vio_write(const void *ptr, sf_count_t count, void *user_data);
        static sf_count_t sf_vio_tell(void *user_data);
};
}
}

#endif
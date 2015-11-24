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

#ifndef ENGINE_ENCODER_PROFILE_WRITER_H
#define ENGINE_ENCODER_PROFILE_WRITER_H

#include "../codecs/encoder.h"
#include "../codecs/lame_profile.h"
#include "../codecs/sndfile_encoder_profile.h"
#include "../core/file_writer.h"

namespace rusty
{
namespace engine
{
class EncoderProfileWriter
{
    private:
        void Write(core::FileWriter &file_writer, const int8_t &value);
        void Write(core::FileWriter &file_writer, const uint8_t &value);
        void Write(core::FileWriter &file_writer, const int16_t &value);
        void Write(core::FileWriter &file_writer, const uint16_t &value);
        void Write(core::FileWriter &file_writer, const int32_t &value);
        void Write(core::FileWriter &file_writer, const uint32_t &value);
        void Write(core::FileWriter &file_writer, const int64_t &value);
        void Write(core::FileWriter &file_writer, const uint64_t &value);
        void Write(core::FileWriter &file_writer, const float &value);
        void Write(core::FileWriter &file_writer, const double &value);
        void Write(core::FileWriter &file_writer, const bool &value);
        void Write(core::FileWriter &file_writer, const std::string &value);

        void Write(const codecs::LameProfile &profile, const boost::filesystem::path &profile_path);
        void Write(const codecs::SndFileEncoderProfile &profile, const boost::filesystem::path &profile_path);

    public:
        EncoderProfileWriter() = default;
        EncoderProfileWriter(const EncoderProfileWriter &) = delete;
        EncoderProfileWriter & operator=(const EncoderProfileWriter &) = delete;

        void WriteFile(const codecs::EncoderProfile &profile, codecs::Encoder<void>::ID encoder_id, const boost::filesystem::path &profile_path);
};
}
}

#endif
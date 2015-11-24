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

#ifndef ENGINE_ENCODER_PROFILE_READER_H
#define ENGINE_ENCODER_PROFILE_READER_H

#include "../codecs/common.h"
#include "../codecs/encoder.h"
#include "../codecs/encoder_profile.h"
#include "../codecs/lame_profile.h"
#include "../codecs/sndfile_encoder_profile.h"
#include "../core/common.h"
#include "../core/file_reader.h"

namespace rusty
{
namespace engine
{
class EncoderProfileReader
{
    private:
        boost::filesystem::path profile_path;

        codecs::Encoder<void>::ID encoder_id;
        std::shared_ptr<codecs::EncoderProfile> profile;

        void Rev1Deserialize(core::FileReader &file_reader, codecs::LameProfile &profile);
        void Rev1Deserialize(core::FileReader &file_reader, codecs::SndFileEncoderProfile &profile);
        void CorruptedFileThrow(const boost::filesystem::path &profile_path);

        void Read(core::FileReader &file_reader, int8_t &value);
        void Read(core::FileReader &file_reader, uint8_t &value);
        void Read(core::FileReader &file_reader, int16_t &value);
        void Read(core::FileReader &file_reader, uint16_t &value);
        void Read(core::FileReader &file_reader, int32_t &value);
        void Read(core::FileReader &file_reader, uint32_t &value);
        void Read(core::FileReader &file_reader, int64_t &value);
        void Read(core::FileReader &file_reader, uint64_t &value);
        void Read(core::FileReader &file_reader, float &value);
        void Read(core::FileReader &file_reader, double &value);
        void Read(core::FileReader &file_reader, bool &value);
        void Read(core::FileReader &file_reader, std::string &value);
        void Read(core::FileReader &file_reader, codecs::LameProfile &profile, uint32_t settings_specification_revision_number);
        void Read(core::FileReader &file_reader, codecs::SndFileEncoderProfile &profile, uint32_t settings_specification_revision_number);
        void Read(void);

    public:
        EncoderProfileReader(const EncoderProfileReader &) = delete;
        EncoderProfileReader & operator=(const EncoderProfileReader &) = delete;

        explicit EncoderProfileReader(const boost::filesystem::path &profile_path);

        void ReadFile(const boost::filesystem::path &profile_path);

        codecs::Encoder<void>::ID GetEncoderID(void) noexcept;

        std::shared_ptr<codecs::EncoderProfile> GetEncoderProfile(void) noexcept;
};
}
}

#endif
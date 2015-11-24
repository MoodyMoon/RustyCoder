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
#include "encoder_profile_writer.h"

void rusty::engine::EncoderProfileWriter::WriteFile(const codecs::EncoderProfile &profile, codecs::Encoder<void>::ID encoder_id, const boost::filesystem::path &profile_path)
{
    switch(encoder_id)
    {
        case codecs::Encoder<void>::ID::LAME:
        {
            const codecs::LameProfile *lame_profile = static_cast<const codecs::LameProfile *>(&profile);
            Write(*lame_profile, profile_path);
            break;
        }
        case codecs::Encoder<void>::ID::SNDFILE_ENCODER:
        {
            const codecs::SndFileEncoderProfile *sndfile_encoder_profile = static_cast<const codecs::SndFileEncoderProfile *>(&profile);
            Write(*sndfile_encoder_profile, profile_path);
            break;
        }
        default:
            assert(false);
    }
}

void rusty::engine::EncoderProfileWriter::Write(const codecs::LameProfile &profile, const boost::filesystem::path &profile_path)
{
    core::FileWriter file_writer(profile_path, core::FileWriter::Access::EXCLUSIVE_WRITE, core::FileWriter::Create::OVERWRITE);

    std::string magic("RUSTYCODER-LAME");

    {
        Write(file_writer, magic);
    }

    {
        uint32_t settings_specification_revision_number = 1u;
        Write(file_writer, settings_specification_revision_number);
    }

    {
        LAME_ALGORITHM_QUALITY_DATA_TYPE algorithm_quality = static_cast<LAME_ALGORITHM_QUALITY_DATA_TYPE>(profile.algorithm_quality);
        Write(file_writer, algorithm_quality);
    }

    {
        LAME_MODE_DATA_TYPE mode = static_cast<LAME_MODE_DATA_TYPE>(profile.mode);
        Write(file_writer, mode);
    }

    {
        LAME_REPLAYGAIN_DATA_TYPE replaygain_mode = static_cast<LAME_REPLAYGAIN_DATA_TYPE>(profile.replaygain_mode);
        Write(file_writer, replaygain_mode);
    }

    {
        Write(file_writer, profile.copyright);
    }

    {
        Write(file_writer, profile.use_naoki_psytune);
    }

    {
        LAME_BITRATE_ENCODING_DATA_TYPE bitrate_encoding = static_cast<LAME_BITRATE_ENCODING_DATA_TYPE>(profile.bitrate_encoding);
        Write(file_writer, bitrate_encoding);
    }

    {
        float vbr_quality = profile.GetVbrQuality();
        Write(file_writer, vbr_quality);
    }

    {
        LAME_BITRATE_DATA_TYPE min_or_max_bitrate1 = static_cast<LAME_BITRATE_DATA_TYPE>(profile.min_or_max_bitrate1);
        Write(file_writer, min_or_max_bitrate1);
    }

    {
        LAME_BITRATE_DATA_TYPE min_or_max_bitrate2 = static_cast<LAME_BITRATE_DATA_TYPE>(profile.min_or_max_bitrate2);
        Write(file_writer, min_or_max_bitrate2);
    }

    {
        Write(file_writer, magic);
    }
}

void rusty::engine::EncoderProfileWriter::Write(const codecs::SndFileEncoderProfile &profile, const boost::filesystem::path &profile_path)
{
    core::FileWriter file_writer(profile_path, core::FileWriter::Access::EXCLUSIVE_WRITE, core::FileWriter::Create::OVERWRITE);

    std::string magic("RUSTYCODER-SNDFILEENCODER");

    {
        Write(file_writer, magic);
    }

    {
        uint32_t settings_specification_revision_number = 1u;
        Write(file_writer, settings_specification_revision_number);
    }

    {
        SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE format = static_cast<uint32_t>(profile.output_format);
        Write(file_writer, format);
    }

    {
        Write(file_writer, magic);
    }
}

void rusty::engine::EncoderProfileWriter::Write(core::FileWriter &file_writer, const int8_t &value)
{
    file_writer.Write(reinterpret_cast<const unsigned char *>(&value), sizeof(value));
}

void rusty::engine::EncoderProfileWriter::Write(core::FileWriter &file_writer, const uint8_t &value)
{
    file_writer.Write(&value, sizeof(value));
}

void rusty::engine::EncoderProfileWriter::Write(core::FileWriter &file_writer, const int16_t &value)
{
    file_writer.Write(reinterpret_cast<const unsigned char *>(&value), sizeof(value));
}

void rusty::engine::EncoderProfileWriter::Write(core::FileWriter &file_writer, const uint16_t &value)
{
    file_writer.Write(reinterpret_cast<const unsigned char *>(&value), sizeof(value));
}

void rusty::engine::EncoderProfileWriter::Write(core::FileWriter &file_writer, const int32_t &value)
{
    file_writer.Write(reinterpret_cast<const unsigned char *>(&value), sizeof(value));
}

void rusty::engine::EncoderProfileWriter::Write(core::FileWriter &file_writer, const uint32_t &value)
{
    file_writer.Write(reinterpret_cast<const unsigned char *>(&value), sizeof(value));
}

void rusty::engine::EncoderProfileWriter::Write(core::FileWriter &file_writer, const int64_t &value)
{
    file_writer.Write(reinterpret_cast<const unsigned char *>(&value), sizeof(value));
}

void rusty::engine::EncoderProfileWriter::Write(core::FileWriter &file_writer, const uint64_t &value)
{
    file_writer.Write(reinterpret_cast<const unsigned char *>(&value), sizeof(value));
}

void rusty::engine::EncoderProfileWriter::Write(core::FileWriter &file_writer, const float &value)
{
    file_writer.Write(reinterpret_cast<const unsigned char *>(&value), sizeof(value));
}

void rusty::engine::EncoderProfileWriter::Write(core::FileWriter &file_writer, const double &value)
{
    file_writer.Write(reinterpret_cast<const unsigned char *>(&value), sizeof(value));
}

void rusty::engine::EncoderProfileWriter::Write(core::FileWriter &file_writer, const bool &value)
{
    uint8_t _value = value ? 1u : 0u;
    file_writer.Write(reinterpret_cast<const unsigned char *>(&_value), sizeof(_value));
}

void rusty::engine::EncoderProfileWriter::Write(core::FileWriter &file_writer, const std::string &value)
{
    size_t string_length = value.length();
    uint8_t data_type;

    if(string_length < std::numeric_limits<uint8_t>::max())
    {
        data_type = static_cast<uint8_t>(core::DataType::INT_U8);
        uint8_t _string_length = static_cast<uint8_t>(string_length);
        Write(file_writer, data_type);
        Write(file_writer, _string_length);
        file_writer.Write(reinterpret_cast<const unsigned char *>(value.c_str()), _string_length);
    }
    else if(string_length < std::numeric_limits<uint16_t>::max())
    {
        data_type = static_cast<uint8_t>(core::DataType::INT_U16);
        uint16_t _string_length = static_cast<uint16_t>(string_length);
        Write(file_writer, data_type);
        Write(file_writer, _string_length);
        file_writer.Write(reinterpret_cast<const unsigned char *>(value.c_str()), _string_length);
    }
    #ifdef _DEBUG
    else
    {
        assert(false);
    }
    #endif
}
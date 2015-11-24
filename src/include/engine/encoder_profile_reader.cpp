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
#include "encoder_profile_reader.h"

rusty::engine::EncoderProfileReader::EncoderProfileReader(const boost::filesystem::path &profile_path) : profile_path(profile_path)
{
    Read();
}

void rusty::engine::EncoderProfileReader::ReadFile(const boost::filesystem::path &profile_path)
{
    this->profile_path = profile_path;
    Read();
}

rusty::codecs::Encoder<void>::ID rusty::engine::EncoderProfileReader::GetEncoderID() noexcept
{
    return encoder_id;
}

std::shared_ptr<rusty::codecs::EncoderProfile> rusty::engine::EncoderProfileReader::GetEncoderProfile() noexcept
{
    return profile;
}

void rusty::engine::EncoderProfileReader::Read()
{
    core::FileReader file_reader(profile_path, core::FileReader::Access::SHARE_READ, core::FileReader::Attribute::SEQUENTIAL);

    const unsigned int valid_magics_count = 2u;

    codecs::Encoder<void>::ID encoder_ids[valid_magics_count] = {codecs::Encoder<void>::ID::LAME,
                                                                 codecs::Encoder<void>::ID::SNDFILE_ENCODER};
    std::string valid_magics[valid_magics_count] = {"RUSTYCODER-LAME",
                                                    "RUSTYCODER-SNDFILEENCODER"};
    std::string read_magic;
    uint8_t read_magic_data_type;

    file_reader.Read(&read_magic_data_type, 1);

    // First byte identifying the magic data type has to be an unsigned 8-bit int becuse the magic can't be longer than 256 characters.
    if(read_magic_data_type != static_cast<uint8_t>(core::DataType::INT_U8))
        CorruptedFileThrow(profile_path);
    else
    {
        file_reader.Seek(core::SeekPosition::START, 0);
        Read(file_reader, read_magic);

        codecs::Encoder<void>::ID encoder_id;

        unsigned int index = 0u;

        for(; index < valid_magics_count; ++index)
        {
            if(read_magic == valid_magics[index])
            {
                encoder_id = encoder_ids[index];
                break;
            }
        }

        if(index == valid_magics_count)
            CorruptedFileThrow(profile_path);
        else
        {
            uint32_t settings_specification_revision_number;
            Read(file_reader, settings_specification_revision_number);

            switch(encoder_id)
            {
                case codecs::Encoder<void>::ID::LAME:
                {
                    profile.reset(new codecs::LameProfile());
                    codecs::LameProfile *lame_profile;
                    lame_profile = static_cast<codecs::LameProfile *>(profile.get());
                    Read(file_reader, *lame_profile, settings_specification_revision_number);
                    break;
                }
                case codecs::Encoder<void>::ID::SNDFILE_ENCODER:
                {
                    profile.reset(new codecs::SndFileEncoderProfile());
                    codecs::SndFileEncoderProfile *sndfile_encoder_profile;
                    sndfile_encoder_profile = static_cast<codecs::SndFileEncoderProfile *>(profile.get());
                    Read(file_reader, *sndfile_encoder_profile, settings_specification_revision_number);
                    break;
                }
                default:
                    assert(false);
            }
        }
    }
}

void rusty::engine::EncoderProfileReader::Read(core::FileReader &file_reader, codecs::LameProfile &profile, uint32_t settings_specification_revision_number)
{
    switch(settings_specification_revision_number)
    {
        case 1u:
            Rev1Deserialize(file_reader, profile);
            encoder_id = codecs::Encoder<void>::ID::LAME;
            break;
        default:
        {
            this->profile.reset();
            std::string error_message("Settings version of \"");
            error_message.append(profile_path.string());
            error_message.append("\" is not supported. It is usually caused by older versions of RustyCoder opening newer versions of preference files.");
            throw core::ReadFileException("EncoderProfileReader", error_message.c_str());
        }
    }
}

void rusty::engine::EncoderProfileReader::Read(core::FileReader &file_reader, codecs::SndFileEncoderProfile &profile, uint32_t settings_specification_revision_number)
{
    switch(settings_specification_revision_number)
    {
        case 1u:
            Rev1Deserialize(file_reader, profile);
            encoder_id = codecs::Encoder<void>::ID::SNDFILE_ENCODER;
            break;
        default:
        {
            this->profile.reset();
            std::string error_message("Settings version of \"");
            error_message.append(profile_path.string());
            error_message.append("\" is not supported. It is usually caused by older versions of RustyCoder opening newer versions of preference files.");
            throw core::ReadFileException("EncoderProfileReader", error_message.c_str());
        }
    }
}

void rusty::engine::EncoderProfileReader::Rev1Deserialize(core::FileReader &file_reader, codecs::LameProfile &profile)
{
    {
        LAME_ALGORITHM_QUALITY_DATA_TYPE algorithm_quality;
        Read(file_reader, algorithm_quality);

        profile.SetAlgorithmQuality(algorithm_quality);
    }

    {
        LAME_MODE_DATA_TYPE mode;
        Read(file_reader, mode);

        profile.SetMode(mode);
    }

    {
        LAME_REPLAYGAIN_DATA_TYPE replaygain_mode;
        Read(file_reader, replaygain_mode);

        profile.SetReplayGainMode(replaygain_mode);
    }

    {
        bool copyright;
        Read(file_reader, copyright);

        profile.SetCopyright(copyright);
    }

    {
        bool use_naoki_psytune;
        Read(file_reader, use_naoki_psytune);

        profile.SetUseNaokiPsytune(use_naoki_psytune);
    }

    {
        LAME_BITRATE_ENCODING_DATA_TYPE bitrate_encoding;
        Read(file_reader, bitrate_encoding);

        profile.SetBitrateEncoding(bitrate_encoding);
    }

    {
        float vbr_quality;
        Read(file_reader, vbr_quality);

        profile.SetVbrQuality(vbr_quality);
    }

    {
        LAME_BITRATE_DATA_TYPE min_or_max_bitrate1;
        Read(file_reader, min_or_max_bitrate1);

        profile.SetMinOrMaxBitrate1(min_or_max_bitrate1);
    }

    {
        LAME_BITRATE_DATA_TYPE min_or_max_bitrate2;
        Read(file_reader, min_or_max_bitrate2);

        profile.SetMinOrMaxBitrate2(min_or_max_bitrate2);
    }
}

void rusty::engine::EncoderProfileReader::Rev1Deserialize(core::FileReader &file_reader, codecs::SndFileEncoderProfile &profile)
{
    {
        SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE format;
        Read(file_reader, format);

        profile.SetOutputFormat(format);
    }
}

void rusty::engine::EncoderProfileReader::CorruptedFileThrow(const boost::filesystem::path &preference_path)
{
    std::string error_message("Corrupted profile in \"");
    error_message.append(preference_path.string());
    error_message.append("\".");
    throw core::ReadFileException("EncoderProfileReader", error_message.c_str());
}

void rusty::engine::EncoderProfileReader::Read(core::FileReader &file_reader, int8_t &value)
{
    file_reader.Read(reinterpret_cast<unsigned char *>(&value), sizeof(value));
}

void rusty::engine::EncoderProfileReader::Read(core::FileReader &file_reader, uint8_t &value)
{
    file_reader.Read(&value, sizeof(value));
}

void rusty::engine::EncoderProfileReader::Read(core::FileReader &file_reader, int16_t &value)
{
    file_reader.Read(reinterpret_cast<unsigned char *>(&value), sizeof(value));
}

void rusty::engine::EncoderProfileReader::Read(core::FileReader &file_reader, uint16_t &value)
{
    file_reader.Read(reinterpret_cast<unsigned char *>(&value), sizeof(value));
}

void rusty::engine::EncoderProfileReader::Read(core::FileReader &file_reader, int32_t &value)
{
    file_reader.Read(reinterpret_cast<unsigned char *>(&value), sizeof(value));
}

void rusty::engine::EncoderProfileReader::Read(core::FileReader &file_reader, uint32_t &value)
{
    file_reader.Read(reinterpret_cast<unsigned char *>(&value), sizeof(value));
}

void rusty::engine::EncoderProfileReader::Read(core::FileReader &file_reader, int64_t &value)
{
    file_reader.Read(reinterpret_cast<unsigned char *>(&value), sizeof(value));
}

void rusty::engine::EncoderProfileReader::Read(core::FileReader &file_reader, uint64_t &value)
{
    file_reader.Read(reinterpret_cast<unsigned char *>(&value), sizeof(value));
}

void rusty::engine::EncoderProfileReader::Read(core::FileReader &file_reader, float &value)
{
    file_reader.Read(reinterpret_cast<unsigned char *>(&value), sizeof(value));
}

void rusty::engine::EncoderProfileReader::Read(core::FileReader &file_reader, double &value)
{
    file_reader.Read(reinterpret_cast<unsigned char *>(&value), sizeof(value));
}

void rusty::engine::EncoderProfileReader::Read(core::FileReader &file_reader, bool &value)
{
    uint8_t int_bool;
    Read(file_reader, int_bool);
    if(int_bool == 0u)
        value = false;
    else if(int_bool == 1u)
        value = true;
    else
    {
        std::string error_message("Invalid boolean value in \"");
        error_message.append(profile_path.string());
        error_message.append("\".");
        throw core::ReadFileException("EncoderProfileReader", error_message.c_str());
    }
}

void rusty::engine::EncoderProfileReader::Read(core::FileReader &file_reader, std::string &value)
{
    uint8_t data_type;
    Read(file_reader, data_type);

    switch(data_type)
    {
        case static_cast<uint8_t>(core::DataType::INT_U8):
        {
            uint8_t string_size;
            Read(file_reader, string_size);
            std::unique_ptr<unsigned char> string(new unsigned char[string_size + 1]);
            file_reader.Read(string.get(), string_size);
            (string.get())[string_size] = '\0';
            value = reinterpret_cast<char *>(string.get());
            break;
        }
        case static_cast<uint8_t>(core::DataType::INT_U16):
        {
            uint16_t string_size;
            Read(file_reader, string_size);
            std::unique_ptr<unsigned char> string(new unsigned char[string_size + 1]);
            file_reader.Read(string.get(), string_size);
            (string.get())[string_size] = '\0';
            value = reinterpret_cast<char *>(string.get());
            break;
        }
        default:
        {
            std::string error_message("Invalid string length in \"");
            error_message.append(profile_path.string());
            error_message.append("\".");
            throw core::ReadFileException("EncoderProfileReader", error_message.c_str());
        }
    }
}
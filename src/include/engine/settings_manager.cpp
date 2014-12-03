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

#include "stdafx.h"
#include "settings_manager.h"

void SettingsManager::Read(LameOptions &profile, std::string file_path)
{
    FileReader reader(file_path.c_str(), false);

    std::string valid_magic("RUSTYCODER-LAME");
    std::string read_magic;

    {
        Read(reader, read_magic, file_path);
        if(read_magic != valid_magic)
            CorruptedFileThrow(file_path);
    }

    {
        uint32_t settings_specification_revision_number;
        Read(reader, settings_specification_revision_number);

        switch(settings_specification_revision_number)
        {
            case 1u:
                Rev1Read(profile, reader, file_path);
                break;
            default:
            {
                std::string error_message("Settings version of \"");
                error_message.append(file_path);
                error_message.append("\" is not supported. It is usually caused by older versions of RustyCoder opening newer versions of settings files.");
                throw ReadFileException("SettingsManager", error_message.c_str());
            }
        }
    }

    {
        Read(reader, read_magic, file_path);
        if(read_magic != valid_magic)
            CorruptedFileThrow(file_path);
    }
}

void SettingsManager::Read(SndFileEncoderOptions &profile, std::string file_path)
{
    FileReader reader(file_path.c_str(), false);

    std::string valid_magic("RUSTYCODER-SNDFILEENCODER");
    std::string read_magic;

    {
        Read(reader, read_magic, file_path);
        if(read_magic != valid_magic)
            CorruptedFileThrow(file_path);
    }

    {
        uint32_t settings_specification_revision_number;
        Read(reader, settings_specification_revision_number);

        switch(settings_specification_revision_number)
        {
            case 1u:
                Rev1Read(profile, reader, file_path);
                break;
            default:
            {
                std::string error_message("Settings version of \"");
                error_message.append(file_path);
                error_message.append("\" is not supported. It is usually caused by older versions of RustyCoder opening newer versions of settings files.");
                throw ReadFileException("SettingsManager", error_message.c_str());
            }
        }
    }

    {
        Read(reader, read_magic, file_path);
        if(read_magic != valid_magic)
            CorruptedFileThrow(file_path);
    }
}

void SettingsManager::Rev1Read(LameOptions &profile, FileReader &reader, std::string &file_path)
{
    {
        uint8_t algorithm_quality;
        Read(reader, algorithm_quality);

        if(!profile.SetAlgorithmQuality(algorithm_quality))
            CorruptedFileThrow(file_path);
    }

    {
        uint8_t mode;
        Read(reader, mode);

        if(!profile.SetMode(mode))
            CorruptedFileThrow(file_path);
    }

    {
        uint8_t replaygain_mode;
        Read(reader, replaygain_mode);

        if(!profile.SetReplayGainMode(replaygain_mode))
            CorruptedFileThrow(file_path);
    }

    {
        bool copyright;
        Read(reader, copyright, file_path);

        profile.SetCopyright(copyright);
    }

    {
        bool use_naoki_psytune;
        Read(reader, use_naoki_psytune, file_path);

        profile.SetUseNaokiPsytune(use_naoki_psytune);
    }

    {
        uint8_t bitrate_encoding;
        Read(reader, bitrate_encoding);

        if(!profile.SetBitrateEncoding(bitrate_encoding))
            CorruptedFileThrow(file_path);
    }

    {
        float vbr_quality;
        Read(reader, vbr_quality);

        if(!profile.SetVbrQuality(vbr_quality))
            CorruptedFileThrow(file_path);
    }

    {
        uint16_t min_or_max_bitrate1;
        Read(reader, min_or_max_bitrate1);

        if(!profile.SetMinOrMaxBitrate1(min_or_max_bitrate1))
            CorruptedFileThrow(file_path);
    }

    {
        uint16_t min_or_max_bitrate2;
        Read(reader, min_or_max_bitrate2);

        if(!profile.SetMinOrMaxBitrate2(min_or_max_bitrate2))
            CorruptedFileThrow(file_path);
    }
}

void SettingsManager::Rev1Read(SndFileEncoderOptions &profile, FileReader &reader, std::string &file_path)
{
    {
        uint32_t format;
        Read(reader, format);

        if(!profile.SetOutputFormat(format))
            CorruptedFileThrow(file_path);
    }
}

void SettingsManager::Write(const LameOptions &profile, std::string file_path)
{
    FileWriter writer(file_path.c_str());

    std::string magic("RUSTYCODER-LAME");

    {
        Write(writer, magic);
    }

    {
        uint32_t settings_specification_revision_number = 1u;
        Write(writer, settings_specification_revision_number);
    }

    {
        uint8_t algorithm_quality = static_cast<uint8_t>(profile.algorithm_quality);
        Write(writer, algorithm_quality);
    }

    {
        uint8_t mode = static_cast<uint8_t>(profile.mode);
        Write(writer, mode);
    }

    {
        uint8_t replaygain_mode = static_cast<uint8_t>(profile.replaygain_mode);
        Write(writer, replaygain_mode);
    }

    {
        Write(writer, profile.copyright);
    }

    {
        Write(writer, profile.use_naoki_psytune);
    }

    {
        uint8_t bitrate_encoding = static_cast<uint8_t>(profile.bitrate_encoding);
        Write(writer, bitrate_encoding);
    }

    {
        float vbr_quality = profile.vbr_quality;
        Write(writer, vbr_quality);
    }

    {
        uint16_t min_or_max_bitrate1 = static_cast<uint16_t>(profile.min_or_max_bitrate1);
        Write(writer, min_or_max_bitrate1);
    }

    {
        uint16_t min_or_max_bitrate2 = static_cast<uint16_t>(profile.min_or_max_bitrate2);
        Write(writer, min_or_max_bitrate2);
    }

    {
        Write(writer, magic);
    }
}

void SettingsManager::Write(const SndFileEncoderOptions &profile, std::string file_path)
{
    //Check ALL options for invalid values before ANY writing

    FileWriter writer(file_path.c_str());

    std::string magic("RUSTYCODER-SNDFILEENCODER");

    {
        Write(writer, magic);
    }

    {
        uint32_t settings_specification_revision_number = 1u;
        Write(writer, settings_specification_revision_number);
    }

    {
        uint32_t format = static_cast<uint32_t>(profile.output_format);
        Write(writer, format);
    }

    {
        Write(writer, magic);
    }
}

void SettingsManager::CorruptedFileThrow(std::string &file_path)
{
    std::string error_message("Corrupted profile in \"");
    error_message.append(file_path);
    error_message.append("\".");
    throw ReadFileException("SettingsManager", error_message.c_str());
}

void SettingsManager::Read(FileReader &reader, int8_t &value)
{
    reader.Read(reinterpret_cast<char *>(&value), sizeof(value));
}

void SettingsManager::Read(FileReader &reader, uint8_t &value)
{
    reader.Read(reinterpret_cast<char *>(&value), sizeof(value));
}

void SettingsManager::Read(FileReader &reader, int16_t &value)
{
    reader.Read(reinterpret_cast<char *>(&value), sizeof(value));
}

void SettingsManager::Read(FileReader &reader, uint16_t &value)
{
    reader.Read(reinterpret_cast<char *>(&value), sizeof(value));
}

void SettingsManager::Read(FileReader &reader, int32_t &value)
{
    reader.Read(reinterpret_cast<char *>(&value), sizeof(value));
}

void SettingsManager::Read(FileReader &reader, uint32_t &value)
{
    reader.Read(reinterpret_cast<char *>(&value), sizeof(value));
}

void SettingsManager::Read(FileReader &reader, int64_t &value)
{
    reader.Read(reinterpret_cast<char *>(&value), sizeof(value));
}

void SettingsManager::Read(FileReader &reader, uint64_t &value)
{
    reader.Read(reinterpret_cast<char *>(&value), sizeof(value));
}

void SettingsManager::Read(FileReader &reader, float &value)
{
    reader.Read(reinterpret_cast<char *>(&value), sizeof(value));
}

void SettingsManager::Read(FileReader &reader, double &value)
{
    reader.Read(reinterpret_cast<char *>(&value), sizeof(value));
}

void SettingsManager::Read(FileReader &reader, bool &value, std::string &file_path)
{
    uint8_t temp;
    Read(reader, temp);
    if(temp == 0u)
        value = false;
    else if(temp == 1u)
        value = true;
    else
    {
        std::string error_message("Invalid boolean value in \"");
        error_message.append(file_path);
        error_message.append("\".");
        throw ReadFileException("SettingsManager", error_message.c_str());
    }
}

void SettingsManager::Read(FileReader &reader, std::string &value, std::string &file_path)
{
    uint8_t data_type_identifier;
    Read(reader, data_type_identifier);

    switch(data_type_identifier)
    {
        case DataTypeIdentifier::INT_U8:
        {
            uint8_t string_size;
            Read(reader, string_size);
            std::unique_ptr<char> string(new char[string_size + 1]);
            reader.Read(string.get(), string_size);
            (string.get())[string_size] = '\0';
            value = string.get();
            break;
        }
        case DataTypeIdentifier::INT_U16:
        {
            uint16_t string_size;
            Read(reader, string_size);
            std::unique_ptr<char> string(new char[string_size + 1]);
            reader.Read(string.get(), string_size);
            (string.get())[string_size] = '\0';
            value = string.get();
            break;
        }
        default:
        {
            std::string error_message("Invalid string length in \"");
            error_message.append(file_path);
            error_message.append("\".");
            throw ReadFileException("SettingsManager", error_message.c_str());
        }
    }
}

void SettingsManager::Write(FileWriter &writer, const int8_t &value)
{
    writer.Write(reinterpret_cast<const char *>(&value), sizeof(value));
}

void SettingsManager::Write(FileWriter &writer, const uint8_t &value)
{
    writer.Write(reinterpret_cast<const char *>(&value), sizeof(value));
}

void SettingsManager::Write(FileWriter &writer, const int16_t &value)
{
    writer.Write(reinterpret_cast<const char *>(&value), sizeof(value));
}

void SettingsManager::Write(FileWriter &writer, const uint16_t &value)
{
    writer.Write(reinterpret_cast<const char *>(&value), sizeof(value));
}

void SettingsManager::Write(FileWriter &writer, const int32_t &value)
{
    writer.Write(reinterpret_cast<const char *>(&value), sizeof(value));
}

void SettingsManager::Write(FileWriter &writer, const uint32_t &value)
{
    writer.Write(reinterpret_cast<const char *>(&value), sizeof(value));
}

void SettingsManager::Write(FileWriter &writer, const int64_t &value)
{
    writer.Write(reinterpret_cast<const char *>(&value), sizeof(value));
}

void SettingsManager::Write(FileWriter &writer, const uint64_t &value)
{
    writer.Write(reinterpret_cast<const char *>(&value), sizeof(value));
}

void SettingsManager::Write(FileWriter &writer, const float &value)
{
    writer.Write(reinterpret_cast<const char *>(&value), sizeof(value));
}

void SettingsManager::Write(FileWriter &writer, const double &value)
{
    writer.Write(reinterpret_cast<const char *>(&value), sizeof(value));
}

void SettingsManager::Write(FileWriter &writer, const bool &value)
{
    uint8_t _value = value ? 1u : 0u;
    writer.Write(reinterpret_cast<const char *>(&_value), sizeof(_value));
}

void SettingsManager::Write(FileWriter &writer, const std::string &value)
{
    size_t string_length = value.length();
    if(string_length < std::numeric_limits<uint8_t>::max())
    {
        uint8_t data_type_identifier = DataTypeIdentifier::INT_U8;
        uint8_t _string_length = static_cast<uint8_t>(string_length);
        Write(writer, data_type_identifier);
        Write(writer, _string_length);
        writer.Write(value.c_str(), _string_length);
    }
    else if(string_length < std::numeric_limits<uint16_t>::max())
    {
        uint16_t data_type_identifier = DataTypeIdentifier::INT_U16;
        uint16_t _string_length = static_cast<uint16_t>(string_length);
        Write(writer, data_type_identifier);
        Write(writer, _string_length);
        writer.Write(value.c_str(), _string_length);
    }
}
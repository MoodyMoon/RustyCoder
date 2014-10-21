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

template<>
void SettingsManager<LameOptions>::Read(std::string file_path)
{
    this->input_file_path = file_path;
    FileReader reader(file_path.c_str(), false);

    std::string valid_magic("RUSTYCODER-LAME");
    std::string read_magic;

    {
        Read(reader, read_magic);
        if(!IsEqual(read_magic, valid_magic))
            CorruptedFileThrow();
    }
    
    {
        uint32_t settings_specification_revision_number;
        Read(reader, settings_specification_revision_number);

        switch(settings_specification_revision_number)
        {
            case 1u:
                Rev1Read(reader);
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
        Read(reader, read_magic);
        if(!IsEqual(read_magic, valid_magic))
            CorruptedFileThrow();
    }
}

template<>
void SettingsManager<SndFileEncoderOptions>::Read(std::string file_path)
{
    this->input_file_path = file_path;
    FileReader reader(file_path.c_str(), false);

    std::string valid_magic("RUSTYCODER-SNDFILEENCODER");
    std::string read_magic;

    {
        Read(reader, read_magic);
        if(!IsEqual(read_magic, valid_magic))
            CorruptedFileThrow();
    }

    {
        uint32_t settings_specification_revision_number;
        Read(reader, settings_specification_revision_number);

        switch(settings_specification_revision_number)
        {
            case 1u:
                Rev1Read(reader);
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
        Read(reader, read_magic);
        if(!IsEqual(read_magic, valid_magic))
            CorruptedFileThrow();
    }
}

template<>
void SettingsManager<LameOptions>::Rev1Read(FileReader &reader)
{
    {
        const size_t array_size = 10;
        uint8_t valid_algorithm_qualities[array_size] = {
        LameOptions::AlgorithmQuality::Q0,
        LameOptions::AlgorithmQuality::Q1,
        LameOptions::AlgorithmQuality::Q2,
        LameOptions::AlgorithmQuality::Q3,
        LameOptions::AlgorithmQuality::Q4,
        LameOptions::AlgorithmQuality::Q5,
        LameOptions::AlgorithmQuality::Q6,
        LameOptions::AlgorithmQuality::Q7,
        LameOptions::AlgorithmQuality::Q8,
        LameOptions::AlgorithmQuality::Q9};

        uint8_t algorithm_quality;
        Read(reader, algorithm_quality);

        size_t element_position = HasElement(algorithm_quality, valid_algorithm_qualities, array_size);

        if(element_position != 0)
            profile.algorithm_quality = static_cast<LameOptions::AlgorithmQuality>(valid_algorithm_qualities[element_position - 1u]);
        else
            CorruptedFileThrow();
    }
    
    {
        const size_t array_size = 3;
        uint8_t valid_modes[array_size] = {
        LameOptions::Mode::STEREO,
        LameOptions::Mode::JOINT_STEREO,
        LameOptions::Mode::MONO};

        uint8_t mode;
        Read(reader, mode);

        size_t element_position = HasElement(mode, valid_modes, array_size);

        if(element_position != 0)
            profile.mode = static_cast<LameOptions::Mode>(valid_modes[element_position - 1u]);
        else
            CorruptedFileThrow();
    }

    {
        const size_t array_size = 3;
        uint8_t valid_replaygain_modes[array_size] = {
        LameOptions::ReplayGain::NONE,
        LameOptions::ReplayGain::FAST,
        LameOptions::ReplayGain::ACCURATE};

        uint8_t replaygain_mode;
        Read(reader, replaygain_mode);

        size_t element_position = HasElement(replaygain_mode, valid_replaygain_modes, array_size);

        if(element_position != 0)
            profile.replaygain_mode = static_cast<LameOptions::ReplayGain>(valid_replaygain_modes[element_position - 1u]);
        else
            CorruptedFileThrow();
    }
    
    {
        Read(reader, profile.copyright);
    }
    
    {
        Read(reader, profile.use_naoki_psytune);
    }

    {
        const size_t array_size = 4;
        uint8_t valid_bitrate_encodings[array_size] = {
        LameOptions::BitrateEncoding::CONSTANT,
        LameOptions::BitrateEncoding::VARIABLE_OLD,
        LameOptions::BitrateEncoding::VARIABLE_NEW,
        LameOptions::BitrateEncoding::AVERAGE};

        uint8_t bitrate_encoding;
        Read(reader, bitrate_encoding);

        size_t element_position = HasElement(bitrate_encoding, valid_bitrate_encodings, array_size);

        if(element_position != 0)
            profile.bitrate_encoding = static_cast<LameOptions::BitrateEncoding>(valid_bitrate_encodings[element_position - 1u]);
        else
            CorruptedFileThrow();
    }
    
    {
        float vbr_quality;
        Read(reader, vbr_quality);

        if(vbr_quality >= 0.f && vbr_quality <= 9.999f)
            profile.vbr_quality = vbr_quality;
        else
            CorruptedFileThrow();
    }

    
    const size_t array_size = 18;
    uint16_t valid_bitrates[array_size] = {
    LameOptions::Bitrate::B_8,
    LameOptions::Bitrate::B_16,
    LameOptions::Bitrate::B_24,
    LameOptions::Bitrate::B_32,
    LameOptions::Bitrate::B_40,
    LameOptions::Bitrate::B_48,
    LameOptions::Bitrate::B_56,
    LameOptions::Bitrate::B_64,
    LameOptions::Bitrate::B_80,
    LameOptions::Bitrate::B_96,
    LameOptions::Bitrate::B_112,
    LameOptions::Bitrate::B_128,
    LameOptions::Bitrate::B_144,
    LameOptions::Bitrate::B_160,
    LameOptions::Bitrate::B_192,
    LameOptions::Bitrate::B_224,
    LameOptions::Bitrate::B_256,
    LameOptions::Bitrate::B_320};

    {
        uint16_t min_or_max_bitrate1;
        Read(reader, min_or_max_bitrate1);

        size_t element_position = HasElement(min_or_max_bitrate1, valid_bitrates, array_size);

        if(element_position != 0)
            profile.min_or_max_bitrate1 = static_cast<LameOptions::Bitrate>(valid_bitrates[element_position - 1u]);
        else
            CorruptedFileThrow();
    }

    {
        uint16_t min_or_max_bitrate2;
        Read(reader, min_or_max_bitrate2);

        size_t element_position = HasElement(min_or_max_bitrate2, valid_bitrates, array_size);

        if(element_position != 0)
            profile.min_or_max_bitrate2 = static_cast<LameOptions::Bitrate>(valid_bitrates[element_position - 1u]);
        else
            CorruptedFileThrow();
    }
}

template<>
void SettingsManager<SndFileEncoderOptions>::Rev1Read(FileReader &reader)
{
    {
        const size_t array_size = 118;
        uint32_t valid_formats[array_size] = {
        SndFileEncoderOptions::OutputFormat::WAV_PCM_INT_U8,
        SndFileEncoderOptions::OutputFormat::WAV_PCM_INT_S16,
        SndFileEncoderOptions::OutputFormat::WAV_PCM_INT_S24,
        SndFileEncoderOptions::OutputFormat::WAV_PCM_INT_S32,
        SndFileEncoderOptions::OutputFormat::WAV_PCM_FLOAT_32,
        SndFileEncoderOptions::OutputFormat::WAV_PCM_FLOAT_64,
        SndFileEncoderOptions::OutputFormat::WAV_ULAW,
        SndFileEncoderOptions::OutputFormat::WAV_ALAW,
        SndFileEncoderOptions::OutputFormat::WAV_IMA_ADPACM,
        SndFileEncoderOptions::OutputFormat::WAV_MS_ADPACM,
        SndFileEncoderOptions::OutputFormat::WAV_GSM610,
        SndFileEncoderOptions::OutputFormat::WAV_G721_32_ADPCM,

        SndFileEncoderOptions::OutputFormat::AIFF_PCM_INT_U8,
        SndFileEncoderOptions::OutputFormat::AIFF_PCM_INT_S8,
        SndFileEncoderOptions::OutputFormat::AIFF_PCM_INT_S16,
        SndFileEncoderOptions::OutputFormat::AIFF_PCM_INT_S24,
        SndFileEncoderOptions::OutputFormat::AIFF_PCM_INT_S32,
        SndFileEncoderOptions::OutputFormat::AIFF_PCM_FLOAT_32,
        SndFileEncoderOptions::OutputFormat::AIFF_PCM_FLOAT_64,
        SndFileEncoderOptions::OutputFormat::AIFF_ULAW,
        SndFileEncoderOptions::OutputFormat::AIFF_ALAW,
        SndFileEncoderOptions::OutputFormat::AIFF_IMA_ADPCM,
        SndFileEncoderOptions::OutputFormat::AIFF_GSM610,
        SndFileEncoderOptions::OutputFormat::AIFF_DWVW_12,
        SndFileEncoderOptions::OutputFormat::AIFF_DWVW_16,
        SndFileEncoderOptions::OutputFormat::AIFF_DWVW_24,

        SndFileEncoderOptions::OutputFormat::AU_PCM_INT_S8,
        SndFileEncoderOptions::OutputFormat::AU_PCM_INT_S16,
        SndFileEncoderOptions::OutputFormat::AU_PCM_INT_S24,
        SndFileEncoderOptions::OutputFormat::AU_PCM_INT_S32,
        SndFileEncoderOptions::OutputFormat::AU_PCM_FLOAT_32,
        SndFileEncoderOptions::OutputFormat::AU_PCM_FLOAT_64,
        SndFileEncoderOptions::OutputFormat::AU_ULAW,
        SndFileEncoderOptions::OutputFormat::AU_ALAW,
        SndFileEncoderOptions::OutputFormat::AU_G721_32_ADPCM,
        SndFileEncoderOptions::OutputFormat::AU_G723_24_ADPCM,
        SndFileEncoderOptions::OutputFormat::AU_G723_40_ADPCM,

        SndFileEncoderOptions::OutputFormat::PAF_PCM_INT_S8,
        SndFileEncoderOptions::OutputFormat::PAF_PCM_INT_S16,
        SndFileEncoderOptions::OutputFormat::PAF_PCM_INT_S24,

        SndFileEncoderOptions::OutputFormat::SVX_PCM_INT_S8,
        SndFileEncoderOptions::OutputFormat::SVX_PCM_INT_S16,

        SndFileEncoderOptions::OutputFormat::NIST_PCM_INT_S8,
        SndFileEncoderOptions::OutputFormat::NIST_PCM_INT_S16,
        SndFileEncoderOptions::OutputFormat::NIST_PCM_INT_S24,
        SndFileEncoderOptions::OutputFormat::NIST_PCM_INT_S32,
        SndFileEncoderOptions::OutputFormat::NIST_ULAW,
        SndFileEncoderOptions::OutputFormat::NIST_ALAW,

        SndFileEncoderOptions::OutputFormat::VOC_PCM_INT_U8,
        SndFileEncoderOptions::OutputFormat::VOC_PCM_INT_S16,
        SndFileEncoderOptions::OutputFormat::VOC_ULAW,
        SndFileEncoderOptions::OutputFormat::VOC_ALAW,

        SndFileEncoderOptions::OutputFormat::IRCAM_PCM_INT_S16,
        SndFileEncoderOptions::OutputFormat::IRCAM_PCM_INT_S32,
        SndFileEncoderOptions::OutputFormat::IRCAM_PCM_FLOAT_32,
        SndFileEncoderOptions::OutputFormat::IRCAM_ULAW,
        SndFileEncoderOptions::OutputFormat::IRCAM_ALAW,

        SndFileEncoderOptions::OutputFormat::W64_PCM_INT_U8,
        SndFileEncoderOptions::OutputFormat::W64_PCM_INT_S16,
        SndFileEncoderOptions::OutputFormat::W64_PCM_INT_S24,
        SndFileEncoderOptions::OutputFormat::W64_PCM_INT_S32,
        SndFileEncoderOptions::OutputFormat::W64_PCM_FLOAT_32,
        SndFileEncoderOptions::OutputFormat::W64_PCM_FLOAT_64,
        SndFileEncoderOptions::OutputFormat::W64_ULAW,
        SndFileEncoderOptions::OutputFormat::W64_ALAW,
        SndFileEncoderOptions::OutputFormat::W64_IMA_ADPCM,
        SndFileEncoderOptions::OutputFormat::W64_MS_ADPCM,
        SndFileEncoderOptions::OutputFormat::W64_GSM610,

        SndFileEncoderOptions::OutputFormat::MAT4_PCM_INT_S16,
        SndFileEncoderOptions::OutputFormat::MAT4_PCM_INT_S32,
        SndFileEncoderOptions::OutputFormat::MAT4_PCM_FLOAT_32,
        SndFileEncoderOptions::OutputFormat::MAT4_PCM_FLOAT_64,

        SndFileEncoderOptions::OutputFormat::MAT5_PCM_INT_U8,
        SndFileEncoderOptions::OutputFormat::MAT5_PCM_INT_S16,
        SndFileEncoderOptions::OutputFormat::MAT5_PCM_INT_S32,
        SndFileEncoderOptions::OutputFormat::MAT5_PCM_FLOAT_32,
        SndFileEncoderOptions::OutputFormat::MAT5_PCM_FLOAT_64,

        SndFileEncoderOptions::OutputFormat::PVF_PCM_INT_S8,
        SndFileEncoderOptions::OutputFormat::PVF_PCM_INT_S16,
        SndFileEncoderOptions::OutputFormat::PVF_PCM_INT_S32,

        SndFileEncoderOptions::OutputFormat::XI_DPCM_8,
        SndFileEncoderOptions::OutputFormat::XI_DPCM_16,

        SndFileEncoderOptions::OutputFormat::HTK_PCM_INT_S16,

        SndFileEncoderOptions::OutputFormat::SDS_PCM_INT_S8,
        SndFileEncoderOptions::OutputFormat::SDS_PCM_INT_S16,
        SndFileEncoderOptions::OutputFormat::SDS_PCM_INT_S24,

        SndFileEncoderOptions::OutputFormat::AVR_PCM_INT_U8,
        SndFileEncoderOptions::OutputFormat::AVR_PCM_INT_S8,
        SndFileEncoderOptions::OutputFormat::AVR_PCM_INT_S16,
            
        SndFileEncoderOptions::OutputFormat::WAVEX_PCM_INT_U8,
        SndFileEncoderOptions::OutputFormat::WAVEX_PCM_INT_S16,
        SndFileEncoderOptions::OutputFormat::WAVEX_PCM_INT_S24,
        SndFileEncoderOptions::OutputFormat::WAVEX_PCM_INT_S32,
        SndFileEncoderOptions::OutputFormat::WAVEX_PCM_FLOAT_32,
        SndFileEncoderOptions::OutputFormat::WAVEX_PCM_FLOAT_64,
        SndFileEncoderOptions::OutputFormat::WAVEX_ULAW,
        SndFileEncoderOptions::OutputFormat::WAVEX_ALAW,

        SndFileEncoderOptions::OutputFormat::SD2_PCM_INT_S8,
        SndFileEncoderOptions::OutputFormat::SD2_PCM_INT_S16,
        SndFileEncoderOptions::OutputFormat::SD2_PCM_INT_S24,

        SndFileEncoderOptions::OutputFormat::CAF_PCM_INT_S8,
        SndFileEncoderOptions::OutputFormat::CAF_PCM_INT_S16,
        SndFileEncoderOptions::OutputFormat::CAF_PCM_INT_S24,
        SndFileEncoderOptions::OutputFormat::CAF_PCM_INT_S32,
        SndFileEncoderOptions::OutputFormat::CAF_PCM_FLOAT_32,
        SndFileEncoderOptions::OutputFormat::CAF_PCM_FLOAT_64,
        SndFileEncoderOptions::OutputFormat::CAF_ULAW,
        SndFileEncoderOptions::OutputFormat::CAF_ALAW,

        SndFileEncoderOptions::OutputFormat::WVE_ALAW,

        SndFileEncoderOptions::OutputFormat::MPC2K_PCM_INT_S16,

        SndFileEncoderOptions::OutputFormat::RF64_PCM_INT_U8,
        SndFileEncoderOptions::OutputFormat::RF64_PCM_INT_S16,
        SndFileEncoderOptions::OutputFormat::RF64_PCM_INT_S24,
        SndFileEncoderOptions::OutputFormat::RF64_PCM_INT_S32,
        SndFileEncoderOptions::OutputFormat::RF64_PCM_FLOAT_32,
        SndFileEncoderOptions::OutputFormat::RF64_PCM_FLOAT_64,
        SndFileEncoderOptions::OutputFormat::RF64_ULAW,
        SndFileEncoderOptions::OutputFormat::RF64_ALAW};

        uint32_t format;
        Read(reader, format);

        size_t element_position = HasElement(format, valid_formats, array_size);

        if(element_position != 0)
            profile.format = static_cast<SndFileEncoderOptions::OutputFormat>(valid_formats[element_position - 1u]);
        else
            CorruptedFileThrow();
    }
}

template<>
void SettingsManager<LameOptions>::Write(std::string file_path)
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
        uint8_t copyright = profile.copyright ? 1u : 0u;
        Write(writer, copyright);
    }

    {
        uint8_t use_naoki_psytune = profile.use_naoki_psytune ? 1u : 0u;
        Write(writer, use_naoki_psytune);
    }

    {
        uint8_t bitrate_encoding = static_cast<uint8_t>(profile.bitrate_encoding);
        Write(writer, bitrate_encoding);
    }

    {
        if(profile.vbr_quality >= 0.f && profile.vbr_quality <= 9.999f)
            Write(writer, profile.vbr_quality);
        else
            CorruptedFileThrow();
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

template<>
void SettingsManager<SndFileEncoderOptions>::Write(std::string file_path)
{
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
        uint32_t format = static_cast<uint32_t>(profile.format);
        Write(writer, format);
    }

    {
        Write(writer, magic);
    }
}

template<class T>
void SettingsManager<T>::CorruptedFileThrow()
{
    std::string error_message("Corrupted profile in \"");
    error_message.append(input_file_path);
    error_message.append("\".");
    throw ReadFileException("SettingsManager", error_message.c_str());
}

template<class T>
void SettingsManager<T>::Read(FileReader &reader, int8_t &value)
{
    reader.Read(reinterpret_cast<char *>(&value), sizeof(value));
}

template<class T>
void SettingsManager<T>::Read(FileReader &reader, uint8_t &value)
{
    reader.Read(reinterpret_cast<char *>(&value), sizeof(value));
}

template<class T>
void SettingsManager<T>::Read(FileReader &reader, int16_t &value)
{
    reader.Read(reinterpret_cast<char *>(&value), sizeof(value));
}

template<class T>
void SettingsManager<T>::Read(FileReader &reader, uint16_t &value)
{
    reader.Read(reinterpret_cast<char *>(&value), sizeof(value));
}

template<class T>
void SettingsManager<T>::Read(FileReader &reader, int32_t &value)
{
    reader.Read(reinterpret_cast<char *>(&value), sizeof(value));
}

template<class T>
void SettingsManager<T>::Read(FileReader &reader, uint32_t &value)
{
    reader.Read(reinterpret_cast<char *>(&value), sizeof(value));
}

template<class T>
void SettingsManager<T>::Read(FileReader &reader, int64_t &value)
{
    reader.Read(reinterpret_cast<char *>(&value), sizeof(value));
}

template<class T>
void SettingsManager<T>::Read(FileReader &reader, uint64_t &value)
{
    reader.Read(reinterpret_cast<char *>(&value), sizeof(value));
}

template<class T>
void SettingsManager<T>::Read(FileReader &reader, float &value)
{
    reader.Read(reinterpret_cast<char *>(&value), sizeof(value));
}

template<class T>
void SettingsManager<T>::Read(FileReader &reader, double &value)
{
    reader.Read(reinterpret_cast<char *>(&value), sizeof(value));
}

template<class T>
void SettingsManager<T>::Read(FileReader &reader, bool &value)
{
    uint8_t temp;
    Read(reader, temp);
    if(temp == 0u)
        value = false;
    else if(temp == 1)
        value = true;
    else
    {
        std::string error_message("Invalid boolean value in \"");
        error_message.append(input_file_path);
        error_message.append("\".");
        throw ReadFileException("SettingsManager", error_message.c_str());
    }
}

template<class T>
void SettingsManager<T>::Read(FileReader &reader, std::string &value)
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
            error_message.append(input_file_path);
            error_message.append("\".");
            throw ReadFileException("SettingsManager", error_message.c_str());
        }
    }
}
template<class T>
void SettingsManager<T>::Write(FileWriter &writer, int8_t &value)
{
    writer.Write(reinterpret_cast<char *>(&value), sizeof(value));
}

template<class T>
void SettingsManager<T>::Write(FileWriter &writer, uint8_t &value)
{
    writer.Write(reinterpret_cast<char *>(&value), sizeof(value));
}

template<class T>
void SettingsManager<T>::Write(FileWriter &writer, int16_t &value)
{
    writer.Write(reinterpret_cast<char *>(&value), sizeof(value));
}

template<class T>
void SettingsManager<T>::Write(FileWriter &writer, uint16_t &value)
{
    writer.Write(reinterpret_cast<char *>(&value), sizeof(value));
}

template<class T>
void SettingsManager<T>::Write(FileWriter &writer, int32_t &value)
{
    writer.Write(reinterpret_cast<char *>(&value), sizeof(value));
}

template<class T>
void SettingsManager<T>::Write(FileWriter &writer, uint32_t &value)
{
    writer.Write(reinterpret_cast<char *>(&value), sizeof(value));
}

template<class T>
void SettingsManager<T>::Write(FileWriter &writer, int64_t &value)
{
    writer.Write(reinterpret_cast<char *>(&value), sizeof(value));
}

template<class T>
void SettingsManager<T>::Write(FileWriter &writer, uint64_t &value)
{
    writer.Write(reinterpret_cast<char *>(&value), sizeof(value));
}

template<class T>
void SettingsManager<T>::Write(FileWriter &writer, float &value)
{
    writer.Write(reinterpret_cast<char *>(&value), sizeof(value));
}

template<class T>
void SettingsManager<T>::Write(FileWriter &writer, double &value)
{
    writer.Write(reinterpret_cast<char *>(&value), sizeof(value));
}

template<class T>
void SettingsManager<T>::Write(FileWriter &writer, bool &value)
{
    writer.Write(reinterpret_cast<char *>(&value), sizeof(value));
}

template<class T>
void SettingsManager<T>::Write(FileWriter &writer, std::string &value)
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

template<class T>
size_t SettingsManager<T>::HasElement(int8_t &value, int8_t value_array[], size_t value_array_size)
{
    for(size_t i = 0u; i < value_array_size; ++i)
    {
        if(IsEqual(value, value_array[i]))
            return i + 1u;
    }
    return 0u;
}

template<class T>
size_t SettingsManager<T>::HasElement(uint8_t &value, uint8_t value_array[], size_t value_array_size)
{
    for(size_t i = 0u; i < value_array_size; ++i)
    {
        if(IsEqual(value, value_array[i]))
            return i + 1u;
    }
    return 0u;
}

template<class T>
size_t SettingsManager<T>::HasElement(int16_t &value, int16_t value_array[], size_t value_array_size)
{
    for(size_t i = 0u; i < value_array_size; ++i)
    {
        if(IsEqual(value, value_array[i]))
            return i + 1u;
    }
    return 0u;
}

template<class T>
size_t SettingsManager<T>::HasElement(uint16_t &value, uint16_t value_array[], size_t value_array_size)
{
    for(size_t i = 0u; i < value_array_size; ++i)
    {
        if(IsEqual(value, value_array[i]))
            return i + 1u;
    }
    return 0u;
}

template<class T>
size_t SettingsManager<T>::HasElement(int32_t &value, int32_t value_array[], size_t value_array_size)
{
    for(size_t i = 0u; i < value_array_size; ++i)
    {
        if(IsEqual(value, value_array[i]))
            return i + 1u;
    }
    return 0u;
}

template<class T>
size_t SettingsManager<T>::HasElement(uint32_t &value, uint32_t value_array[], size_t value_array_size)
{
    for(size_t i = 0u; i < value_array_size; ++i)
    {
        if(IsEqual(value, value_array[i]))
            return i + 1u;
    }
    return 0u;
}

template<class T>
size_t SettingsManager<T>::HasElement(int64_t &value, int64_t value_array[], size_t value_array_size)
{
    for(size_t i = 0u; i < value_array_size; ++i)
    {
        if(IsEqual(value, value_array[i]))
            return i + 1u;
    }
    return 0u;
}

template<class T>
size_t SettingsManager<T>::HasElement(uint64_t &value, uint64_t value_array[], size_t value_array_size)
{
    for(size_t i = 0u; i < value_array_size; ++i)
    {
        if(IsEqual(value, value_array[i]))
            return i + 1u;
    }
    return 0u;
}

template<class T>
size_t SettingsManager<T>::HasElement(bool &value, bool value_array[], size_t value_array_size)
{
    for(size_t i = 0u; i < value_array_size; ++i)
    {
        if(IsEqual(value, value_array[i]))
            return i + 1u;
    }
    return 0u;
}

template<class T>
size_t SettingsManager<T>::HasElement(std::string &value, std::string value_array[], size_t value_array_size)
{
    for(size_t i = 0u; i < value_array_size; ++i)
    {
        if(IsEqual(value, value_array[i]))
            return i + 1u;
    }
    return 0u;
}

template<class T>
bool SettingsManager<T>::IsEqual(int8_t &value1, int8_t &value2)
{
    return value1 == value2;
}

template<class T>
bool SettingsManager<T>::IsEqual(uint8_t &value1, uint8_t &value2)
{
    return value1 == value2;
}

template<class T>
bool SettingsManager<T>::IsEqual(int16_t &value1, int16_t &value2)
{
    return value1 == value2;
}

template<class T>
bool SettingsManager<T>::IsEqual(uint16_t &value1, uint16_t &value2)
{
    return value1 == value2;
}

template<class T>
bool SettingsManager<T>::IsEqual(int32_t &value1, int32_t &value2)
{
    return value1 == value2;
}

template<class T>
bool SettingsManager<T>::IsEqual(uint32_t &value1, uint32_t &value2)
{
    return value1 == value2;
}

template<class T>
bool SettingsManager<T>::IsEqual(int64_t &value1, int64_t &value2)
{
    return value1 == value2;
}

template<class T>
bool SettingsManager<T>::IsEqual(uint64_t &value1, uint64_t &value2)
{
    return value1 == value2;
}

template<class T>
bool SettingsManager<T>::IsEqual(bool &value1, bool &value2)
{
    return value1 == value2;
}

template<class T>
bool SettingsManager<T>::IsEqual(std::string &value1, std::string &value2)
{
    return value1.compare(value2) == 0;
}
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
#include "rst_lame.h"

const char *LameOptions::output_file_extension = "mp3";

const std::map<const LameOptions::AlgorithmQuality, const char *> LameOptions::algorithm_quality_to_text = {
        {AlgorithmQuality::Q0, "0"},
        {AlgorithmQuality::Q1, "1"},
        {AlgorithmQuality::Q2, "2"},
        {AlgorithmQuality::Q3, "3"},
        {AlgorithmQuality::Q4, "4"},
        {AlgorithmQuality::Q5, "5"},
        {AlgorithmQuality::Q6, "6"},
        {AlgorithmQuality::Q7, "7"},
        {AlgorithmQuality::Q8, "8"},
        {AlgorithmQuality::Q9, "9"}
};

const std::map<const LameOptions::Mode, const char *> LameOptions::mode_to_text = {
        {Mode::STEREO, "Stereo"},
        {Mode::JOINT_STEREO, "Joint stereo"},
        {Mode::MONO, "Mono"}
};

const std::map<const LameOptions::ReplayGain, const char *> LameOptions::replaygain_mode_to_text = {
        {ReplayGain::NONE, "None"},
        {ReplayGain::FAST, "Fast"},
        {ReplayGain::ACCURATE, "Accurate"}
};

const std::map<const LameOptions::BitrateEncoding, const char *> LameOptions::bitrate_encoding_to_text = {
        {BitrateEncoding::CONSTANT, "Constant"},
        {BitrateEncoding::VARIABLE_OLD, "Old variable"},
        {BitrateEncoding::VARIABLE_NEW, "New variable"},
        {BitrateEncoding::AVERAGE, "Average"}
};

const std::map<const LameOptions::Bitrate, const char *> LameOptions::bitrate_to_text = {
        {Bitrate::B_8, "8"},
        {Bitrate::B_16, "16"},
        {Bitrate::B_24, "24"},
        {Bitrate::B_32, "32"},
        {Bitrate::B_40, "40"},
        {Bitrate::B_48, "48"},
        {Bitrate::B_56, "56"},
        {Bitrate::B_64, "64"},
        {Bitrate::B_80, "80"},
        {Bitrate::B_96, "96"},
        {Bitrate::B_112, "112"},
        {Bitrate::B_128, "128"},
        {Bitrate::B_144, "144"},
        {Bitrate::B_160, "160"},
        {Bitrate::B_192, "192"},
        {Bitrate::B_224, "224"},
        {Bitrate::B_256, "256"},
        {Bitrate::B_320, "320"}
};

const std::map<const char *, const LameOptions::AlgorithmQuality> LameOptions::text_to_algorithm_quality = {
        {LameOptions::algorithm_quality_to_text.at(AlgorithmQuality::Q0), AlgorithmQuality::Q0},
        {LameOptions::algorithm_quality_to_text.at(AlgorithmQuality::Q1), AlgorithmQuality::Q1},
        {LameOptions::algorithm_quality_to_text.at(AlgorithmQuality::Q2), AlgorithmQuality::Q2},
        {LameOptions::algorithm_quality_to_text.at(AlgorithmQuality::Q3), AlgorithmQuality::Q3},
        {LameOptions::algorithm_quality_to_text.at(AlgorithmQuality::Q4), AlgorithmQuality::Q4},
        {LameOptions::algorithm_quality_to_text.at(AlgorithmQuality::Q5), AlgorithmQuality::Q5},
        {LameOptions::algorithm_quality_to_text.at(AlgorithmQuality::Q6), AlgorithmQuality::Q6},
        {LameOptions::algorithm_quality_to_text.at(AlgorithmQuality::Q7), AlgorithmQuality::Q7},
        {LameOptions::algorithm_quality_to_text.at(AlgorithmQuality::Q8), AlgorithmQuality::Q8},
        {LameOptions::algorithm_quality_to_text.at(AlgorithmQuality::Q9), AlgorithmQuality::Q9}
};

const std::map<const char *, const LameOptions::Mode> LameOptions::text_to_mode = {
        {LameOptions::mode_to_text.at(Mode::STEREO), Mode::STEREO},
        {LameOptions::mode_to_text.at(Mode::JOINT_STEREO), Mode::JOINT_STEREO},
        {LameOptions::mode_to_text.at(Mode::MONO), Mode::MONO}
};

const std::map<const char *, const LameOptions::ReplayGain> LameOptions::text_to_replaygain_mode = {
        {LameOptions::replaygain_mode_to_text.at(ReplayGain::NONE), ReplayGain::NONE},
        {LameOptions::replaygain_mode_to_text.at(ReplayGain::FAST), ReplayGain::FAST},
        {LameOptions::replaygain_mode_to_text.at(ReplayGain::ACCURATE), ReplayGain::ACCURATE}
};

const std::map<const char *, const LameOptions::BitrateEncoding> LameOptions::text_to_bitrate_encoding = {
        {LameOptions::bitrate_encoding_to_text.at(BitrateEncoding::CONSTANT), BitrateEncoding::CONSTANT},
        {LameOptions::bitrate_encoding_to_text.at(BitrateEncoding::VARIABLE_OLD), BitrateEncoding::VARIABLE_OLD},
        {LameOptions::bitrate_encoding_to_text.at(BitrateEncoding::VARIABLE_NEW), BitrateEncoding::VARIABLE_NEW},
        {LameOptions::bitrate_encoding_to_text.at(BitrateEncoding::AVERAGE), BitrateEncoding::AVERAGE}
};

const std::map<const char *, const LameOptions::Bitrate> LameOptions::text_to_bitrate = {
        {LameOptions::bitrate_to_text.at(Bitrate::B_8), Bitrate::B_8},
        {LameOptions::bitrate_to_text.at(Bitrate::B_16), Bitrate::B_16},
        {LameOptions::bitrate_to_text.at(Bitrate::B_24), Bitrate::B_24},
        {LameOptions::bitrate_to_text.at(Bitrate::B_32), Bitrate::B_32},
        {LameOptions::bitrate_to_text.at(Bitrate::B_40), Bitrate::B_40},
        {LameOptions::bitrate_to_text.at(Bitrate::B_48), Bitrate::B_48},
        {LameOptions::bitrate_to_text.at(Bitrate::B_56), Bitrate::B_56},
        {LameOptions::bitrate_to_text.at(Bitrate::B_64), Bitrate::B_64},
        {LameOptions::bitrate_to_text.at(Bitrate::B_80), Bitrate::B_80},
        {LameOptions::bitrate_to_text.at(Bitrate::B_96), Bitrate::B_96},
        {LameOptions::bitrate_to_text.at(Bitrate::B_112), Bitrate::B_112},
        {LameOptions::bitrate_to_text.at(Bitrate::B_128), Bitrate::B_128},
        {LameOptions::bitrate_to_text.at(Bitrate::B_144), Bitrate::B_144},
        {LameOptions::bitrate_to_text.at(Bitrate::B_160), Bitrate::B_160},
        {LameOptions::bitrate_to_text.at(Bitrate::B_192), Bitrate::B_192},
        {LameOptions::bitrate_to_text.at(Bitrate::B_224), Bitrate::B_224},
        {LameOptions::bitrate_to_text.at(Bitrate::B_256), Bitrate::B_256},
        {LameOptions::bitrate_to_text.at(Bitrate::B_320), Bitrate::B_320}
};

void LameOptions::LoadDefaultProfile(Profile default_profile)
{
    switch(default_profile)
    {
        case DEFAULT:
        {
            algorithm_quality = AlgorithmQuality::Q0;
            mode = Mode::JOINT_STEREO;
            replaygain_mode = ReplayGain::ACCURATE;
            copyright = false;
            use_naoki_psytune = true;
            bitrate_encoding = BitrateEncoding::CONSTANT;
            vbr_quality = 0.0f;
            min_or_max_bitrate1 = Bitrate::B_320;
            min_or_max_bitrate2 = Bitrate::B_8;
            break;
        }
    }
}

bool LameOptions::SetAlgorithmQuality(uint8_t algorithm_quality)
{
    switch(algorithm_quality)
    {
        case AlgorithmQuality::Q0:
        case AlgorithmQuality::Q1:
        case AlgorithmQuality::Q2:
        case AlgorithmQuality::Q3:
        case AlgorithmQuality::Q4:
        case AlgorithmQuality::Q5:
        case AlgorithmQuality::Q6:
        case AlgorithmQuality::Q7:
        case AlgorithmQuality::Q8:
        case AlgorithmQuality::Q9:
            break;
        default:
            return false;
    }

    this->algorithm_quality = static_cast<AlgorithmQuality>(algorithm_quality);
    return true;
}

bool LameOptions::SetMode(uint8_t mode)
{
    switch(mode)
    {
        case Mode::STEREO:
        case Mode::JOINT_STEREO:
        case Mode::MONO:
            break;
        default:
            return false;
    }

    this->mode = static_cast<Mode>(mode);
    return true;
}

bool LameOptions::SetReplayGainMode(uint8_t replaygain_mode)
{
    switch(replaygain_mode)
    {
        case ReplayGain::NONE:
        case ReplayGain::FAST:
        case ReplayGain::ACCURATE:
            break;
        default:
            return false;
    }

    this->replaygain_mode = static_cast<ReplayGain>(replaygain_mode);
    return true;
}

void LameOptions::SetCopyright(bool copyright)
{
    this->copyright = copyright;
}

void LameOptions::SetUseNaokiPsytune(bool use_naoki_psytune)
{
    this->use_naoki_psytune = use_naoki_psytune;
}

bool LameOptions::SetBitrateEncoding(uint8_t bitrate_encoding)
{
    switch(bitrate_encoding)
    {
        case BitrateEncoding::CONSTANT:
        case BitrateEncoding::VARIABLE_OLD:
        case BitrateEncoding::VARIABLE_NEW:
        case BitrateEncoding::AVERAGE:
            break;
        default:
            return false;
    }

    this->bitrate_encoding = static_cast<BitrateEncoding>(bitrate_encoding);
    return true;
}

bool LameOptions::SetVbrQuality(float vbr_quality)
{
    if(vbr_quality >= 0.f && vbr_quality <= 9.999f)
    {
        this->vbr_quality = vbr_quality;
        return true;
    }
    else
        return false;
}

bool LameOptions::SetMinOrMaxBitrate(uint16_t min_or_max_bitrate, bool one)
{
    switch(min_or_max_bitrate)
    {
        case Bitrate::B_8:
        case Bitrate::B_16:
        case Bitrate::B_24:
        case Bitrate::B_32:
        case Bitrate::B_40:
        case Bitrate::B_48:
        case Bitrate::B_56:
        case Bitrate::B_64:
        case Bitrate::B_80:
        case Bitrate::B_96:
        case Bitrate::B_112:
        case Bitrate::B_128:
        case Bitrate::B_144:
        case Bitrate::B_160:
        case Bitrate::B_192:
        case Bitrate::B_224:
        case Bitrate::B_256:
        case Bitrate::B_320:
            break;
        default:
            return false;
    }

    if(one)
        this->min_or_max_bitrate1 = static_cast<Bitrate>(min_or_max_bitrate);
    else
        this->min_or_max_bitrate2 = static_cast<Bitrate>(min_or_max_bitrate);

    return true;
}

bool LameOptions::SetMinOrMaxBitrate1(uint16_t min_or_max_bitrate1)
{
    return SetMinOrMaxBitrate(min_or_max_bitrate1, true);
}

bool LameOptions::SetMinOrMaxBitrate2(uint16_t min_or_max_bitrate2)
{
    return SetMinOrMaxBitrate(min_or_max_bitrate2, false);
}

Lame<short>::Lame(const char * const file,
                  int sample_rate,
                  int channel_count,
                  LameOptions::AlgorithmQuality algorithm_quality,
                  LameOptions::Mode mode,
                  LameOptions::ReplayGain replaygain_mode,
                  bool copyright,
                  bool use_naoki_psytune,
                  LameOptions::BitrateEncoding bitrate_encoding,
                  float vbr_quality,
                  LameOptions::Bitrate min_or_max_bitrate1,
                  LameOptions::Bitrate min_or_max_bitrate2,
                  short *container,
                  uint64_t container_size)
{
    Lame2(file, sample_rate, channel_count, algorithm_quality, mode, replaygain_mode, copyright, use_naoki_psytune, bitrate_encoding, vbr_quality, min_or_max_bitrate1, min_or_max_bitrate2, container, container_size);
}

Lame<float>::Lame(const char * const file,
                  int sample_rate,
                  int channel_count,
                  LameOptions::AlgorithmQuality algorithm_quality,
                  LameOptions::Mode mode,
                  LameOptions::ReplayGain replaygain_mode,
                  bool copyright,
                  bool use_naoki_psytune,
                  LameOptions::BitrateEncoding bitrate_encoding,
                  float vbr_quality,
                  LameOptions::Bitrate min_or_max_bitrate1,
                  LameOptions::Bitrate min_or_max_bitrate2,
                  float *container,
                  uint64_t container_size)
{
    Lame2(file, sample_rate, channel_count, algorithm_quality, mode, replaygain_mode, copyright, use_naoki_psytune, bitrate_encoding, vbr_quality, min_or_max_bitrate1, min_or_max_bitrate2, container, container_size);
}

Lame<double>::Lame(const char * const file,
                   int sample_rate,
                   int channel_count,
                   LameOptions::AlgorithmQuality algorithm_quality,
                   LameOptions::Mode mode,
                   LameOptions::ReplayGain replaygain_mode,
                   bool copyright,
                   bool use_naoki_psytune,
                   LameOptions::BitrateEncoding bitrate_encoding,
                   float vbr_quality,
                   LameOptions::Bitrate min_or_max_bitrate1,
                   LameOptions::Bitrate min_or_max_bitrate2,
                   double *container,
                   uint64_t container_size)
{
    Lame2(file, sample_rate, channel_count, algorithm_quality, mode, replaygain_mode, copyright, use_naoki_psytune, bitrate_encoding, vbr_quality, min_or_max_bitrate1, min_or_max_bitrate2, container, container_size);
}

template<class T>
void Lame<T>::Lame2(const char * const file,
                    int sample_rate,
                    int channel_count,
                    LameOptions::AlgorithmQuality algorithm_quality,
                    LameOptions::Mode mode,
                    LameOptions::ReplayGain replaygain_mode,
                    bool copyright,
                    bool use_naoki_psytune,
                    LameOptions::BitrateEncoding bitrate_encoding,
                    float vbr_quality,
                    LameOptions::Bitrate min_or_max_bitrate1,
                    LameOptions::Bitrate min_or_max_bitrate2,
                    T *container,
                    uint64_t container_size)
{
    gf = lame_init();
    if(gf == nullptr)
        throw EncoderConfigurationException("LAME", "Fail to initialize LAME encoder.");

    error = lame_set_in_samplerate(gf, sample_rate);
    IfErrorThenFreeAndThrow("Invalid sample rate.");

    this->channel_count = channel_count;

    error = lame_set_num_channels(gf, channel_count);
    IfErrorThenFreeAndThrow("Invalid number of channels.");

    lame_set_write_id3tag_automatic(gf, 0);

    error = lame_set_quality(gf, algorithm_quality);
    IfErrorThenFreeAndThrow("Cannot set internal algorithm quality.");

    switch(mode)
    {
        case STEREO:
            error = lame_set_mode(gf, MPEG_mode::STEREO);
            break;
        case JOINT_STEREO:
            error = lame_set_mode(gf, MPEG_mode::JOINT_STEREO);
            break;
        default:
            error = lame_set_mode(gf, MPEG_mode::MONO);
    }

    IfErrorThenFreeAndThrow("Cannot set output channel mode.");

    switch(replaygain_mode)
    {
        case LameOptions::ReplayGain::FAST:
        case LameOptions::ReplayGain::ACCURATE:
        {
            error = lame_set_findReplayGain(gf, 1);
            IfErrorThenFreeAndThrow("Cannot enable ReplayGain analysis.");

            if(replaygain_mode == LameOptions::ReplayGain::ACCURATE)
            {
                error = lame_set_decode_on_the_fly(gf, 1);
                IfErrorThenFreeAndThrow("Cannot enable peak sample searching.");
            }
            break;
        }
    }

    error = lame_set_copyright(gf, copyright ? 1 : 0);
    IfErrorThenFreeAndThrow("Cannot set copyright bit.");

    error = lame_set_exp_nspsytune(gf, use_naoki_psytune ? 1 : 0);
    IfErrorThenFreeAndThrow("Cannot use Naoki's psycho acoustic model.");

    switch(bitrate_encoding)
    {
        case LameOptions::BitrateEncoding::CONSTANT:
            error = lame_set_VBR(gf, vbr_mode::vbr_off);
            break;
        case LameOptions::BitrateEncoding::VARIABLE_OLD:
            error = lame_set_VBR(gf, vbr_mode::vbr_rh);
            break;
        case LameOptions::BitrateEncoding::VARIABLE_NEW:
            error = lame_set_VBR(gf, vbr_mode::vbr_mtrh);
            break;
        default:
            error = lame_set_VBR(gf, vbr_mode::vbr_abr);
    }

    IfErrorThenFreeAndThrow("Cannot use bitrate encoding.");

    switch(bitrate_encoding)
    {
        case LameOptions::BitrateEncoding::CONSTANT:
            error = lame_set_brate(gf, min_or_max_bitrate1);
            IfErrorThenFreeAndThrow("Cannot set constant bitrate.");
            break;
        case LameOptions::BitrateEncoding::VARIABLE_OLD:
        case LameOptions::BitrateEncoding::VARIABLE_NEW:
        {
            error = lame_set_VBR_quality(gf, vbr_quality);
            IfErrorThenFreeAndThrow("Cannot set vbr quality.");

            if(min_or_max_bitrate1 < min_or_max_bitrate2)
            {
                error = lame_set_VBR_min_bitrate_kbps(gf, min_or_max_bitrate1);
                IfErrorThenFreeAndThrow("Cannot set minimum bitrate.");
                error = lame_set_VBR_max_bitrate_kbps(gf, min_or_max_bitrate2);
                IfErrorThenFreeAndThrow("Cannot set maximum bitrate.");
            }
            else
            {
                error = lame_set_VBR_min_bitrate_kbps(gf, min_or_max_bitrate2);
                IfErrorThenFreeAndThrow("Cannot set minimum bitrate.");
                error = lame_set_VBR_max_bitrate_kbps(gf, min_or_max_bitrate1);
                IfErrorThenFreeAndThrow("Cannot set maximum bitrate.");
            }
            break;
        }
        case LameOptions::BitrateEncoding::AVERAGE:
            lame_set_VBR_mean_bitrate_kbps(gf, min_or_max_bitrate1);
            IfErrorThenFreeAndThrow("Cannot set mean bitrate.");
            break;
    }

    error = lame_init_params(gf);
    IfErrorThenFreeAndThrow("One or more encoder settings are invalid.");

    writer.reset(new (std::nothrow) FileWriter(file));

    if(writer.get() == nullptr)
    {
        lame_close(gf);
        throw MemoryAllocationException("LAME");
    }

    SetFrameBuffer(container, container_size);
}

template<class T>
void Lame<T>::SetFrameBuffer(T * container, uint64_t container_size)
{
    assert(container != nullptr);
    assert(container_size > 0);
    assert(container_size <= INT_MAX);
    assert((container_size % (channel_count * sizeof(T))) == 0);

    this->container = container;
    this->container_size = container_size;
    container_frame_capacity = container_size / (channel_count * sizeof(T));

    mp3buffer_size = static_cast<int>(2 * container_frame_capacity * channel_count + 7200);
    mp3buffer.reset(new (std::nothrow) unsigned char[mp3buffer_size]); /*!< Give it more than worse case <tt>(1.25 * num_samples + 7200)</tt> and eliminate the need for float values */
    if(mp3buffer.get() == nullptr)
        throw MemoryAllocationException("LAME");
}

template<class T>
const char * const Lame<T>::GetFileExtension(void) const noexcept
{
    return layer3_extension;
}

template<class T>
void Lame<T>::WriteFrames2()
{
    if(encountered_start_frame)
    {
        WriteTag(Tag::ID3V2_TAG);
        encountered_start_frame = false;
    }
}

void Lame<short>::WriteFrames(uint64_t container_valid_frame_count)
{
    WriteFrames2();

    WriteFrames3(lame_encode_buffer_interleaved(gf, container, static_cast<int>(container_frame_capacity), mp3buffer.get(), mp3buffer_size), container_valid_frame_count);
}

void Lame<float>::WriteFrames(uint64_t container_valid_frame_count)
{
    WriteFrames2();

    WriteFrames3(lame_encode_buffer_interleaved_ieee_float(gf, container, static_cast<int>(container_frame_capacity), mp3buffer.get(), mp3buffer_size), container_valid_frame_count);
}

void Lame<double>::WriteFrames(uint64_t container_valid_frame_count)
{
    WriteFrames2();

    WriteFrames3(lame_encode_buffer_interleaved_ieee_double(gf, container, static_cast<int>(container_frame_capacity), mp3buffer.get(), mp3buffer_size), container_valid_frame_count);
}

template<class T>
void Lame<T>::WriteFrames3(int encoded_bytes_count, uint64_t container_valid_frame_count)
{
    switch(encoded_bytes_count)
    {
        case -1:
            throw WriteFileException("LAME", encoded_bytes_count, "The output buffer is too small.");
            break;
        case -2:
            throw MemoryAllocationException("LAME");
            break;
        case -4:
            throw WriteFileException("LAME", encoded_bytes_count, "Psycho acoustic problems.");
            break;
    }

    writer->Write(reinterpret_cast<char *>(mp3buffer.get()), encoded_bytes_count);

    if((container_valid_frame_count < container_frame_capacity) && (encountered_end_frame == false))
    {
        encoded_bytes_count = lame_encode_flush_nogap(gf, mp3buffer.get(), mp3buffer_size);

        writer->Write(reinterpret_cast<char *>(mp3buffer.get()), encoded_bytes_count);

        WriteTag(Tag::ID3V1_TAG);

        size_t id3v2size = lame_get_id3v2_tag(gf, nullptr, 0);

        writer->Seek(SeekPosition::START, id3v2size);

        WriteTag(Tag::XING_FRAME);

        encountered_end_frame = true;
    }
}

template<class T>
void Lame<T>::WriteTag(Tag tag) const
{
    size_t tag_size;

    switch(tag)
    {
        case ID3V1_TAG:
            tag_size = lame_get_id3v1_tag(gf, nullptr, 0);
            break;
        case ID3V2_TAG:
            tag_size = lame_get_id3v2_tag(gf, nullptr, 0);
            break;
        default:
            tag_size = lame_get_lametag_frame(gf, nullptr, 0);
    }

    if(tag_size > 0)
    {
        std::unique_ptr<unsigned char> tag_buffer(new (std::nothrow) unsigned char[tag_size]);
        if(tag_buffer.get() == nullptr)
            throw MemoryAllocationException("LAME");

        switch(tag)
        {
            case ID3V1_TAG:
                tag_size = lame_get_id3v1_tag(gf, tag_buffer.get(), tag_size);
                break;
            case ID3V2_TAG:
                tag_size = lame_get_id3v2_tag(gf, tag_buffer.get(), tag_size);
                break;
            default:
                tag_size = lame_get_lametag_frame(gf, tag_buffer.get(), tag_size);
        }

        writer->Write(reinterpret_cast<char *>(tag_buffer.get()), static_cast<uint32_t>(tag_size));
    }
}

template<class T>
void Lame<T>::IfErrorThenFreeAndThrow(const char * const message)
{
    if(error != lame_errorcodes_t::LAME_OKAY)
    {
        lame_close(gf);
        throw EncoderConfigurationException("LAME", error, message);
    }
}

template<class T>
Lame<T>::~Lame()
{
    lame_close(gf);
}

Lame<void>::Lame()
{
    Encoder<void>::valid_containers.reset(new Sample::SampleContainer[valid_containers_count]);
    Sample::SampleContainer * const _valid_containers = Encoder<void>::valid_containers.get();
    _valid_containers[0] = Sample::SampleContainer::INT_S16;
    _valid_containers[1] = Sample::SampleContainer::FLOAT_32;
    _valid_containers[2] = Sample::SampleContainer::FLOAT_64;
}

size_t Lame<void>::GetValidContainersCount() const noexcept
{
    return valid_containers_count;
}
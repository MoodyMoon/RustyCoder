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
#include "lame.h"

rusty::codecs::Lame<short>::Lame(const boost::filesystem::path &path,
                                 int sample_rate,
                                 int channel_count,
                                 LameProfile::AlgorithmQuality algorithm_quality,
                                 LameProfile::Mode mode,
                                 LameProfile::ReplayGain replaygain_mode,
                                 bool copyright,
                                 bool use_naoki_psytune,
                                 LameProfile::BitrateEncoding bitrate_encoding,
                                 float vbr_quality,
                                 LameProfile::Bitrate min_or_max_bitrate1,
                                 LameProfile::Bitrate min_or_max_bitrate2,
                                 short *container,
                                 uint64_t container_size)
{
    Lame2(path, sample_rate, channel_count, algorithm_quality, mode, replaygain_mode, copyright, use_naoki_psytune, bitrate_encoding, vbr_quality, min_or_max_bitrate1, min_or_max_bitrate2, container, container_size);
}

rusty::codecs::Lame<float>::Lame(const boost::filesystem::path &path,
                                 int sample_rate,
                                 int channel_count,
                                 LameProfile::AlgorithmQuality algorithm_quality,
                                 LameProfile::Mode mode,
                                 LameProfile::ReplayGain replaygain_mode,
                                 bool copyright,
                                 bool use_naoki_psytune,
                                 LameProfile::BitrateEncoding bitrate_encoding,
                                 float vbr_quality,
                                 LameProfile::Bitrate min_or_max_bitrate1,
                                 LameProfile::Bitrate min_or_max_bitrate2,
                                 float *container,
                                 uint64_t container_size)
{
    Lame2(path, sample_rate, channel_count, algorithm_quality, mode, replaygain_mode, copyright, use_naoki_psytune, bitrate_encoding, vbr_quality, min_or_max_bitrate1, min_or_max_bitrate2, container, container_size);
}

rusty::codecs::Lame<double>::Lame(const boost::filesystem::path &path,
                                  int sample_rate,
                                  int channel_count,
                                  LameProfile::AlgorithmQuality algorithm_quality,
                                  LameProfile::Mode mode,
                                  LameProfile::ReplayGain replaygain_mode,
                                  bool copyright,
                                  bool use_naoki_psytune,
                                  LameProfile::BitrateEncoding bitrate_encoding,
                                  float vbr_quality,
                                  LameProfile::Bitrate min_or_max_bitrate1,
                                  LameProfile::Bitrate min_or_max_bitrate2,
                                  double *container,
                                  uint64_t container_size)
{
    Lame2(path, sample_rate, channel_count, algorithm_quality, mode, replaygain_mode, copyright, use_naoki_psytune, bitrate_encoding, vbr_quality, min_or_max_bitrate1, min_or_max_bitrate2, container, container_size);
}

template<class T>
void rusty::codecs::Lame<T>::Lame2(const boost::filesystem::path &path,
                                   int sample_rate,
                                   int channel_count,
                                   LameProfile::AlgorithmQuality algorithm_quality,
                                   LameProfile::Mode mode,
                                   LameProfile::ReplayGain replaygain_mode,
                                   bool copyright,
                                   bool use_naoki_psytune,
                                   LameProfile::BitrateEncoding bitrate_encoding,
                                   float vbr_quality,
                                   LameProfile::Bitrate min_or_max_bitrate1,
                                   LameProfile::Bitrate min_or_max_bitrate2,
                                   T *container,
                                   uint64_t container_size)
{
    gf = lame_init();
    if(gf == nullptr)
        throw core::EncoderConfigurationException("LAME", "Fail to initialize LAME encoder.");

    error = lame_set_in_samplerate(gf, sample_rate);
    IfErrorThenFreeAndThrow("Invalid sample rate.");

    this->channel_count = channel_count;

    error = lame_set_num_channels(gf, channel_count);
    IfErrorThenFreeAndThrow("Invalid number of channels.");

    lame_set_write_id3tag_automatic(gf, 0);

    error = lame_set_quality(gf, static_cast<LAME_ALGORITHM_QUALITY_DATA_TYPE>(algorithm_quality));
    IfErrorThenFreeAndThrow("Cannot set internal algorithm quality.");

    switch(mode)
    {
        case STEREO:
            error = lame_set_mode(gf, MPEG_mode::STEREO);
            break;
        case JOINT_STEREO:
            error = lame_set_mode(gf, MPEG_mode::JOINT_STEREO);
            break;
        case MONO:
            error = lame_set_mode(gf, MPEG_mode::MONO);
            break;
        default:
            assert(false);
    }

    IfErrorThenFreeAndThrow("Cannot set output channel mode.");

    switch(replaygain_mode)
    {
        case LameProfile::ReplayGain::FAST:
        case LameProfile::ReplayGain::ACCURATE:
        {
            error = lame_set_findReplayGain(gf, 1);
            IfErrorThenFreeAndThrow("Cannot enable ReplayGain analysis.");

            if(replaygain_mode == LameProfile::ReplayGain::ACCURATE)
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
        case LameProfile::BitrateEncoding::CONSTANT:
            error = lame_set_VBR(gf, vbr_mode::vbr_off);
            break;
        case LameProfile::BitrateEncoding::VARIABLE_OLD:
            error = lame_set_VBR(gf, vbr_mode::vbr_rh);
            break;
        case LameProfile::BitrateEncoding::VARIABLE_NEW:
            error = lame_set_VBR(gf, vbr_mode::vbr_mtrh);
            break;
        case LameProfile::BitrateEncoding::AVERAGE:
            error = lame_set_VBR(gf, vbr_mode::vbr_abr);
            break;
        default:
            assert(false);
    }

    IfErrorThenFreeAndThrow("Cannot use bitrate encoding.");

    switch(bitrate_encoding)
    {
        case LameProfile::BitrateEncoding::CONSTANT:
            error = lame_set_brate(gf, static_cast<LAME_BITRATE_DATA_TYPE>(min_or_max_bitrate1));
            IfErrorThenFreeAndThrow("Cannot set constant bitrate.");
            break;
        case LameProfile::BitrateEncoding::VARIABLE_OLD:
        case LameProfile::BitrateEncoding::VARIABLE_NEW:
        {
            error = lame_set_VBR_quality(gf, vbr_quality);
            IfErrorThenFreeAndThrow("Cannot set vbr quality.");

            if(min_or_max_bitrate1 < min_or_max_bitrate2)
            {
                error = lame_set_VBR_min_bitrate_kbps(gf, static_cast<LAME_BITRATE_DATA_TYPE>(min_or_max_bitrate1));
                IfErrorThenFreeAndThrow("Cannot set minimum bitrate.");
                error = lame_set_VBR_max_bitrate_kbps(gf, static_cast<LAME_BITRATE_DATA_TYPE>(min_or_max_bitrate2));
                IfErrorThenFreeAndThrow("Cannot set maximum bitrate.");
            }
            else
            {
                error = lame_set_VBR_min_bitrate_kbps(gf, static_cast<LAME_BITRATE_DATA_TYPE>(min_or_max_bitrate2));
                IfErrorThenFreeAndThrow("Cannot set minimum bitrate.");
                error = lame_set_VBR_max_bitrate_kbps(gf, static_cast<LAME_BITRATE_DATA_TYPE>(min_or_max_bitrate1));
                IfErrorThenFreeAndThrow("Cannot set maximum bitrate.");
            }
            break;
        }
        case LameProfile::BitrateEncoding::AVERAGE:
            lame_set_VBR_mean_bitrate_kbps(gf, static_cast<LAME_BITRATE_DATA_TYPE>(min_or_max_bitrate1));
            IfErrorThenFreeAndThrow("Cannot set mean bitrate.");
            break;
    }

    error = lame_init_params(gf);
    IfErrorThenFreeAndThrow("One or more encoder settings are invalid.");

    file_writer.reset(new (std::nothrow) core::FileWriter(path, core::FileWriter::Access::EXCLUSIVE_WRITE, core::FileWriter::Create::OVERWRITE));

    if(file_writer.get() == nullptr)
    {
        lame_close(gf);
        throw core::MemoryAllocationException("LAME");
    }

    SetFrameBuffer(container, container_size);
}

template<class T>
void rusty::codecs::Lame<T>::SetFrameBuffer(T * container, uint64_t container_size)
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
        throw core::MemoryAllocationException("LAME");
}

template<class T>
void rusty::codecs::Lame<T>::WriteFrames2()
{
    if(encountered_start_frame)
    {
        WriteTag(Tag::ID3V2_TAG);
        encountered_start_frame = false;
    }
}

void rusty::codecs::Lame<short>::WriteFrames(uint64_t container_valid_frame_count)
{
    WriteFrames2();

    WriteFrames3(lame_encode_buffer_interleaved(gf, container, static_cast<int>(container_frame_capacity), mp3buffer.get(), mp3buffer_size), container_valid_frame_count);
}

void rusty::codecs::Lame<float>::WriteFrames(uint64_t container_valid_frame_count)
{
    WriteFrames2();

    WriteFrames3(lame_encode_buffer_interleaved_ieee_float(gf, container, static_cast<int>(container_frame_capacity), mp3buffer.get(), mp3buffer_size), container_valid_frame_count);
}

void rusty::codecs::Lame<double>::WriteFrames(uint64_t container_valid_frame_count)
{
    WriteFrames2();

    WriteFrames3(lame_encode_buffer_interleaved_ieee_double(gf, container, static_cast<int>(container_frame_capacity), mp3buffer.get(), mp3buffer_size), container_valid_frame_count);
}

template<class T>
void rusty::codecs::Lame<T>::WriteFrames3(int encoded_bytes_count, uint64_t container_valid_frame_count)
{
    switch(encoded_bytes_count)
    {
        case -1:
            throw core::WriteFileException("LAME", encoded_bytes_count, "The output buffer is too small.");
            break;
        case -2:
            throw core::MemoryAllocationException("LAME");
            break;
        case -4:
            throw core::WriteFileException("LAME", encoded_bytes_count, "Psycho acoustic problems.");
            break;
    }

    file_writer->Write(mp3buffer.get(), encoded_bytes_count);

    if((container_valid_frame_count < container_frame_capacity) && (encountered_end_frame == false))
    {
        encoded_bytes_count = lame_encode_flush_nogap(gf, mp3buffer.get(), mp3buffer_size);

        file_writer->Write(mp3buffer.get(), encoded_bytes_count);

        WriteTag(Tag::ID3V1_TAG);

        size_t id3v2size = lame_get_id3v2_tag(gf, nullptr, 0);

        file_writer->Seek(core::SeekPosition::START, id3v2size);

        WriteTag(Tag::XING_FRAME);

        encountered_end_frame = true;
    }
}

template<class T>
void rusty::codecs::Lame<T>::WriteTag(Tag tag) const
{
    size_t tag_size = 0u;

    switch(tag)
    {
        case Tag::ID3V1_TAG:
            tag_size = lame_get_id3v1_tag(gf, nullptr, 0);
            break;
        case Tag::ID3V2_TAG:
            tag_size = lame_get_id3v2_tag(gf, nullptr, 0);
            break;
        case Tag::XING_FRAME:
            tag_size = lame_get_lametag_frame(gf, nullptr, 0);
            break;
        default:
            assert(false);
    }

    if(tag_size > 0)
    {
        std::unique_ptr<unsigned char> tag_buffer(new (std::nothrow) unsigned char[tag_size]);
        if(tag_buffer.get() == nullptr)
            throw core::MemoryAllocationException("LAME");

        switch(tag)
        {
            case Tag::ID3V1_TAG:
                tag_size = lame_get_id3v1_tag(gf, tag_buffer.get(), tag_size);
                break;
            case Tag::ID3V2_TAG:
                tag_size = lame_get_id3v2_tag(gf, tag_buffer.get(), tag_size);
                break;
            case Tag::XING_FRAME:
                tag_size = lame_get_lametag_frame(gf, tag_buffer.get(), tag_size);
                break;
            default:
                assert(false);
        }

        file_writer->Write(tag_buffer.get(), static_cast<uint32_t>(tag_size));
    }
}

template<class T>
void rusty::codecs::Lame<T>::IfErrorThenFreeAndThrow(const char * const message)
{
    if(error != lame_errorcodes_t::LAME_OKAY)
    {
        lame_close(gf);
        throw core::EncoderConfigurationException("LAME", error, message);
    }
}

template<class T>
rusty::codecs::Lame<T>::~Lame()
{
    lame_close(gf);
}

const rusty::codecs::Sample::SampleContainer rusty::codecs::Lame<void>::supported_containers[3] = {Sample::SampleContainer::INT_S16,
                                                                                                   Sample::SampleContainer::FLOAT_32,
                                                                                                   Sample::SampleContainer::FLOAT_64};

const rusty::codecs::Sample::SampleContainer * rusty::codecs::Lame<void>::GetSupportedContainers() const noexcept
{
    return supported_containers;
}

size_t rusty::codecs::Lame<void>::GetSupportedContainersCount() const noexcept
{
    static constexpr const size_t supported_containers_count = sizeof(supported_containers) / sizeof(supported_containers[0]);
    return supported_containers_count;
}
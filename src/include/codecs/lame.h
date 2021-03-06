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

#ifndef CODECS_LAME_H
#define CODECS_LAME_H

#include "../core/file_writer.h"
#include "encoder.h"
#include "lame_profile.h"

namespace rusty
{
namespace codecs
{
/*!
Encoder for (MPEG-1, MPEG-2, MPEG-2.5) Audio Layer III
*/
template<class T>
class Lame : public Encoder<T>
{
    public:
        enum class Tag : uint32_t
        {
            ID3V1_TAG,
            ID3V2_TAG,
            XING_FRAME
        };

    private:
        lame_t gf = nullptr;
        bool encountered_start_frame = true;
        bool encountered_end_frame = false;
        std::unique_ptr<core::FileWriter> file_writer;
        std::unique_ptr<unsigned char> mp3buffer;
        int error;
        int mp3buffer_size;
        unsigned int channel_count;
        T *container = nullptr;
        uint64_t container_size = 0;
        uint64_t container_frame_capacity = 0;
        uint64_t valid_output_frame_count = 0;

        void Lame2(const boost::filesystem::path &path,
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
                   uint64_t container_size);

        void IfErrorThenFreeAndThrow(const char * const message);
        virtual void SetFrameBuffer(T *container, uint64_t container_size);

        void WriteTag(Tag tag) const;
        void WriteFrames2(void);
        void WriteFrames3(int encoded_bytes_count, uint64_t container_valid_frame_count);

    public:
        Lame(const Lame &) = delete;
        Lame & operator=(const Lame &) = delete;

        /*!
        Initialize lame library.
        \param[in] path                Output file path.
        \param[in] sample_rate         Input audio sample rate.
        \param[in] channel_count       Number of input audio channels.
        \param[in] algorithm_quality   A number indicator for determining the best scalefactors and Huffman coding (noise shaping).
        \param[in] mode                Channel mode.
        \param[in] replaygain_mode     Replaygain quality selection.
        \param[in] copyright           Set copyright bit in MPEG frame.
        \param[in] use_naoki_psytune   Use Naoki psycho-acoustic model.
        \param[in] bitrate_encoding    Bitrate encoding selection.
        \param[in] vbr_quality         Used if \c bitrate_encoding is set to variable bitrate. Range from 0.000 to 9.999.
        \param[in] min_or_max_bitrate1 Bitrate for constant bitrate encoding and minimum bitrate for variable bitrate encoding.
        \param[in] min_or_max_bitrate2 Maximum bitrate for variable bitrate encoding.
        \param[in] container           Pointer to the buffer which contains audio samples.
        \param[in] container_size      sizeof(\c container)
        \throw EncoderConfigurationException
        \throw MemoryAllocationException
        \throw WriteFileException
        \warning \c container must not be null.
        \warning \c container_size must be > 0.
        \warning \c container_size must be <= INT_MAX because lame cannot handle > 2GB per write.
        \warning \c container_size must be multiple of the number of audio channels.
        */
        Lame(const boost::filesystem::path &path,
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
             uint64_t container_size);

        /*!
        \throw MemoryAllocationException
        \throw WriteFileException
        */
        virtual void WriteFrames(uint64_t container_valid_frame_count);
        virtual ~Lame(void);
};

template<>
class Lame<void> : public Encoder<void>
{
    private:
        static const Sample::SampleContainer supported_containers[3];

    public:
        Lame(void) = default;
        Lame(const Lame &) = delete;
        Lame & operator=(const Lame &) = delete;

        virtual const Sample::SampleContainer * GetSupportedContainers(void) const noexcept;
        virtual size_t GetSupportedContainersCount(void) const noexcept;
};
}
}

#endif
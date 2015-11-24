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

#ifndef CODECS_SNDFILE_ENCODER_H
#define CODECS_SNDFILE_ENCODER_H

#include "../core/exception.h"
#include "../core/file_writer.h"
#include "encoder.h"
#include "sndfile_encoder_profile.h"
#include "samples.h"
#include "sndfile.h"

namespace rusty
{
namespace codecs
{
/*!
Encoder for WAV (Microsoft), AIFF (Apple/SGI), AU (Sun/NeXT), PAF (Ensoniq PARIS), IFF (Amiga IFF/SVX8/SV16),
WAV (NIST Sphere), VOC (Creative Labs), SF (Berkeley/IRCAM/CARL), W64 (SoundFoundry WAVE 64),
MAT4 (GNU Octave 2.0 / Matlab 4.2), MAT5 (GNU Octave 2.1 / Matlab 5.0), PVF (Portable Voice Format),
XI (FastTracker 2), HTK (HMM Tool Kit), SDS(Midi Sample Dump Standard), AVR (Audio Visual Research),
WAVEX (Microsoft), SD2 (Sound Designer II), CAF (Apple Core Audio File), WVE(Psion Series 3),
MPC(Akai MPC 2k), RF64 (RIFF 64).
*/
template<class T>
class SndFileEncoder : public Encoder<T>
{
    private:
        std::unique_ptr<core::FileWriter> file_writer;

        SF_INFO sfinfo;
        SNDFILE *sndfile = nullptr;
        T *container = nullptr;
        uint64_t container_size = 0;
        uint64_t container_frame_capacity = 0;
        uint64_t valid_output_frame_count = 0;

        void SndFileEncoder2(const boost::filesystem::path path, int sample_rate, int channel_count, SndFileEncoderProfile::OutputFormat format, T *container, uint64_t container_size);
        virtual void SetFrameBuffer(T *container, uint64_t container_size);

    public:
        SndFileEncoder(const SndFileEncoder &) = delete;
        SndFileEncoder & operator=(const SndFileEncoder &) = delete;

        /*!
        Initialize libsndfile encoder.
        \param[in] path           Output file path.
        \param[in] sample_rate    Input audio sample rate.
        \param[in] channel_count  Number of input audio channels.
        \param[in] format         Output file format.
        \param[in] container      Pointer to the buffer which contains audio samples.
        \param[in] container_size sizeof(\c container)
        \throw WriteFileException
        \warning \c container must not be null.
        \warning \c container_size must be > 0.
        \warning \c container_size must be multiple of the number of audio channels.
        */
        SndFileEncoder(const boost::filesystem::path path, int sample_rate, int channel_count, SndFileEncoderProfile::OutputFormat format, T *container, uint64_t container_size);

        /*!
        \throw WriteFileException
        */
        virtual void WriteFrames(uint64_t container_valid_frame_count);

        virtual ~SndFileEncoder(void);
};

template<>
class SndFileEncoder<void> : public Encoder<void>
{
    private:
        std::unique_ptr<core::FileWriter> file_writer;

        static const Sample::SampleContainer supported_containers[4];

    public:
        SndFileEncoder(void) = default;
        SndFileEncoder(const SndFileEncoder &) = delete;
        SndFileEncoder & operator=(const SndFileEncoder &) = delete;

        virtual const Sample::SampleContainer * GetSupportedContainers(void) const noexcept;
        virtual size_t GetSupportedContainersCount(void) const noexcept;
};
}
}

#endif
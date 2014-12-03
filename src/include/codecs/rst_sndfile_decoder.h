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

#ifndef CODECS_RST_SNDFILE_DECODER_H
#define CODECS_RST_SNDFILE_DECODER_H

/*!
Decoder for WAV (Microsoft), AIFF (Apple/SGI), AU (Sun/NeXT), PAF (Ensoniq PARIS), IFF (Amiga IFF/SVX8/SV16),
WAV (NIST Sphere), VOC (Creative Labs), SF (Berkeley/IRCAM/CARL), W64 (SoundFoundry WAVE 64),
MAT4 (GNU Octave 2.0 / Matlab 4.2), MAT5 (GNU Octave 2.1 / Matlab 5.0), PVF (Portable Voice Format),
XI (FastTracker 2), HTK (HMM Tool Kit), SDS(Midi Sample Dump Standard), AVR (Audio Visual Research),
WAVEX (Microsoft), SD2 (Sound Designer II), CAF (Apple Core Audio File), WVE(Psion Series 3),
MPC(Akai MPC 2k), RF64 (RIFF 64).
*/
template<class T>
class SndFileDecoder : public Decoder<T>
{
    private:
        SF_INFO sfinfo;
        SNDFILE *sndfile = nullptr;
        T *container = nullptr;
        uint64_t container_size = 0;
        uint64_t container_frame_capacity = 0;
        uint64_t container_valid_frame_count = 0;

        void SndFileDecoder2(const char * const file, T *container, uint64_t container_size);
        inline void ReadFrames2(void);
        virtual void SetFrameBuffer(T *container, uint64_t container_size);

    public:
        SndFileDecoder(const SndFileDecoder &) = delete;
        SndFileDecoder & operator=(const SndFileDecoder &) = delete;

        /*!
        Initialize libsndfile decoder.
        \param[in]  file           Input file path.
        \param[out] container      Pointer to the buffer which contains audio samples.
        \param[in]  container_size sizeof(\c container)
        \throw ReadFileException
        \warning \c container must not be null.
        \warning \c container_size must be > 0.
        \warning \c container_size must be multiple of the number of audio channels.
        */
        SndFileDecoder(const char * const file, T * container, uint64_t container_size);

        /*!
        \throw SeekException
        */
        virtual uint64_t GetCurrentFrameOffset(void) const;

        /*!
        \throw SeekException
        */
        virtual uint64_t SeekToFrame(SeekPosition position, int64_t offset);

        /*!
        \throw ReadFileException
        */
        virtual uint64_t ReadFrames(void);

        virtual ~SndFileDecoder(void);
};

template<>
class SndFileDecoder<void> : public Decoder<void>
{
    private:
        const size_t valid_containers_count = 4;
        SF_INFO sfinfo;
        SNDFILE *sndfile = nullptr;

    public:
        SndFileDecoder(const SndFileDecoder &) = delete;
        SndFileDecoder & operator=(const SndFileDecoder &) = delete;

        /*!
        Initialize libsndfile analyzer.
        \param[in] file Input file path.
        \throw ReadFileException
        */
        SndFileDecoder(const char * const file);

        virtual unsigned int GetChannelCount(void) const noexcept;
        virtual unsigned int GetSampleRate(void) const noexcept;
        virtual uint64_t GetFrameCount(void) const noexcept;
        virtual Sample::SampleContainer GetPreferableOutputContainer(void) const noexcept;
        virtual size_t GetValidContainersCount(void) const noexcept;
        ~SndFileDecoder(void);
};

#endif
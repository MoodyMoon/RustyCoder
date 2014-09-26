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

#ifndef CODECS_RST_SNDFILE_ENCODER_H
#define CODECS_RST_SNDFILE_ENCODER_H

class SndFileEncoderOptions
{
    public:
        /*!
        Valid output formats are extracted from sndfile.c function "sf_format_check" Format names are from command.c
        */
        enum OutputFormat
        {
            /*! WAV (Microsoft) */
            WAV_PCM_INT_U8 = SF_FORMAT_WAV | SF_FORMAT_PCM_U8,
            WAV_PCM_INT_S16 = SF_FORMAT_WAV | SF_FORMAT_PCM_16,
            WAV_PCM_INT_S24 = SF_FORMAT_WAV | SF_FORMAT_PCM_24,
            WAV_PCM_INT_S32 = SF_FORMAT_WAV | SF_FORMAT_PCM_32,
            WAV_PCM_FLOAT_32 = SF_FORMAT_WAV | SF_FORMAT_FLOAT,
            WAV_PCM_FLOAT_64 = SF_FORMAT_WAV | SF_FORMAT_DOUBLE,
            WAV_ULAW = SF_FORMAT_WAV | SF_FORMAT_ULAW,
            WAV_ALAW = SF_FORMAT_WAV | SF_FORMAT_ALAW,
            WAV_IMA_ADPACM = SF_FORMAT_WAV | SF_FORMAT_IMA_ADPCM,
            WAV_MS_ADPACM = SF_FORMAT_WAV | SF_FORMAT_MS_ADPCM,
            WAV_GSM610 = SF_FORMAT_WAV | SF_FORMAT_GSM610,
            WAV_G721_32_ADPCM = SF_FORMAT_WAV | SF_FORMAT_G721_32,

            /*! AIFF (Apple/SGI) */
            AIFF_PCM_INT_U8 = SF_FORMAT_AIFF | SF_FORMAT_PCM_U8,
            AIFF_PCM_INT_S8 = SF_FORMAT_AIFF | SF_FORMAT_PCM_S8,
            AIFF_PCM_INT_S16 = SF_FORMAT_AIFF | SF_FORMAT_PCM_16,
            AIFF_PCM_INT_S24 = SF_FORMAT_AIFF | SF_FORMAT_PCM_24,
            AIFF_PCM_INT_S32 = SF_FORMAT_AIFF | SF_FORMAT_PCM_32,
            AIFF_PCM_FLOAT_32 = SF_FORMAT_AIFF | SF_FORMAT_FLOAT,
            AIFF_PCM_FLOAT_64 = SF_FORMAT_AIFF | SF_FORMAT_DOUBLE,
            AIFF_ULAW = SF_FORMAT_AIFF | SF_FORMAT_ULAW,
            AIFF_ALAW = SF_FORMAT_AIFF | SF_FORMAT_ALAW,
            AIFF_IMA_ADPCM = SF_FORMAT_AIFF | SF_FORMAT_IMA_ADPCM,
            AIFF_GSM610 = SF_FORMAT_AIFF | SF_FORMAT_GSM610,
            AIFF_DWVW_12 = SF_FORMAT_AIFF | SF_FORMAT_DWVW_12,
            AIFF_DWVW_16 = SF_FORMAT_AIFF | SF_FORMAT_DWVW_16,
            AIFF_DWVW_24 = SF_FORMAT_AIFF | SF_FORMAT_DWVW_24,

            /*! AU (Sun/NeXT) */
            AU_PCM_INT_S8 = SF_FORMAT_AU | SF_FORMAT_PCM_S8,
            AU_PCM_INT_S16 = SF_FORMAT_AU | SF_FORMAT_PCM_16,
            AU_PCM_INT_S24 = SF_FORMAT_AU | SF_FORMAT_PCM_24,
            AU_PCM_INT_S32 = SF_FORMAT_AU | SF_FORMAT_PCM_32,
            AU_PCM_FLOAT_32 = SF_FORMAT_AU | SF_FORMAT_FLOAT,
            AU_PCM_FLOAT_64 = SF_FORMAT_AU | SF_FORMAT_DOUBLE,
            AU_ULAW = SF_FORMAT_AU | SF_FORMAT_ULAW,
            AU_ALAW = SF_FORMAT_AU | SF_FORMAT_ALAW,
            AU_G721_32_ADPCM = SF_FORMAT_AU | SF_FORMAT_G721_32,
            AU_G723_24_ADPCM = SF_FORMAT_AU | SF_FORMAT_G723_24,
            AU_G723_40_ADPCM = SF_FORMAT_AU | SF_FORMAT_G723_40,

            /*! PAF (Ensoniq PARIS) */
            PAF_PCM_INT_S8 = SF_FORMAT_PAF | SF_FORMAT_PCM_S8,
            PAF_PCM_INT_S16 = SF_FORMAT_PAF | SF_FORMAT_PCM_16,
            PAF_PCM_INT_S24 = SF_FORMAT_PAF | SF_FORMAT_PCM_24,

            /*! IFF (Amiga IFF/SVX8/SV16) */
            SVX_PCM_INT_S8 = SF_FORMAT_SVX | SF_FORMAT_PCM_S8,
            SVX_PCM_INT_S16 = SF_FORMAT_SVX | SF_FORMAT_PCM_16,

            /*! WAV (NIST Sphere) */
            NIST_PCM_INT_S8 = SF_FORMAT_NIST | SF_FORMAT_PCM_S8,
            NIST_PCM_INT_S16 = SF_FORMAT_NIST | SF_FORMAT_PCM_16,
            NIST_PCM_INT_S24 = SF_FORMAT_NIST | SF_FORMAT_PCM_24,
            NIST_PCM_INT_S32 = SF_FORMAT_NIST | SF_FORMAT_PCM_32,
            NIST_ULAW = SF_FORMAT_NIST | SF_FORMAT_ULAW,
            NIST_ALAW = SF_FORMAT_NIST | SF_FORMAT_ALAW,

            /*! VOC (Creative Labs) */
            VOC_PCM_INT_U8 = SF_FORMAT_VOC | SF_FORMAT_PCM_U8,
            VOC_PCM_INT_S16 = SF_FORMAT_VOC | SF_FORMAT_PCM_16,
            VOC_ULAW = SF_FORMAT_VOC | SF_FORMAT_ULAW,
            VOC_ALAW = SF_FORMAT_VOC | SF_FORMAT_ALAW,

            /*! SF (Berkeley/IRCAM/CARL) */
            IRCAM_PCM_INT_S16 = SF_FORMAT_IRCAM | SF_FORMAT_PCM_16,
            IRCAM_PCM_INT_S32 = SF_FORMAT_IRCAM | SF_FORMAT_PCM_32,
            IRCAM_PCM_FLOAT_32 = SF_FORMAT_IRCAM | SF_FORMAT_FLOAT,
            IRCAM_ULAW = SF_FORMAT_IRCAM | SF_FORMAT_ULAW,
            IRCAM_ALAW = SF_FORMAT_IRCAM | SF_FORMAT_ALAW,

            /*! W64 (SoundFoundry WAVE 64) */
            W64_PCM_INT_U8 = SF_FORMAT_W64 | SF_FORMAT_PCM_U8,
            W64_PCM_INT_S16 = SF_FORMAT_W64 | SF_FORMAT_PCM_16,
            W64_PCM_INT_S24 = SF_FORMAT_W64 | SF_FORMAT_PCM_24,
            W64_PCM_INT_S32 = SF_FORMAT_W64 | SF_FORMAT_PCM_32,
            W64_PCM_FLOAT_32 = SF_FORMAT_W64 | SF_FORMAT_FLOAT,
            W64_PCM_FLOAT_64 = SF_FORMAT_W64 | SF_FORMAT_DOUBLE,
            W64_ULAW = SF_FORMAT_W64 | SF_FORMAT_ULAW,
            W64_ALAW = SF_FORMAT_W64 | SF_FORMAT_ALAW,
            W64_IMA_ADPCM = SF_FORMAT_W64 | SF_FORMAT_IMA_ADPCM,
            W64_MS_ADPCM = SF_FORMAT_W64 | SF_FORMAT_MS_ADPCM,
            W64_GSM610 = SF_FORMAT_W64 | SF_FORMAT_GSM610,

            /*! MAT4 (GNU Octave 2.0 / Matlab 4.2) */
            MAT4_PCM_INT_S16 = SF_FORMAT_MAT4 | SF_FORMAT_PCM_16,
            MAT4_PCM_INT_S32 = SF_FORMAT_MAT4 | SF_FORMAT_PCM_32,
            MAT4_PCM_FLOAT_32 = SF_FORMAT_MAT4 | SF_FORMAT_FLOAT,
            MAT4_PCM_FLOAT_64 = SF_FORMAT_MAT4 | SF_FORMAT_DOUBLE,

            /*! MAT5 (GNU Octave 2.1 / Matlab 5.0) */
            MAT5_PCM_INT_U8 = SF_FORMAT_MAT5 | SF_FORMAT_PCM_U8,
            MAT5_PCM_INT_S16 = SF_FORMAT_MAT5 | SF_FORMAT_PCM_16,
            MAT5_PCM_INT_S32 = SF_FORMAT_MAT5 | SF_FORMAT_PCM_32,
            MAT5_PCM_FLOAT_32 = SF_FORMAT_MAT5 | SF_FORMAT_FLOAT,
            MAT5_PCM_FLOAT_64 = SF_FORMAT_MAT5 | SF_FORMAT_DOUBLE,

            /*! PVF (Portable Voice Format) */
            PVF_PCM_INT_S8 = SF_FORMAT_PVF | SF_FORMAT_PCM_S8,
            PVF_PCM_INT_S16 = SF_FORMAT_PVF | SF_FORMAT_PCM_16,
            PVF_PCM_INT_S32 = SF_FORMAT_PVF | SF_FORMAT_PCM_32,

            /*! XI (FastTracker 2) */
            XI_DPCM_8 = SF_FORMAT_XI | SF_FORMAT_DPCM_8,
            XI_DPCM_16 = SF_FORMAT_XI | SF_FORMAT_DPCM_16,

            /*! HTK (HMM Tool Kit) */
            HTK_PCM_INT_S16 = SF_FORMAT_HTK | SF_FORMAT_PCM_16,

            /*! SDS(Midi Sample Dump Standard) */
            SDS_PCM_INT_S8 = SF_FORMAT_SDS | SF_FORMAT_PCM_S8,
            SDS_PCM_INT_S16 = SF_FORMAT_SDS | SF_FORMAT_PCM_16,
            SDS_PCM_INT_S24 = SF_FORMAT_SDS | SF_FORMAT_PCM_24,

            /*! AVR (Audio Visual Research) */
            AVR_PCM_INT_U8 = SF_FORMAT_AVR | SF_FORMAT_PCM_U8,
            AVR_PCM_INT_S8 = SF_FORMAT_AVR | SF_FORMAT_PCM_S8,
            AVR_PCM_INT_S16 = SF_FORMAT_AVR | SF_FORMAT_PCM_16,

            /*! WAVEX (Microsoft) */
            WAVEX_PCM_INT_U8 = SF_FORMAT_WAVEX | SF_FORMAT_PCM_U8,
            WAVEX_PCM_INT_S16 = SF_FORMAT_WAVEX | SF_FORMAT_PCM_16,
            WAVEX_PCM_INT_S24 = SF_FORMAT_WAVEX | SF_FORMAT_PCM_24,
            WAVEX_PCM_INT_S32 = SF_FORMAT_WAVEX | SF_FORMAT_PCM_32,
            WAVEX_PCM_FLOAT_32 = SF_FORMAT_WAVEX | SF_FORMAT_FLOAT,
            WAVEX_PCM_FLOAT_64 = SF_FORMAT_WAVEX | SF_FORMAT_DOUBLE,
            WAVEX_ULAW = SF_FORMAT_WAVEX | SF_FORMAT_ULAW,
            WAVEX_ALAW = SF_FORMAT_WAVEX | SF_FORMAT_ALAW,

            /*! SD2 (Sound Designer II) */
            SD2_PCM_INT_S8 = SF_FORMAT_SD2 | SF_FORMAT_PCM_S8,
            SD2_PCM_INT_S16 = SF_FORMAT_SD2 | SF_FORMAT_PCM_16,
            SD2_PCM_INT_S24 = SF_FORMAT_SD2 | SF_FORMAT_PCM_24,

            /*! CAF (Apple Core Audio File) */
            CAF_PCM_INT_S8 = SF_FORMAT_CAF | SF_FORMAT_PCM_S8,
            CAF_PCM_INT_S16 = SF_FORMAT_CAF | SF_FORMAT_PCM_16,
            CAF_PCM_INT_S24 = SF_FORMAT_CAF | SF_FORMAT_PCM_24,
            CAF_PCM_INT_S32 = SF_FORMAT_CAF | SF_FORMAT_PCM_32,
            CAF_PCM_FLOAT_32 = SF_FORMAT_CAF | SF_FORMAT_FLOAT,
            CAF_PCM_FLOAT_64 = SF_FORMAT_CAF | SF_FORMAT_DOUBLE,
            CAF_ULAW = SF_FORMAT_CAF | SF_FORMAT_ULAW,
            CAF_ALAW = SF_FORMAT_CAF | SF_FORMAT_ALAW,

            /*! WVE(Psion Series 3) */
            WVE_ALAW = SF_FORMAT_WVE | SF_FORMAT_ALAW,

            /*! MPC(Akai MPC 2k) */
            MPC2K_PCM_INT_S16 = SF_FORMAT_MPC2K | SF_FORMAT_PCM_16,

            /*! RF64 (RIFF 64) */
            RF64_PCM_INT_U8 = SF_FORMAT_RF64 | SF_FORMAT_PCM_U8,
            RF64_PCM_INT_S16 = SF_FORMAT_RF64 | SF_FORMAT_PCM_16,
            RF64_PCM_INT_S24 = SF_FORMAT_RF64 | SF_FORMAT_PCM_24,
            RF64_PCM_INT_S32 = SF_FORMAT_RF64 | SF_FORMAT_PCM_32,
            RF64_PCM_FLOAT_32 = SF_FORMAT_RF64 | SF_FORMAT_FLOAT,
            RF64_PCM_FLOAT_64 = SF_FORMAT_RF64 | SF_FORMAT_DOUBLE,
            RF64_ULAW = SF_FORMAT_RF64 | SF_FORMAT_ULAW,
            RF64_ALAW = SF_FORMAT_RF64 | SF_FORMAT_ALAW
        };

        OutputFormat format;
};

/*!
Encoder for WAV (Microsoft), AIFF (Apple/SGI), AU (Sun/NeXT), PAF (Ensoniq PARIS), IFF (Amiga IFF/SVX8/SV16),
WAV (NIST Sphere), VOC (Creative Labs), SF (Berkeley/IRCAM/CARL), W64 (SoundFoundry WAVE 64),
MAT4 (GNU Octave 2.0 / Matlab 4.2), MAT5 (GNU Octave 2.1 / Matlab 5.0), PVF (Portable Voice Format),
XI (FastTracker 2), HTK (HMM Tool Kit), SDS(Midi Sample Dump Standard), AVR (Audio Visual Research),
WAVEX (Microsoft), SD2 (Sound Designer II), CAF (Apple Core Audio File), WVE(Psion Series 3),
MPC(Akai MPC 2k), RF64 (RIFF 64).
*/
template<class T>
class SndFileEncoder : public EncoderInterface<T>
{
    private:
        SF_INFO sfinfo;
        SNDFILE *sndfile = nullptr;
        T *container = nullptr;
        uint64_t container_size = 0;
        uint64_t container_frame_capacity = 0;
        uint64_t valid_output_frame_count = 0;

        void SndFileEncoder2(const char * const file, int sample_rate, int channel_count, SndFileEncoderOptions::OutputFormat format, T *container, uint64_t container_size);
        virtual void SetFrameBuffer(T *container, uint64_t container_size);

    public:
        SndFileEncoder(const SndFileEncoder &) = delete;
        SndFileEncoder & operator=(const SndFileEncoder &) = delete;

        /*!
        Initialize libsndfile encoder.
        \param[in] file           Output file path.
        \param[in] sample_rate    Input audio sample rate.
        \param[in] channel_count  Number of input audio channels.
        \param[in] format         Output file format.
        \param[in] container      Pointer to the buffer which contains audio samples.
        \param[in] container_size sizeof(\c container)
        \throw UnimplementedFeatureException
        \throw UnsupportedFormatException
        \throw WriteFileException
        \warning \c container must not be null.
        \warning \c container_size must be > 0.
        \warning \c container_size must be multiple of the number of audio channels.
        */
        SndFileEncoder(const char * const file, int sample_rate, int channel_count, SndFileEncoderOptions::OutputFormat format, T *container, uint64_t container_size);

        virtual const char * const GetFileExtension(void) const noexcept;

        /*!
        \throw WriteFileException
        */
        virtual void WriteFrames(uint64_t container_valid_frame_count);

        virtual ~SndFileEncoder(void);
};

template<>
class SndFileEncoder<void> : public EncoderInterface<void>
{
    public:
        const size_t valid_containers_count = 4;

        SndFileEncoder(const SndFileEncoder &) = delete;
        SndFileEncoder & operator=(const SndFileEncoder &) = delete;

        SndFileEncoder(void);
        virtual size_t GetValidContainersCount(void) const noexcept;
};

#endif
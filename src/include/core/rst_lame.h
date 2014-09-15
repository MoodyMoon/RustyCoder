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

#ifndef CORE_RST_LAME_H
#define CORE_RST_LAME_H

/*!
Encoder for (MPEG-1, MPEG-2, MPEG-2.5) Audio Layer III
*/
template<class T>
class Lame : public EncoderInterface<T>
{
    public:
        /*!
        Similar to \c -q in lame command line
        */
        enum AlgorithmQuality
        {
            Q0, /*!< <tt>-q 0</tt> (Best quality, slowest) average 245kbps*/
            Q1, /*!< <tt>-q 1</tt> */
            Q2, /*!< <tt>-q 2</tt> average 190kbps */
            Q3, /*!< <tt>-q 3</tt> average 175kbps */
            Q4, /*!< <tt>-q 4</tt> average 165kbps */
            Q5, /*!< <tt>-q 5</tt> average 130kbps */
            Q6, /*!< <tt>-q 6</tt> */
            Q7, /*!< <tt>-q 7</tt> */
            Q8, /*!< <tt>-q 8</tt> */
            Q9  /*!< <tt>-q 9</tt> (Low quality, fastest) */
        };
        
        /*!
        Similar to \c -m in lame command line
        */
        enum Mode
        {
            STEREO = MPEG_mode::STEREO,             /*!< <tt>-m s</tt> */
            JOINT_STEREO = MPEG_mode::JOINT_STEREO, /*!< <tt>-m j</tt> */
            MONO = MPEG_mode::MONO                  /*!< <tt>-m m</tt> */
        };
        
        /*!
        Similar to \c --*+replaygain*+ in lame command line
        */
        enum ReplayGain
        {
            NONE,    /*!< <tt>\--noreplaygain</tt> */
            FAST,    /*!< <tt>\--replaygain-fast</tt> */
            ACCURATE /*!< <tt>\--replaygain-accurate</tt> */
        };
        
        /*!
        Bitrate encoding selection
        */
        enum BitrateEncoding
        {
            CONSTANT = vbr_mode::vbr_off,      /*!< <tt>\--cbr -b \<bitrate\></tt> */
            VARIABLE_OLD = vbr_mode::vbr_rh,   /*!< <tt>\--vbr-old</tt> */
            VARIABLE_NEW = vbr_mode::vbr_mtrh, /*!< <tt>\--vbr-new</tt> */
            AVERAGE = vbr_mode::vbr_abr        /*!< <tt>\--abr \<bitrate\></tt> */
        };
        
        /*!
        For the option \c -b and \c -B in lame command line. Obtained from LAME USAGE.\n\n
        
        <tt>
        MPEG-1   layer III sample frequencies (kHz):  32  48  44.1\n
        bitrates (kbps): 32 40 48 56 64 80 96 112 128 160 192 224 256 320\n\n

        MPEG-2   layer III sample frequencies (kHz):  16  24  22.05\n
        bitrates (kbps):  8 16 24 32 40 48 56 64 80 96 112 128 144 160\n\n

        MPEG-2.5 layer III sample frequencies (kHz):   8  12  11.025\n
        bitrates (kbps):  8 16 24 32 40 48 56 64
        </tt>
        */
        enum Bitrate
        {
            B_8 = 8,
            B_16 = 16,
            B_24 = 24,
            B_32 = 32,
            B_40 = 40,
            B_48 = 48,
            B_56 = 56,
            B_64 = 64,
            B_80 = 80,
            B_96 = 96,
            B_112 = 112,
            B_128 = 128,
            B_144 = 144,
            B_160 = 160,
            B_192 = 192,
            B_224 = 224,
            B_256 = 256,
            B_320 = 320
        };

        enum Tag
        {
            ID3V1_TAG,
            ID3V2_TAG,
            XING_FRAME
        };
    
    private:
        lame_t gf = nullptr;
        bool encountered_start_frame = true;
        bool encountered_end_frame = false;
        std::unique_ptr<FileWriter> writer;
        std::unique_ptr<unsigned char> mp3buffer;
        int error;
        int mp3buffer_size;
        unsigned int channel_count;
        const char * const layer3_extension = "mp3";
        T *container = nullptr;
        uint64_t container_size = 0;
        uint64_t container_frame_capacity = 0;
        uint64_t valid_output_frame_count = 0;
        
        void Lame2(const char * const file,
                   int sample_rate,
                   int channel_count,
                   AlgorithmQuality algorithm_quality,
                   Mode mode,
                   ReplayGain replaygain_mode,
                   bool copyright,
                   bool use_naoki_psytune,
                   BitrateEncoding bitrate_encoding,
                   float vbr_quality,
                   Bitrate min_or_max_bitrate1,
                   Bitrate min_or_max_bitrate2,
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
        \param[in] file                Output file path.
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
        \throw UnimplementedFeatureException
        \throw UnsupportedFormatException
        \throw WriteFileException
        \warning \c container must not be null.
        \warning \c container_size must be > 0.
        \warning \c container_size must be <= INT_MAX because lame cannot handle > 2GB per write.
        \warning \c container_size must be multiple of the number of audio channels.
        */
        Lame(const char * const file,
             int sample_rate,
             int channel_count,
             AlgorithmQuality algorithm_quality,
             Mode mode,
             ReplayGain replaygain_mode,
             bool copyright,
             bool use_naoki_psytune,
             BitrateEncoding bitrate_encoding,
             float vbr_quality,
             Bitrate min_or_max_bitrate1,
             Bitrate min_or_max_bitrate2,
             T *container,
             uint64_t container_size);

        virtual const char * const GetFileExtension(void) const noexcept;
        
        /*!
        \throw MemoryAllocationException
        \throw WriteFileException
        */
        virtual void WriteFrames(uint64_t container_valid_frame_count);
        virtual ~Lame(void);
};

template<>
class Lame<void> : public EncoderInterface<void>
{
    public:
        static const Samples::SampleContainers valid_containers[3];

        Lame() = delete;
        Lame(const Lame &) = delete;
        Lame & operator=(const Lame &) = delete;
};

#endif
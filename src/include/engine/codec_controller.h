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

#ifndef ENGINE_CODEC_CONTROLLER_H
#define ENGINE_CODEC_CONTROLLER_H

#include "../codecs/decoder.h"
#include "../codecs/encoder.h"
#include "../codecs/encoder_profile.h"
#include "../codecs/lame.h"
#include "../codecs/lame_profile.h"
#include "../codecs/mpg123.h"
#include "../codecs/sndfile_decoder.h"
#include "../codecs/sndfile_encoder.h"
#include "../codecs/sndfile_encoder_profile.h"

namespace rusty
{
namespace engine
{
class CodecController
{
    private:
        const boost::filesystem::path source_file_path;
        const boost::filesystem::path output_file_path;
        codecs::Decoder<void>::ID decoder_id;
        codecs::Encoder<void>::ID encoder_id;
        codecs::Sample::SampleContainer chosen_container_type;
        std::unique_ptr<const codecs::LameProfile> lame_profile;
        std::unique_ptr<const codecs::SndFileEncoderProfile> sndfile_encoder_profile;
        std::unique_ptr<codecs::Mpg123LifetimeHandler> mpg123_lifetime_handler;

        std::unique_ptr<codecs::Decoder<char>> decoder_char;
        std::unique_ptr<codecs::Decoder<unsigned char>> decoder_u_char;
        std::unique_ptr<codecs::Decoder<short>> decoder_short;
        std::unique_ptr<codecs::Decoder<unsigned short>> decoder_u_short;
        std::unique_ptr<codecs::Decoder<int>> decoder_int;
        std::unique_ptr<codecs::Decoder<unsigned int>> decoder_u_int;
        std::unique_ptr<codecs::Decoder<float>> decoder_float;
        std::unique_ptr<codecs::Decoder<double>> decoder_double;

        std::unique_ptr<codecs::Encoder<char>> encoder_char;
        std::unique_ptr<codecs::Encoder<unsigned char>> encoder_u_char;
        std::unique_ptr<codecs::Encoder<short>> encoder_short;
        std::unique_ptr<codecs::Encoder<unsigned short>> encoder_u_short;
        std::unique_ptr<codecs::Encoder<int>> encoder_int;
        std::unique_ptr<codecs::Encoder<unsigned int>> encoder_u_int;
        std::unique_ptr<codecs::Encoder<float>> encoder_float;
        std::unique_ptr<codecs::Encoder<double>> encoder_double;

        std::unique_ptr<char> sample_buffer_char;
        std::unique_ptr<unsigned char> sample_buffer_u_char;
        std::unique_ptr<short> sample_buffer_short;
        std::unique_ptr<unsigned short> sample_buffer_u_short;
        std::unique_ptr<int> sample_buffer_int;
        std::unique_ptr<unsigned int> sample_buffer_u_int;
        std::unique_ptr<float> sample_buffer_float;
        std::unique_ptr<double> sample_buffer_double;

        codecs::Decoder<char> *_decoder_char = nullptr;
        codecs::Decoder<unsigned char> *_decoder_u_char = nullptr;
        codecs::Decoder<short> *_decoder_short = nullptr;
        codecs::Decoder<unsigned short> *_decoder_u_short = nullptr;
        codecs::Decoder<int> *_decoder_int = nullptr;
        codecs::Decoder<unsigned int> *_decoder_u_int = nullptr;
        codecs::Decoder<float> *_decoder_float = nullptr;
        codecs::Decoder<double> *_decoder_double = nullptr;

        codecs::Encoder<char> *_encoder_char = nullptr;
        codecs::Encoder<unsigned char> *_encoder_u_char = nullptr;
        codecs::Encoder<short> *_encoder_short = nullptr;
        codecs::Encoder<unsigned short> *_encoder_u_short = nullptr;
        codecs::Encoder<int> *_encoder_int = nullptr;
        codecs::Encoder<unsigned int> *_encoder_u_int = nullptr;
        codecs::Encoder<float> *_encoder_float = nullptr;
        codecs::Encoder<double> *_encoder_double = nullptr;

        const unsigned int min_samples_in_buffer = 2520; /*!< least common multiple of 1-9 channels. Current maximum number of channels in a single track as far as I know. */
        const unsigned int max_samples_in_buffer = min_samples_in_buffer * 13;
        unsigned int channel_count;
        unsigned int sample_rate;

        uint64_t total_frame_count;
        bool can_convert = true;

        uint64_t buffer_valid_frames_count;
        uint64_t max_buffer_valid_frames_count;

        void PopulateAudioProperties(void);
        void BeforeConvert(void);

    public:
        CodecController(const CodecController &) = delete;
        CodecController & operator=(const CodecController &) = delete;

        CodecController(const boost::filesystem::path source_file_path, const boost::filesystem::path output_file_path, codecs::Decoder<void>::ID decoder_id, const codecs::EncoderProfile &encoder_profile, codecs::Encoder<void>::ID encoder_id);

        uint64_t Convert(void);
        unsigned int GetChannelCount(void);
        unsigned int GetSampleRate(void);

        uint64_t GetTotalFrameCount(void);
        bool CanConvert(void);
};
}
}

#endif
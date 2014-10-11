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

#ifndef ENGINE_CODEC_CONTROLLER_H
#define ENGINE_CODEC_CONTROLLER_H

class CodecController
{
    private:
        std::string source_file_full_path;
        std::string output_file_full_path;
        Decoder<void>::DecoderID decoder_id;
        Encoder<void>::EncoderID encoder_id;
        Sample::SampleContainer chosen_container_type;
        std::unique_ptr<EncoderOptions> encoder_options;
        std::unique_ptr<Mpg123LifetimeHandler> mpg123_lifetime_handler;

        std::unique_ptr<Decoder<char>> decoder_char;
        std::unique_ptr<Decoder<unsigned char>> decoder_u_char;
        std::unique_ptr<Decoder<short>> decoder_short;
        std::unique_ptr<Decoder<unsigned short>> decoder_u_short;
        std::unique_ptr<Decoder<int>> decoder_int;
        std::unique_ptr<Decoder<unsigned int>> decoder_u_int;
        std::unique_ptr<Decoder<float>> decoder_float;
        std::unique_ptr<Decoder<double>> decoder_double;

        std::unique_ptr<Encoder<char>> encoder_char;
        std::unique_ptr<Encoder<unsigned char>> encoder_u_char;
        std::unique_ptr<Encoder<short>> encoder_short;
        std::unique_ptr<Encoder<unsigned short>> encoder_u_short;
        std::unique_ptr<Encoder<int>> encoder_int;
        std::unique_ptr<Encoder<unsigned int>> encoder_u_int;
        std::unique_ptr<Encoder<float>> encoder_float;
        std::unique_ptr<Encoder<double>> encoder_double;

        std::unique_ptr<char> sample_buffer_char;
        std::unique_ptr<unsigned char> sample_buffer_u_char;
        std::unique_ptr<short> sample_buffer_short;
        std::unique_ptr<unsigned short> sample_buffer_u_short;
        std::unique_ptr<int> sample_buffer_int;
        std::unique_ptr<unsigned int> sample_buffer_u_int;
        std::unique_ptr<float> sample_buffer_float;
        std::unique_ptr<double> sample_buffer_double;

        const unsigned int min_samples_in_buffer = 2520; /*!< least common multiple of 1-9 channels. Current maximum number of channels in a single track as far as I know. */
        const unsigned int max_samples_in_buffer = min_samples_in_buffer * 20;
        unsigned int channel_count;
        unsigned int sample_rate;
        uint64_t frame_count;

        void PopulateAudioProperties(void);
        void BeforeConvert(void);
        void Convert(void);

    public:
        CodecController(const CodecController &) = delete;
        CodecController & operator=(const CodecController &) = delete;

        CodecController(std::string source_file_full_path, std::string output_file_full_path, Decoder<void>::DecoderID decoder_id, SndFileEncoderOptions &options);
        CodecController(std::string source_file_full_path, std::string output_file_full_path, Decoder<void>::DecoderID decoder_id, LameOptions &options);
};

#endif
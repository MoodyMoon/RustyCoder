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

#ifndef CODECS_CODEC_CONTROLLER_H
#define CODECS_CODEC_CONTROLLER_H

class CodecController
{
    public:
        enum Decoder
        {
            SNDFILEDECODER,
            MPG123
        };

        enum Encoder
        {
            SNDFILEENCODER,
            LAME
        };

    private:
        const std::string source_file_full_path;
        const std::string output_file_full_path;
        Decoder decoder_id;
        Encoder encoder_id;
        SndFileEncoderOptions * const sndfileencoder_options = nullptr;
        LameOptions * const lame_options = nullptr;

        std::unique_ptr<DecoderInterface<char>> decoder_char;
        std::unique_ptr<DecoderInterface<unsigned char>> decoder_unsigned_char;
        std::unique_ptr<DecoderInterface<short>> decoder_short;
        std::unique_ptr<DecoderInterface<unsigned short>> decoder_unsigned_short;
        std::unique_ptr<DecoderInterface<int>> decoder_int;
        std::unique_ptr<DecoderInterface<unsigned int>> decoder_unsigned_int;
        std::unique_ptr<DecoderInterface<float>> decoder_float;
        std::unique_ptr<DecoderInterface<double>> decoder_double;

        std::unique_ptr<Mpg123LifetimeHandler> mpg123_lifetime_handler;

        std::unique_ptr<EncoderInterface<char>> encoder_char;
        std::unique_ptr<EncoderInterface<unsigned char>> encoder_unsigned_char;
        std::unique_ptr<EncoderInterface<short>> encoder_short;
        std::unique_ptr<EncoderInterface<unsigned short>> encoder_unsigned_short;
        std::unique_ptr<EncoderInterface<int>> encoder_int;
        std::unique_ptr<EncoderInterface<unsigned int>> encoder_unsigned_int;
        std::unique_ptr<EncoderInterface<float>> encoder_float;
        std::unique_ptr<EncoderInterface<double>> encoder_double;

        std::unique_ptr<char> sample_buffer_char;
        std::unique_ptr<unsigned char> sample_buffer_unsigned_char;
        std::unique_ptr<short> sample_buffer_short;
        std::unique_ptr<unsigned short> sample_buffer_unsigned_short;
        std::unique_ptr<int> sample_buffer_int;
        std::unique_ptr<unsigned int> sample_buffer_unsigned_int;
        std::unique_ptr<float> sample_buffer_float;
        std::unique_ptr<double> sample_buffer_double;

        uint64_t buffer_valid_frames_count;

        void CodecController2(void);
        Sample::SampleContainer GetPreferableOutputContainer(void);

    public:
        CodecController(const CodecController &) = delete;
        CodecController & operator=(const CodecController &) = delete;

        CodecController(std::string source_file_full_path, std::string output_file_full_path, Decoder decoder_id, Encoder encoder_id, SndFileEncoderOptions * const options);
        CodecController(std::string source_file_full_path, std::string output_file_full_path, Decoder decoder_id, Encoder encoder_id, LameOptions * const options);
        void Convert(void);
        ~CodecController(void);
};

#endif
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
#include "codec_controller.h"

CodecController::CodecController(std::string source_file_full_path, std::string output_file_full_path, DecoderID decoder_id, SndFileEncoderOptions &options) : source_file_full_path(source_file_full_path), output_file_full_path(output_file_full_path), decoder_id(decoder_id)
{
    encoder_id = EncoderID::SNDFILEENCODER;
    encoder_options.reset(new SndFileEncoderOptions());
    sndfileencoder_options = static_cast<SndFileEncoderOptions *>(encoder_options.get());
    sndfileencoder_options->format = options.format;
    chosen_container_type = GetPreferableOutputContainer();
}

CodecController::CodecController(std::string source_file_full_path, std::string output_file_full_path, DecoderID decoder_id, LameOptions &options) : source_file_full_path(source_file_full_path), output_file_full_path(output_file_full_path), decoder_id(decoder_id)
{
    encoder_id = EncoderID::LAME;
    encoder_options.reset(new LameOptions());
    lame_options = static_cast<LameOptions *>(encoder_options.get());
    lame_options->algorithm_quality = options.algorithm_quality;
    lame_options->mode = options.mode;
    lame_options->replaygain_mode = options.replaygain_mode;
    lame_options->copyright = options.copyright;
    lame_options->use_naoki_psytune = options.use_naoki_psytune;
    lame_options->bitrate_encoding = options.bitrate_encoding;
    lame_options->min_or_max_bitrate1 = options.min_or_max_bitrate1;
    lame_options->min_or_max_bitrate2 = options.min_or_max_bitrate2;
    chosen_container_type = GetPreferableOutputContainer();
}

Sample::SampleContainer CodecController::GetPreferableOutputContainer()
{
    std::unique_ptr<Decoder<void>> decoder_void;
    std::unique_ptr<Mpg123LifetimeHandler> mpg123_lifetime_handler;

    switch(decoder_id)
    {
        case DecoderID::SNDFILEDECODER:
        {
            decoder_void.reset(new SndFileDecoder<void>(source_file_full_path.c_str()));
            break;
        }
        default: /*!< MPG123 */
        {
            mpg123_lifetime_handler.reset(new Mpg123LifetimeHandler());
            decoder_void.reset(new Mpg123<void>(source_file_full_path.c_str(), *mpg123_lifetime_handler.get()));
            break;
        }
    }

    assert(decoder_void != nullptr);

    Sample::SampleContainer decoder_container_type = decoder_void->GetPreferableOutputContainer();

    std::unique_ptr<Encoder<void>> encoder_void;

    switch(encoder_id)
    {
        case EncoderID::SNDFILEENCODER:
            encoder_void.reset(new SndFileEncoder<void>());
            break;
        default: /*!< MPG123 */
            encoder_void.reset(new Lame<void>());
            break;
    }

    assert(encoder_void != nullptr);

    Encoder<void> *_encoder_void = encoder_void.get();
    Sample::SampleContainer *encoder_valid_containers = _encoder_void->valid_containers.get();
    size_t encoder_valid_containers_count = encoder_void->GetValidContainersCount();

    for(size_t i = 0; i < encoder_valid_containers_count; ++i)
    {
        if(decoder_container_type == encoder_valid_containers[i])
            return decoder_container_type;
    }

    Decoder<void> *_decoder_void = decoder_void.get();
    Sample::SampleContainer *decoder_valid_containers = _decoder_void->valid_containers.get();
    size_t decoder_valid_containers_count = _decoder_void->GetValidContainersCount();

    for(size_t i = decoder_valid_containers_count - 1; i >= 0; --i)
    {
        decoder_container_type = decoder_valid_containers[i];
        for(size_t j = encoder_valid_containers_count - 1; j >= 0; --j)
        {
            if(decoder_container_type == encoder_valid_containers[j])
                return decoder_container_type;
        }
    }

    assert(false);

    return Sample::SampleContainer::INT_S16; /*!< Fail safe */
}

void CodecController::BeforeConvert()
{
    switch(chosen_container_type)
    {
        case Sample::SampleContainer::INT_S8:
            sample_buffer_char.reset(new char[max_buffer]);
            break;
        case Sample::SampleContainer::INT_U8:
            sample_buffer_u_char.reset(new unsigned char[max_buffer]);
            break;
        case Sample::SampleContainer::INT_S16:
            sample_buffer_short.reset(new short[max_buffer]);
            break;
        case Sample::SampleContainer::INT_U16:
            sample_buffer_u_short.reset(new unsigned short[max_buffer]);
            break;
        case Sample::SampleContainer::INT_S32:
            sample_buffer_int.reset(new int[max_buffer]);
            break;
        case Sample::SampleContainer::INT_U32:
            sample_buffer_u_int.reset(new unsigned int[max_buffer]);
            break;
        case Sample::SampleContainer::FLOAT_32:
            sample_buffer_float.reset(new float[max_buffer]);
            break;
        default: /*!< Sample::SampleContainer::FLOAT_64 */
            sample_buffer_double.reset(new double[max_buffer]);
            break;
    }
    
    switch(decoder_id)
    {
        case DecoderID::SNDFILEDECODER:
        {
            switch(chosen_container_type)
            {
                case Sample::SampleContainer::INT_S16:
                {
                    short *buffer = sample_buffer_short.get();
                    decoder_short.reset(new SndFileDecoder<short>(source_file_full_path.c_str(), buffer, sizeof(buffer)));
                    break;
                }
                case Sample::SampleContainer::INT_S32:
                {
                    int *buffer = sample_buffer_int.get();
                    decoder_int.reset(new SndFileDecoder<int>(source_file_full_path.c_str(), buffer, sizeof(buffer)));
                    break;
                }
                case Sample::SampleContainer::FLOAT_32:
                {
                    float *buffer = sample_buffer_float.get();
                    decoder_float.reset(new SndFileDecoder<float>(source_file_full_path.c_str(), buffer, sizeof(buffer)));
                    break;
                }
                default: //Sample::SampleContainer::FLOAT_64
                {
                    double *buffer = sample_buffer_double.get();
                    decoder_double.reset(new SndFileDecoder<double>(source_file_full_path.c_str(), buffer, sizeof(buffer)));
                }
            }
        }
        default: /*!< MPG123 */
        {
            switch(chosen_container_type)
            {
                case Sample::SampleContainer::INT_S8:
                {
                    char *buffer = sample_buffer_char.get();
                    mpg123_lifetime_handler.reset(new Mpg123LifetimeHandler());
                    decoder_char.reset(new Mpg123<char>(source_file_full_path.c_str(), buffer, sizeof(buffer), *mpg123_lifetime_handler.get()));
                    break;
                }
            }
        }
    }
}

void CodecController::Convert()
{
    /*
    int64_t buffer_valid_frames_count;

    Mpg123LifetimeHandler life;
    Mpg123<void> mpg1(WindowsUtilities::UTF8_Encode(source).c_str(), life);
    Mpg123<float> mpg2(WindowsUtilities::UTF8_Encode(source).c_str(), buffer, sizeof(buffer), life);
    //SndFileEncoder<float> snd(TypeConv::utf8_encode(destination).c_str(), mpg1.GetSampleRate(), mpg1.GetChannelCount(), SndFileEncoder<float>::OutputFormat::WAV_PCM_FLOAT_32, buffer, sizeof(buffer));
    Lame<float> lame(WindowsUtilities::UTF8_Encode(destination).c_str(), mpg1.GetSampleRate(), mpg1.GetChannelCount(), LameOptions::AlgorithmQuality::Q0, LameOptions::Mode::JOINT_STEREO, LameOptions::ReplayGain::ACCURATE, false, true, LameOptions::BitrateEncoding::VARIABLE_NEW, 0, LameOptions::Bitrate::B_224, LameOptions::Bitrate::B_320, buffer, sizeof(buffer));
    do
    {
        buffer_valid_frames_count = mpg2.ReadFrames();
        mpg2.GetCurrentFrameOffset();
        lame.WriteFrames(buffer_valid_frames_count);
    }while(buffer_valid_frames_count == 1000);
    */
}
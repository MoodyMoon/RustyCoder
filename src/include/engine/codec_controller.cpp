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

CodecController::CodecController(const std::string &source_file_full_path, const std::string &output_file_full_path, Decoder<void>::ID decoder_id, const SndFileEncoderOptions &options) : source_file_full_path(source_file_full_path), output_file_full_path(output_file_full_path), decoder_id(decoder_id), encoder_options(&options)
{
    encoder_id = Encoder<void>::ID::SNDFILEENCODER;
    PopulateAudioProperties();
    BeforeConvert();
}

CodecController::CodecController(const std::string &source_file_full_path, const std::string &output_file_full_path, Decoder<void>::ID decoder_id, const LameOptions &options) : source_file_full_path(source_file_full_path), output_file_full_path(output_file_full_path), decoder_id(decoder_id), encoder_options(&options)
{
    encoder_id = Encoder<void>::ID::LAME;
    PopulateAudioProperties();
    BeforeConvert();
}

void CodecController::PopulateAudioProperties()
{
    std::unique_ptr<Decoder<void>> decoder_void;
    std::unique_ptr<Mpg123LifetimeHandler> mpg123_lifetime_handler;

    switch(decoder_id)
    {
        case Decoder<void>::ID::SNDFILEDECODER:
        {
            decoder_void.reset(new SndFileDecoder<void>(source_file_full_path.c_str()));
            break;
        }
        default: /*!< MPG123 */
        {
            mpg123_lifetime_handler.reset(new Mpg123LifetimeHandler());
            decoder_void.reset(new Mpg123<void>(source_file_full_path.c_str(), *mpg123_lifetime_handler.get()));
        }
    }

    assert(decoder_void != nullptr);

    channel_count = decoder_void->GetChannelCount();
    sample_rate = decoder_void->GetSampleRate();
    total_frame_count = decoder_void->GetFrameCount();
    Sample::SampleContainer decoder_container_type = decoder_void->GetPreferableOutputContainer();

    std::unique_ptr<Encoder<void>> encoder_void;

    switch(encoder_id)
    {
        case Encoder<void>::ID::SNDFILEENCODER:
            encoder_void.reset(new SndFileEncoder<void>());
            break;
        default: /*!< MPG123 */
            encoder_void.reset(new Lame<void>());
    }

    assert(encoder_void != nullptr);

    Encoder<void> *_encoder_void = encoder_void.get();
    Sample::SampleContainer *encoder_valid_containers = _encoder_void->valid_containers.get();
    size_t encoder_valid_containers_count = encoder_void->GetValidContainersCount();

    for(size_t i = 0; i < encoder_valid_containers_count; ++i)
    {
        if(decoder_container_type == encoder_valid_containers[i])
        {
            chosen_container_type = decoder_container_type;
            return;
        }
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
            {
                chosen_container_type = decoder_container_type;
                return;
            }
        }
    }

    assert(false);

    chosen_container_type = Sample::SampleContainer::INT_S16; /*!< Fail safe */
}

void CodecController::BeforeConvert()
{
    uint64_t buffer_size_in_bytes;

    switch(chosen_container_type)
    {
        case Sample::SampleContainer::INT_S8:
        {
            sample_buffer_char.reset(new char[max_samples_in_buffer]);
            buffer_size_in_bytes = max_samples_in_buffer * sizeof(char);
            break;
        }
        case Sample::SampleContainer::INT_U8:
        {
            sample_buffer_u_char.reset(new unsigned char[max_samples_in_buffer]);
            buffer_size_in_bytes = max_samples_in_buffer * sizeof(unsigned char);
            break;
        }
        case Sample::SampleContainer::INT_S16:
        {
            sample_buffer_short.reset(new short[max_samples_in_buffer]);
            buffer_size_in_bytes = max_samples_in_buffer * sizeof(short);
            break;
        }
        case Sample::SampleContainer::INT_U16:
        {
            sample_buffer_u_short.reset(new unsigned short[max_samples_in_buffer]);
            buffer_size_in_bytes = max_samples_in_buffer * sizeof(unsigned short);
            break;
        }
        case Sample::SampleContainer::INT_S32:
        {
            sample_buffer_int.reset(new int[max_samples_in_buffer]);
            buffer_size_in_bytes = max_samples_in_buffer * sizeof(int);
            break;
        }
        case Sample::SampleContainer::INT_U32:
        {
            sample_buffer_u_int.reset(new unsigned int[max_samples_in_buffer]);
            buffer_size_in_bytes = max_samples_in_buffer * sizeof(unsigned int);
            break;
        }
        case Sample::SampleContainer::FLOAT_32:
        {
            sample_buffer_float.reset(new float[max_samples_in_buffer]);
            buffer_size_in_bytes = max_samples_in_buffer * sizeof(float);
            break;
        }
        default: /*!< Sample::SampleContainer::FLOAT_64 */
        {
            sample_buffer_double.reset(new double[max_samples_in_buffer]);
            buffer_size_in_bytes = max_samples_in_buffer * sizeof(double);
        }
    }

    switch(decoder_id)
    {
        case Decoder<void>::ID::SNDFILEDECODER:
        {
            switch(chosen_container_type)
            {
                case Sample::SampleContainer::INT_S16:
                    decoder_short.reset(new SndFileDecoder<short>(source_file_full_path.c_str(), sample_buffer_short.get(), buffer_size_in_bytes));
                    break;
                case Sample::SampleContainer::INT_S32:
                    decoder_int.reset(new SndFileDecoder<int>(source_file_full_path.c_str(), sample_buffer_int.get(), buffer_size_in_bytes));
                    break;
                case Sample::SampleContainer::FLOAT_32:
                    decoder_float.reset(new SndFileDecoder<float>(source_file_full_path.c_str(), sample_buffer_float.get(), buffer_size_in_bytes));
                    break;
                default: //Sample::SampleContainer::FLOAT_64
                    decoder_double.reset(new SndFileDecoder<double>(source_file_full_path.c_str(), sample_buffer_double.get(), buffer_size_in_bytes));
            }
            break;
        }
        default: /*!< MPG123 */
        {
            mpg123_lifetime_handler.reset(new Mpg123LifetimeHandler());

            switch(chosen_container_type)
            {
                case Sample::SampleContainer::INT_S8:
                    decoder_char.reset(new Mpg123<char>(source_file_full_path.c_str(), sample_buffer_char.get(), buffer_size_in_bytes, *mpg123_lifetime_handler.get()));
                    break;
                case Sample::SampleContainer::INT_U8:
                    decoder_u_char.reset(new Mpg123<unsigned char>(source_file_full_path.c_str(), sample_buffer_u_char.get(), buffer_size_in_bytes, *mpg123_lifetime_handler.get()));
                    break;
                case Sample::SampleContainer::INT_S16:
                    decoder_short.reset(new Mpg123<short>(source_file_full_path.c_str(), sample_buffer_short.get(), buffer_size_in_bytes, *mpg123_lifetime_handler.get()));
                    break;
                case Sample::SampleContainer::INT_U16:
                    decoder_u_short.reset(new Mpg123<unsigned short>(source_file_full_path.c_str(), sample_buffer_u_short.get(), buffer_size_in_bytes, *mpg123_lifetime_handler.get()));
                    break;
                case Sample::SampleContainer::INT_S32:
                    decoder_int.reset(new Mpg123<int>(source_file_full_path.c_str(), sample_buffer_int.get(), buffer_size_in_bytes, *mpg123_lifetime_handler.get()));
                    break;
                case Sample::SampleContainer::INT_U32:
                    decoder_u_int.reset(new Mpg123<unsigned int>(source_file_full_path.c_str(), sample_buffer_u_int.get(), buffer_size_in_bytes, *mpg123_lifetime_handler.get()));
                    break;
                default: /*!< Sample::SampleContainer::FLOAT_32 */
                    decoder_float.reset(new Mpg123<float>(source_file_full_path.c_str(), sample_buffer_float.get(), buffer_size_in_bytes, *mpg123_lifetime_handler.get()));
            }
        }
    }

    switch(encoder_id)
    {
        case Encoder<void>::ID::SNDFILEENCODER:
        {
            const SndFileEncoderOptions *options = static_cast<const SndFileEncoderOptions *>(encoder_options);

            switch(chosen_container_type)
            {
                case Sample::SampleContainer::INT_S16:
                    encoder_short.reset(new SndFileEncoder<short>(output_file_full_path.c_str(), sample_rate, channel_count, options->output_format, sample_buffer_short.get(), buffer_size_in_bytes));
                    break;
                case Sample::SampleContainer::INT_S32:
                    encoder_int.reset(new SndFileEncoder<int>(output_file_full_path.c_str(), sample_rate, channel_count, options->output_format, sample_buffer_int.get(), buffer_size_in_bytes));
                    break;
                case Sample::SampleContainer::FLOAT_32:
                    encoder_float.reset(new SndFileEncoder<float>(output_file_full_path.c_str(), sample_rate, channel_count, options->output_format, sample_buffer_float.get(), buffer_size_in_bytes));
                    break;
                default: //Sample::SampleContainer::FLOAT_64
                    encoder_double.reset(new SndFileEncoder<double>(output_file_full_path.c_str(), sample_rate, channel_count, options->output_format, sample_buffer_double.get(), buffer_size_in_bytes));
            }
            break;
        }
        default: /*!< LAME */
        {
            const LameOptions *options = static_cast<const LameOptions *>(encoder_options);

            switch(chosen_container_type)
            {
                case Sample::SampleContainer::INT_S16:
                    encoder_short.reset(new Lame<short>(output_file_full_path.c_str(), sample_rate, channel_count, options->algorithm_quality, options->mode, options->replaygain_mode, options->copyright, options->use_naoki_psytune, options->bitrate_encoding, options->GetVbrQuality(), options->min_or_max_bitrate1, options->min_or_max_bitrate1, sample_buffer_short.get(), buffer_size_in_bytes));
                    break;
                case Sample::SampleContainer::FLOAT_32:
                    encoder_float.reset(new Lame<float>(output_file_full_path.c_str(), sample_rate, channel_count, options->algorithm_quality, options->mode, options->replaygain_mode, options->copyright, options->use_naoki_psytune, options->bitrate_encoding, options->GetVbrQuality(), options->min_or_max_bitrate1, options->min_or_max_bitrate1, sample_buffer_float.get(), buffer_size_in_bytes));
                    break;
                default: /*<! Sample::SampleContainer::FLOAT_64 */
                    encoder_double.reset(new Lame<double>(output_file_full_path.c_str(), sample_rate, channel_count, options->algorithm_quality, options->mode, options->replaygain_mode, options->copyright, options->use_naoki_psytune, options->bitrate_encoding, options->GetVbrQuality(), options->min_or_max_bitrate1, options->min_or_max_bitrate1, sample_buffer_double.get(), buffer_size_in_bytes));
            }
        }
    }

    max_buffer_valid_frames_count = max_samples_in_buffer / channel_count;

    switch(chosen_container_type)
    {
        case Sample::SampleContainer::INT_S8:
        {
            _decoder_char = decoder_char.get();
            _encoder_char = encoder_char.get();
            break;
        }
        case Sample::SampleContainer::INT_U8:
        {
            _decoder_u_char = decoder_u_char.get();
            _encoder_u_char = encoder_u_char.get();
            break;
        }
        case Sample::SampleContainer::INT_S16:
        {
            _decoder_short = decoder_short.get();
            _encoder_short = encoder_short.get();
            break;
        }
        case Sample::SampleContainer::INT_U16:
        {
            _decoder_u_short = decoder_u_short.get();
            _encoder_u_short = encoder_u_short.get();
            break;
        }
        case Sample::SampleContainer::INT_S32:
        {
            _decoder_int = decoder_int.get();
            _encoder_int = encoder_int.get();
            break;
        }
        case Sample::SampleContainer::INT_U32:
        {
            _decoder_u_int = decoder_u_int.get();
            _encoder_u_int = encoder_u_int.get();
            break;
        }
        case Sample::SampleContainer::FLOAT_32:
        {
            _decoder_float = decoder_float.get();
            _encoder_float = encoder_float.get();
            break;
        }
        default: /*!< Sample::SampleContainer::FLOAT_64 */
        {
            _decoder_double = decoder_double.get();
            _encoder_double = encoder_double.get();
        }
    }
}

uint64_t CodecController::Convert()
{
    assert(can_convert);

    if(!can_convert)
        return 0u;

    switch(chosen_container_type)
    {
        case Sample::SampleContainer::INT_S8:
        {
            buffer_valid_frames_count = _decoder_char->ReadFrames();
            _encoder_char->WriteFrames(buffer_valid_frames_count);
            break;
        }
        case Sample::SampleContainer::INT_U8:
        {
            buffer_valid_frames_count = _decoder_u_char->ReadFrames();
            _encoder_u_char->WriteFrames(buffer_valid_frames_count);
            break;
        }
        case Sample::SampleContainer::INT_S16:
        {
            buffer_valid_frames_count = _decoder_short->ReadFrames();
            _encoder_short->WriteFrames(buffer_valid_frames_count);
            break;
        }
        case Sample::SampleContainer::INT_U16:
        {
            buffer_valid_frames_count = _decoder_u_short->ReadFrames();
            _encoder_u_short->WriteFrames(buffer_valid_frames_count);
            break;
        }
        case Sample::SampleContainer::INT_S32:
        {
            buffer_valid_frames_count = _decoder_int->ReadFrames();
            _encoder_int->WriteFrames(buffer_valid_frames_count);
            break;
        }
        case Sample::SampleContainer::INT_U32:
        {
            buffer_valid_frames_count = _decoder_u_int->ReadFrames();
            _encoder_u_int->WriteFrames(buffer_valid_frames_count);
            break;
        }
        case Sample::SampleContainer::FLOAT_32:
        {
            buffer_valid_frames_count = _decoder_float->ReadFrames();
            _encoder_float->WriteFrames(buffer_valid_frames_count);
            break;
        }
        default: /*!< Sample::SampleContainer::FLOAT_64 */
        {
            buffer_valid_frames_count = _decoder_double->ReadFrames();
            _encoder_double->WriteFrames(buffer_valid_frames_count);
        }
    }

    if(buffer_valid_frames_count < max_buffer_valid_frames_count)
        can_convert = false;

    /*!
    \c buffer_valid_frames_count is equal to the amount of samples decoded and not frames.
    I have no idea why. Just a simple hack to solve the problem. Dividing it by \c channel_count again.
    */
    return buffer_valid_frames_count / channel_count;
}

unsigned int CodecController::GetChannelCount()
{
    return channel_count;
}

unsigned int CodecController::GetSampleRate()
{
    return sample_rate;
}

uint64_t CodecController::GetTotalFrameCount()
{
    return total_frame_count;
}

bool CodecController::CanConvert()
{
    return can_convert;
}
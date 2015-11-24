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

#include "stdafx.h"
#include "codec_controller.h"

rusty::engine::CodecController::CodecController(const boost::filesystem::path source_file_path, const boost::filesystem::path output_file_path, rusty::codecs::Decoder<void>::ID decoder_id, const codecs::EncoderProfile &encoder_profile, codecs::Encoder<void>::ID encoder_id) : source_file_path(source_file_path), output_file_path(output_file_path), decoder_id(decoder_id), encoder_id(encoder_id)
{
    switch(encoder_id)
    {
        case codecs::Encoder<void>::ID::LAME:
        {
            const codecs::LameProfile *_lame_profile = dynamic_cast<const codecs::LameProfile *>(&encoder_profile);
            lame_profile.reset(new codecs::LameProfile(*_lame_profile));
            PopulateAudioProperties();
            BeforeConvert();
            break;
        }
        case codecs::Encoder<void>::ID::SNDFILE_ENCODER:
        {
            const codecs::SndFileEncoderProfile *_sndfile_encoder_profile = dynamic_cast<const codecs::SndFileEncoderProfile *>(&encoder_profile);
            sndfile_encoder_profile.reset(new codecs::SndFileEncoderProfile(*_sndfile_encoder_profile));
            PopulateAudioProperties();
            BeforeConvert();
            break;
        }
        default:
            assert(false);
    }
}

void rusty::engine::CodecController::PopulateAudioProperties()
{
    std::unique_ptr<rusty::codecs::Decoder<void>> decoder_void;
    std::unique_ptr<rusty::codecs::Mpg123LifetimeHandler> mpg123_lifetime_handler;

    switch(decoder_id)
    {
        case codecs::Decoder<void>::ID::MPG123:
        {
            mpg123_lifetime_handler.reset(new rusty::codecs::Mpg123LifetimeHandler());
            decoder_void.reset(new rusty::codecs::Mpg123<void>(source_file_path, *mpg123_lifetime_handler.get()));
            break;
        }
        case codecs::Decoder<void>::ID::SNDFILE_DECODER:
        {
            decoder_void.reset(new rusty::codecs::SndFileDecoder<void>(source_file_path));
            break;
        }
        default:
            assert(false);
    }

    assert(decoder_void != nullptr);

    channel_count = decoder_void->GetChannelCount();
    sample_rate = decoder_void->GetSampleRate();
    total_frame_count = decoder_void->GetFrameCount();
    codecs::Sample::SampleContainer decoder_container_type = decoder_void->GetPreferableOutputContainer();

    std::unique_ptr<codecs::Encoder<void>> encoder_void;

    switch(encoder_id)
    {
        case codecs::Encoder<void>::ID::LAME:
            encoder_void.reset(new codecs::Lame<void>());
            break;
        case codecs::Encoder<void>::ID::SNDFILE_ENCODER:
            encoder_void.reset(new codecs::SndFileEncoder<void>());
            break;
        default:
            assert(false);
    }

    assert(encoder_void != nullptr);

    codecs::Encoder<void> *_encoder_void = encoder_void.get();
    const codecs::Sample::SampleContainer *encoder_valid_containers = _encoder_void->GetSupportedContainers();
    size_t encoder_valid_containers_count = encoder_void->GetSupportedContainersCount();

    for(size_t i = 0; i < encoder_valid_containers_count; ++i)
    {
        if(decoder_container_type == encoder_valid_containers[i])
        {
            chosen_container_type = decoder_container_type;
            return;
        }
    }

    codecs::Decoder<void> *_decoder_void = decoder_void.get();
    const codecs::Sample::SampleContainer *decoder_valid_containers = _decoder_void->GetSupportedContainers();
    size_t decoder_valid_containers_count = _decoder_void->GetSupportedContainersCount();

    for(size_t i = decoder_valid_containers_count - 1; i < decoder_valid_containers_count; --i)
    {
        decoder_container_type = decoder_valid_containers[i];
        for(size_t j = encoder_valid_containers_count - 1; j < decoder_valid_containers_count; --j)
        {
            if(decoder_container_type == encoder_valid_containers[j])
            {
                chosen_container_type = decoder_container_type;
                return;
            }
        }
    }

    assert(false);
}

void rusty::engine::CodecController::BeforeConvert()
{
    uint64_t buffer_size_in_bytes = 0ull;

    switch(chosen_container_type)
    {
        case codecs::Sample::SampleContainer::INT_S8:
        {
            sample_buffer_char.reset(new char[max_samples_in_buffer]);
            buffer_size_in_bytes = max_samples_in_buffer * sizeof(char);
            break;
        }
        case codecs::Sample::SampleContainer::INT_U8:
        {
            sample_buffer_u_char.reset(new unsigned char[max_samples_in_buffer]);
            buffer_size_in_bytes = max_samples_in_buffer * sizeof(unsigned char);
            break;
        }
        case codecs::Sample::SampleContainer::INT_S16:
        {
            sample_buffer_short.reset(new short[max_samples_in_buffer]);
            buffer_size_in_bytes = max_samples_in_buffer * sizeof(short);
            break;
        }
        case codecs::Sample::SampleContainer::INT_U16:
        {
            sample_buffer_u_short.reset(new unsigned short[max_samples_in_buffer]);
            buffer_size_in_bytes = max_samples_in_buffer * sizeof(unsigned short);
            break;
        }
        case codecs::Sample::SampleContainer::INT_S32:
        {
            sample_buffer_int.reset(new int[max_samples_in_buffer]);
            buffer_size_in_bytes = max_samples_in_buffer * sizeof(int);
            break;
        }
        case codecs::Sample::SampleContainer::INT_U32:
        {
            sample_buffer_u_int.reset(new unsigned int[max_samples_in_buffer]);
            buffer_size_in_bytes = max_samples_in_buffer * sizeof(unsigned int);
            break;
        }
        case codecs::Sample::SampleContainer::FLOAT_32:
        {
            sample_buffer_float.reset(new float[max_samples_in_buffer]);
            buffer_size_in_bytes = max_samples_in_buffer * sizeof(float);
            break;
        }
        case codecs::Sample::SampleContainer::FLOAT_64:
        {
            sample_buffer_double.reset(new double[max_samples_in_buffer]);
            buffer_size_in_bytes = max_samples_in_buffer * sizeof(double);
            break;
        }
        default:
            assert(false);
    }

    switch(decoder_id)
    {
        case codecs::Decoder<void>::ID::MPG123:
        {
            mpg123_lifetime_handler.reset(new codecs::Mpg123LifetimeHandler());

            switch(chosen_container_type)
            {
                case codecs::Sample::SampleContainer::INT_S8:
                    decoder_char.reset(new codecs::Mpg123<char>(source_file_path, sample_buffer_char.get(), buffer_size_in_bytes, *mpg123_lifetime_handler.get()));
                    break;
                case codecs::Sample::SampleContainer::INT_U8:
                    decoder_u_char.reset(new codecs::Mpg123<unsigned char>(source_file_path, sample_buffer_u_char.get(), buffer_size_in_bytes, *mpg123_lifetime_handler.get()));
                    break;
                case codecs::Sample::SampleContainer::INT_S16:
                    decoder_short.reset(new codecs::Mpg123<short>(source_file_path, sample_buffer_short.get(), buffer_size_in_bytes, *mpg123_lifetime_handler.get()));
                    break;
                case codecs::Sample::SampleContainer::INT_U16:
                    decoder_u_short.reset(new codecs::Mpg123<unsigned short>(source_file_path, sample_buffer_u_short.get(), buffer_size_in_bytes, *mpg123_lifetime_handler.get()));
                    break;
                case codecs::Sample::SampleContainer::INT_S32:
                    decoder_int.reset(new codecs::Mpg123<int>(source_file_path, sample_buffer_int.get(), buffer_size_in_bytes, *mpg123_lifetime_handler.get()));
                    break;
                case codecs::Sample::SampleContainer::INT_U32:
                    decoder_u_int.reset(new codecs::Mpg123<unsigned int>(source_file_path, sample_buffer_u_int.get(), buffer_size_in_bytes, *mpg123_lifetime_handler.get()));
                    break;
                case codecs::Sample::SampleContainer::FLOAT_32:
                    decoder_float.reset(new codecs::Mpg123<float>(source_file_path, sample_buffer_float.get(), buffer_size_in_bytes, *mpg123_lifetime_handler.get()));
                    break;
                default:
                    assert(false);
            }
            break;
        }
        case codecs::Decoder<void>::ID::SNDFILE_DECODER:
        {
            switch(chosen_container_type)
            {
                case codecs::Sample::SampleContainer::INT_S16:
                    decoder_short.reset(new codecs::SndFileDecoder<short>(source_file_path, sample_buffer_short.get(), buffer_size_in_bytes));
                    break;
                case codecs::Sample::SampleContainer::INT_S32:
                    decoder_int.reset(new codecs::SndFileDecoder<int>(source_file_path, sample_buffer_int.get(), buffer_size_in_bytes));
                    break;
                case codecs::Sample::SampleContainer::FLOAT_32:
                    decoder_float.reset(new codecs::SndFileDecoder<float>(source_file_path, sample_buffer_float.get(), buffer_size_in_bytes));
                    break;
                case codecs::Sample::SampleContainer::FLOAT_64:
                    decoder_double.reset(new codecs::SndFileDecoder<double>(source_file_path, sample_buffer_double.get(), buffer_size_in_bytes));
                    break;
                default:
                    assert(false);
            }
            break;
        }
        default:
            assert(false);
    }

    switch(encoder_id)
    {
        case codecs::Encoder<void>::ID::LAME:
        {
            const codecs::LameProfile *_lame_profile = lame_profile.get();

            switch(chosen_container_type)
            {
                case codecs::Sample::SampleContainer::INT_S16:
                    encoder_short.reset(new codecs::Lame<short>(output_file_path, sample_rate, channel_count, _lame_profile->algorithm_quality, _lame_profile->mode, _lame_profile->replaygain_mode, _lame_profile->copyright, _lame_profile->use_naoki_psytune, _lame_profile->bitrate_encoding, _lame_profile->GetVbrQuality(), _lame_profile->min_or_max_bitrate1, _lame_profile->min_or_max_bitrate2, sample_buffer_short.get(), buffer_size_in_bytes));
                    break;
                case codecs::Sample::SampleContainer::FLOAT_32:
                    encoder_float.reset(new codecs::Lame<float>(output_file_path, sample_rate, channel_count, _lame_profile->algorithm_quality, _lame_profile->mode, _lame_profile->replaygain_mode, _lame_profile->copyright, _lame_profile->use_naoki_psytune, _lame_profile->bitrate_encoding, _lame_profile->GetVbrQuality(), _lame_profile->min_or_max_bitrate1, _lame_profile->min_or_max_bitrate2, sample_buffer_float.get(), buffer_size_in_bytes));
                    break;
                case codecs::Sample::SampleContainer::FLOAT_64:
                    encoder_double.reset(new codecs::Lame<double>(output_file_path, sample_rate, channel_count, _lame_profile->algorithm_quality, _lame_profile->mode, _lame_profile->replaygain_mode, _lame_profile->copyright, _lame_profile->use_naoki_psytune, _lame_profile->bitrate_encoding, _lame_profile->GetVbrQuality(), _lame_profile->min_or_max_bitrate1, _lame_profile->min_or_max_bitrate2, sample_buffer_double.get(), buffer_size_in_bytes));
                    break;
                default:
                    assert(false);
            }
            break;
        }
        case codecs::Encoder<void>::ID::SNDFILE_ENCODER:
        {
            const codecs::SndFileEncoderProfile *_sndfile_encoder_profile = sndfile_encoder_profile.get();

            switch(chosen_container_type)
            {
                case codecs::Sample::SampleContainer::INT_S16:
                    encoder_short.reset(new codecs::SndFileEncoder<short>(output_file_path, sample_rate, channel_count, _sndfile_encoder_profile->output_format, sample_buffer_short.get(), buffer_size_in_bytes));
                    break;
                case codecs::Sample::SampleContainer::INT_S32:
                    encoder_int.reset(new codecs::SndFileEncoder<int>(output_file_path, sample_rate, channel_count, _sndfile_encoder_profile->output_format, sample_buffer_int.get(), buffer_size_in_bytes));
                    break;
                case codecs::Sample::SampleContainer::FLOAT_32:
                    encoder_float.reset(new codecs::SndFileEncoder<float>(output_file_path, sample_rate, channel_count, _sndfile_encoder_profile->output_format, sample_buffer_float.get(), buffer_size_in_bytes));
                    break;
                case codecs::Sample::SampleContainer::FLOAT_64:
                    encoder_double.reset(new codecs::SndFileEncoder<double>(output_file_path, sample_rate, channel_count, _sndfile_encoder_profile->output_format, sample_buffer_double.get(), buffer_size_in_bytes));
                    break;
                default:
                    assert(false);
            }
            break;
        }
        default:
            assert(false);
    }

    max_buffer_valid_frames_count = max_samples_in_buffer / channel_count;

    switch(chosen_container_type)
    {
        case codecs::Sample::SampleContainer::INT_S8:
        {
            _decoder_char = decoder_char.get();
            _encoder_char = encoder_char.get();
            break;
        }
        case codecs::Sample::SampleContainer::INT_U8:
        {
            _decoder_u_char = decoder_u_char.get();
            _encoder_u_char = encoder_u_char.get();
            break;
        }
        case codecs::Sample::SampleContainer::INT_S16:
        {
            _decoder_short = decoder_short.get();
            _encoder_short = encoder_short.get();
            break;
        }
        case codecs::Sample::SampleContainer::INT_U16:
        {
            _decoder_u_short = decoder_u_short.get();
            _encoder_u_short = encoder_u_short.get();
            break;
        }
        case codecs::Sample::SampleContainer::INT_S32:
        {
            _decoder_int = decoder_int.get();
            _encoder_int = encoder_int.get();
            break;
        }
        case codecs::Sample::SampleContainer::INT_U32:
        {
            _decoder_u_int = decoder_u_int.get();
            _encoder_u_int = encoder_u_int.get();
            break;
        }
        case codecs::Sample::SampleContainer::FLOAT_32:
        {
            _decoder_float = decoder_float.get();
            _encoder_float = encoder_float.get();
            break;
        }
        case codecs::Sample::SampleContainer::FLOAT_64:
        {
            _decoder_double = decoder_double.get();
            _encoder_double = encoder_double.get();
            break;
        }
        default:
            assert(false);
    }
}

uint64_t rusty::engine::CodecController::Convert()
{
    assert(can_convert);

    if(!can_convert)
        return 0u;

    switch(chosen_container_type)
    {
        case codecs::Sample::SampleContainer::INT_S8:
        {
            buffer_valid_frames_count = _decoder_char->ReadFrames();
            _encoder_char->WriteFrames(buffer_valid_frames_count);
            break;
        }
        case codecs::Sample::SampleContainer::INT_U8:
        {
            buffer_valid_frames_count = _decoder_u_char->ReadFrames();
            _encoder_u_char->WriteFrames(buffer_valid_frames_count);
            break;
        }
        case codecs::Sample::SampleContainer::INT_S16:
        {
            buffer_valid_frames_count = _decoder_short->ReadFrames();
            _encoder_short->WriteFrames(buffer_valid_frames_count);
            break;
        }
        case codecs::Sample::SampleContainer::INT_U16:
        {
            buffer_valid_frames_count = _decoder_u_short->ReadFrames();
            _encoder_u_short->WriteFrames(buffer_valid_frames_count);
            break;
        }
        case codecs::Sample::SampleContainer::INT_S32:
        {
            buffer_valid_frames_count = _decoder_int->ReadFrames();
            _encoder_int->WriteFrames(buffer_valid_frames_count);
            break;
        }
        case codecs::Sample::SampleContainer::INT_U32:
        {
            buffer_valid_frames_count = _decoder_u_int->ReadFrames();
            _encoder_u_int->WriteFrames(buffer_valid_frames_count);
            break;
        }
        case codecs::Sample::SampleContainer::FLOAT_32:
        {
            buffer_valid_frames_count = _decoder_float->ReadFrames();
            _encoder_float->WriteFrames(buffer_valid_frames_count);
            break;
        }
        case codecs::Sample::SampleContainer::FLOAT_64:
        {
            buffer_valid_frames_count = _decoder_double->ReadFrames();
            _encoder_double->WriteFrames(buffer_valid_frames_count);
            break;
        }
        default:
            assert(false);
    }

    if(buffer_valid_frames_count < max_buffer_valid_frames_count)
        can_convert = false;

    /*!
    \c buffer_valid_frames_count is equal to the amount of samples decoded and not frames.
    I have no idea why. Just a simple hack to solve the problem. Dividing it by \c channel_count again.
    */
    return buffer_valid_frames_count / channel_count;
}

unsigned int rusty::engine::CodecController::GetChannelCount()
{
    return channel_count;
}

unsigned int rusty::engine::CodecController::GetSampleRate()
{
    return sample_rate;
}

uint64_t rusty::engine::CodecController::GetTotalFrameCount()
{
    return total_frame_count;
}

bool rusty::engine::CodecController::CanConvert()
{
    return can_convert;
}
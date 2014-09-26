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

CodecController::CodecController(std::string source_file_full_path, std::string output_file_full_path, Decoder decoder_id, Encoder encoder_id, SndFileEncoderOptions * const options) : source_file_full_path(source_file_full_path), output_file_full_path(output_file_full_path), decoder_id(decoder_id), encoder_id(encoder_id), sndfileencoder_options(options)
{
    CodecController2();
}

CodecController::CodecController(std::string source_file_full_path, std::string output_file_full_path, Decoder decoder_id, Encoder encoder_id, LameOptions * const options) : source_file_full_path(source_file_full_path), output_file_full_path(output_file_full_path), decoder_id(decoder_id), encoder_id(encoder_id), lame_options(options)
{
    CodecController2();
}

void CodecController::CodecController2()
{
    GetPreferableOutputContainer();
}

void CodecController::Convert()
{

}

Sample::SampleContainer CodecController::GetPreferableOutputContainer(void)
{
    std::unique_ptr<DecoderInterface<void>> decoder_void;
    std::unique_ptr<Mpg123LifetimeHandler> mpg123_lifetime_handler2;

    switch(decoder_id)
    {
        case SNDFILEDECODER:
        {
            decoder_void.reset(new SndFileDecoder<void>(source_file_full_path.c_str()));
            break;
        }
        default: //MPG123
        {
            mpg123_lifetime_handler2.reset(new Mpg123LifetimeHandler());
            decoder_void.reset(new Mpg123<void>(source_file_full_path.c_str(), *mpg123_lifetime_handler.get()));
            break;
        }
    }

    assert(decoder_void != nullptr);

    Sample::SampleContainer decoder_container_type = decoder_void->GetPreferableOutputContainer();

    std::unique_ptr<EncoderInterface<void>> encoder_void;

    switch(encoder_id)
    {
        case SNDFILEENCODER:
            encoder_void.reset(new SndFileEncoder<void>());
            break;
        default: //MPG123
            encoder_void.reset(new Lame<void>());
            break;
    }

    assert(encoder_void != nullptr);

    EncoderInterface<void> *_encoder_void = encoder_void.get();
    Sample::SampleContainer *encoder_valid_containers = _encoder_void->valid_containers.get();
    size_t encoder_valid_containers_count = encoder_void->GetValidContainersCount();

    for(unsigned int i = 0; i < encoder_valid_containers_count; ++i)
    {
        if(decoder_container_type == encoder_valid_containers[i])
            return decoder_container_type;
    }

    DecoderInterface<void> *_decoder_void = decoder_void.get();
    Sample::SampleContainer *decoder_valid_containers = _decoder_void->valid_containers.get();
    size_t decoder_valid_containers_count = _decoder_void->GetValidContainersCount();

    for(unsigned int i = decoder_valid_containers_count - 1; i >= 0; --i)
    {
        decoder_container_type = decoder_valid_containers[i];
        for(unsigned j = encoder_valid_containers_count - 1; j >= 0; --j)
        {
            if(decoder_container_type == encoder_valid_containers[j])
                return decoder_container_type;
        }
    }

    assert(false);
}

CodecController::~CodecController()
{

}
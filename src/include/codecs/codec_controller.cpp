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

CodecController::CodecController(const std::string source_file_full_path, const std::string output_file_full_path, Decoder decoder_id, Encoder encoder_id, SndFileEncoderOptions * const options) : source_file_full_path(source_file_full_path), output_file_full_path(output_file_full_path), decoder_id(decoder_id), encoder_id(encoder_id), sndfileencoder_options(options)
{
    CodecController2();
}

CodecController::CodecController(const std::string source_file_full_path, const std::string output_file_full_path, Decoder decoder_id, Encoder encoder_id, LameOptions * const options) : source_file_full_path(source_file_full_path), output_file_full_path(output_file_full_path), decoder_id(decoder_id), encoder_id(encoder_id), lame_options(options)
{
    CodecController2();
}

void CodecController::CodecController2()
{

}

void CodecController::Convert()
{

}

Sample::SampleContainer CodecController::GetPreferableOutputContainer(void)
{
    switch(decoder_id)
    {
        case SNDFILEDECODER:
            break;
        case MPG123:
            break;
    }
}

CodecController::~CodecController()
{

}
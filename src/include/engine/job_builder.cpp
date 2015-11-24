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
#include "job_builder.h"

const std::unordered_map<std::string, rusty::codecs::Decoder<void>::ID> rusty::engine::JobBuilder::audio_file_extension_to_estimated_decoder_id =
{
    {"." AUDIO_EXTENSION_AIF,  codecs::Decoder<void>::ID::SNDFILE_DECODER},
    {"." AUDIO_EXTENSION_AIFC, codecs::Decoder<void>::ID::SNDFILE_DECODER},
    {"." AUDIO_EXTENSION_AIFF, codecs::Decoder<void>::ID::SNDFILE_DECODER},
    {"." AUDIO_EXTENSION_AMPC, codecs::Decoder<void>::ID::SNDFILE_DECODER},
    {"." AUDIO_EXTENSION_AU,   codecs::Decoder<void>::ID::SNDFILE_DECODER},
    {"." AUDIO_EXTENSION_AVR,  codecs::Decoder<void>::ID::SNDFILE_DECODER},
    {"." AUDIO_EXTENSION_CAF,  codecs::Decoder<void>::ID::SNDFILE_DECODER},
    {"." AUDIO_EXTENSION_HTK,  codecs::Decoder<void>::ID::SNDFILE_DECODER},
    {"." AUDIO_EXTENSION_IFF,  codecs::Decoder<void>::ID::SNDFILE_DECODER},
    {"." AUDIO_EXTENSION_MAT,  codecs::Decoder<void>::ID::SNDFILE_DECODER},
    {"." AUDIO_EXTENSION_MP1,  codecs::Decoder<void>::ID::MPG123},
    {"." AUDIO_EXTENSION_MP2,  codecs::Decoder<void>::ID::MPG123},
    {"." AUDIO_EXTENSION_MP3,  codecs::Decoder<void>::ID::MPG123},
    {"." AUDIO_EXTENSION_PAF,  codecs::Decoder<void>::ID::SNDFILE_DECODER},
    {"." AUDIO_EXTENSION_PVF,  codecs::Decoder<void>::ID::SNDFILE_DECODER},
    {"." AUDIO_EXTENSION_RF64, codecs::Decoder<void>::ID::SNDFILE_DECODER},
    {"." AUDIO_EXTENSION_SD2,  codecs::Decoder<void>::ID::SNDFILE_DECODER},
    {"." AUDIO_EXTENSION_SDS,  codecs::Decoder<void>::ID::SNDFILE_DECODER},
    {"." AUDIO_EXTENSION_SF,   codecs::Decoder<void>::ID::SNDFILE_DECODER},
    {"." AUDIO_EXTENSION_VOC,  codecs::Decoder<void>::ID::SNDFILE_DECODER},
    {"." AUDIO_EXTENSION_WAV,  codecs::Decoder<void>::ID::SNDFILE_DECODER},
    {"." AUDIO_EXTENSION_W64,  codecs::Decoder<void>::ID::SNDFILE_DECODER},
    {"." AUDIO_EXTENSION_WVE,  codecs::Decoder<void>::ID::SNDFILE_DECODER},
    {"." AUDIO_EXTENSION_XI,   codecs::Decoder<void>::ID::SNDFILE_DECODER}
};

const std::unordered_map<std::string, rusty::codecs::Encoder<void>::ID> rusty::engine::JobBuilder::profile_extension_to_estimated_encoder_id =
{
    {"." PROFILE_EXTENSION_LAME_MP3,             codecs::Encoder<void>::ID::LAME},
    {"." PROFILE_EXTENSION_SNDFILE_ENCODER_AIF,  codecs::Encoder<void>::ID::SNDFILE_ENCODER},
    {"." PROFILE_EXTENSION_SNDFILE_ENCODER_AIFC, codecs::Encoder<void>::ID::SNDFILE_ENCODER},
    {"." PROFILE_EXTENSION_SNDFILE_ENCODER_AIFF, codecs::Encoder<void>::ID::SNDFILE_ENCODER},
    {"." PROFILE_EXTENSION_SNDFILE_ENCODER_AMPC, codecs::Encoder<void>::ID::SNDFILE_ENCODER},
    {"." PROFILE_EXTENSION_SNDFILE_ENCODER_AU,   codecs::Encoder<void>::ID::SNDFILE_ENCODER},
    {"." PROFILE_EXTENSION_SNDFILE_ENCODER_AVR,  codecs::Encoder<void>::ID::SNDFILE_ENCODER},
    {"." PROFILE_EXTENSION_SNDFILE_ENCODER_CAF,  codecs::Encoder<void>::ID::SNDFILE_ENCODER},
    {"." PROFILE_EXTENSION_SNDFILE_ENCODER_HTK,  codecs::Encoder<void>::ID::SNDFILE_ENCODER},
    {"." PROFILE_EXTENSION_SNDFILE_ENCODER_IFF,  codecs::Encoder<void>::ID::SNDFILE_ENCODER},
    {"." PROFILE_EXTENSION_SNDFILE_ENCODER_MAT,  codecs::Encoder<void>::ID::SNDFILE_ENCODER},
    {"." PROFILE_EXTENSION_SNDFILE_ENCODER_PAF,  codecs::Encoder<void>::ID::SNDFILE_ENCODER},
    {"." PROFILE_EXTENSION_SNDFILE_ENCODER_PVF,  codecs::Encoder<void>::ID::SNDFILE_ENCODER},
    {"." PROFILE_EXTENSION_SNDFILE_ENCODER_RF64, codecs::Encoder<void>::ID::SNDFILE_ENCODER},
    {"." PROFILE_EXTENSION_SNDFILE_ENCODER_SD2,  codecs::Encoder<void>::ID::SNDFILE_ENCODER},
    {"." PROFILE_EXTENSION_SNDFILE_ENCODER_SDS,  codecs::Encoder<void>::ID::SNDFILE_ENCODER},
    {"." PROFILE_EXTENSION_SNDFILE_ENCODER_SF,   codecs::Encoder<void>::ID::SNDFILE_ENCODER},
    {"." PROFILE_EXTENSION_SNDFILE_ENCODER_VOC,  codecs::Encoder<void>::ID::SNDFILE_ENCODER},
    {"." PROFILE_EXTENSION_SNDFILE_ENCODER_WAV,  codecs::Encoder<void>::ID::SNDFILE_ENCODER},
    {"." PROFILE_EXTENSION_SNDFILE_ENCODER_W64,  codecs::Encoder<void>::ID::SNDFILE_ENCODER},
    {"." PROFILE_EXTENSION_SNDFILE_ENCODER_WVE,  codecs::Encoder<void>::ID::SNDFILE_ENCODER},
    {"." PROFILE_EXTENSION_SNDFILE_ENCODER_XI,   codecs::Encoder<void>::ID::SNDFILE_ENCODER}
};

rusty::engine::JobBuilder::JobBuilder(const boost::filesystem::path &input_file_path, CallbackInterface &job_builder_callback_interface) : job_builder_callback_interface(&job_builder_callback_interface)
{
    assert(input_file_path.has_parent_path() && input_file_path.has_filename() && input_file_path.filename() != "." && input_file_path.has_extension() && input_file_path.extension() != ".");

    codecs::Decoder<void>::ID estimated_decoder_id_temporary;

    boost::filesystem::path absolute_input_file_path;

    if(input_file_path.is_relative())
        absolute_input_file_path = boost::filesystem::absolute(input_file_path);
    else
        absolute_input_file_path = input_file_path;

    estimated_decoder_id_temporary = audio_file_extension_to_estimated_decoder_id.at(absolute_input_file_path.extension().string());

    this->input_file_path = absolute_input_file_path;
    this->estimated_decoder_id = estimated_decoder_id_temporary;

    job_builder_callback_interface.OnInputFilePathChanged(this->input_file_path);
    job_builder_callback_interface.OnEstimatedDecoderIDChanged(this->estimated_decoder_id);
}

void rusty::engine::JobBuilder::SetEncoderProfilePath(const boost::filesystem::path &encoder_profile_path)
{
    if(!encoder_profile_path.has_parent_path() || encoder_profile_path.filename() == "." || encoder_profile_path.extension() == ".")
        return;

    boost::filesystem::path encoder_profile_path_temporary(this->encoder_profile_path);
    codecs::Encoder<void>::ID estimated_encoder_id_temporary;
    boost::filesystem::path output_file_path_temporary(this->output_file_path);

    boost::filesystem::path absolute_encoder_profile_path;

    if(encoder_profile_path.is_relative())
        absolute_encoder_profile_path = boost::filesystem::absolute(encoder_profile_path);
    else
        absolute_encoder_profile_path = encoder_profile_path;

    bool encoder_profile_path_temporary_changed = false;
    bool estimated_encoder_id_temporary_changed = false;
    bool output_file_path_changed = false;

    if(encoder_profile_path_temporary != absolute_encoder_profile_path)
    {
        encoder_profile_path_temporary = absolute_encoder_profile_path;
        encoder_profile_path_temporary_changed = true;
    }

    if(this->encoder_profile_path.extension() != absolute_encoder_profile_path.extension())
    {
        estimated_encoder_id_temporary = profile_extension_to_estimated_encoder_id.at(absolute_encoder_profile_path.extension().string());
        estimated_encoder_id_temporary_changed = true;
    }

    const std::string file_extension(encoder_profile_path_temporary.extension().string());

    size_t position_of_output_audio_extension = file_extension.find_first_of("-") + 1u;

    const std::string output_audio_extension('.' + file_extension.substr(position_of_output_audio_extension));

    if(output_file_path_temporary.has_parent_path() && ((!output_file_path_temporary.has_filename() || output_file_path_temporary.filename() == ".") || output_file_path_temporary.extension() != output_audio_extension) && estimated_encoder_id_temporary_changed)
    {
        output_file_path_temporary = output_file_path_temporary.parent_path() / input_file_path.filename().replace_extension(output_audio_extension);
        output_file_path_changed = true;
    }

    if(encoder_profile_path_temporary_changed)
    {
        this->encoder_profile_path = encoder_profile_path_temporary;

        job_builder_callback_interface->OnEncoderProfilePathChanged(this->encoder_profile_path);
    }

    if(estimated_encoder_id_temporary_changed)
    {
        this->estimated_encoder_id = estimated_encoder_id_temporary;
        estimated_encoder_id_set = true;

        job_builder_callback_interface->OnEstimatedEncoderIDChanged(this->estimated_encoder_id);
    }

    if(output_file_path_changed)
    {
        this->output_file_path = output_file_path_temporary;

        job_builder_callback_interface->OnOutputFilePathChanged(this->output_file_path);
    }
}

void rusty::engine::JobBuilder::SetOutputFilePath(const boost::filesystem::path &output_file_path)
{
    if(!output_file_path.has_parent_path())
        return;

    boost::filesystem::path output_file_path_temporary(this->output_file_path);

    boost::filesystem::path absolute_output_file_path;

    if(output_file_path.is_relative())
        absolute_output_file_path = boost::filesystem::absolute(output_file_path);
    else
        absolute_output_file_path = output_file_path;

    bool output_file_path_changed = false;

    if(output_file_path_temporary != absolute_output_file_path)
    {
        if(absolute_output_file_path.has_filename() && absolute_output_file_path.filename() != ".")
        {
            output_file_path_temporary = absolute_output_file_path;
        }
        else
        {
            if(output_file_path_temporary.has_filename() && output_file_path_temporary.filename() != ".")
            {
                output_file_path_temporary = absolute_output_file_path.parent_path() / output_file_path_temporary.filename();
            }
            else
            {
                output_file_path_temporary = absolute_output_file_path;
            }
        }

        output_file_path_changed = true;
    }

    if((!output_file_path_temporary.has_filename() || output_file_path_temporary.filename() == ".") && estimated_encoder_id_set)
    {
        const std::string file_extension(this->encoder_profile_path.extension().string());

        size_t position_of_output_audio_extension = file_extension.find_first_of("-") + 1u;

        const std::string output_audio_extension('.' + file_extension.substr(position_of_output_audio_extension));

        output_file_path_temporary = output_file_path_temporary.parent_path() / input_file_path.filename().replace_extension(output_audio_extension);
        output_file_path_changed = true;
    }

    if(output_file_path_changed)
    {
        this->output_file_path = output_file_path_temporary;

        job_builder_callback_interface->OnOutputFilePathChanged(this->output_file_path);
    }
}

const boost::filesystem::path & rusty::engine::JobBuilder::GetInputFilePath() const
{
    return input_file_path;
}

rusty::codecs::Decoder<void>::ID rusty::engine::JobBuilder::GetEstimatedDecoderID() const
{
    return estimated_decoder_id;
}

const boost::filesystem::path & rusty::engine::JobBuilder::GetEncoderProfilePath() const
{
    return encoder_profile_path;
}

bool rusty::engine::JobBuilder::IsEstimatedEncoderIDSet() const
{
    return estimated_encoder_id_set;
}

rusty::codecs::Encoder<void>::ID rusty::engine::JobBuilder::GetEstimatedEncoderID() const
{
    assert(estimated_encoder_id_set);
    return estimated_encoder_id;
}

const boost::filesystem::path & rusty::engine::JobBuilder::GetOutputFilePath() const
{
    return output_file_path;
}

bool rusty::engine::JobBuilder::IsBuilderCompleted() const
{
    return !encoder_profile_path.empty() && estimated_encoder_id_set && !output_file_path.empty();
}

rusty::engine::JobBuilder::CompletedBuilder rusty::engine::JobBuilder::GetCompletedBuilder()
{
    assert(IsBuilderCompleted());
    return CompletedBuilder(input_file_path, estimated_decoder_id, encoder_profile_path, estimated_encoder_id, output_file_path);
}

rusty::engine::JobBuilder::CompletedBuilder::CompletedBuilder(const boost::filesystem::path &input_file_path,
                                                              const codecs::Decoder<void>::ID estimated_decoder_id,
                                                              const boost::filesystem::path &encoder_profile_path,
                                                              const codecs::Encoder<void>::ID estimated_encoder_id,
                                                              const boost::filesystem::path &output_file_path) :
    input_file_path(input_file_path),
    estimated_decoder_id(estimated_decoder_id),
    encoder_profile_path(encoder_profile_path),
    estimated_encoder_id(estimated_encoder_id),
    output_file_path(output_file_path) {}

const boost::filesystem::path & rusty::engine::JobBuilder::CompletedBuilder::GetInputFilePath() const
{
    return input_file_path;
}

rusty::codecs::Decoder<void>::ID rusty::engine::JobBuilder::CompletedBuilder::GetEstimatedDecoderID() const
{
    return estimated_decoder_id;
}

const boost::filesystem::path & rusty::engine::JobBuilder::CompletedBuilder::GetEncoderProfilePath() const
{
    return encoder_profile_path;
}

rusty::codecs::Encoder<void>::ID rusty::engine::JobBuilder::CompletedBuilder::GetEstimatedEncoderID() const
{
    return estimated_encoder_id;
}

const boost::filesystem::path & rusty::engine::JobBuilder::CompletedBuilder::GetOutputFilePath() const
{
    return output_file_path;
}
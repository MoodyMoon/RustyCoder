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
#include "job_description.h"

JobDescription::JobDescription(const std::string &source_file_full_path) :
state(Job::State::NOT_READY)
{
    assert(!source_file_full_path.empty());

    this->source_file_full_path = source_file_full_path;

    SetDecoderID(source_file_full_path);
}

const std::string & JobDescription::GetSourceFileFullPath() const noexcept
{
    return source_file_full_path;
}

const std::string & JobDescription::GetOutputPath() const noexcept
{
    return output_path;
}

const std::string & JobDescription::GetOutputFileName() const noexcept
{
    return output_file_name;
}

const std::string & JobDescription::GetOutputFileExtension() const noexcept
{
    return output_file_extension;
}

const std::string & JobDescription::GetProfileFullPath() const noexcept
{
    return profile_full_path;
}

Decoder<void>::ID JobDescription::GetDecoderID() const noexcept
{
    return decoder_id;
}

Encoder<void>::ID JobDescription::GetEncoderID() const noexcept
{
    return encoder_id;
}

Job::State JobDescription::GetState() const noexcept
{
    return state;
}

void JobDescription::SetOutputPath(const std::string &output_path)
{
    assert(!output_path.empty());

    this->output_path = output_path;

    if(output_file_name.empty() || output_file_extension.empty() || profile_full_path.empty())
    {
        state = Job::State::NOT_READY;
    }
    else if(output_path == RustyFile::GetFile(source_file_full_path, RustyFile::File::PATH) && output_file_name == RustyFile::GetFile(source_file_full_path, RustyFile::File::NAME) && output_file_extension == RustyFile::GetFile(source_file_full_path, RustyFile::File::EXTENSION))
    {
        state = Job::State::NOT_READY;
        throw InvalidArgumentException("JobDescription", "Output file destination cannot be the same as the source file path.");
    }
    else
    {
        state = Job::State::READY;
    }
}

void JobDescription::SetOutputFileName(const std::string &output_file_name)
{
    assert(!output_file_name.empty());

    this->output_file_name = output_file_name;

    if(output_path.empty() || output_file_extension.empty() || profile_full_path.empty())
    {
        state = Job::State::NOT_READY;
    }
    else if(output_path == RustyFile::GetFile(source_file_full_path, RustyFile::File::PATH) && output_file_name == RustyFile::GetFile(source_file_full_path, RustyFile::File::NAME) && output_file_extension == RustyFile::GetFile(source_file_full_path, RustyFile::File::EXTENSION))
    {
        state = Job::State::NOT_READY;
        throw InvalidArgumentException("JobDescription", "Output file destination cannot be the same as the source file path.");
    }
    else
    {
        state = Job::State::READY;
    }
}

void JobDescription::SetProfileFullPath(const std::string &profile_full_path)
{
    assert(!profile_full_path.empty());

    this->profile_full_path = profile_full_path;

    try
    {
        SetEncoderID(profile_full_path);

        if(output_path.empty() || output_file_name.empty() || output_file_extension.empty())
            state = Job::State::NOT_READY;
        else
            state = Job::State::READY;
    }
    catch(InvalidArgumentException &)
    {
        throw;
    }
}

void JobDescription::SetState(Job::State state) noexcept
{
    switch(state)
    {
        case Job::NOT_READY:
        case Job::READY:
            assert(false);
            break;
        default:
            this->state = state;
    }
}

void JobDescription::SetDecoderID(const std::string &source_file_full_path)
{
    std::string source_file_extension(RustyFile::GetFile(source_file_full_path, RustyFile::File::EXTENSION));

    if(source_file_extension == AUDIO_EXTENSION_MP1 || source_file_extension == AUDIO_EXTENSION_MP2 || source_file_extension == AUDIO_EXTENSION_MP3)
    {
        decoder_id = Decoder<void>::ID::MPG123;
    }
    else
    {
        decoder_id = Decoder<void>::ID::SNDFILEDECODER;
    }
}

void JobDescription::SetEncoderID(const std::string &profile_full_path)
{
    std::string profile_file_extension(RustyFile::GetFile(profile_full_path, RustyFile::File::EXTENSION));

    if(profile_file_extension == PROFILE_EXTENSION_SNDFILEENCODER)
    {
        encoder_id = Encoder<void>::ID::SNDFILEENCODER;

        SndFileEncoderOptions sndfileencoder_options;

        try
        {
            SettingsManager::Read(sndfileencoder_options, profile_full_path);
        }
        catch(ReadFileException &)
        {
            state = Job::State::NOT_READY;
            throw;
        }

        SetOutputFileExtension(profile_full_path, sndfileencoder_options.output_format_to_file_extension.at(sndfileencoder_options.output_format));
    }
    else if(profile_file_extension == PROFILE_EXTENSION_LAME)
    {
        encoder_id = Encoder<void>::ID::LAME;

        SetOutputFileExtension(profile_full_path, AUDIO_EXTENSION_MP3);
    }
}

void JobDescription::SetOutputFileExtension(const std::string &profile_full_path, const std::string &output_file_extension)
{
    assert(!output_file_extension.empty());

    this->output_file_extension = output_file_extension;

    if(output_path.empty() || output_file_name.empty() || profile_full_path.empty())
    {
        state = Job::State::NOT_READY;
    }
    else if(output_path == RustyFile::GetFile(source_file_full_path, RustyFile::File::PATH) && output_file_name == RustyFile::GetFile(source_file_full_path, RustyFile::File::NAME) && output_file_extension == RustyFile::GetFile(source_file_full_path, RustyFile::File::EXTENSION))
    {
        state = Job::State::NOT_READY;
        throw InvalidArgumentException("JobDescription", "Output file destination cannot be the same as the source file path.");
    }
    else
    {
        state = Job::State::READY;
    }
}
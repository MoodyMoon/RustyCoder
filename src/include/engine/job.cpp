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
#include "job.h"

const std::unordered_map<Job::State, std::string> Job::state_to_string =
{
    {State::NOT_READY, "Not ready"},
    {State::READY, "Ready"},
    {State::RUNNING, "Running"},
    {State::PAUSE, "Paused"},
    {State::DONE, "Done"},
    {State::ERROR_OCCURED, "Error"}
};

Job::Job(const std::string &source_file_full_path, const std::string &output_file_full_path, Decoder<void>::ID decoder_id, const LameOptions &lame_options) : encoder_options(new LameOptions(lame_options))
{
    LameOptions *_encoder_options = static_cast<LameOptions *>(this->encoder_options.get());

    codec_controller.reset(new CodecController(source_file_full_path, output_file_full_path, decoder_id, *_encoder_options));

    total_frame_count = codec_controller->GetTotalFrameCount();
}

Job::Job(const std::string &source_file_full_path, const std::string &output_file_full_path, Decoder<void>::ID decoder_id, const SndFileEncoderOptions &sndfileencoder_options) : encoder_options(new SndFileEncoderOptions(sndfileencoder_options))
{
    SndFileEncoderOptions *_encoder_options = static_cast<SndFileEncoderOptions *>(this->encoder_options.get());

    codec_controller.reset(new CodecController(source_file_full_path, output_file_full_path, decoder_id, *_encoder_options));

    total_frame_count = codec_controller->GetTotalFrameCount();
}

void Job::StartAsync()
{
    State _state = state.load();

    if(_state == State::READY || _state == State::PAUSE)
    {
        state.store(State::RUNNING);
        thread.reset(new RustyThread(this, nullptr, RustyThread::Priority::NORMAL));
    }
    #ifdef _DEBUG
    else
        assert(false);
    #endif
}

void Job::PauseSync()
{
    if(state.load() == State::RUNNING)
    {
        state.store(State::PAUSE);
        thread.reset();
    }
    #ifdef _DEBUG
    else
        assert(false);
    #endif
}

Job::State Job::GetStateSync() const noexcept
{
    return state.load();
}

Exception * Job::GetError() const noexcept
{
    return error.load().get();
}

uint64_t Job::GetWrittenFrameCount() const noexcept
{
    return written_frame_count.load();
}

uint64_t Job::GetTotalFrameCount() const noexcept
{
    return total_frame_count.load();
}

DWORD Job::DoSync(void *)
{
    CodecController *_codec_controller = codec_controller.get();

    int check_pause_count = 0;

    try
    {
        do
        {
            if(_codec_controller->CanConvert())
            {
                written_frame_count.fetch_add(_codec_controller->Convert());
            }
            else
            {
                state.store(State::DONE);
                codec_controller.reset();
                break;
            }
            if(check_pause_count < 10)
            {
                ++check_pause_count;
                continue;
            }
            else
            {
                check_pause_count = 0;
            }
        }while(state.load() == State::RUNNING);
    }
    catch(Exception &ex)
    {
        state.store(State::ERROR_OCCURED);
        error.load().reset(new Exception(ex));
    }

    return 0ul;
}

Job::~Job()
{
    if(state.load() == State::RUNNING)
    {
        state.store(State::PAUSE);
        thread.reset();
    }
}
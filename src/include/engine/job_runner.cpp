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
#include "job_runner.h"

rusty::engine::JobRunner::JobRunner(const boost::filesystem::path &input_file_path, const boost::filesystem::path &output_file_path, codecs::Decoder<void>::ID decoder_id, const codecs::EncoderProfile &encoder_profile, codecs::Encoder<void>::ID encoder_id, CallbackInterface &callback_interface) : callback_interface(&callback_interface), timer(this, 200u, false), old_state(Common::JobRunnerState::PAUSED), state(old_state), old_written_frame_count(0ull), written_frame_count(old_written_frame_count), total_frame_count(0ull)
{
    try
    {
        codec_controller.reset(new CodecController(input_file_path, output_file_path, decoder_id, encoder_profile, encoder_id));

        total_frame_count = codec_controller->GetTotalFrameCount();

        callback_interface.OnStateChanged(state.load());

        callback_interface.OnWrittenFrameCountChanged(written_frame_count);

        callback_interface.OnTotalFrameCountChanged(total_frame_count);
    }
    catch(const core::Exception &ex)
    {
        state.store(Common::JobRunnerState::ERROR_OCCURRED);
        error.reset(new core::Exception(ex));
        callback_interface.OnStateChanged(state.load());
        callback_interface.OnErrorOccurred(GetError());
    }
}

void rusty::engine::JobRunner::Start()
{
    Common::JobRunnerState expected = Common::JobRunnerState::PAUSED;
    bool exchanged = state.compare_exchange_strong(expected, Common::JobRunnerState::RUNNING);

    if(exchanged)
    {
        thread.reset(new core::Thread(*this, core::Thread::Priority::NORMAL));
        timer.Start();
    }
}

void rusty::engine::JobRunner::Pause()
{
    Pause(true);
}

void rusty::engine::JobRunner::Pause(bool callback)
{
    Common::JobRunnerState expected = Common::JobRunnerState::RUNNING;
    bool exchanged = state.compare_exchange_strong(expected, Common::JobRunnerState::PAUSED);

    if(exchanged)
    {
        thread.reset();
        timer.Stop();
    }

    if(callback)
        OnTimerSyncTick();
}

void rusty::engine::JobRunner::OnTimerSyncTick()
{
    Common::JobRunnerState state = GetState();

    if(old_state != state)
    {
        old_state = state;
        callback_interface->OnStateChanged(state);

        if(state == Common::JobRunnerState::DONE || state == Common::JobRunnerState::ERROR_OCCURRED)
        {
            thread.reset();

            timer.Stop();

            if(state == Common::JobRunnerState::ERROR_OCCURRED)
            {
                callback_interface->OnErrorOccurred(GetError());
            }
        }
    }

    uint64_t written_frame_count = GetWrittenFrameCount();

    if(old_written_frame_count != written_frame_count)
    {
        callback_interface->OnWrittenFrameCountChanged(written_frame_count);
    }
}

void rusty::engine::JobRunner::ThreadDo()
{
    CodecController *_codec_controller = codec_controller.get();

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
                codec_controller.reset();
                state.store(Common::JobRunnerState::DONE);
                break;
            }
        }
        while(state.load() == Common::JobRunnerState::RUNNING);
    }
    catch(const core::Exception &ex)
    {
        codec_controller.reset();
        state.store(Common::JobRunnerState::ERROR_OCCURRED);
        error_lock.ExclusiveLock();
        error.reset(new core::Exception(ex));
        error_lock.ExclusiveUnlock();
    }
}

rusty::engine::Common::JobRunnerState rusty::engine::JobRunner::GetState() const noexcept
{
    return state.load();
}

const rusty::core::Exception * rusty::engine::JobRunner::GetError()
{
    core::ManagedSharedReaderWriterLock managed_error_lock(error_lock);
    return error.get();
}

uint64_t rusty::engine::JobRunner::GetWrittenFrameCount() const noexcept
{
    return written_frame_count.load();
}

uint64_t rusty::engine::JobRunner::GetTotalFrameCount() const noexcept
{
    return total_frame_count;
}

rusty::engine::JobRunner::~JobRunner()
{
    Pause(false);
}
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

#ifndef ENGINE_JOB_RUNNER_H
#define ENGINE_JOB_RUNNER_H

#include "../codecs/decoder.h"
#include "../codecs/encoder_profile.h"
#include "../codecs/lame_profile.h"
#include "../codecs/sndfile_encoder_profile.h"
#include "../core/exception.h"
#include "../core/reader_writer_lock.h"
#include "../core/thread.h"
#include "../core/timer_sync.h"
#include "codec_controller.h"
#include "common.h"

namespace rusty
{
namespace engine
{
class JobRunner : public core::Thread::CallbackInterface, public core::TimerSync::CallbackInterface
{
    public:
        class CallbackInterface;

    private:
        std::unique_ptr<CodecController> codec_controller;

        CallbackInterface *callback_interface;

        core::TimerSync timer;

        std::unique_ptr<core::Thread> thread;

        Common::JobRunnerState old_state;
        std::atomic<Common::JobRunnerState> state;

        core::ReaderWriterLock error_lock;
        std::unique_ptr<core::Exception> error;

        uint64_t old_written_frame_count;
        std::atomic<uint64_t> written_frame_count;
        uint64_t total_frame_count;

        void Pause(bool callback);

        virtual void OnTimerSyncTick(void);

        virtual void ThreadDo(void);

    public:
        JobRunner(const JobRunner &) = delete;
        JobRunner & operator=(const JobRunner &) = delete;

        JobRunner(const boost::filesystem::path &input_file_path, const boost::filesystem::path &output_file_path, codecs::Decoder<void>::ID decoder_id, const codecs::EncoderProfile &encoder_profile, codecs::Encoder<void>::ID encoder_id, CallbackInterface &callback_interface);

        void Start(void);
        void Pause(void);

        Common::JobRunnerState GetState(void) const noexcept;
        const core::Exception * GetError(void);

        uint64_t GetWrittenFrameCount(void) const noexcept;
        uint64_t GetTotalFrameCount(void) const noexcept;

        virtual ~JobRunner(void);
};

class JobRunner::CallbackInterface
{
    protected:
        CallbackInterface(void) = default;

    public:
        CallbackInterface(const CallbackInterface &) = delete;
        CallbackInterface & operator=(const CallbackInterface &) = delete;

        virtual void OnStateChanged(Common::JobRunnerState state) = 0;
        virtual void OnErrorOccurred(const core::Exception *error) = 0;
        virtual void OnWrittenFrameCountChanged(uint64_t written_frame_count) = 0;
        virtual void OnTotalFrameCountChanged(uint64_t total_frame_count) = 0;

        virtual ~CallbackInterface(void) {};
};
}
}

#endif
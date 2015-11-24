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
#include "job_builder_runner.h"

rusty::engine2::JobBuilderRunner::JobBuilderRunner(const boost::filesystem::path &input_file_path, Callback &callback) : job_builder(input_file_path, callback), job_builder_runner_callback(&callback)
{
    callback.OnStateChanged(Common::JobBuilderRunnerState::NOT_READY);
}

const boost::filesystem::path & rusty::engine2::JobBuilderRunner::GetOutputFilePath() const
{
    return job_builder.GetOutputFilePath();
}

void rusty::engine2::JobBuilderRunner::SetEncoderProfilePath(const boost::filesystem::path &encoder_profile_path)
{
    if(job_runner.get() == nullptr)
    {
        job_builder.SetEncoderProfilePath(encoder_profile_path);

        TryAnnounceStateChanged();
    }
}

void rusty::engine2::JobBuilderRunner::SetOutputFilePath(const boost::filesystem::path &output_file_path)
{
    if(job_runner.get() == nullptr)
    {
        job_builder.SetOutputFilePath(output_file_path);

        TryAnnounceStateChanged();
    }
}

void rusty::engine2::JobBuilderRunner::TryAnnounceStateChanged()
{
    now_ready = job_builder.IsBuilderCompleted();

    if(old_ready != now_ready)
    {
        job_builder_runner_callback->OnStateChanged(now_ready ? Common::JobBuilderRunnerState::READY : Common::JobBuilderRunnerState::NOT_READY);
        old_ready = now_ready;
    }
}

void rusty::engine2::JobBuilderRunner::Start()
{
    if(job_runner.get() == nullptr)
    {
        if(job_builder.IsBuilderCompleted())
        {
            engine::JobBuilder::CompletedBuilder completed_job_builder(job_builder.GetCompletedBuilder());

            engine::EncoderProfileReader encoder_profile_reader(completed_job_builder.GetEncoderProfilePath());

            std::shared_ptr<codecs::EncoderProfile> encoder_profile(encoder_profile_reader.GetEncoderProfile());

            const codecs::EncoderProfile * _enocder_profile = encoder_profile.get();

            job_runner.reset(new engine::JobRunner(completed_job_builder.GetInputFilePath(), completed_job_builder.GetOutputFilePath(), completed_job_builder.GetEstimatedDecoderID(), *_enocder_profile, encoder_profile_reader.GetEncoderID(), *job_builder_runner_callback));

            job_runner->Start();
        }
    }
    else if(job_runner->GetState() == engine::Common::JobRunnerState::PAUSED)
    {
        job_runner->Start();
    }
}

void rusty::engine2::JobBuilderRunner::Pause()
{
    if(job_runner.get() != nullptr && job_runner->GetState() == engine::Common::JobRunnerState::RUNNING)
    {
        job_runner->Pause();
    }
}

const boost::filesystem::path & rusty::engine2::JobBuilderRunner::GetInputFilePath() const
{
    return job_builder.GetInputFilePath();
}

std::string rusty::engine2::JobBuilderRunner::GetEstimatedDecoderID() const
{
    return codecs::Decoder<void>::decoder_id_to_text.at(job_builder.GetEstimatedDecoderID());
}

const boost::filesystem::path & rusty::engine2::JobBuilderRunner::GetEncoderProfilePath() const
{
    return job_builder.GetEncoderProfilePath();
}

std::string rusty::engine2::JobBuilderRunner::GetEstimatedEncoderID() const
{
    if(job_builder.IsEstimatedEncoderIDSet())
        return codecs::Encoder<void>::encoder_id_to_text.at(job_builder.GetEstimatedEncoderID());
    else
        return nullptr;
}

rusty::engine2::Common::JobBuilderRunnerState rusty::engine2::JobBuilderRunner::GetState() const
{
    if(job_runner.get() == nullptr)
    {
        return now_ready ? Common::JobBuilderRunnerState::READY : Common::JobBuilderRunnerState::NOT_READY;
    }
    else
    {
        return engine2::Common::JobRunnerStateToJobBuilderRunnerState(job_runner->GetState());
    }
}
const rusty::core::Exception * rusty::engine2::JobBuilderRunner::GetError()
{
    if(job_runner.get() == nullptr)
        return nullptr;
    else
        return job_runner->GetError();
}

uint64_t rusty::engine2::JobBuilderRunner::GetWrittenFrameCount() const noexcept
{
    if(job_runner.get() == nullptr)
        return 0ull;
    else
        return job_runner->GetWrittenFrameCount();
}

uint64_t rusty::engine2::JobBuilderRunner::GetTotalFrameCount() const noexcept
{
    if(job_runner.get() == nullptr)
        return 0ull;
    else
        return job_runner->GetTotalFrameCount();
}

void rusty::engine2::JobBuilderRunner::Callback::OnStateChanged(engine::Common::JobRunnerState state)
{
    OnStateChanged(Common::JobRunnerStateToJobBuilderRunnerState(state));
}
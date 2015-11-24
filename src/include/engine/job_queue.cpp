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
#include "job_queue.h"

const unsigned int rusty::engine2::JobQueue::MAX_CONCURRENT_JOB_COUNT = std::thread::hardware_concurrency() == 0u ? 1u : std::thread::hardware_concurrency();

void rusty::engine2::JobQueue::AppendJob(const boost::filesystem::path &input_file_path, Callback &callback)
{
    indexed_job_builder_runner_callbacks.emplace_back(std::unique_ptr<IndexedJobBuilderRunnerCallback>(new IndexedJobBuilderRunnerCallback(callback, std::bind(&JobQueue::OnJobStateChanged, this, std::placeholders::_1))));

    size_t job_index = job_builders_runners.size();

    indexed_job_builder_runner_callbacks.back()->SetJobIndex(job_index);

    job_builders_runners.emplace_back(std::unique_ptr<JobBuilderRunner>(new JobBuilderRunner(input_file_path, *indexed_job_builder_runner_callbacks.back().get())));
}

void rusty::engine2::JobQueue::RemoveJob(std::vector<std::unique_ptr<JobBuilderRunner>>::const_iterator job_iterator_first, std::vector<std::unique_ptr<JobBuilderRunner>>::const_iterator job_iterator_last)
{
    if(job_iterator_first < job_iterator_last)
    {
        ptrdiff_t removed_elements_count = job_iterator_last - job_iterator_first;

        ptrdiff_t first_distance = std::distance(job_builders_runners.cbegin(), job_iterator_first);
        ptrdiff_t last_distance = std::distance(job_builders_runners.cbegin(), job_iterator_last);

        std::vector<std::unique_ptr<JobBuilderRunner>>::const_iterator job_builders_runners_iterator = job_builders_runners.erase(job_iterator_first, job_iterator_last);

        std::vector<std::unique_ptr<IndexedJobBuilderRunnerCallback>>::const_iterator indexed_job_builder_runner_callbacks_iterator_first = indexed_job_builder_runner_callbacks.cbegin() + first_distance;
        std::vector<std::unique_ptr<IndexedJobBuilderRunnerCallback>>::const_iterator indexed_job_builder_runner_callbacks_iterator_last = indexed_job_builder_runner_callbacks.cbegin() + last_distance;

        std::vector<std::unique_ptr<IndexedJobBuilderRunnerCallback>>::const_iterator indexed_job_builder_runner_callbacks_iterator = indexed_job_builder_runner_callbacks.erase(indexed_job_builder_runner_callbacks_iterator_first, indexed_job_builder_runner_callbacks_iterator_last);

        for(; indexed_job_builder_runner_callbacks_iterator < indexed_job_builder_runner_callbacks.cend(); ++indexed_job_builder_runner_callbacks_iterator)
        {
            (*indexed_job_builder_runner_callbacks_iterator)->SetJobIndex((*indexed_job_builder_runner_callbacks_iterator)->GetJobIndex() - removed_elements_count);
        }
    }
}

void rusty::engine2::JobQueue::Start()
{
    TryResumeActiveJobs();

    TryQueueNewJobs();
}

void rusty::engine2::JobQueue::Pause()
{
    std::vector<std::unique_ptr<JobBuilderRunner>>::const_iterator job_builder_runner_iterator = job_builders_runners.cbegin();

    for(; running_job_count > 0u && job_builder_runner_iterator < job_builders_runners.cend(); ++job_builder_runner_iterator)
    {
        if((*job_builder_runner_iterator)->GetState() == Common::JobBuilderRunnerState::RUNNING)
        {
            (*job_builder_runner_iterator)->Pause();
            --running_job_count;
        }
    }
}

std::vector<std::unique_ptr<rusty::engine2::JobBuilderRunner>>::const_iterator rusty::engine2::JobQueue::GetJobIterator(unsigned int job_index)
{
    return job_builders_runners.cbegin() + job_index;
}

void rusty::engine2::JobQueue::TryResumeActiveJobs(void)
{
    std::vector<std::unique_ptr<JobBuilderRunner>>::const_iterator job_builder_runner_iterator = job_builders_runners.cbegin();

    for(; running_job_count < active_job_count && job_builder_runner_iterator < job_builders_runners.cend(); ++job_builder_runner_iterator)
    {
        if((*job_builder_runner_iterator)->GetState() == Common::JobBuilderRunnerState::PAUSED)
        {
            (*job_builder_runner_iterator)->Start();
            ++running_job_count;
        }
    }
}

void rusty::engine2::JobQueue::TryQueueNewJobs()
{
    std::vector<std::unique_ptr<JobBuilderRunner>>::const_iterator job_builder_runner_iterator = job_builders_runners.cbegin();

    for(; active_job_count < MAX_CONCURRENT_JOB_COUNT && job_builder_runner_iterator < job_builders_runners.cend(); ++job_builder_runner_iterator)
    {
        if((*job_builder_runner_iterator)->GetState() == Common::JobBuilderRunnerState::READY)
        {
            (*job_builder_runner_iterator)->Start();
            ++running_job_count;
            ++active_job_count;
        }
    }
}

void rusty::engine2::JobQueue::OnJobStateChanged(Common::JobBuilderRunnerState state)
{
    if(state == Common::JobBuilderRunnerState::DONE || state == Common::JobBuilderRunnerState::ERROR_OCCURRED)
    {
        --running_job_count;
        --active_job_count;

        TryQueueNewJobs();
    }
}

rusty::engine2::JobQueue::IndexedJobBuilderRunnerCallback::IndexedJobBuilderRunnerCallback(JobQueue::Callback &job_queue_callback, std::function<void(Common::JobBuilderRunnerState state)> on_job_state_change) : job_queue_callback(&job_queue_callback), on_job_state_change(on_job_state_change) {}

void rusty::engine2::JobQueue::IndexedJobBuilderRunnerCallback::SetJobIndex(unsigned int job_index)
{
    this->job_index = job_index;
}

unsigned int rusty::engine2::JobQueue::IndexedJobBuilderRunnerCallback::GetJobIndex(void)
{
    return job_index;
}

void rusty::engine2::JobQueue::IndexedJobBuilderRunnerCallback::OnInputFilePathChanged(const boost::filesystem::path &input_file_path)
{
    job_queue_callback->OnInputFilePathChanged(input_file_path, job_index);
}

void rusty::engine2::JobQueue::IndexedJobBuilderRunnerCallback::OnEstimatedDecoderIDChanged(codecs::Decoder<void>::ID estimated_decoder_id)
{
    job_queue_callback->OnEstimatedDecoderIDChanged(estimated_decoder_id, job_index);
}

void rusty::engine2::JobQueue::IndexedJobBuilderRunnerCallback::OnEncoderProfilePathChanged(const boost::filesystem::path &encoder_profile_path)
{
    job_queue_callback->OnEncoderProfilePathChanged(encoder_profile_path, job_index);
}

void rusty::engine2::JobQueue::IndexedJobBuilderRunnerCallback::OnEstimatedEncoderIDChanged(codecs::Encoder<void>::ID estimated_encoder_id)
{
    job_queue_callback->OnEstimatedEncoderIDChanged(estimated_encoder_id, job_index);
}

void rusty::engine2::JobQueue::IndexedJobBuilderRunnerCallback::OnOutputFilePathChanged(boost::filesystem::path output_file_path)
{
    job_queue_callback->OnOutputFilePathChanged(output_file_path, job_index);
}

void rusty::engine2::JobQueue::IndexedJobBuilderRunnerCallback::OnStateChanged(Common::JobBuilderRunnerState state)
{
    job_queue_callback->OnStateChanged(state, job_index);

    on_job_state_change(state);
}

void rusty::engine2::JobQueue::IndexedJobBuilderRunnerCallback::OnErrorOccurred(const core::Exception *error)
{
    job_queue_callback->OnErrorOccurred(error, job_index);
}

void rusty::engine2::JobQueue::IndexedJobBuilderRunnerCallback::OnWrittenFrameCountChanged(uint64_t written_frame_count)
{
    job_queue_callback->OnWrittenFrameCountChanged(written_frame_count, job_index);
}

void rusty::engine2::JobQueue::IndexedJobBuilderRunnerCallback::OnTotalFrameCountChanged(uint64_t total_frame_count)
{
    job_queue_callback->OnTotalFrameCountChanged(total_frame_count, job_index);
}
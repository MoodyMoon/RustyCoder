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

#ifndef ENGINE_JOB_QUEUE_H
#define ENGINE_JOB_QUEUE_H

#include "job_builder_runner.h"

namespace rusty
{
namespace engine2
{
class JobQueue
{
    public:
        class Callback;

    private:
        class IndexedJobBuilderRunnerCallback;

    private:
        std::vector<std::unique_ptr<JobBuilderRunner>> job_builders_runners;
        std::vector<std::unique_ptr<IndexedJobBuilderRunnerCallback>> indexed_job_builder_runner_callbacks;

        void TryResumeActiveJobs(void);
        void TryQueueNewJobs(void);

        void OnJobStateChanged(Common::JobBuilderRunnerState state);

    public:
        const static unsigned int MAX_CONCURRENT_JOB_COUNT;
        unsigned int running_job_count = 0u;
        unsigned int active_job_count = 0u;

        JobQueue(void) = default;
        JobQueue(const JobQueue &) = delete;
        JobQueue & operator=(const JobQueue &) = delete;

        void AppendJob(const boost::filesystem::path &input_file_path, Callback &callback);
        void RemoveJob(std::vector<std::unique_ptr<JobBuilderRunner>>::const_iterator job_iterator_first, std::vector<std::unique_ptr<JobBuilderRunner>>::const_iterator job_iterator_last);

        void Start(void);
        void Pause(void);

        std::vector<std::unique_ptr<JobBuilderRunner>>::const_iterator GetJobIterator(unsigned int job_index);
};

class JobQueue::Callback
{
    protected:
        Callback(void) = default;

    public:
        Callback(const Callback &) = delete;
        Callback & operator=(const Callback &) = delete;

        virtual void OnInputFilePathChanged(const boost::filesystem::path &input_file_path, unsigned int job_index) = 0;
        virtual void OnEstimatedDecoderIDChanged(codecs::Decoder<void>::ID estimated_decoder_id, unsigned int job_index) = 0;
        virtual void OnEncoderProfilePathChanged(const boost::filesystem::path &encoder_profile_path, unsigned int job_index) = 0;
        virtual void OnEstimatedEncoderIDChanged(codecs::Encoder<void>::ID estimated_encoder_id, unsigned int job_index) = 0;
        virtual void OnOutputFilePathChanged(boost::filesystem::path output_file_path, unsigned int job_index) = 0;

        virtual void OnStateChanged(Common::JobBuilderRunnerState state, unsigned int job_index) = 0;
        virtual void OnErrorOccurred(const core::Exception *error, unsigned int job_index) = 0;
        virtual void OnWrittenFrameCountChanged(uint64_t written_frame_count, unsigned int job_index) = 0;
        virtual void OnTotalFrameCountChanged(uint64_t total_frame_count, unsigned int job_index) = 0;

        virtual ~Callback(void) {};
};

class JobQueue::IndexedJobBuilderRunnerCallback : public JobBuilderRunner::Callback
{
    private:
        unsigned int job_index;

        JobQueue::Callback *job_queue_callback;

        std::function<void(Common::JobBuilderRunnerState state)> on_job_state_change;

        virtual void OnInputFilePathChanged(const boost::filesystem::path &input_file_path);
        virtual void OnEstimatedDecoderIDChanged(codecs::Decoder<void>::ID estimated_decoder_id);
        virtual void OnEncoderProfilePathChanged(const boost::filesystem::path &encoder_profile_path);
        virtual void OnEstimatedEncoderIDChanged(codecs::Encoder<void>::ID estimated_encoder_id);
        virtual void OnOutputFilePathChanged(boost::filesystem::path output_file_path);

        virtual void OnStateChanged(Common::JobBuilderRunnerState state);
        virtual void OnErrorOccurred(const core::Exception *error);
        virtual void OnWrittenFrameCountChanged(uint64_t written_frame_count);
        virtual void OnTotalFrameCountChanged(uint64_t total_frame_count);

    public:
        IndexedJobBuilderRunnerCallback(const IndexedJobBuilderRunnerCallback &) = delete;
        IndexedJobBuilderRunnerCallback & operator=(const IndexedJobBuilderRunnerCallback &) = delete;

        explicit IndexedJobBuilderRunnerCallback(JobQueue::Callback &job_queue_callback, std::function<void(Common::JobBuilderRunnerState state)> on_job_state_change);

        void SetJobIndex(unsigned int job_index);
        unsigned int GetJobIndex(void);
};
}
}

#endif
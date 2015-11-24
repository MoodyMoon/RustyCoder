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

#ifndef ENGINE2_JOB_BUILDER_RUNNER_H
#define ENGINE2_JOB_BUILDER_RUNNER_H

#include "common.h"
#include "encoder_profile_reader.h"
#include "job_builder.h"
#include "job_runner.h"

namespace rusty
{
namespace engine2
{
class JobBuilderRunner
{
    public:
        class Callback;

    private:
        bool old_ready = false;
        bool now_ready = false;

        engine::JobBuilder job_builder;
        std::unique_ptr<engine::JobRunner> job_runner;
        JobBuilderRunner::Callback *job_builder_runner_callback;

        void TryAnnounceStateChanged(void);

    public:
        JobBuilderRunner(const JobBuilderRunner &) = delete;
        JobBuilderRunner & operator=(const JobBuilderRunner &) = delete;

        JobBuilderRunner(const boost::filesystem::path &input_file_path, Callback &callback);

        void SetEncoderProfilePath(const boost::filesystem::path &encoder_profile_path);
        void SetOutputFilePath(const boost::filesystem::path &output_file_path);

        void Start(void);
        void Pause(void);

        const boost::filesystem::path & GetInputFilePath(void) const;
        std::string GetEstimatedDecoderID(void) const;
        const boost::filesystem::path & GetEncoderProfilePath(void) const;
        std::string GetEstimatedEncoderID(void) const;
        const boost::filesystem::path & GetOutputFilePath(void) const;

        Common::JobBuilderRunnerState GetState() const;

        const core::Exception * GetError(void);
        uint64_t GetWrittenFrameCount(void) const noexcept;
        uint64_t GetTotalFrameCount(void) const noexcept;
};

class JobBuilderRunner::Callback : public engine::JobBuilder::CallbackInterface, public engine::JobRunner::CallbackInterface
{
    private:
        virtual void OnStateChanged(engine::Common::JobRunnerState state);

    protected:
        Callback(void) = default;

    public:
        Callback(const Callback &) = delete;
        Callback & operator=(const Callback &) = delete;

        virtual void OnStateChanged(Common::JobBuilderRunnerState state) = 0;

        virtual ~Callback(void) {};
};
}
}

#endif
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

#ifndef ENGINE_COMMON_H
#define ENGINE_COMMON_H

#include "stdafx.h"

namespace rusty
{
namespace engine
{
class Common
{
    public:
        enum class JobRunnerState : uint8_t
        {
            RUNNING,
            PAUSED,
            DONE,
            ERROR_OCCURRED
        };

        static const std::unordered_map<JobRunnerState, std::string> job_runner_state_to_string;
};
}

namespace engine2
{
class Common
{
    public:
        enum class JobBuilderRunnerState : uint8_t
        {
            NOT_READY,
            READY,
            RUNNING,
            PAUSED,
            DONE,
            ERROR_OCCURRED
        };

        static const std::unordered_map<JobBuilderRunnerState, std::string> job_builder_runner_state_to_string;

        static JobBuilderRunnerState JobRunnerStateToJobBuilderRunnerState(engine::Common::JobRunnerState state);
};
}
}

#endif
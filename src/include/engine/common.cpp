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
#include "common.h"

const std::unordered_map<rusty::engine::Common::JobRunnerState, std::string> rusty::engine::Common::job_runner_state_to_string =
{
    {JobRunnerState::RUNNING, "Running"},
    {JobRunnerState::PAUSED, "Paused"},
    {JobRunnerState::DONE, "Done"},
    {JobRunnerState::ERROR_OCCURRED, "Error"}
};

const std::unordered_map<rusty::engine2::Common::JobBuilderRunnerState, std::string> rusty::engine2::Common::job_builder_runner_state_to_string =
{
    {JobBuilderRunnerState::NOT_READY, "Not ready"},
    {JobBuilderRunnerState::READY, "Ready"},
    {JobBuilderRunnerState::RUNNING, "Running"},
    {JobBuilderRunnerState::PAUSED, "Paused"},
    {JobBuilderRunnerState::DONE, "Done"},
    {JobBuilderRunnerState::ERROR_OCCURRED, "Error"}
};

rusty::engine2::Common::JobBuilderRunnerState rusty::engine2::Common::JobRunnerStateToJobBuilderRunnerState(engine::Common::JobRunnerState state)
{
    switch(state)
    {
        case engine::Common::JobRunnerState::RUNNING:
            return JobBuilderRunnerState::RUNNING;
        case engine::Common::JobRunnerState::PAUSED:
            return JobBuilderRunnerState::PAUSED;
        case engine::Common::JobRunnerState::DONE:
            return JobBuilderRunnerState::DONE;
        case engine::Common::JobRunnerState::ERROR_OCCURRED:
            return JobBuilderRunnerState::ERROR_OCCURRED;
        default:
            assert(false);
    }
}
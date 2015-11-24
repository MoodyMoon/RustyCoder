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
#include "exception.h"

rusty::core::Exception::Exception(const char * const caller_name, bool has_code, int code, const char * const message, ID exception_id) : exception_id(exception_id),
                                                                                                                                          caller_name(caller_name),
                                                                                                                                          has_code(has_code),
                                                                                                                                          code(code),
                                                                                                                                          message(message)
{
    assert(caller_name != nullptr);
    assert(message != nullptr);

    CreateWhatMessage();
}

void rusty::core::Exception::CreateWhatMessage(void)
{
    what_message = caller_name;

    if(has_code)
    {
        what_message.append(" error ");
        what_message.append(std::to_string(code));
    }

    what_message.append(": ");
    what_message.append(message);
}

const char * rusty::core::Exception::GetCallerName(void) const noexcept
{
    return caller_name.c_str();
}

void rusty::core::Exception::SetCallerName(std::string &caller_name)
{
    this->caller_name = caller_name;
    CreateWhatMessage();
}

bool rusty::core::Exception::HasCode(void) const noexcept
{
    return has_code;
}

int rusty::core::Exception::GetErrorCode(void) const noexcept
{
    return code;
}
void rusty::core::Exception::SetErrorCode(int code)
{
    this->code = code;
    CreateWhatMessage();
}

const char * rusty::core::Exception::GetErrorMessage(void) const noexcept
{
    return message.c_str();
}

rusty::core::Exception::ID rusty::core::Exception::GetExceptionID(void) const noexcept
{
    return exception_id;
}

void rusty::core::Exception::SetErrorMessage(std::string &message)
{
    this->message = message;
    CreateWhatMessage();
}

const char * rusty::core::Exception::what() const noexcept
{
    return what_message.c_str();
}

rusty::core::DecoderConfigurationException::DecoderConfigurationException(const char * const caller_name, const char * const message) : Exception(caller_name, false, 0, message, Exception::ID::DECODER_CONFIGURATION_EXCEPTION) {}
rusty::core::DecoderConfigurationException::DecoderConfigurationException(const char * const caller_name, int code, const char * const message) : Exception(caller_name, true, code, message, Exception::ID::DECODER_CONFIGURATION_EXCEPTION) {}

rusty::core::EncoderConfigurationException::EncoderConfigurationException(const char * const caller_name, const char * const message) : Exception(caller_name, false, 0, message, Exception::ID::ENCODER_CONFIGURATION_EXCEPTION) {}
rusty::core::EncoderConfigurationException::EncoderConfigurationException(const char * const caller_name, int code, const char * const message) : Exception(caller_name, true, code, message, Exception::ID::ENCODER_CONFIGURATION_EXCEPTION) {}

rusty::core::InvalidArgumentException::InvalidArgumentException(const char * const caller_name, const char * const message) : Exception(caller_name, false, 0, message, Exception::ID::INVALID_ARGUMENT_EXCEPTION) {}
rusty::core::InvalidArgumentException::InvalidArgumentException(const char * const caller_name, int code, const char * const message) : Exception(caller_name, true, code, message, Exception::ID::INVALID_ARGUMENT_EXCEPTION) {}

rusty::core::MemoryAllocationException::MemoryAllocationException(const char * const caller_name) : Exception(caller_name, false, 0, message, Exception::ID::MEMORY_ALLOCATION_EXCEPTION) {}

rusty::core::OutOfRangeException::OutOfRangeException(const char * const caller_name, const char * const message) : Exception(caller_name, false, 0, message, Exception::ID::OUT_OF_RANGE_EXCEPTION) {}
rusty::core::OutOfRangeException::OutOfRangeException(const char * const caller_name, int code, const char * const message) : Exception(caller_name, true, code, message, Exception::ID::OUT_OF_RANGE_EXCEPTION) {}

rusty::core::SeekException::SeekException(const char * const caller_name, const char * const message) : Exception(caller_name, false, 0, message, Exception::ID::SEEK_EXCEPTION) {}
rusty::core::SeekException::SeekException(const char * const caller_name, int code, const char * const message) : Exception(caller_name, true, code, message, Exception::ID::SEEK_EXCEPTION) {}

rusty::core::ReadFileException::ReadFileException(const char * const caller_name, const char * const message) : Exception(caller_name, false, 0, message, Exception::ID::READ_FILE_EXCEPTION) {}
rusty::core::ReadFileException::ReadFileException(const char * const caller_name, int code, const char * const message) : Exception(caller_name, true, code, message, Exception::ID::READ_FILE_EXCEPTION) {}

rusty::core::WriteFileException::WriteFileException(const char * const caller_name, const char * const message) : Exception(caller_name, false, 0, message, Exception::ID::WRITE_FILE_EXCEPTION) {}
rusty::core::WriteFileException::WriteFileException(const char * const caller_name, int code, const char * const message) : Exception(caller_name, true, code, message, Exception::ID::WRITE_FILE_EXCEPTION) {}
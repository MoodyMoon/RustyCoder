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
#include "exceptions.h"
Exception::Exception(const char * const caller_name, bool has_code, int code, const char * const message, ID exception_id) : exception_id(exception_id)
{
    assert(caller_name != nullptr);
    assert(message != nullptr);

    this->caller_name = caller_name;
    this->has_code = has_code;
    this->code = code;
    this->message = message;

    CreateWhatMessage();
}

void Exception::CreateWhatMessage(void)
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

const char * Exception::GetCallerName(void) const noexcept
{
    return caller_name.c_str();
}

void Exception::SetCallerName(std::string &caller_name)
{
    this->caller_name = caller_name;
    CreateWhatMessage();
}

bool Exception::HasCode(void) const noexcept
{
    return has_code;
}

int Exception::GetErrorCode(void) const noexcept
{
    return code;
}
void Exception::SetErrorCode(int code)
{
    this->code = code;
    CreateWhatMessage();
}

const char * Exception::GetErrorMessage(void) const noexcept
{
    return message.c_str();
}

Exception::ID Exception::GetExceptionID(void) const noexcept
{
    return exception_id;
}

void Exception::SetErrorMessage(std::string &message)
{
    this->message = message;
    CreateWhatMessage();
}

const char * Exception::what() const noexcept
{
    return what_message.c_str();
}

DecoderConfigurationException::DecoderConfigurationException(const char * const caller_name, const char * const message) : Exception(caller_name, false, 0, message, Exception::ID::DECODER_CONFIGURATION_EXCEPTION) {}
DecoderConfigurationException::DecoderConfigurationException(const char * const caller_name, int code, const char * const message) : Exception(caller_name, true, code, message, Exception::ID::DECODER_CONFIGURATION_EXCEPTION) {}

EncoderConfigurationException::EncoderConfigurationException(const char * const caller_name, const char * const message) : Exception(caller_name, false, 0, message, Exception::ID::ENCODER_CONFIGURATION_EXCEPTION) {}
EncoderConfigurationException::EncoderConfigurationException(const char * const caller_name, int code, const char * const message) : Exception(caller_name, true, code, message, Exception::ID::ENCODER_CONFIGURATION_EXCEPTION) {}

MemoryAllocationException::MemoryAllocationException(const char * const caller_name) : Exception(caller_name, false, 0, message, Exception::ID::MEMORY_ALLOCATION_EXCEPTION) {}

SeekException::SeekException(const char * const caller_name, const char * const message) : Exception(caller_name, false, 0, message, Exception::ID::SEEK_EXCEPTION) {}
SeekException::SeekException(const char * const caller_name, int code, const char * const message) : Exception(caller_name, true, code, message, Exception::ID::SEEK_EXCEPTION) {}

ReadFileException::ReadFileException(const char * const caller_name, const char * const message) : Exception(caller_name, false, 0, message, Exception::ID::READ_FILE_EXCEPTION) {}
ReadFileException::ReadFileException(const char * const caller_name, int code, const char * const message) : Exception(caller_name, true, code, message, Exception::ID::READ_FILE_EXCEPTION) {}

WriteFileException::WriteFileException(const char * const caller_name, const char * const message) : Exception(caller_name, false, 0, message, Exception::ID::WRITE_FILE_EXCEPTION) {}
WriteFileException::WriteFileException(const char * const caller_name, int code, const char * const message) : Exception(caller_name, true, code, message, Exception::ID::WRITE_FILE_EXCEPTION) {}
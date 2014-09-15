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

Exception::Exception(const char * const caller_name, bool has_code, int code, const char * const message)
{
    assert(caller_name != nullptr);
    assert(message != nullptr);

    this->caller_name = caller_name;
    this->has_code = has_code;
    this->code = code;
    this->message = message;
    
    what_message.append(caller_name);

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

bool Exception::HasCode(void) const noexcept
{
    return has_code;
}

int Exception::GetErrorCode(void) const noexcept
{
    return code;
}

const char * Exception::GetErrorMessage(void) const noexcept
{
    return message.c_str();
}

const char * Exception::what() const noexcept
{
    return what_message.c_str();
}

DecoderConfigurationException::DecoderConfigurationException(const char * const caller_name, const char * const message) : Exception(caller_name, false, 0, message) {}
DecoderConfigurationException::DecoderConfigurationException(const char * const caller_name, int code, const char * const message) : Exception(caller_name, true, code, message) {}

EncoderConfigurationException::EncoderConfigurationException(const char * const caller_name, const char * const message) : Exception(caller_name, false, 0, message) {}
EncoderConfigurationException::EncoderConfigurationException(const char * const caller_name, int code, const char * const message) : Exception(caller_name, true, code, message) {}

GuiGenericException::GuiGenericException(const char * const caller_name, const char * const message) : Exception(caller_name, false, 0, message) {}
GuiGenericException::GuiGenericException(const char * const caller_name, int code, const char * const message) : Exception(caller_name, true, code, message) {}

MemoryAllocationException::MemoryAllocationException(const char * const caller_name) : Exception(caller_name, false, 0, message) {}

SeekException::SeekException(const char * const caller_name, const char * const message) : Exception(caller_name, false, 0, message) {}
SeekException::SeekException(const char * const caller_name, int code, const char * const message) : Exception(caller_name, true, code, message) {}

ReadFileException::ReadFileException(const char * const caller_name, const char * const message) : Exception(caller_name, false, 0, message) {}
ReadFileException::ReadFileException(const char * const caller_name, int code, const char * const message) : Exception(caller_name, true, code, message) {}

WriteFileException::WriteFileException(const char * const caller_name, const char * const message) : Exception(caller_name, false, 0, message) {}
WriteFileException::WriteFileException(const char * const caller_name, int code, const char * const message) : Exception(caller_name, true, code, message) {}

UnsupportedFormatException::UnsupportedFormatException(const char * const caller_name, const char * const message) : Exception(caller_name, false, 0, message) {}
UnsupportedFormatException::UnsupportedFormatException(const char * const caller_name, int code, const char * const message) : Exception(caller_name, true, code, message) {}

UnimplementedFeatureException::UnimplementedFeatureException(const char * const caller_name) : Exception(caller_name, false, 0, message) {}
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

#ifndef CORE_EXCEPTIONS_H
#define CORE_EXCEPTIONS_H

class Exception : public std::exception
{
    private:
        std::string caller_name;
        bool has_code;
        int code;
        std::string message;
        std::string what_message;

    public:
        Exception(const char * const caller_name, bool has_code, int code, const char * const message);
        const char * GetCallerName(void) const noexcept;
        bool HasCode(void) const noexcept;
        int GetErrorCode(void) const noexcept;
        const char * GetErrorMessage(void) const noexcept;
        virtual const char * what() const noexcept;
};

class DecoderConfigurationException : public Exception
{
    public:
        DecoderConfigurationException(const char * const caller_name, const char * const message);
        DecoderConfigurationException(const char * const caller_name, int code, const char * const message);
};

class EncoderConfigurationException : public Exception
{
    public:
        EncoderConfigurationException(const char * const caller_name, const char * const message);
        EncoderConfigurationException(const char * const caller_name, int code, const char * const message);
};

class GuiGenericException : public Exception
{
    public:
        GuiGenericException(const char * const caller_name, const char * const message);
        GuiGenericException(const char * const caller_name, int code, const char * const message);
};

class MemoryAllocationException : public Exception
{
    private:
        const char * message = "Fail to allocate memory.";

    public:
        MemoryAllocationException(const char * const caller_name);
};

class SeekException : public Exception
{
    public:
        SeekException(const char * const caller_name, const char * const message);
        SeekException(const char * const caller_name, int code, const char * const message);
};

class ReadFileException : public Exception
{
    public:
        ReadFileException(const char * const caller_name, const char * const message);
        ReadFileException(const char * const caller_name, int code, const char * const message);
};

class WriteFileException : public Exception
{
    public:
        WriteFileException(const char * const caller_name, const char * const message);
        WriteFileException(const char * const caller_name, int code, const char * const message);
};

class UnsupportedFormatException : public Exception
{
    public:
        UnsupportedFormatException(const char * const caller_name, const char * const message);
        UnsupportedFormatException(const char * const caller_name, int code, const char * const message);
};

class UnimplementedFeatureException : public Exception
{
    private:
        const char * message = "Function is not implemented yet. This normally indicates programming error so please contact the developer for assistance.";

    public:
        UnimplementedFeatureException(const char * const caller_name);
};

#endif
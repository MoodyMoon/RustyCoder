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

#ifndef CORE_COMMON_H
#define CORE_COMMON_H

namespace rusty
{
namespace core
{
/*!
\file common.h
Commonly used for serializing and deserializing objects.
\warning Do not modify the values because they will be written to settings files.
*/
enum class DataType : uint8_t
{
    STRING = 1,
    INT_S8 = 2,
    INT_U8 = 3,
    INT_S16 = 4,
    INT_U16 = 5,
    INT_S32 = 6,
    INT_U32 = 7,
    INT_S64 = 8,
    INT_U64 = 9,
    FLOAT = 10,
    DOUBLE = 11,
    BOOL = 12
};

/*!
\file common.h
For specifying the seeking position of the file.
*/
enum class SeekPosition : uint32_t
{
    START,   /*!< Start of the audio data */
    CURRENT, /*!< Current position on the audio data */
    END      /*!< End of audio data */
};
}
}

#endif
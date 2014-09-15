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

#ifndef CORE_COMMON_H
#define CORE_COMMON_H

/*!
\file common.h
For specifying the seeking position of the file.
*/
enum SeekPosition
{
    START,   /*!< Start of the audio data */
    CURRENT, /*!< Current position on the audio data */
    END      /*!< End of audio data */
};

#endif
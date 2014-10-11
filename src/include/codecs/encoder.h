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

#ifndef CODECS_ENCODER_H
#define CODECS_ENCODER_H

#include "stdafx.h"

class EncoderOptions
{
    public:
        EncoderOptions(void) = default;
        EncoderOptions(const EncoderOptions &) = delete;
        EncoderOptions & operator=(const EncoderOptions &) = delete;
        virtual ~EncoderOptions(void) {};
};

/*!
Base class for all encoders.
\note All encoders must implement this class to be of use to higher levels classes. All samples
obtained from all relevant member functions must return samples which are SCALED
to the value range of its container. This interface assumes char is 8 bits wide, short 16 bits and int 32 bits.
The word "frame" refers to the a decoded audio frame and not a encoded audio frame like a MPEG frame.
A frame may have multiple samples which is number is equal to the number of channels in the audio.
*/
template<class T>
class Encoder
{
    private:
        /*!
        Attach the buffer pointer which (may) contain valid audio frames.
        \param[in] container      Pointer to the buffer which contains audio samples.
        \param[in] container_size \c sizeof(container)
        \warning \c container pointer must not be null. 
        \warning \c container_size must > 0.
        \warning \c container_size must be multiple of the number of audio channels.
        */
        virtual void SetFrameBuffer(T * container, uint64_t container_size) = 0;

    public:
        Encoder(void) = default;
        Encoder(const Encoder &) = delete;
        Encoder & operator=(const Encoder &) = delete;

        /*!
        Get the file extension for the output format.
        \return file extension
        */
        virtual const char * const GetFileExtension(void) const noexcept = 0;

        /*!
        Write all valid frames in the container to file.
        \warning \c container_valid_frame_count must be <= container_frame_capacity.
        \note Writing 0 frame (<tt>container_valid_frame_count == 0</tt>) must not cause function to throw.
        */
        virtual void WriteFrames(uint64_t container_valid_frame_count) = 0;

        virtual ~Encoder(void) {};
};

/*!
Base class for all encoders.
\note All encoders must implement this class to be of use to higher levels classes.\n
<b>All encoders must initialize \c valid_containers with supported sample formats.
It shows all supported intermediate sample formats.</b>
*/
template<>
class Encoder<void>
{
    public:
        enum EncoderID
        {
            SNDFILEENCODER,
            LAME
        };

        std::unique_ptr<Sample::SampleContainer> valid_containers;

        Encoder(void) = default;
        Encoder(const Encoder &) = delete;
        Encoder & operator=(const Encoder &) = delete;

        /*!
        Get number of valid containers
        \return Number of valid containers
        */
        virtual size_t GetValidContainersCount(void) const noexcept = 0;

        virtual ~Encoder(void) {};
};

#endif
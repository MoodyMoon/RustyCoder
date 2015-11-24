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

#ifndef CODECS_DECODER_H
#define CODECS_DECODER_H

#include "../core/common.h"
#include "common.h"
#include "samples.h"

namespace rusty
{
namespace codecs
{
/*!
Base class for all decoders.
\note All decoders must implement this class to be of use to higher levels classes. All samples
obtained from all relevant member functions must return samples which are SCALED
to the value range of its container. This class assumes char is 8 bits wide, short 16 bits and int 32 bits.
The word "frame" refers to the a decoded audio frame and not a encoded audio frame like a MPEG frame.
A frame may have multiple samples which is number is equal to the number of channels in the audio.
*/
template<class T>
class Decoder
{
    private:
        /*!
        Attach the buffer pointer for storing samples in later decoding process.
        \param[out] container      Pointer to the buffer which contains audio samples.
        \param[in]  container_size \c sizeof(container)
        \warning \c container pointer must not be null.
        \warning \c container_size must be > 0.
        \warning \c container_size must be multiple of the number of audio channels.
        */
        virtual void SetFrameBuffer(T * container, uint64_t container_size) = 0;

    protected:
        Decoder(void) = default;

    public:
        Decoder(const Decoder &) = delete;
        Decoder & operator=(const Decoder &) = delete;

        /*!
        Get the current offset of the file in frames.
        \return The current offset of the file in frames.
        */
        virtual uint64_t GetCurrentFrameOffset(void) const = 0;

        /*!
        Seek to the decoded audio frame specified by \c offset relative to the \c position of the file.
        \param[in] position Refer to \ref SeekPosition.
        \param[in] offset   An offset relative to \c position.
        \return offset relative to the start of the audio data.
        */
        virtual uint64_t SeekToFrame(core::SeekPosition position, int64_t offset) = 0;

        /*!
        Read the file and decode enough audio frames to fill the container or until the end of audio data is reached.
        \return the number of valid frames in the container.
        \note The return value must be the same as the \c container_frame_capacity unless the end of audio data is reached.
        \note End-of-file must not cause function to throw. Return value < container_frame_capacity instead.
        */
        virtual uint64_t ReadFrames(void) = 0;

        virtual ~Decoder(void) {};
};

/*!
Base class for all decoders. Retrieves information about the audio file.
\note All decoders must implement this class to be of use to higher levels classes.\n
<b>All decoders must initialize \c valid_containers with supported sample formats.
It shows all supported intermediate sample formats.</b>
*/
template<>
class Decoder<void>
{
    public:
        enum class ID : uint32_t
        {
            MPG123,
            SNDFILE_DECODER
        };

        static constexpr const unsigned int decoder_count = 2u;

        static const std::unordered_map<ID, std::string> decoder_id_to_text;

    protected:
        Decoder(void) = default;

    public:
        Decoder(const Decoder &) = delete;
        Decoder & operator=(const Decoder &) = delete;

        /*!
        Get the number of channels in the audio.
        \return Number of channels
        */
        virtual unsigned int GetChannelCount(void) const noexcept = 0;

        /*!
        Get the sample rate of the audio. Sample rate refers to the number of samples in one second of audio.
        \return Sample rate
        */
        virtual unsigned int GetSampleRate(void) const noexcept = 0;

        /*!
        Get number of frames in the entire audio stream.
        \return Number of audio frames
        */
        virtual uint64_t GetFrameCount(void) const noexcept = 0;

        /*!
        Get the preferable type of container which will improve the efficiency of the decoding process
        due to data type conversion that might occur when the actual data type of the samples stored in
        the file cannot fit the data type of the container. The preferable data type (maybe) represents the
        actual sample data type. Most lossy compression might store samples in a form which does not match
        any data type so the decoded sample can be in any format supported by the decoder. In this case, a larger
        container type is returned which allows preservation of most of the audio quality.
        \return Samples::SampleContainers
        */
        virtual Sample::SampleContainer GetPreferableOutputContainer(void) const noexcept = 0;

        /*!
        Get an array of supported containers.
        \return An array of supported containers
        */
        virtual const Sample::SampleContainer * GetSupportedContainers(void) const noexcept = 0;

        /*!
        Get number of supported containers
        \return Number of supported containers
        */
        virtual size_t GetSupportedContainersCount(void) const noexcept = 0;

        virtual ~Decoder(void) {};
};
}
}
#endif
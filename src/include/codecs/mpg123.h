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

#ifndef CODECS_MPG123_H
#define CODECS_MPG123_H

#include "../core/common.h"
#include "../core/exception.h"
#include "../core/file_reader.h"
#include "decoder.h"
#include "samples.h"

namespace rusty
{
namespace codecs
{
class Mpg123LifetimeHandler;

/*!
Decoder for (MPEG-1, MPEG-2, MPEG-2.5) Audio Layer (I, II, III)
*/
template<class T>
class Mpg123 : public Decoder<T>
{
    private:
        std::unique_ptr<core::FileReader> file_reader;

        mpg123_handle *mh = nullptr;
        unsigned int channel_count;
        size_t decoded_bytes_count;
        int error = 0;

        T *container = nullptr;
        uint64_t container_size = 0;
        size_t container_size_ = 0;
        uint64_t container_frame_capacity = 0;
        uint64_t container_valid_frame_count = 0;

        void Mpg123_2(const boost::filesystem::path &path, T *container, uint64_t container_size, const Mpg123LifetimeHandler &life);
        void ReadFrames2(void);

        /*!
        \warning \c container_size cannot be bigger than maximum of value \c size_t
        */
        virtual void SetFrameBuffer(T *container, uint64_t container_size);

    public:
        Mpg123(const Mpg123 &) = delete;
        Mpg123 & operator=(const Mpg123 &) = delete;

        /*!
        Initialize mpg123 decoder.
        \param[in]  path           Input file path.
        \param[out] container      Pointer to the buffer which contains audio samples.
        \param[in]  container_size \c sizeof(container)
        \param[in]  life           Reference to an instance of Mpg123LifetimeHandler
        \throw DecoderConfigurationException
        \throw ReadFileException
        \warning \c container must not be null.
        \warning \c container_size must be > 0.
        \warning \c container_size must be <= max value of <tt>size_t</tt> because mpg123 cannot handle > 4GB per read for x86. Mpg123 can handle unsigned 64-bit value per read.
        \warning \c container_size must be multiple of the number of audio channels.
        */
        Mpg123(const boost::filesystem::path &path, T *container, uint64_t container_size, const Mpg123LifetimeHandler &life);

        /*!
        \throw SeekException
        \note Frame offset may not be the same as the number of decoded frames.
        */
        virtual uint64_t GetCurrentFrameOffset(void) const;

        /*!
        \throw SeekException
        */
        virtual uint64_t SeekToFrame(core::SeekPosition position, int64_t offset);

        /*!
        \throw ReadFileException
        */
        virtual uint64_t ReadFrames(void);

        virtual ~Mpg123(void);
};

template<>
class Mpg123<void> : public Decoder<void>
{
    private:
        static const Sample::SampleContainer supported_containers[7];

        std::unique_ptr<core::FileReader> file_reader;

        mpg123_handle *mh = nullptr;
        unsigned int channel_count;
        unsigned int sample_rate;
        uint64_t frame_count;
        int error;

        void FreeAndThrow(int error_code);

    public:
        Mpg123(const Mpg123 &) = delete;
        Mpg123 & operator=(const Mpg123 &) = delete;

        /*!
        Initialize mpg123 analyzer.
        \param[in] path Input file path.
        \param[in] life Reference to an instance of Mpg123LifetimeHandler
        \throw DecoderConfigurationException
        \throw ReadFileException
        */
        Mpg123(const boost::filesystem::path &path, const Mpg123LifetimeHandler &life);

        virtual unsigned int GetChannelCount(void) const noexcept;
        virtual unsigned int GetSampleRate(void) const noexcept;
        virtual uint64_t GetFrameCount(void) const noexcept;
        virtual Sample::SampleContainer GetPreferableOutputContainer(void) const noexcept;
        virtual const Sample::SampleContainer * GetSupportedContainers(void) const noexcept;
        virtual size_t GetSupportedContainersCount(void) const noexcept;

        static ssize_t r_read(void *iohandle, void *buffer, size_t byte_count);
        static off_t r_lseek(void *iohandle, off_t offset, int whence);

        ~Mpg123(void);
};

/*!
For minimizing the times needed to call \c mpg123_init() and \c mpg123_exit() as mpg123
documentation has already mentioned to only init and exit once per process. However this class
does not implement this correctly because it does not prevent another call to \c mpg123_init()
after \c mpg123_exit() was called in the previous instance.\n
The important point is this problem does not matter because \c libmpg123.c shows there is a check
to prevent mpg123_init() to be called twice in the same process and mpg123_exit() doesn't really do anything.
\warning This may not persist for future versions though.
*/
class Mpg123LifetimeHandler
{
    private:
        static std::atomic<uint32_t> init_count;

    public:
        Mpg123LifetimeHandler(const Mpg123LifetimeHandler &) = delete;
        Mpg123LifetimeHandler & operator=(const Mpg123LifetimeHandler &) = delete;

        /*!
        Initialize mpg123 library
        \throw DecoderConfigurationException
        \warning Can only have one instance at any given time
        */
        Mpg123LifetimeHandler(void);

        ~Mpg123LifetimeHandler(void);
};
}
}
#endif
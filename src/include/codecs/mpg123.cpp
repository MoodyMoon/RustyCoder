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
#include "mpg123.h"

std::atomic<uint32_t> rusty::codecs::Mpg123LifetimeHandler::init_count(0u);

rusty::codecs::Mpg123<char>::Mpg123(const boost::filesystem::path &path, char *container, uint64_t container_size, const Mpg123LifetimeHandler &life)
{
    Mpg123_2(path, container, container_size, life);
}

rusty::codecs::Mpg123<unsigned char>::Mpg123(const boost::filesystem::path &path, unsigned char *container, uint64_t container_size, const Mpg123LifetimeHandler &life)
{
    Mpg123_2(path, container, container_size, life);
}

rusty::codecs::Mpg123<short>::Mpg123(const boost::filesystem::path &path, short *container, uint64_t container_size, const Mpg123LifetimeHandler &life)
{
    Mpg123_2(path, container, container_size, life);
}

rusty::codecs::Mpg123<unsigned short>::Mpg123(const boost::filesystem::path &path, unsigned short *container, uint64_t container_size, const Mpg123LifetimeHandler &life)
{
    Mpg123_2(path, container, container_size, life);
}

rusty::codecs::Mpg123<int>::Mpg123(const boost::filesystem::path &path, int *container, uint64_t container_size, const Mpg123LifetimeHandler &life)
{
    Mpg123_2(path, container, container_size, life);
}

rusty::codecs::Mpg123<unsigned int>::Mpg123(const boost::filesystem::path &path, unsigned int *container, uint64_t container_size, const Mpg123LifetimeHandler &life)
{
    Mpg123_2(path, container, container_size, life);
}

rusty::codecs::Mpg123<float>::Mpg123(const boost::filesystem::path &path, float * container, uint64_t container_size, const Mpg123LifetimeHandler &life)
{
    Mpg123_2(path, container, container_size, life);
}

template<class T>
void rusty::codecs::Mpg123<T>::Mpg123_2(const boost::filesystem::path &path, T *container, uint64_t container_size, const Mpg123LifetimeHandler &life)
{
    mh = mpg123_new(nullptr, &error);

    if(mh == nullptr)
        throw core::DecoderConfigurationException("Mpg123", error, mpg123_strerror(mh));

    size_t type_hash = typeid(T).hash_code();

    Sample::SampleContainer container_type;

    if(type_hash == typeid(char).hash_code())
        container_type = Sample::SampleContainer::INT_S8;
    else if(type_hash == typeid(unsigned char).hash_code())
        container_type = Sample::SampleContainer::INT_U8;
    else if(type_hash == typeid(short).hash_code())
        container_type = Sample::SampleContainer::INT_S16;
    else if(type_hash == typeid(unsigned short).hash_code())
        container_type = Sample::SampleContainer::INT_U16;
    else if(type_hash == typeid(int).hash_code())
        container_type = Sample::SampleContainer::INT_S32;
    else if(type_hash == typeid(unsigned int).hash_code())
        container_type = Sample::SampleContainer::INT_U32;
    else
        container_type = Sample::SampleContainer::FLOAT_32;

    switch(container_type)
    {
        case Sample::SampleContainer::INT_S8:
        case Sample::SampleContainer::INT_U8:
            error = mpg123_param(mh, MPG123_ADD_FLAGS, MPG123_FORCE_8BIT, 0.0);
            break;
        case Sample::SampleContainer::FLOAT_32:
            error = mpg123_param(mh, MPG123_ADD_FLAGS, MPG123_FORCE_FLOAT, 0.0);
            break;
        default:
            assert(false);
    }

    switch(container_type)
    {
        case Sample::SampleContainer::INT_S8:
        case Sample::SampleContainer::INT_U8:
        case Sample::SampleContainer::FLOAT_32:
        {
            if(error != MPG123_OK)
            {
                mpg123_delete(mh);
                throw core::DecoderConfigurationException("Mpg123", error, mpg123_plain_strerror(error));
            }
            break;
        }
        default:
            assert(false);
    }

    error = mpg123_format_none(mh);

    if(error != MPG123_OK)
    {
        mpg123_delete(mh);
        throw core::DecoderConfigurationException("Mpg123", error, mpg123_plain_strerror(error));
    }

    Mpg123<void> mpg123_void(path, life);

    switch(container_type)
    {
        case Sample::SampleContainer::INT_S8:
            error = mpg123_format(mh, mpg123_void.GetSampleRate(), mpg123_void.GetChannelCount(), MPG123_ENC_SIGNED_8);
            break;
        case Sample::SampleContainer::INT_U8:
            error = mpg123_format(mh, mpg123_void.GetSampleRate(), mpg123_void.GetChannelCount(), MPG123_ENC_UNSIGNED_8);
            break;
        case Sample::SampleContainer::INT_S16:
            error = mpg123_format(mh, mpg123_void.GetSampleRate(), mpg123_void.GetChannelCount(), MPG123_ENC_SIGNED_16);
            break;
        case Sample::SampleContainer::INT_U16:
            error = mpg123_format(mh, mpg123_void.GetSampleRate(), mpg123_void.GetChannelCount(), MPG123_ENC_UNSIGNED_16);
            break;
        case Sample::SampleContainer::INT_S32:
            error = mpg123_format(mh, mpg123_void.GetSampleRate(), mpg123_void.GetChannelCount(), MPG123_ENC_SIGNED_32);
            break;
        case Sample::SampleContainer::INT_U32:
            error = mpg123_format(mh, mpg123_void.GetSampleRate(), mpg123_void.GetChannelCount(), MPG123_ENC_UNSIGNED_32);
            break;
        case Sample::SampleContainer::FLOAT_32:
            error = mpg123_format(mh, mpg123_void.GetSampleRate(), mpg123_void.GetChannelCount(), MPG123_ENC_FLOAT_32);
            break;
        default:
            assert(false);
    }

    if(error != MPG123_OK)
    {
        mpg123_delete(mh);
        throw core::DecoderConfigurationException("Mpg123", error, mpg123_plain_strerror(error));
    }

    error = mpg123_replace_reader_handle(mh, Mpg123<void>::r_read, Mpg123<void>::r_lseek, nullptr);

    if(error != MPG123_OK)
    {
        mpg123_delete(mh);
        throw core::DecoderConfigurationException("Mpg123", error, mpg123_plain_strerror(error));
    }

    file_reader.reset(new core::FileReader(path, core::FileReader::Access::SHARE_READ, core::FileReader::Attribute::SEQUENTIAL));

    error = mpg123_open_handle(mh, file_reader.get());

    if(error != MPG123_OK)
    {
        mpg123_delete(mh);
        throw core::ReadFileException("Mpg123", error, mpg123_plain_strerror(error));
    }

    int encoding;
    long sample_rate;
    int channel_count_fit;
    error = mpg123_getformat(mh, &sample_rate, &channel_count_fit, &encoding);
    channel_count = static_cast<unsigned int>(channel_count_fit);

    if(error != MPG123_OK)
    {
        ASSERT_METHOD(mpg123_close(mh), == , MPG123_OK);
        mpg123_delete(mh);
        throw core::DecoderConfigurationException("Mpg123", error, mpg123_plain_strerror(error));
    }

    SetFrameBuffer(container, container_size);
}

template<class T>
uint64_t rusty::codecs::Mpg123<T>::GetCurrentFrameOffset() const
{
    off_t position = mpg123_tell(mh);
    if(position == MPG123_ERR)
        throw core::SeekException("Mpg123", position, mpg123_plain_strerror(position));
    return position / channel_count;
}

template<class T>
void rusty::codecs::Mpg123<T>::SetFrameBuffer(T * container, uint64_t container_size)
{
    assert(container != nullptr);
    assert(container_size > 0 && container_size <= std::numeric_limits<size_t>::max());
    assert((container_size % (channel_count * sizeof(T))) == 0);

    this->container = container;
    this->container_size = container_size;
    this->container_size_ = static_cast<size_t>(container_size);
    container_frame_capacity = container_size / (channel_count * sizeof(T));
}

template<class T>
uint64_t rusty::codecs::Mpg123<T>::SeekToFrame(core::SeekPosition position, int64_t offset)
{
    int whence = SEEK_SET;

    switch(position)
    {
        case core::SeekPosition::START:
            whence = SEEK_SET;
            break;
        case core::SeekPosition::CURRENT:
            whence = SEEK_CUR;
            break;
        case core::SeekPosition::END:
            whence = SEEK_END;
            break;
        default:
            assert(false);
    }

    offset *= 2;

    if(offset < std::numeric_limits<off_t>::min() || offset > std::numeric_limits<off_t>::max())
        throw core::SeekException("Mpg123", "Offset is out of range");

    offset = mpg123_seek(mh, static_cast<off_t>(offset), whence);

    if(offset < 0)
        throw core::SeekException("Mpg123", static_cast<int>(offset), mpg123_plain_strerror(static_cast<int>(offset)));

    return offset;
}

uint64_t rusty::codecs::Mpg123<char>::ReadFrames()
{
    ReadFrames2();
    return container_valid_frame_count;
}

uint64_t rusty::codecs::Mpg123<unsigned char>::ReadFrames()
{
    ReadFrames2();
    return container_valid_frame_count;
}

uint64_t rusty::codecs::Mpg123<short>::ReadFrames()
{
    ReadFrames2();
    return container_valid_frame_count;
}

uint64_t rusty::codecs::Mpg123<unsigned short>::ReadFrames()
{
    ReadFrames2();
    return container_valid_frame_count;
}

uint64_t rusty::codecs::Mpg123<int>::ReadFrames()
{
    ReadFrames2();
    return container_valid_frame_count;
}

uint64_t rusty::codecs::Mpg123<unsigned int>::ReadFrames()
{
    ReadFrames2();
    return container_valid_frame_count;
}

uint64_t rusty::codecs::Mpg123<float>::ReadFrames()
{
    ReadFrames2();
    return container_valid_frame_count;
}

template<class T>
void rusty::codecs::Mpg123<T>::ReadFrames2()
{
    error = mpg123_read(mh, reinterpret_cast<unsigned char *>(container), container_size_, &decoded_bytes_count);

    if(error != MPG123_OK && error != MPG123_DONE)
        throw core::ReadFileException("Mpg123", error, mpg123_plain_strerror(error));

    /*!
    if there are no decoded samples and <tt>error == MPG123_DONE</tt> in rare cases where
    <tt>(total number of samples of the entire audio stream % (container_frame_capacity * channel_count)) == 0</tt>
    */
    if(decoded_bytes_count > 0)
        container_valid_frame_count = decoded_bytes_count / sizeof(T) / channel_count;
    else
        container_valid_frame_count = 0;
}

template<class T>
rusty::codecs::Mpg123<T>::~Mpg123()
{
    ASSERT_METHOD(mpg123_close(mh), == , MPG123_OK);
    mpg123_delete(mh);
}

const rusty::codecs::Sample::SampleContainer rusty::codecs::Mpg123<void>::supported_containers[7] = {Sample::SampleContainer::INT_S8,
                                                                                                     Sample::SampleContainer::INT_U8,
                                                                                                     Sample::SampleContainer::INT_S16,
                                                                                                     Sample::SampleContainer::INT_U16,
                                                                                                     Sample::SampleContainer::INT_S32,
                                                                                                     Sample::SampleContainer::INT_U32,
                                                                                                     Sample::SampleContainer::FLOAT_32};

rusty::codecs::Mpg123<void>::Mpg123(const boost::filesystem::path &path, const Mpg123LifetimeHandler &/*life*/)
{
    mh = mpg123_new(nullptr, &error);

    if(mh == nullptr)
        throw core::DecoderConfigurationException("Mpg123", error, mpg123_strerror(mh));

    error = mpg123_replace_reader_handle(mh, r_read, r_lseek, nullptr);

    if(error != MPG123_OK)
    {
        mpg123_delete(mh);
        throw core::DecoderConfigurationException("Mpg123", error, mpg123_plain_strerror(error));
    }

    file_reader.reset(new core::FileReader(path, core::FileReader::Access::SHARE_READ, core::FileReader::Attribute::SEQUENTIAL));

    error = mpg123_open_handle(mh, file_reader.get());

    if(error != MPG123_OK)
    {
        mpg123_delete(mh);
        throw core::ReadFileException("Mpg123", error, mpg123_plain_strerror(error));
    }

    int encoding;
    long sample_rate_fit;
    int channel_count_fit;
    error = mpg123_getformat(mh, &sample_rate_fit, &channel_count_fit, &encoding);
    sample_rate = static_cast<unsigned int>(sample_rate_fit);
    channel_count = static_cast<unsigned int>(channel_count_fit);

    if(error != MPG123_OK)
        FreeAndThrow(error);

    /*! This is important for calculating the exact amount of samples in the track */
    error = mpg123_scan(mh);

    if(error != MPG123_OK)
        FreeAndThrow(error);

    long val1, val2;
    double fval;

    error = mpg123_getstate(mh, MPG123_ACCURATE, &val1, &fval);

    if(error != MPG123_OK)
        FreeAndThrow(error);

    error = mpg123_getstate(mh, MPG123_FRANKENSTEIN, &val2, &fval);

    if(error != MPG123_OK)
        FreeAndThrow(error);

    if(val1 != 1l || val2 != 0l)
        FreeAndThrow(error);

    frame_count = mpg123_length(mh) / channel_count;
}

void rusty::codecs::Mpg123<void>::FreeAndThrow(int error_code)
{
    ASSERT_METHOD(mpg123_close(mh), == , MPG123_OK);
    mpg123_delete(mh);
    throw core::DecoderConfigurationException("Mpg123", error_code, mpg123_plain_strerror(error_code));
}

unsigned int rusty::codecs::Mpg123<void>::GetChannelCount() const noexcept
{
    return channel_count;
}

unsigned int rusty::codecs::Mpg123<void>::GetSampleRate() const noexcept
{
    return sample_rate;
}

uint64_t rusty::codecs::Mpg123<void>::GetFrameCount() const noexcept
{
    return frame_count;
}

rusty::codecs::Sample::SampleContainer rusty::codecs::Mpg123<void>::GetPreferableOutputContainer() const noexcept
{
    return supported_containers[6];
}

const rusty::codecs::Sample::SampleContainer * rusty::codecs::Mpg123<void>::GetSupportedContainers() const noexcept
{
    return supported_containers;
}

size_t rusty::codecs::Mpg123<void>::GetSupportedContainersCount() const noexcept
{
    static constexpr const size_t supported_containers_count = sizeof(supported_containers) / sizeof(supported_containers[0]);
    return supported_containers_count;
}

ssize_t rusty::codecs::Mpg123<void>::r_read(void * iohandle, void * buffer, size_t byte_count)
{
    core::FileReader *file_reader = static_cast<core::FileReader *>(iohandle);

    bool error;
    uint64_t bytes_read;

    bytes_read = file_reader->Read(reinterpret_cast<unsigned char *>(buffer), byte_count, error);

    if(error)
        return -1;
    else
        return bytes_read;
}

off_t rusty::codecs::Mpg123<void>::r_lseek(void * iohandle, off_t offset, int whence)
{
    core::FileReader *file_reader = static_cast<core::FileReader *>(iohandle);

    bool error;
    uint64_t position;

    switch(whence)
    {
        case SEEK_SET:
            position = file_reader->Seek(core::SeekPosition::START, offset, error);
            break;
        case SEEK_CUR:
            position = file_reader->Seek(core::SeekPosition::CURRENT, offset, error);
            break;
        case SEEK_END:
            position = file_reader->Seek(core::SeekPosition::END, offset, error);
            break;
        default:
            assert(false);
    }

    if(error)
        return -1;
    else
        return position;
}

rusty::codecs::Mpg123<void>::~Mpg123(void)
{
    ASSERT_METHOD(mpg123_close(mh), == , MPG123_OK);
    mpg123_delete(mh);
}

rusty::codecs::Mpg123LifetimeHandler::Mpg123LifetimeHandler()
{
    if(init_count.load() == 0u)
    {
        int error = mpg123_init();
        if(error != MPG123_OK)
            throw core::DecoderConfigurationException("Mpg123LifetimeHandler", error, mpg123_plain_strerror(error));
    }

    ++init_count;
}

rusty::codecs::Mpg123LifetimeHandler::~Mpg123LifetimeHandler()
{
    --init_count;

    if(init_count.load() == 0u)
    {
        mpg123_exit();
    }
}
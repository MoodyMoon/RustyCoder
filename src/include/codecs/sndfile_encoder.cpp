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
#include "sndfile_encoder.h"

rusty::codecs::SndFileEncoder<short>::SndFileEncoder(const boost::filesystem::path path, int sample_rate, int channel_count, SndFileEncoderProfile::OutputFormat format, short *container, uint64_t container_size)
{
    SndFileEncoder2(path, sample_rate, channel_count, format, container, container_size);
}

rusty::codecs::SndFileEncoder<int>::SndFileEncoder(const boost::filesystem::path path, int sample_rate, int channel_count, SndFileEncoderProfile::OutputFormat format, int *container, uint64_t container_size)
{
    SndFileEncoder2(path, sample_rate, channel_count, format, container, container_size);
}

rusty::codecs::SndFileEncoder<float>::SndFileEncoder(const boost::filesystem::path path, int sample_rate, int channel_count, SndFileEncoderProfile::OutputFormat format, float *container, uint64_t container_size)
{
    SndFileEncoder2(path, sample_rate, channel_count, format, container, container_size);
}

rusty::codecs::SndFileEncoder<double>::SndFileEncoder(const boost::filesystem::path path, int sample_rate, int channel_count, SndFileEncoderProfile::OutputFormat format, double *container, uint64_t container_size)
{
    SndFileEncoder2(path, sample_rate, channel_count, format, container, container_size);
}

template<class T>
void rusty::codecs::SndFileEncoder<T>::SndFileEncoder2(const boost::filesystem::path path, int sample_rate, int channel_count, SndFileEncoderProfile::OutputFormat format, T *container, uint64_t container_size)
{
    sfinfo.samplerate = sample_rate;
    sfinfo.channels = channel_count;
    sfinfo.format = static_cast<int>(format);

    if(!sf_format_check(&sfinfo))
        throw core::WriteFileException("SndFileEncoder", sf_error(sndfile), sf_strerror(sndfile));

    file_writer.reset(new core::FileWriter(path, core::FileWriter::Access::EXCLUSIVE_WRITE, core::FileWriter::Create::OVERWRITE));

    SF_VIRTUAL_IO sf_virtual_io;
    sf_virtual_io.get_filelen = SndFile::sf_vio_get_filelen;
    sf_virtual_io.seek = SndFile::sf_vio_seek;
    sf_virtual_io.write = SndFile::sf_vio_write;
    sf_virtual_io.tell = SndFile::sf_vio_tell;

    sndfile = sf_open_virtual(&sf_virtual_io, SFM_WRITE, &sfinfo, file_writer.get());

    if(sndfile == nullptr)
        throw core::WriteFileException("SndFileEncoder", sf_error(sndfile), sf_strerror(sndfile));

    sf_command(sndfile, SFC_SET_SCALE_INT_FLOAT_WRITE, nullptr, SF_TRUE);

    SetFrameBuffer(container, container_size);
}

template<class T>
void rusty::codecs::SndFileEncoder<T>::SetFrameBuffer(T *container, uint64_t container_size)
{
    assert(container != nullptr);
    assert(container_size > 0);
    assert((container_size % (sfinfo.channels * sizeof(T))) == 0);

    this->container = container;
    this->container_size = container_size;
    container_frame_capacity = container_size / (sfinfo.channels * sizeof(T));
}

void rusty::codecs::SndFileEncoder<short>::WriteFrames(uint64_t container_valid_frame_count)
{
    assert(container_valid_frame_count <= container_frame_capacity);

    valid_output_frame_count = sf_writef_short(sndfile, container, container_valid_frame_count);

    if(valid_output_frame_count != container_valid_frame_count)
        throw core::WriteFileException("SndFileEncoder", sf_error(sndfile), sf_strerror(sndfile));
}

void rusty::codecs::SndFileEncoder<int>::WriteFrames(uint64_t container_valid_frame_count)
{
    assert(container_valid_frame_count <= container_frame_capacity);

    valid_output_frame_count = sf_writef_int(sndfile, container, container_valid_frame_count);

    if(valid_output_frame_count != container_valid_frame_count)
        throw core::WriteFileException("SndFileEncoder", sf_error(sndfile), sf_strerror(sndfile));
}

void rusty::codecs::SndFileEncoder<float>::WriteFrames(uint64_t container_valid_frame_count)
{
    assert(container_valid_frame_count <= container_frame_capacity);

    valid_output_frame_count = sf_writef_float(sndfile, container, container_valid_frame_count);

    if(valid_output_frame_count != container_valid_frame_count)
        throw core::WriteFileException("SndFileEncoder", sf_error(sndfile), sf_strerror(sndfile));
}

void rusty::codecs::SndFileEncoder<double>::WriteFrames(uint64_t container_valid_frame_count)
{
    assert(container_valid_frame_count <= container_frame_capacity);

    valid_output_frame_count = sf_writef_double(sndfile, container, container_valid_frame_count);

    if(valid_output_frame_count != container_valid_frame_count)
        throw core::WriteFileException("SndFileEncoder", sf_error(sndfile), sf_strerror(sndfile));
}

template<class T>
rusty::codecs::SndFileEncoder<T>::~SndFileEncoder()
{
    ASSERT_METHOD(sf_close(sndfile), ==, 0);
}

const rusty::codecs::Sample::SampleContainer rusty::codecs::SndFileEncoder<void>::supported_containers[4] = {Sample::SampleContainer::INT_S16,
                                                                                                             Sample::SampleContainer::INT_S32,
                                                                                                             Sample::SampleContainer::FLOAT_32,
                                                                                                             Sample::SampleContainer::FLOAT_64};

const rusty::codecs::Sample::SampleContainer * rusty::codecs::SndFileEncoder<void>::GetSupportedContainers() const noexcept
{
    return supported_containers;
}

size_t rusty::codecs::SndFileEncoder<void>::GetSupportedContainersCount() const noexcept
{
    static constexpr const size_t supported_containers_count = sizeof(supported_containers) / sizeof(supported_containers[0]);
    return supported_containers_count;
}
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
#include "rst_sndfile_encoder.h"

template<class T>
SndFileEncoder<T>::SndFileEncoder(const char * const file, int sample_rate, int channel_count, SndFileEncoderOptions::OutputFormat format, T *container, uint64_t container_size)
{
    throw UnimplementedFeatureException("SndFileEncoder");
}

template<>
SndFileEncoder<short>::SndFileEncoder(const char * const file, int sample_rate, int channel_count, SndFileEncoderOptions::OutputFormat format, short *container, uint64_t container_size)
{
    SndFileEncoder2(file, sample_rate, channel_count, format, container, container_size);
}

template<>
SndFileEncoder<int>::SndFileEncoder(const char * const file, int sample_rate, int channel_count, SndFileEncoderOptions::OutputFormat format, int *container, uint64_t container_size)
{
    SndFileEncoder2(file, sample_rate, channel_count, format, container, container_size);
}

template<>
SndFileEncoder<float>::SndFileEncoder(const char * const file, int sample_rate, int channel_count, SndFileEncoderOptions::OutputFormat format, float *container, uint64_t container_size)
{
    SndFileEncoder2(file, sample_rate, channel_count, format, container, container_size);
}

template<>
SndFileEncoder<double>::SndFileEncoder(const char * const file, int sample_rate, int channel_count, SndFileEncoderOptions::OutputFormat format, double *container, uint64_t container_size)
{
    SndFileEncoder2(file, sample_rate, channel_count, format, container, container_size);
}

template<class T>
void SndFileEncoder<T>::SndFileEncoder2(const char * const file, int sample_rate, int channel_count, SndFileEncoderOptions::OutputFormat format, T *container, uint64_t container_size)
{
    sfinfo.samplerate = sample_rate;
    sfinfo.channels = channel_count;
    sfinfo.format = format;

    if(!sf_format_check(&sfinfo))
        throw UnsupportedFormatException("SndFileEncoder", sf_error(sndfile), sf_strerror(sndfile));

    sndfile = sf_open(file, SFM_WRITE, &sfinfo);

    if(sndfile == nullptr)
        throw WriteFileException("SndFileEncoder", sf_error(sndfile), sf_strerror(sndfile));

    sf_command(sndfile, SFC_SET_SCALE_INT_FLOAT_WRITE, nullptr, SF_TRUE);

    SetFrameBuffer(container, container_size);
}

template<class T>
void SndFileEncoder<T>::SetFrameBuffer(T *container, uint64_t container_size)
{
    assert(container != nullptr);
    assert(container_size > 0);
    assert((container_size % (sfinfo.channels * sizeof(T))) == 0);

    this->container = container;
    this->container_size = container_size;
    container_frame_capacity = container_size / (sfinfo.channels * sizeof(T));
}

template<class T>
const char * const SndFileEncoder<T>::GetFileExtension(void) const noexcept
{
    SF_FORMAT_INFO format_info;
    format_info.format = sfinfo.format;

    sf_command(sndfile, SFC_GET_FORMAT_INFO, &format_info, sizeof(format_info));

    return format_info.extension;
}

template<>
void SndFileEncoder<short>::WriteFrames(uint64_t container_valid_frame_count)
{
    assert(container_valid_frame_count <= container_frame_capacity);

    valid_output_frame_count = sf_writef_short(sndfile, container, container_valid_frame_count);

    if(valid_output_frame_count != container_valid_frame_count)
        throw WriteFileException("SndFileEncoder", sf_error(sndfile), sf_strerror(sndfile));
}

template<>
void SndFileEncoder<int>::WriteFrames(uint64_t container_valid_frame_count)
{
    assert(container_valid_frame_count <= container_frame_capacity);

    valid_output_frame_count = sf_writef_int(sndfile, container, container_valid_frame_count);

    if(valid_output_frame_count != container_valid_frame_count)
        throw WriteFileException("SndFileEncoder", sf_error(sndfile), sf_strerror(sndfile));
}

template<>
void SndFileEncoder<float>::WriteFrames(uint64_t container_valid_frame_count)
{
    assert(container_valid_frame_count <= container_frame_capacity);

    valid_output_frame_count = sf_writef_float(sndfile, container, container_valid_frame_count);

    if(valid_output_frame_count != container_valid_frame_count)
        throw WriteFileException("SndFileEncoder", sf_error(sndfile), sf_strerror(sndfile));
}

template<>
void SndFileEncoder<double>::WriteFrames(uint64_t container_valid_frame_count)
{
    assert(container_valid_frame_count <= container_frame_capacity);

    valid_output_frame_count = sf_writef_double(sndfile, container, container_valid_frame_count);

    if(valid_output_frame_count != container_valid_frame_count)
        throw WriteFileException("SndFileEncoder", sf_error(sndfile), sf_strerror(sndfile));
}

template<class T>
SndFileEncoder<T>::~SndFileEncoder()
{
    METHOD_ASSERT(sf_close(sndfile), ==, 0);
}

SndFileEncoder<void>::SndFileEncoder()
{
    Encoder<void>::valid_containers.reset(new Sample::SampleContainer[valid_containers_count]);
    Sample::SampleContainer * const _valid_containers = Encoder<void>::valid_containers.get();
    _valid_containers[0] = Sample::SampleContainer::INT_S16;
    _valid_containers[1] = Sample::SampleContainer::INT_S32;
    _valid_containers[2] = Sample::SampleContainer::FLOAT_32;
    _valid_containers[3] = Sample::SampleContainer::FLOAT_64;
}

size_t SndFileEncoder<void>::GetValidContainersCount() const noexcept
{
    return valid_containers_count;
}
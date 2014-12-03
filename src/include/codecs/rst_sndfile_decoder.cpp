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
#include "rst_sndfile_decoder.h"

SndFileDecoder<short>::SndFileDecoder(const char * const file, short *container, uint64_t container_size)
{
    SndFileDecoder2(file, container, container_size);
}

SndFileDecoder<int>::SndFileDecoder(const char * const file, int *container, uint64_t container_size)
{
    SndFileDecoder2(file, container, container_size);
}

SndFileDecoder<float>::SndFileDecoder(const char * const file, float *container, uint64_t container_size)
{
    SndFileDecoder2(file, container, container_size);
}

SndFileDecoder<double>::SndFileDecoder(const char * const file, double *container, uint64_t container_size)
{
    SndFileDecoder2(file, container, container_size);
}

template<class T>
void SndFileDecoder<T>::SndFileDecoder2(const char * const file, T *container, uint64_t container_size)
{
    sfinfo.format = 0;

    sndfile = sf_open(file, SFM_READ, &sfinfo);

    if(sndfile == nullptr)
        throw ReadFileException("SndFileDecoder", sf_error(sndfile), sf_strerror(sndfile));

    sf_command(sndfile, SFC_SET_SCALE_FLOAT_INT_READ, nullptr, SF_TRUE);

    SetFrameBuffer(container, container_size);
}

template<class T>
void SndFileDecoder<T>::SetFrameBuffer(T *container, uint64_t container_size)
{
    assert(container != nullptr);
    assert(container_size > 0);
    assert((container_size % (sfinfo.channels * sizeof(T))) == 0);

    this->container = container;
    this->container_size = container_size;
    container_frame_capacity = container_size / (sfinfo.channels * sizeof(T));
}

template<class T>
uint64_t SndFileDecoder<T>::GetCurrentFrameOffset() const
{
    sf_count_t position = sf_seek(sndfile, 0, SEEK_CUR);
    if(position == -1)
        throw SeekException("SndFileDecoder", sf_error(sndfile), sf_strerror(sndfile));
    return position;
}

template<class T>
uint64_t SndFileDecoder<T>::SeekToFrame(SeekPosition position, int64_t offset)
{
    int whence;

    switch(position)
    {
        case START:
            whence = SEEK_SET;
            break;
        case CURRENT:
            whence = SEEK_CUR;
            break;
        default:
            whence = SEEK_END;
    }

    offset = sf_seek(sndfile, offset, whence);
    if(offset == -1)
        throw SeekException("SndFileDecoder", sf_error(sndfile), sf_strerror(sndfile));
    return offset;
}

uint64_t SndFileDecoder<short>::ReadFrames()
{
    container_valid_frame_count = sf_readf_short(sndfile, container, container_frame_capacity);

    ReadFrames2();

    return container_valid_frame_count;
}

uint64_t SndFileDecoder<int>::ReadFrames()
{
    container_valid_frame_count = sf_readf_int(sndfile, container, container_frame_capacity);

    ReadFrames2();

    return container_valid_frame_count;
}

uint64_t SndFileDecoder<float>::ReadFrames()
{
    container_valid_frame_count = sf_readf_float(sndfile, container, container_frame_capacity);

    ReadFrames2();

    return container_valid_frame_count;
}

uint64_t SndFileDecoder<double>::ReadFrames()
{
    container_valid_frame_count = sf_readf_double(sndfile, container, container_frame_capacity);

    ReadFrames2();

    return container_valid_frame_count;
}

template<class T>
inline void SndFileDecoder<T>::ReadFrames2()
{
    int error = sf_error(sndfile);
    if(error != SF_ERR_NO_ERROR)
        throw ReadFileException("SndFileDecoder", error, sf_strerror(sndfile));
}

template<class T>
SndFileDecoder<T>::~SndFileDecoder()
{
    METHOD_ASSERT(sf_close(sndfile), == , SF_ERR_NO_ERROR);
}

SndFileDecoder<void>::SndFileDecoder(const char * const file)
{
    Decoder<void>::valid_containers.reset(new Sample::SampleContainer[valid_containers_count]);
    Sample::SampleContainer * const _valid_containers = Decoder<void>::valid_containers.get();
    _valid_containers[0] = Sample::SampleContainer::INT_S16;
    _valid_containers[1] = Sample::SampleContainer::INT_S32;
    _valid_containers[2] = Sample::SampleContainer::FLOAT_32;
    _valid_containers[3] = Sample::SampleContainer::FLOAT_64;

    sfinfo.format = 0;

    sndfile = sf_open(file, SFM_READ, &sfinfo);

    if(sndfile == nullptr)
    {
        ReadFileException ex("SndFileDecoder", sf_error(sndfile), sf_strerror(sndfile));
        throw ex;
    }
}

unsigned int SndFileDecoder<void>::GetChannelCount() const noexcept
{
    return sfinfo.channels;
}

unsigned int SndFileDecoder<void>::GetSampleRate() const noexcept
{
    return sfinfo.samplerate;
}

uint64_t SndFileDecoder<void>::GetFrameCount() const noexcept
{
    return sfinfo.frames;
}

Sample::SampleContainer SndFileDecoder<void>::GetPreferableOutputContainer() const noexcept
{
    int subtype = SF_FORMAT_ENDMASK | SF_FORMAT_TYPEMASK | sfinfo.format;

    Sample::SampleContainer * const _valid_containers = Decoder<void>::valid_containers.get();

    switch(subtype)
    {
        case SF_FORMAT_ENDMASK | SF_FORMAT_TYPEMASK | SF_FORMAT_PCM_S8:
        case SF_FORMAT_ENDMASK | SF_FORMAT_TYPEMASK | SF_FORMAT_PCM_16:
            return _valid_containers[0];
        case SF_FORMAT_ENDMASK | SF_FORMAT_TYPEMASK | SF_FORMAT_PCM_24:
        case SF_FORMAT_ENDMASK | SF_FORMAT_TYPEMASK | SF_FORMAT_PCM_32:
            return _valid_containers[1];
        case SF_FORMAT_ENDMASK | SF_FORMAT_TYPEMASK | SF_FORMAT_PCM_U8:
            return _valid_containers[0];
        case SF_FORMAT_ENDMASK | SF_FORMAT_TYPEMASK | SF_FORMAT_FLOAT:
            return _valid_containers[2];
        case SF_FORMAT_ENDMASK | SF_FORMAT_TYPEMASK | SF_FORMAT_DOUBLE:
            return _valid_containers[3];
        case SF_FORMAT_ENDMASK | SF_FORMAT_TYPEMASK | SF_FORMAT_ULAW:
        case SF_FORMAT_ENDMASK | SF_FORMAT_TYPEMASK | SF_FORMAT_ALAW:
        case SF_FORMAT_ENDMASK | SF_FORMAT_TYPEMASK | SF_FORMAT_IMA_ADPCM:
        case SF_FORMAT_ENDMASK | SF_FORMAT_TYPEMASK | SF_FORMAT_MS_ADPCM:
        case SF_FORMAT_ENDMASK | SF_FORMAT_TYPEMASK | SF_FORMAT_GSM610:
        case SF_FORMAT_ENDMASK | SF_FORMAT_TYPEMASK | SF_FORMAT_VOX_ADPCM:
        case SF_FORMAT_ENDMASK | SF_FORMAT_TYPEMASK | SF_FORMAT_G721_32:
        case SF_FORMAT_ENDMASK | SF_FORMAT_TYPEMASK | SF_FORMAT_G723_24:
        case SF_FORMAT_ENDMASK | SF_FORMAT_TYPEMASK | SF_FORMAT_G723_40:
            return _valid_containers[0];
        case SF_FORMAT_ENDMASK | SF_FORMAT_TYPEMASK | SF_FORMAT_DWVW_12:
        case SF_FORMAT_ENDMASK | SF_FORMAT_TYPEMASK | SF_FORMAT_DWVW_16:
        case SF_FORMAT_ENDMASK | SF_FORMAT_TYPEMASK | SF_FORMAT_DWVW_24:
        case SF_FORMAT_ENDMASK | SF_FORMAT_TYPEMASK | SF_FORMAT_DWVW_N:
            return _valid_containers[1];
        case SF_FORMAT_ENDMASK | SF_FORMAT_TYPEMASK | SF_FORMAT_DPCM_8:
        case SF_FORMAT_ENDMASK | SF_FORMAT_TYPEMASK | SF_FORMAT_DPCM_16:
            return _valid_containers[0];
        default:
            return _valid_containers[2];
    }
}

size_t SndFileDecoder<void>::GetValidContainersCount() const noexcept
{
    return valid_containers_count;
}

SndFileDecoder<void>::~SndFileDecoder(void)
{
    METHOD_ASSERT(sf_close(sndfile), == , SF_ERR_NO_ERROR);
}
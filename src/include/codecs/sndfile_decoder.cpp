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
#include "sndfile_decoder.h"

rusty::codecs::SndFileDecoder<short>::SndFileDecoder(const boost::filesystem::path path, short *container, uint64_t container_size)
{
    SndFileDecoder2(path, container, container_size);
}

rusty::codecs::SndFileDecoder<int>::SndFileDecoder(const boost::filesystem::path path, int *container, uint64_t container_size)
{
    SndFileDecoder2(path, container, container_size);
}

rusty::codecs::SndFileDecoder<float>::SndFileDecoder(const boost::filesystem::path path, float *container, uint64_t container_size)
{
    SndFileDecoder2(path, container, container_size);
}

rusty::codecs::SndFileDecoder<double>::SndFileDecoder(const boost::filesystem::path path, double *container, uint64_t container_size)
{
    SndFileDecoder2(path, container, container_size);
}

template<class T>
void rusty::codecs::SndFileDecoder<T>::SndFileDecoder2(const boost::filesystem::path path, T *container, uint64_t container_size)
{
    sfinfo.format = 0;

    file_reader.reset(new core::FileReader(path, core::FileReader::Access::SHARE_READ, core::FileReader::Attribute::SEQUENTIAL));

    SF_VIRTUAL_IO sf_virtual_io;
    sf_virtual_io.get_filelen = SndFile::sf_vio_get_filelen;
    sf_virtual_io.read = SndFile::sf_vio_read;
    sf_virtual_io.seek = SndFile::sf_vio_seek;
    sf_virtual_io.tell = SndFile::sf_vio_tell;

    sndfile = sf_open_virtual(&sf_virtual_io, SFM_READ, &sfinfo, file_reader.get());

    if(sndfile == nullptr)
        throw core::ReadFileException("SndFileDecoder", sf_error(sndfile), sf_strerror(sndfile));

    sf_command(sndfile, SFC_SET_SCALE_FLOAT_INT_READ, nullptr, SF_TRUE);

    SetFrameBuffer(container, container_size);
}

template<class T>
void rusty::codecs::SndFileDecoder<T>::SetFrameBuffer(T *container, uint64_t container_size)
{
    assert(container != nullptr);
    assert(container_size > 0);
    assert((container_size % (sfinfo.channels * sizeof(T))) == 0);

    this->container = container;
    this->container_size = container_size;
    container_frame_capacity = container_size / (sfinfo.channels * sizeof(T));
}

template<class T>
uint64_t rusty::codecs::SndFileDecoder<T>::GetCurrentFrameOffset() const
{
    sf_count_t position = sf_seek(sndfile, 0, SEEK_CUR);
    if(position == -1)
        throw core::SeekException("SndFileDecoder", sf_error(sndfile), sf_strerror(sndfile));
    return position;
}

template<class T>
uint64_t rusty::codecs::SndFileDecoder<T>::SeekToFrame(core::SeekPosition position, int64_t offset)
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

    offset = sf_seek(sndfile, offset, whence);
    if(offset == -1)
        throw core::SeekException("SndFileDecoder", sf_error(sndfile), sf_strerror(sndfile));
    return offset;
}

uint64_t rusty::codecs::SndFileDecoder<short>::ReadFrames()
{
    container_valid_frame_count = sf_readf_short(sndfile, container, container_frame_capacity);

    ReadFrames2();

    return container_valid_frame_count;
}

uint64_t rusty::codecs::SndFileDecoder<int>::ReadFrames()
{
    container_valid_frame_count = sf_readf_int(sndfile, container, container_frame_capacity);

    ReadFrames2();

    return container_valid_frame_count;
}

uint64_t rusty::codecs::SndFileDecoder<float>::ReadFrames()
{
    container_valid_frame_count = sf_readf_float(sndfile, container, container_frame_capacity);

    ReadFrames2();

    return container_valid_frame_count;
}

uint64_t rusty::codecs::SndFileDecoder<double>::ReadFrames()
{
    container_valid_frame_count = sf_readf_double(sndfile, container, container_frame_capacity);

    ReadFrames2();

    return container_valid_frame_count;
}

template<class T>
void rusty::codecs::SndFileDecoder<T>::ReadFrames2()
{
    int error = sf_error(sndfile);
    if(error != SF_ERR_NO_ERROR)
        throw core::ReadFileException("SndFileDecoder", error, sf_strerror(sndfile));
}

template<class T>
rusty::codecs::SndFileDecoder<T>::~SndFileDecoder()
{
    ASSERT_METHOD(sf_close(sndfile), == , SF_ERR_NO_ERROR);
}

const rusty::codecs::Sample::SampleContainer rusty::codecs::SndFileDecoder<void>::supported_containers[4] = {Sample::SampleContainer::INT_S16,
                                                                                                             Sample::SampleContainer::INT_S32,
                                                                                                             Sample::SampleContainer::FLOAT_32,
                                                                                                             Sample::SampleContainer::FLOAT_64};

rusty::codecs::SndFileDecoder<void>::SndFileDecoder(const boost::filesystem::path path)
{
    sfinfo.format = 0;

    file_reader.reset(new core::FileReader(path, core::FileReader::Access::SHARE_READ, core::FileReader::Attribute::SEQUENTIAL));

    SF_VIRTUAL_IO sf_virtual_io;
    sf_virtual_io.get_filelen = SndFile::sf_vio_get_filelen;
    sf_virtual_io.seek = SndFile::sf_vio_seek;
    sf_virtual_io.read = SndFile::sf_vio_read;
    sf_virtual_io.tell = SndFile::sf_vio_tell;

    sndfile = sf_open_virtual(&sf_virtual_io, SFM_READ, &sfinfo, file_reader.get());

    if(sndfile == nullptr)
    {
        core::ReadFileException ex("SndFileDecoder", sf_error(sndfile), sf_strerror(sndfile));
        throw ex;
    }
}

unsigned int rusty::codecs::SndFileDecoder<void>::GetChannelCount() const noexcept
{
    return sfinfo.channels;
}

unsigned int rusty::codecs::SndFileDecoder<void>::GetSampleRate() const noexcept
{
    return sfinfo.samplerate;
}

uint64_t rusty::codecs::SndFileDecoder<void>::GetFrameCount() const noexcept
{
    //sfinfo.frames is in fact samples, NOT frames
    return sfinfo.frames / sfinfo.channels;
}

rusty::codecs::Sample::SampleContainer rusty::codecs::SndFileDecoder<void>::GetPreferableOutputContainer() const noexcept
{
    int subtype = SF_FORMAT_ENDMASK | SF_FORMAT_TYPEMASK | sfinfo.format;

    switch(subtype)
    {
        case SF_FORMAT_ENDMASK | SF_FORMAT_TYPEMASK | SF_FORMAT_PCM_S8:
        case SF_FORMAT_ENDMASK | SF_FORMAT_TYPEMASK | SF_FORMAT_PCM_16:
            return supported_containers[0];
        case SF_FORMAT_ENDMASK | SF_FORMAT_TYPEMASK | SF_FORMAT_PCM_24:
        case SF_FORMAT_ENDMASK | SF_FORMAT_TYPEMASK | SF_FORMAT_PCM_32:
            return supported_containers[1];
        case SF_FORMAT_ENDMASK | SF_FORMAT_TYPEMASK | SF_FORMAT_PCM_U8:
            return supported_containers[0];
        case SF_FORMAT_ENDMASK | SF_FORMAT_TYPEMASK | SF_FORMAT_FLOAT:
            return supported_containers[2];
        case SF_FORMAT_ENDMASK | SF_FORMAT_TYPEMASK | SF_FORMAT_DOUBLE:
            return supported_containers[3];
        case SF_FORMAT_ENDMASK | SF_FORMAT_TYPEMASK | SF_FORMAT_ULAW:
        case SF_FORMAT_ENDMASK | SF_FORMAT_TYPEMASK | SF_FORMAT_ALAW:
        case SF_FORMAT_ENDMASK | SF_FORMAT_TYPEMASK | SF_FORMAT_IMA_ADPCM:
        case SF_FORMAT_ENDMASK | SF_FORMAT_TYPEMASK | SF_FORMAT_MS_ADPCM:
        case SF_FORMAT_ENDMASK | SF_FORMAT_TYPEMASK | SF_FORMAT_GSM610:
        case SF_FORMAT_ENDMASK | SF_FORMAT_TYPEMASK | SF_FORMAT_VOX_ADPCM:
        case SF_FORMAT_ENDMASK | SF_FORMAT_TYPEMASK | SF_FORMAT_G721_32:
        case SF_FORMAT_ENDMASK | SF_FORMAT_TYPEMASK | SF_FORMAT_G723_24:
        case SF_FORMAT_ENDMASK | SF_FORMAT_TYPEMASK | SF_FORMAT_G723_40:
            return supported_containers[0];
        case SF_FORMAT_ENDMASK | SF_FORMAT_TYPEMASK | SF_FORMAT_DWVW_12:
        case SF_FORMAT_ENDMASK | SF_FORMAT_TYPEMASK | SF_FORMAT_DWVW_16:
        case SF_FORMAT_ENDMASK | SF_FORMAT_TYPEMASK | SF_FORMAT_DWVW_24:
        case SF_FORMAT_ENDMASK | SF_FORMAT_TYPEMASK | SF_FORMAT_DWVW_N:
            return supported_containers[1];
        case SF_FORMAT_ENDMASK | SF_FORMAT_TYPEMASK | SF_FORMAT_DPCM_8:
        case SF_FORMAT_ENDMASK | SF_FORMAT_TYPEMASK | SF_FORMAT_DPCM_16:
            return supported_containers[0];
        default:
            assert(false);
    }
}

const rusty::codecs::Sample::SampleContainer * rusty::codecs::SndFileDecoder<void>::GetSupportedContainers() const noexcept
{
    return supported_containers;
}

size_t rusty::codecs::SndFileDecoder<void>::GetSupportedContainersCount() const noexcept
{
    static constexpr const size_t supported_containers_count = sizeof(supported_containers) / sizeof(supported_containers[0]);
    return supported_containers_count;
}

rusty::codecs::SndFileDecoder<void>::~SndFileDecoder(void)
{
    ASSERT_METHOD(sf_close(sndfile), == , SF_ERR_NO_ERROR);
}
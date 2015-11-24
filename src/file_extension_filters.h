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
#include "include/codecs/common.h"

#ifndef GUI_FILE_EXTENSION_FILTERS_H
#define GUI_FILE_EXTENSION_FILTERS_H

#define ALL_SUPPORTED_TYPES_DESCRIPTION L"All supported types"
#define ANYTHING_WILDCARD L"*."
#define EXTENSION_SEPARATOR_AND_ANYTHING_WILDCARD L";" ANYTHING_WILDCARD

#define AUDIO_EXTENSION_FILTER_STACK                            AUDIO_EXTENSION_AIF_W \
                                                                EXTENSION_SEPARATOR_AND_ANYTHING_WILDCARD \
                                                                AUDIO_EXTENSION_AIFC_W \
                                                                EXTENSION_SEPARATOR_AND_ANYTHING_WILDCARD \
                                                                AUDIO_EXTENSION_AIFF_W \
                                                                EXTENSION_SEPARATOR_AND_ANYTHING_WILDCARD \
                                                                AUDIO_EXTENSION_AMPC_W \
                                                                EXTENSION_SEPARATOR_AND_ANYTHING_WILDCARD \
                                                                AUDIO_EXTENSION_AU_W \
                                                                EXTENSION_SEPARATOR_AND_ANYTHING_WILDCARD \
                                                                AUDIO_EXTENSION_AVR_W \
                                                                EXTENSION_SEPARATOR_AND_ANYTHING_WILDCARD \
                                                                AUDIO_EXTENSION_CAF_W \
                                                                EXTENSION_SEPARATOR_AND_ANYTHING_WILDCARD \
                                                                AUDIO_EXTENSION_HTK_W \
                                                                EXTENSION_SEPARATOR_AND_ANYTHING_WILDCARD \
                                                                AUDIO_EXTENSION_IFF_W \
                                                                EXTENSION_SEPARATOR_AND_ANYTHING_WILDCARD \
                                                                AUDIO_EXTENSION_MAT_W \
                                                                EXTENSION_SEPARATOR_AND_ANYTHING_WILDCARD \
                                                                AUDIO_EXTENSION_MP1_W \
                                                                EXTENSION_SEPARATOR_AND_ANYTHING_WILDCARD \
                                                                AUDIO_EXTENSION_MP2_W \
                                                                EXTENSION_SEPARATOR_AND_ANYTHING_WILDCARD \
                                                                AUDIO_EXTENSION_MP3_W \
                                                                EXTENSION_SEPARATOR_AND_ANYTHING_WILDCARD \
                                                                AUDIO_EXTENSION_PAF_W \
                                                                EXTENSION_SEPARATOR_AND_ANYTHING_WILDCARD \
                                                                AUDIO_EXTENSION_PVF_W \
                                                                EXTENSION_SEPARATOR_AND_ANYTHING_WILDCARD \
                                                                AUDIO_EXTENSION_RF64_W \
                                                                EXTENSION_SEPARATOR_AND_ANYTHING_WILDCARD \
                                                                AUDIO_EXTENSION_SD2_W \
                                                                EXTENSION_SEPARATOR_AND_ANYTHING_WILDCARD \
                                                                AUDIO_EXTENSION_SDS_W \
                                                                EXTENSION_SEPARATOR_AND_ANYTHING_WILDCARD \
                                                                AUDIO_EXTENSION_SF_W \
                                                                EXTENSION_SEPARATOR_AND_ANYTHING_WILDCARD \
                                                                AUDIO_EXTENSION_VOC_W \
                                                                EXTENSION_SEPARATOR_AND_ANYTHING_WILDCARD \
                                                                AUDIO_EXTENSION_WAV_W \
                                                                EXTENSION_SEPARATOR_AND_ANYTHING_WILDCARD \
                                                                AUDIO_EXTENSION_W64_W \
                                                                EXTENSION_SEPARATOR_AND_ANYTHING_WILDCARD \
                                                                AUDIO_EXTENSION_WVE_W \
                                                                EXTENSION_SEPARATOR_AND_ANYTHING_WILDCARD \
                                                                AUDIO_EXTENSION_XI_W

#define SNDFILE_ENCODER_PROFILE_EXTENSION_FILTER_STACK          PROFILE_EXTENSION_SNDFILE_ENCODER_AIF_W \
                                                                EXTENSION_SEPARATOR_AND_ANYTHING_WILDCARD \
                                                                PROFILE_EXTENSION_SNDFILE_ENCODER_AIFC_W \
                                                                EXTENSION_SEPARATOR_AND_ANYTHING_WILDCARD \
                                                                PROFILE_EXTENSION_SNDFILE_ENCODER_AIFF_W \
                                                                EXTENSION_SEPARATOR_AND_ANYTHING_WILDCARD \
                                                                PROFILE_EXTENSION_SNDFILE_ENCODER_AMPC_W \
                                                                EXTENSION_SEPARATOR_AND_ANYTHING_WILDCARD \
                                                                PROFILE_EXTENSION_SNDFILE_ENCODER_AU_W \
                                                                EXTENSION_SEPARATOR_AND_ANYTHING_WILDCARD \
                                                                PROFILE_EXTENSION_SNDFILE_ENCODER_AVR_W \
                                                                EXTENSION_SEPARATOR_AND_ANYTHING_WILDCARD \
                                                                PROFILE_EXTENSION_SNDFILE_ENCODER_CAF_W \
                                                                EXTENSION_SEPARATOR_AND_ANYTHING_WILDCARD \
                                                                PROFILE_EXTENSION_SNDFILE_ENCODER_HTK_W \
                                                                EXTENSION_SEPARATOR_AND_ANYTHING_WILDCARD \
                                                                PROFILE_EXTENSION_SNDFILE_ENCODER_IFF_W \
                                                                EXTENSION_SEPARATOR_AND_ANYTHING_WILDCARD \
                                                                PROFILE_EXTENSION_SNDFILE_ENCODER_MAT_W \
                                                                EXTENSION_SEPARATOR_AND_ANYTHING_WILDCARD \
                                                                PROFILE_EXTENSION_SNDFILE_ENCODER_PAF_W \
                                                                EXTENSION_SEPARATOR_AND_ANYTHING_WILDCARD \
                                                                PROFILE_EXTENSION_SNDFILE_ENCODER_PVF_W \
                                                                EXTENSION_SEPARATOR_AND_ANYTHING_WILDCARD \
                                                                PROFILE_EXTENSION_SNDFILE_ENCODER_RF64_W \
                                                                EXTENSION_SEPARATOR_AND_ANYTHING_WILDCARD \
                                                                PROFILE_EXTENSION_SNDFILE_ENCODER_SD2_W \
                                                                EXTENSION_SEPARATOR_AND_ANYTHING_WILDCARD \
                                                                PROFILE_EXTENSION_SNDFILE_ENCODER_SDS_W \
                                                                EXTENSION_SEPARATOR_AND_ANYTHING_WILDCARD \
                                                                PROFILE_EXTENSION_SNDFILE_ENCODER_SF_W \
                                                                EXTENSION_SEPARATOR_AND_ANYTHING_WILDCARD \
                                                                PROFILE_EXTENSION_SNDFILE_ENCODER_VOC_W \
                                                                EXTENSION_SEPARATOR_AND_ANYTHING_WILDCARD \
                                                                PROFILE_EXTENSION_SNDFILE_ENCODER_WAV_W \
                                                                EXTENSION_SEPARATOR_AND_ANYTHING_WILDCARD \
                                                                PROFILE_EXTENSION_SNDFILE_ENCODER_W64_W \
                                                                EXTENSION_SEPARATOR_AND_ANYTHING_WILDCARD \
                                                                PROFILE_EXTENSION_SNDFILE_ENCODER_WVE_W \
                                                                EXTENSION_SEPARATOR_AND_ANYTHING_WILDCARD \
                                                                PROFILE_EXTENSION_SNDFILE_ENCODER_XI_W

#define LAME_ENCODER_PROFILE_EXTENSION_FILTER_STACK             PROFILE_EXTENSION_LAME_MP3_W

#define ALL_ENCODER_PROFILES_EXTENSION_FILTER_STACK             LAME_ENCODER_PROFILE_EXTENSION_FILTER_STACK \
                                                                EXTENSION_SEPARATOR_AND_ANYTHING_WILDCARD \
                                                                SNDFILE_ENCODER_PROFILE_EXTENSION_FILTER_STACK

namespace rusty
{
namespace gui
{
class FileExtensionFilters
{
    public:
        static const COMDLG_FILTERSPEC input_audio_format_filters[23];
        static const COMDLG_FILTERSPEC profile_format_filters[3];
        static const COMDLG_FILTERSPEC lame_profile_format_filters[1];
        static const COMDLG_FILTERSPEC sndfile_encoder_profile_format_filters[1];
};
}
}


#endif
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
#include "file_extension_filters.h"

#define WILDCARD L"*."
#define EXTENSION_SEPARATOR_AND_WILDCARD L";" WILDCARD

const COMDLG_FILTERSPEC FileExtensionFilters::input_audio_format_filters[] =
{
    {AUDIO_EXTENSION_DESCRIPTION_AUDIO_INTERCHANGE_W,           WILDCARD
                                                                AUDIO_EXTENSION_AIF_W
                                                                EXTENSION_SEPARATOR_AND_WILDCARD
                                                                AUDIO_EXTENSION_AIFC_W
                                                                EXTENSION_SEPARATOR_AND_WILDCARD
                                                                AUDIO_EXTENSION_AIFF_W},

    {AUDIO_EXTENSION_DESCRIPTION_AKAI_MPC_2000_W,               WILDCARD
                                                                AUDIO_EXTENSION_AMPC_W},

    {AUDIO_EXTENSION_DESCRIPTION_SUN_MICROSYSTEM_W,             WILDCARD
                                                                AUDIO_EXTENSION_AU_W},

    {AUDIO_EXTENSION_DESCRIPTION_AUDIO_VISUAL_RESEARCH_W,       WILDCARD
                                                                AUDIO_EXTENSION_AVR_W},

    {AUDIO_EXTENSION_DESCRIPTION_APPLE_CORE_W,                  WILDCARD
                                                                AUDIO_EXTENSION_CAF_W},

    {AUDIO_EXTENSION_DESCRIPTION_HIDDEN_MARKOV_MODEL_TOOLKIT_W, WILDCARD
                                                                AUDIO_EXTENSION_HTK_W},

    {AUDIO_EXTENSION_DESCRIPTION_AMIGA_W,                       WILDCARD
                                                                AUDIO_EXTENSION_IFF_W},

    {AUDIO_EXTENSION_DESCRIPTION_GNU_OCTAVE_MATLAB_W,           WILDCARD
                                                                AUDIO_EXTENSION_MAT_W},

    {AUDIO_EXTENSION_DESCRIPTION_MPEG_AUDIO_LAYER_1_W,          WILDCARD
                                                                AUDIO_EXTENSION_MP1_W},

    {AUDIO_EXTENSION_DESCRIPTION_MPEG_AUDIO_LAYER_2_W,          WILDCARD
                                                                AUDIO_EXTENSION_MP2_W},

    {AUDIO_EXTENSION_DESCRIPTION_MPEG_AUDIO_LAYER_3_W,          WILDCARD
                                                                AUDIO_EXTENSION_MP3_W},

    {AUDIO_EXTENSION_DESCRIPTION_ENSONIQ_PARIS_W,               WILDCARD
                                                                AUDIO_EXTENSION_PAF_W},

    {AUDIO_EXTENSION_DESCRIPTION_PORTABLE_VOICE_W,              WILDCARD
                                                                AUDIO_EXTENSION_PVF_W},

    {AUDIO_EXTENSION_DESCRIPTION_RIFF_64_W,                     WILDCARD
                                                                AUDIO_EXTENSION_RF64_W},

    {AUDIO_EXTENSION_DESCRIPTION_SOUND_DESIGNER_II_W,           WILDCARD
                                                                AUDIO_EXTENSION_SD2_W},

    {AUDIO_EXTENSION_DESCRIPTION_MIDI_SAMPLE_DUMP_W,            WILDCARD
                                                                AUDIO_EXTENSION_SDS_W},

    {AUDIO_EXTENSION_DESCRIPTION_BERKELEY_IRCAM_W,              WILDCARD
                                                                AUDIO_EXTENSION_SF_W},

    {AUDIO_EXTENSION_DESCRIPTION_CREATIVE_LABS_W,               WILDCARD
                                                                AUDIO_EXTENSION_VOC_W},

    {AUDIO_EXTENSION_DESCRIPTION_WAV_W,                         WILDCARD
                                                                AUDIO_EXTENSION_WAV_W},

    {AUDIO_EXTENSION_DESCRPTION_SOUNDFOUNDRY_WAVE_64_W,         WILDCARD
                                                                AUDIO_EXTENSION_W64_W},

    {AUDIO_EXTENSION_DESCRIPTION_PSION_SERIES_3_W,              WILDCARD
                                                                AUDIO_EXTENSION_WVE_W},

    {AUDIO_EXTENSION_DESCRIPTION_FASTTRACKER_W,                 WILDCARD
                                                                AUDIO_EXTENSION_XI_W}
};

const COMDLG_FILTERSPEC FileExtensionFilters::input_profile_format_filters[] =
{
    {L"All supported types",                            WILDCARD
                                                        PROFILE_EXTENSION_LAME_W
                                                        EXTENSION_SEPARATOR_AND_WILDCARD
                                                        PROFILE_EXTENSION_SNDFILEENCODER_W},

    {PROFILE_EXTENSION_DESCRIPTION_LAME_W,              WILDCARD
                                                        PROFILE_EXTENSION_LAME_W},

    {PROFILE_EXTENSION_DESCRIPTION_SNDFILEENCODER_W,    WILDCARD
                                                        PROFILE_EXTENSION_SNDFILEENCODER_W}
};

#undef EXTENSION_SEPARATOR_AND_WILDCARD
#undef WILDCARD
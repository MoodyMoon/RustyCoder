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
#include "sndfile_encoder_profile.h"

const std::unordered_map<const rusty::codecs::SndFileEncoderProfile::OutputFormat, std::string> rusty::codecs::SndFileEncoderProfile::output_format_to_file_extension =
{
    /*! WAV (Microsoft) */
    {OutputFormat::WAV_PCM_INT_U8, AUDIO_EXTENSION_WAV},
    {OutputFormat::WAV_PCM_INT_S16, AUDIO_EXTENSION_WAV},
    {OutputFormat::WAV_PCM_INT_S24, AUDIO_EXTENSION_WAV},
    {OutputFormat::WAV_PCM_INT_S32, AUDIO_EXTENSION_WAV},
    {OutputFormat::WAV_PCM_FLOAT_32, AUDIO_EXTENSION_WAV},
    {OutputFormat::WAV_PCM_FLOAT_64, AUDIO_EXTENSION_WAV},
    {OutputFormat::WAV_ULAW, AUDIO_EXTENSION_WAV},
    {OutputFormat::WAV_ALAW, AUDIO_EXTENSION_WAV},
    {OutputFormat::WAV_IMA_ADPACM, AUDIO_EXTENSION_WAV},
    {OutputFormat::WAV_MS_ADPACM, AUDIO_EXTENSION_WAV},
    {OutputFormat::WAV_GSM610, AUDIO_EXTENSION_WAV},
    {OutputFormat::WAV_G721_32_ADPCM, AUDIO_EXTENSION_WAV},

    /*! AIFF (Apple/SGI) */
    {OutputFormat::AIFF_PCM_INT_U8, AUDIO_EXTENSION_AIFF},
    {OutputFormat::AIFF_PCM_INT_S8, AUDIO_EXTENSION_AIFF},
    {OutputFormat::AIFF_PCM_INT_S16, AUDIO_EXTENSION_AIFF},
    {OutputFormat::AIFF_PCM_INT_S24, AUDIO_EXTENSION_AIFF},
    {OutputFormat::AIFF_PCM_INT_S32, AUDIO_EXTENSION_AIFF},
    {OutputFormat::AIFF_PCM_FLOAT_32, AUDIO_EXTENSION_AIFC},
    {OutputFormat::AIFF_PCM_FLOAT_64, AUDIO_EXTENSION_AIFF},
    {OutputFormat::AIFF_ULAW, AUDIO_EXTENSION_AIFF},
    {OutputFormat::AIFF_ALAW, AUDIO_EXTENSION_AIFF},
    {OutputFormat::AIFF_IMA_ADPCM, AUDIO_EXTENSION_AIFF},
    {OutputFormat::AIFF_GSM610, AUDIO_EXTENSION_AIFF},
    {OutputFormat::AIFF_DWVW_12, AUDIO_EXTENSION_AIFF},
    {OutputFormat::AIFF_DWVW_16, AUDIO_EXTENSION_AIFF},
    {OutputFormat::AIFF_DWVW_24, AUDIO_EXTENSION_AIFF},

    /*! AU (Sun/NeXT) */
    {OutputFormat::AU_PCM_INT_S8, AUDIO_EXTENSION_AU},
    {OutputFormat::AU_PCM_INT_S16, AUDIO_EXTENSION_AU},
    {OutputFormat::AU_PCM_INT_S24, AUDIO_EXTENSION_AU},
    {OutputFormat::AU_PCM_INT_S32, AUDIO_EXTENSION_AU},
    {OutputFormat::AU_PCM_FLOAT_32, AUDIO_EXTENSION_AU},
    {OutputFormat::AU_PCM_FLOAT_64, AUDIO_EXTENSION_AU},
    {OutputFormat::AU_ULAW, AUDIO_EXTENSION_AU},
    {OutputFormat::AU_ALAW, AUDIO_EXTENSION_AU},
    {OutputFormat::AU_G721_32_ADPCM, AUDIO_EXTENSION_AU},
    {OutputFormat::AU_G723_24_ADPCM, AUDIO_EXTENSION_AU},
    {OutputFormat::AU_G723_40_ADPCM, AUDIO_EXTENSION_AU},

    /*! PAF (Ensoniq PARIS) */
    {OutputFormat::PAF_PCM_INT_S8, AUDIO_EXTENSION_PAF},
    {OutputFormat::PAF_PCM_INT_S16, AUDIO_EXTENSION_PAF},
    {OutputFormat::PAF_PCM_INT_S24, AUDIO_EXTENSION_PAF},

    /*! IFF (Amiga IFF/SVX8/SV16) */
    {OutputFormat::SVX_PCM_INT_S8, AUDIO_EXTENSION_IFF},
    {OutputFormat::SVX_PCM_INT_S16, AUDIO_EXTENSION_IFF},

    /*! WAV (NIST Sphere) */
    {OutputFormat::NIST_PCM_INT_S8, AUDIO_EXTENSION_WAV},
    {OutputFormat::NIST_PCM_INT_S16, AUDIO_EXTENSION_WAV},
    {OutputFormat::NIST_PCM_INT_S24, AUDIO_EXTENSION_WAV},
    {OutputFormat::NIST_PCM_INT_S32, AUDIO_EXTENSION_WAV},
    {OutputFormat::NIST_ULAW, AUDIO_EXTENSION_WAV},
    {OutputFormat::NIST_ALAW, AUDIO_EXTENSION_WAV},

    /*! VOC (Creative Labs) */
    {OutputFormat::VOC_PCM_INT_U8, AUDIO_EXTENSION_VOC},
    {OutputFormat::VOC_PCM_INT_S16, AUDIO_EXTENSION_VOC},
    {OutputFormat::VOC_ULAW, AUDIO_EXTENSION_VOC},
    {OutputFormat::VOC_ALAW, AUDIO_EXTENSION_VOC},

    /*! SF (Berkeley/IRCAM/CARL) */
    {OutputFormat::IRCAM_PCM_INT_S16, AUDIO_EXTENSION_SF},
    {OutputFormat::IRCAM_PCM_INT_S32, AUDIO_EXTENSION_SF},
    {OutputFormat::IRCAM_PCM_FLOAT_32, AUDIO_EXTENSION_SF},
    {OutputFormat::IRCAM_ULAW, AUDIO_EXTENSION_SF},
    {OutputFormat::IRCAM_ALAW, AUDIO_EXTENSION_SF},

    /*! W64 (SoundFoundry WAVE 64) */
    {OutputFormat::W64_PCM_INT_U8, AUDIO_EXTENSION_W64},
    {OutputFormat::W64_PCM_INT_S16, AUDIO_EXTENSION_W64},
    {OutputFormat::W64_PCM_INT_S24, AUDIO_EXTENSION_W64},
    {OutputFormat::W64_PCM_INT_S32, AUDIO_EXTENSION_W64},
    {OutputFormat::W64_PCM_FLOAT_32, AUDIO_EXTENSION_W64},
    {OutputFormat::W64_PCM_FLOAT_64, AUDIO_EXTENSION_W64},
    {OutputFormat::W64_ULAW, AUDIO_EXTENSION_W64},
    {OutputFormat::W64_ALAW, AUDIO_EXTENSION_W64},
    {OutputFormat::W64_IMA_ADPCM, AUDIO_EXTENSION_W64},
    {OutputFormat::W64_MS_ADPCM, AUDIO_EXTENSION_W64},
    {OutputFormat::W64_GSM610, AUDIO_EXTENSION_W64},

    /*! MAT4 (GNU Octave 2.0 / Matlab 4.2) */
    {OutputFormat::MAT4_PCM_INT_S16, AUDIO_EXTENSION_MAT},
    {OutputFormat::MAT4_PCM_INT_S32, AUDIO_EXTENSION_MAT},
    {OutputFormat::MAT4_PCM_FLOAT_32, AUDIO_EXTENSION_MAT},
    {OutputFormat::MAT4_PCM_FLOAT_64, AUDIO_EXTENSION_MAT},

    /*! MAT5 (GNU Octave 2.1 / Matlab 5.0) */
    {OutputFormat::MAT5_PCM_INT_U8, AUDIO_EXTENSION_MAT},
    {OutputFormat::MAT5_PCM_INT_S16, AUDIO_EXTENSION_MAT},
    {OutputFormat::MAT5_PCM_INT_S32, AUDIO_EXTENSION_MAT},
    {OutputFormat::MAT5_PCM_FLOAT_32, AUDIO_EXTENSION_MAT},
    {OutputFormat::MAT5_PCM_FLOAT_64, AUDIO_EXTENSION_MAT},

    /*! PVF (Portable Voice Format) */
    {OutputFormat::PVF_PCM_INT_S8, AUDIO_EXTENSION_PVF},
    {OutputFormat::PVF_PCM_INT_S16, AUDIO_EXTENSION_PVF},
    {OutputFormat::PVF_PCM_INT_S32, AUDIO_EXTENSION_PVF},

    /*! XI (FastTracker 2) */
    {OutputFormat::XI_DPCM_8, AUDIO_EXTENSION_XI},
    {OutputFormat::XI_DPCM_16, AUDIO_EXTENSION_XI},

    /*! HTK (HMM Tool Kit) */
    {OutputFormat::HTK_PCM_INT_S16, AUDIO_EXTENSION_HTK},

    /*! SDS (Midi Sample Dump Standard) */
    {OutputFormat::SDS_PCM_INT_S8, AUDIO_EXTENSION_SDS},
    {OutputFormat::SDS_PCM_INT_S16, AUDIO_EXTENSION_SDS},
    {OutputFormat::SDS_PCM_INT_S24, AUDIO_EXTENSION_SDS},

    /*! AVR (Audio Visual Research) */
    {OutputFormat::AVR_PCM_INT_U8, AUDIO_EXTENSION_AVR},
    {OutputFormat::AVR_PCM_INT_S8, AUDIO_EXTENSION_AVR},
    {OutputFormat::AVR_PCM_INT_S16, AUDIO_EXTENSION_AVR},

    /*! WAVEX (Microsoft) */
    {OutputFormat::WAVEX_PCM_INT_U8, AUDIO_EXTENSION_WAV},
    {OutputFormat::WAVEX_PCM_INT_S16, AUDIO_EXTENSION_WAV},
    {OutputFormat::WAVEX_PCM_INT_S24, AUDIO_EXTENSION_WAV},
    {OutputFormat::WAVEX_PCM_INT_S32, AUDIO_EXTENSION_WAV},
    {OutputFormat::WAVEX_PCM_FLOAT_32, AUDIO_EXTENSION_WAV},
    {OutputFormat::WAVEX_PCM_FLOAT_64, AUDIO_EXTENSION_WAV},
    {OutputFormat::WAVEX_ULAW, AUDIO_EXTENSION_WAV},
    {OutputFormat::WAVEX_ALAW, AUDIO_EXTENSION_WAV},

    /*! SD2 (Sound Designer II) */
    {OutputFormat::SD2_PCM_INT_S8, AUDIO_EXTENSION_SD2},
    {OutputFormat::SD2_PCM_INT_S16, AUDIO_EXTENSION_SD2},
    {OutputFormat::SD2_PCM_INT_S24, AUDIO_EXTENSION_SD2},

    /*! CAF (Apple Core Audio File) */
    {OutputFormat::CAF_PCM_INT_S8, AUDIO_EXTENSION_CAF},
    {OutputFormat::CAF_PCM_INT_S16, AUDIO_EXTENSION_CAF},
    {OutputFormat::CAF_PCM_INT_S24, AUDIO_EXTENSION_CAF},
    {OutputFormat::CAF_PCM_INT_S32, AUDIO_EXTENSION_CAF},
    {OutputFormat::CAF_PCM_FLOAT_32, AUDIO_EXTENSION_CAF},
    {OutputFormat::CAF_PCM_FLOAT_64, AUDIO_EXTENSION_CAF},
    {OutputFormat::CAF_ULAW, AUDIO_EXTENSION_CAF},
    {OutputFormat::CAF_ALAW, AUDIO_EXTENSION_CAF},

    /*! WVE (Psion Series 3) */
    {OutputFormat::WVE_ALAW, AUDIO_EXTENSION_WVE},

    /*! MPC (Akai MPC 2k) */
    {OutputFormat::MPC2K_PCM_INT_S16, AUDIO_EXTENSION_AMPC},

    /*! RF64 (RIFF 64) */
    {OutputFormat::RF64_PCM_INT_U8, AUDIO_EXTENSION_RF64},
    {OutputFormat::RF64_PCM_INT_S16, AUDIO_EXTENSION_RF64},
    {OutputFormat::RF64_PCM_INT_S24, AUDIO_EXTENSION_RF64},
    {OutputFormat::RF64_PCM_INT_S32, AUDIO_EXTENSION_RF64},
    {OutputFormat::RF64_PCM_FLOAT_32, AUDIO_EXTENSION_RF64},
    {OutputFormat::RF64_PCM_FLOAT_64, AUDIO_EXTENSION_RF64},
    {OutputFormat::RF64_ULAW, AUDIO_EXTENSION_RF64},
    {OutputFormat::RF64_ALAW, AUDIO_EXTENSION_RF64}
};

const std::unordered_map<const rusty::codecs::SndFileEncoderProfile::OutputFormat, std::string> rusty::codecs::SndFileEncoderProfile::output_format_to_text =
{
    /*! WAV (Microsoft) */
    {OutputFormat::WAV_PCM_INT_U8, "WAV_PCM_INT_U8"},
    {OutputFormat::WAV_PCM_INT_S16, "WAV_PCM_INT_S16"},
    {OutputFormat::WAV_PCM_INT_S24, "WAV_PCM_INT_S24"},
    {OutputFormat::WAV_PCM_INT_S32, "WAV_PCM_INT_S32"},
    {OutputFormat::WAV_PCM_FLOAT_32, "WAV_PCM_FLOAT_32"},
    {OutputFormat::WAV_PCM_FLOAT_64, "WAV_PCM_FLOAT_64"},
    {OutputFormat::WAV_ULAW, "WAV_ULAW"},
    {OutputFormat::WAV_ALAW, "WAV_ALAW"},
    {OutputFormat::WAV_IMA_ADPACM, "WAV_IMA_ADPACM"},
    {OutputFormat::WAV_MS_ADPACM, "WAV_MS_ADPACM"},
    {OutputFormat::WAV_GSM610, "WAV_GSM610"},
    {OutputFormat::WAV_G721_32_ADPCM, "WAV_G721_32_ADPCM"},

    /*! AIFF (Apple/SGI) */
    {OutputFormat::AIFF_PCM_INT_U8, "AIFF_PCM_INT_U8"},
    {OutputFormat::AIFF_PCM_INT_S8, "AIFF_PCM_INT_S8"},
    {OutputFormat::AIFF_PCM_INT_S16, "AIFF_PCM_INT_S16"},
    {OutputFormat::AIFF_PCM_INT_S24, "AIFF_PCM_INT_S24"},
    {OutputFormat::AIFF_PCM_INT_S32, "AIFF_PCM_INT_S32"},
    {OutputFormat::AIFF_PCM_FLOAT_32, "AIFF_PCM_FLOAT_32"},
    {OutputFormat::AIFF_PCM_FLOAT_64, "AIFF_PCM_FLOAT_64"},
    {OutputFormat::AIFF_ULAW, "AIFF_ULAW"},
    {OutputFormat::AIFF_ALAW, "AIFF_ALAW"},
    {OutputFormat::AIFF_IMA_ADPCM, "AIFF_IMA_ADPCM"},
    {OutputFormat::AIFF_GSM610, "AIFF_GSM610"},
    {OutputFormat::AIFF_DWVW_12, "AIFF_DWVW_12"},
    {OutputFormat::AIFF_DWVW_16, "AIFF_DWVW_16"},
    {OutputFormat::AIFF_DWVW_24, "AIFF_DWVW_24"},

    /*! AU (Sun/NeXT) */
    {OutputFormat::AU_PCM_INT_S8, "AU_PCM_INT_S8"},
    {OutputFormat::AU_PCM_INT_S16, "AU_PCM_INT_S16"},
    {OutputFormat::AU_PCM_INT_S24, "AU_PCM_INT_S24"},
    {OutputFormat::AU_PCM_INT_S32, "AU_PCM_INT_S32"},
    {OutputFormat::AU_PCM_FLOAT_32, "AU_PCM_FLOAT_32"},
    {OutputFormat::AU_PCM_FLOAT_64, "AU_PCM_FLOAT_64"},
    {OutputFormat::AU_ULAW, "AU_ULAW"},
    {OutputFormat::AU_ALAW, "AU_ALAW"},
    {OutputFormat::AU_G721_32_ADPCM, "AU_G721_32_ADPCM"},
    {OutputFormat::AU_G723_24_ADPCM, "AU_G723_24_ADPCM"},
    {OutputFormat::AU_G723_40_ADPCM, "AU_G723_40_ADPCM"},

    /*! PAF (Ensoniq PARIS) */
    {OutputFormat::PAF_PCM_INT_S8, "PAF_PCM_INT_S8"},
    {OutputFormat::PAF_PCM_INT_S16, "PAF_PCM_INT_S16"},
    {OutputFormat::PAF_PCM_INT_S24, "PAF_PCM_INT_S24"},

    /*! IFF (Amiga IFF/SVX8/SV16) */
    {OutputFormat::SVX_PCM_INT_S8, "SVX_PCM_INT_S8"},
    {OutputFormat::SVX_PCM_INT_S16, "SVX_PCM_INT_S16"},

    /*! WAV (NIST Sphere) */
    {OutputFormat::NIST_PCM_INT_S8, "NIST_PCM_INT_S8"},
    {OutputFormat::NIST_PCM_INT_S16, "NIST_PCM_INT_S16"},
    {OutputFormat::NIST_PCM_INT_S24, "NIST_PCM_INT_S24"},
    {OutputFormat::NIST_PCM_INT_S32, "NIST_PCM_INT_S32"},
    {OutputFormat::NIST_ULAW, "NIST_ULAW"},
    {OutputFormat::NIST_ALAW, "NIST_ALAW"},

    /*! VOC (Creative Labs) */
    {OutputFormat::VOC_PCM_INT_U8, "VOC_PCM_INT_U8"},
    {OutputFormat::VOC_PCM_INT_S16, "VOC_PCM_INT_S16"},
    {OutputFormat::VOC_ULAW, "VOC_ULAW"},
    {OutputFormat::VOC_ALAW, "VOC_ALAW"},

    /*! SF (Berkeley/IRCAM/CARL) */
    {OutputFormat::IRCAM_PCM_INT_S16, "IRCAM_PCM_INT_S16"},
    {OutputFormat::IRCAM_PCM_INT_S32, "IRCAM_PCM_INT_S32"},
    {OutputFormat::IRCAM_PCM_FLOAT_32, "IRCAM_PCM_FLOAT_32"},
    {OutputFormat::IRCAM_ULAW, "IRCAM_ULAW"},
    {OutputFormat::IRCAM_ALAW, "IRCAM_ALAW"},

    /*! W64 (SoundFoundry WAVE 64) */
    {OutputFormat::W64_PCM_INT_U8, "W64_PCM_INT_U8"},
    {OutputFormat::W64_PCM_INT_S16, "W64_PCM_INT_S16"},
    {OutputFormat::W64_PCM_INT_S24, "W64_PCM_INT_S24"},
    {OutputFormat::W64_PCM_INT_S32, "W64_PCM_INT_S32"},
    {OutputFormat::W64_PCM_FLOAT_32, "W64_PCM_FLOAT_32"},
    {OutputFormat::W64_PCM_FLOAT_64, "W64_PCM_FLOAT_64"},
    {OutputFormat::W64_ULAW, "W64_ULAW"},
    {OutputFormat::W64_ALAW, "W64_ALAW"},
    {OutputFormat::W64_IMA_ADPCM, "W64_IMA_ADPCM"},
    {OutputFormat::W64_MS_ADPCM, "W64_MS_ADPCM"},
    {OutputFormat::W64_GSM610, "W64_GSM610"},

    /*! MAT4 (GNU Octave 2.0 / Matlab 4.2) */
    {OutputFormat::MAT4_PCM_INT_S16, "MAT4_PCM_INT_S16"},
    {OutputFormat::MAT4_PCM_INT_S32, "MAT4_PCM_INT_S32"},
    {OutputFormat::MAT4_PCM_FLOAT_32, "MAT4_PCM_FLOAT_32"},
    {OutputFormat::MAT4_PCM_FLOAT_64, "MAT4_PCM_FLOAT_64"},

    /*! MAT5 (GNU Octave 2.1 / Matlab 5.0) */
    {OutputFormat::MAT5_PCM_INT_U8, "MAT5_PCM_INT_U8"},
    {OutputFormat::MAT5_PCM_INT_S16, "MAT5_PCM_INT_S16"},
    {OutputFormat::MAT5_PCM_INT_S32, "MAT5_PCM_INT_S32"},
    {OutputFormat::MAT5_PCM_FLOAT_32, "MAT5_PCM_FLOAT_32"},
    {OutputFormat::MAT5_PCM_FLOAT_64, "MAT5_PCM_FLOAT_64"},

    /*! PVF (Portable Voice Format) */
    {OutputFormat::PVF_PCM_INT_S8, "PVF_PCM_INT_S8"},
    {OutputFormat::PVF_PCM_INT_S16, "PVF_PCM_INT_S16"},
    {OutputFormat::PVF_PCM_INT_S32, "PVF_PCM_INT_S32"},

    /*! XI (FastTracker 2) */
    {OutputFormat::XI_DPCM_8, "XI_DPCM_8"},
    {OutputFormat::XI_DPCM_16, "XI_DPCM_16"},

    /*! HTK (HMM Tool Kit) */
    {OutputFormat::HTK_PCM_INT_S16, "HTK_PCM_INT_S16"},

    /*! SDS (Midi Sample Dump Standard) */
    {OutputFormat::SDS_PCM_INT_S8, "SDS_PCM_INT_S8"},
    {OutputFormat::SDS_PCM_INT_S16, "SDS_PCM_INT_S16"},
    {OutputFormat::SDS_PCM_INT_S24, "SDS_PCM_INT_S24"},

    /*! AVR (Audio Visual Research) */
    {OutputFormat::AVR_PCM_INT_U8, "AVR_PCM_INT_U8"},
    {OutputFormat::AVR_PCM_INT_S8, "AVR_PCM_INT_S8"},
    {OutputFormat::AVR_PCM_INT_S16, "AVR_PCM_INT_S16"},

    /*! WAVEX (Microsoft) */
    {OutputFormat::WAVEX_PCM_INT_U8, "WAVEX_PCM_INT_U8"},
    {OutputFormat::WAVEX_PCM_INT_S16, "WAVEX_PCM_INT_S16"},
    {OutputFormat::WAVEX_PCM_INT_S24, "WAVEX_PCM_INT_S24"},
    {OutputFormat::WAVEX_PCM_INT_S32, "WAVEX_PCM_INT_S32"},
    {OutputFormat::WAVEX_PCM_FLOAT_32, "WAVEX_PCM_FLOAT_32"},
    {OutputFormat::WAVEX_PCM_FLOAT_64, "WAVEX_PCM_FLOAT_64"},
    {OutputFormat::WAVEX_ULAW, "WAVEX_ULAW"},
    {OutputFormat::WAVEX_ALAW, "WAVEX_ALAW"},

    /*! SD2 (Sound Designer II) */
    {OutputFormat::SD2_PCM_INT_S8, "SD2_PCM_INT_S8"},
    {OutputFormat::SD2_PCM_INT_S16, "SD2_PCM_INT_S16"},
    {OutputFormat::SD2_PCM_INT_S24, "SD2_PCM_INT_S24"},

    /*! CAF (Apple Core Audio File) */
    {OutputFormat::CAF_PCM_INT_S8, "CAF_PCM_INT_S8"},
    {OutputFormat::CAF_PCM_INT_S16, "CAF_PCM_INT_S16"},
    {OutputFormat::CAF_PCM_INT_S24, "CAF_PCM_INT_S24"},
    {OutputFormat::CAF_PCM_INT_S32, "CAF_PCM_INT_S32"},
    {OutputFormat::CAF_PCM_FLOAT_32, "CAF_PCM_FLOAT_32"},
    {OutputFormat::CAF_PCM_FLOAT_64, "CAF_PCM_FLOAT_64"},
    {OutputFormat::CAF_ULAW, "CAF_ULAW"},
    {OutputFormat::CAF_ALAW, "CAF_ALAW"},

    /*! WVE (Psion Series 3) */
    {OutputFormat::WVE_ALAW, "WVE_ALAW"},

    /*! MPC (Akai MPC 2k) */
    {OutputFormat::MPC2K_PCM_INT_S16, "MPC2K_PCM_INT_S16"},

    /*! RF64 (RIFF 64) */
    {OutputFormat::RF64_PCM_INT_U8, "RF64_PCM_INT_U8"},
    {OutputFormat::RF64_PCM_INT_S16, "RF64_PCM_INT_S16"},
    {OutputFormat::RF64_PCM_INT_S24, "RF64_PCM_INT_S24"},
    {OutputFormat::RF64_PCM_INT_S32, "RF64_PCM_INT_S32"},
    {OutputFormat::RF64_PCM_FLOAT_32, "RF64_PCM_FLOAT_32"},
    {OutputFormat::RF64_PCM_FLOAT_64, "RF64_PCM_FLOAT_64"},
    {OutputFormat::RF64_ULAW, "RF64_ULAW"},
    {OutputFormat::RF64_ALAW, "RF64_ALAW"}
};

const std::unordered_map<std::string, const rusty::codecs::SndFileEncoderProfile::OutputFormat> rusty::codecs::SndFileEncoderProfile::text_to_output_format =
{
    /*! WAV (Microsoft) */
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::WAV_PCM_INT_U8), OutputFormat::WAV_PCM_INT_U8},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::WAV_PCM_INT_S16), OutputFormat::WAV_PCM_INT_S16},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::WAV_PCM_INT_S24), OutputFormat::WAV_PCM_INT_S24},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::WAV_PCM_INT_S32), OutputFormat::WAV_PCM_INT_S32},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::WAV_PCM_FLOAT_32), OutputFormat::WAV_PCM_FLOAT_32},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::WAV_PCM_FLOAT_64), OutputFormat::WAV_PCM_FLOAT_64},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::WAV_ULAW), OutputFormat::WAV_ULAW},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::WAV_ALAW), OutputFormat::WAV_ALAW},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::WAV_IMA_ADPACM), OutputFormat::WAV_IMA_ADPACM},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::WAV_MS_ADPACM), OutputFormat::WAV_MS_ADPACM},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::WAV_GSM610), OutputFormat::WAV_GSM610},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::WAV_G721_32_ADPCM), OutputFormat::WAV_G721_32_ADPCM},

    /*! AIFF (Apple/SGI) */
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AIFF_PCM_INT_U8), OutputFormat::AIFF_PCM_INT_U8},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AIFF_PCM_INT_S8), OutputFormat::AIFF_PCM_INT_S8},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AIFF_PCM_INT_S16), OutputFormat::AIFF_PCM_INT_S16},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AIFF_PCM_INT_S24), OutputFormat::AIFF_PCM_INT_S24},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AIFF_PCM_INT_S32), OutputFormat::AIFF_PCM_INT_S32},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AIFF_PCM_FLOAT_32), OutputFormat::AIFF_PCM_FLOAT_32},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AIFF_PCM_FLOAT_64), OutputFormat::AIFF_PCM_FLOAT_64},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AIFF_ULAW), OutputFormat::AIFF_ULAW},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AIFF_ALAW), OutputFormat::AIFF_ALAW},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AIFF_IMA_ADPCM), OutputFormat::AIFF_IMA_ADPCM},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AIFF_GSM610), OutputFormat::AIFF_GSM610},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AIFF_DWVW_12), OutputFormat::AIFF_DWVW_12},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AIFF_DWVW_16), OutputFormat::AIFF_DWVW_16},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AIFF_DWVW_24), OutputFormat::AIFF_DWVW_24},

    /*! AU (Sun/NeXT) */
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AU_PCM_INT_S8), OutputFormat::AU_PCM_INT_S8},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AU_PCM_INT_S16), OutputFormat::AU_PCM_INT_S16},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AU_PCM_INT_S24), OutputFormat::AU_PCM_INT_S24},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AU_PCM_INT_S32), OutputFormat::AU_PCM_INT_S32},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AU_PCM_FLOAT_32), OutputFormat::AU_PCM_FLOAT_32},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AU_PCM_FLOAT_64), OutputFormat::AU_PCM_FLOAT_64},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AU_ULAW), OutputFormat::AU_ULAW},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AU_ALAW), OutputFormat::AU_ALAW},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AU_G721_32_ADPCM), OutputFormat::AU_G721_32_ADPCM},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AU_G723_24_ADPCM), OutputFormat::AU_G723_24_ADPCM},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AU_G723_40_ADPCM), OutputFormat::AU_G723_40_ADPCM},

    /*! PAF (Ensoniq PARIS) */
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::PAF_PCM_INT_S8), OutputFormat::PAF_PCM_INT_S8},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::PAF_PCM_INT_S16), OutputFormat::PAF_PCM_INT_S16},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::PAF_PCM_INT_S24), OutputFormat::PAF_PCM_INT_S24},

    /*! IFF (Amiga IFF/SVX8/SV16) */
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::SVX_PCM_INT_S8), OutputFormat::SVX_PCM_INT_S8},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::SVX_PCM_INT_S16), OutputFormat::SVX_PCM_INT_S16},

    /*! WAV (NIST Sphere) */
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::NIST_PCM_INT_S8), OutputFormat::NIST_PCM_INT_S8},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::NIST_PCM_INT_S16), OutputFormat::NIST_PCM_INT_S16},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::NIST_PCM_INT_S24), OutputFormat::NIST_PCM_INT_S24},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::NIST_PCM_INT_S32), OutputFormat::NIST_PCM_INT_S32},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::NIST_ULAW), OutputFormat::NIST_ULAW},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::NIST_ALAW), OutputFormat::NIST_ALAW},

    /*! VOC (Creative Labs) */
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::VOC_PCM_INT_U8), OutputFormat::VOC_PCM_INT_U8},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::VOC_PCM_INT_S16), OutputFormat::VOC_PCM_INT_S16},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::VOC_ULAW), OutputFormat::VOC_ULAW},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::VOC_ALAW), OutputFormat::VOC_ALAW},

    /*! SF (Berkeley/IRCAM/CARL) */
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::IRCAM_PCM_INT_S16), OutputFormat::IRCAM_PCM_INT_S16},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::IRCAM_PCM_INT_S32), OutputFormat::IRCAM_PCM_INT_S32},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::IRCAM_PCM_FLOAT_32), OutputFormat::IRCAM_PCM_FLOAT_32},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::IRCAM_ULAW), OutputFormat::IRCAM_ULAW},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::IRCAM_ALAW), OutputFormat::IRCAM_ALAW},

    /*! W64 (SoundFoundry WAVE 64) */
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::W64_PCM_INT_U8), OutputFormat::W64_PCM_INT_U8},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::W64_PCM_INT_S16), OutputFormat::W64_PCM_INT_S16},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::W64_PCM_INT_S24), OutputFormat::W64_PCM_INT_S24},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::W64_PCM_INT_S32), OutputFormat::W64_PCM_INT_S32},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::W64_PCM_FLOAT_32), OutputFormat::W64_PCM_FLOAT_32},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::W64_PCM_FLOAT_64), OutputFormat::W64_PCM_FLOAT_64},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::W64_ULAW), OutputFormat::W64_ULAW},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::W64_ALAW), OutputFormat::W64_ALAW},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::W64_IMA_ADPCM), OutputFormat::W64_IMA_ADPCM},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::W64_MS_ADPCM), OutputFormat::W64_MS_ADPCM},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::W64_GSM610), OutputFormat::W64_GSM610},

    /*! MAT4 (GNU Octave 2.0 / Matlab 4.2) */
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::MAT4_PCM_INT_S16), OutputFormat::MAT4_PCM_INT_S16},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::MAT4_PCM_INT_S32), OutputFormat::MAT4_PCM_INT_S32},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::MAT4_PCM_FLOAT_32), OutputFormat::MAT4_PCM_FLOAT_32},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::MAT4_PCM_FLOAT_64), OutputFormat::MAT4_PCM_FLOAT_64},

    /*! MAT5 (GNU Octave 2.1 / Matlab 5.0) */
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::MAT5_PCM_INT_U8), OutputFormat::MAT5_PCM_INT_U8},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::MAT5_PCM_INT_S16), OutputFormat::MAT5_PCM_INT_S16},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::MAT5_PCM_INT_S32), OutputFormat::MAT5_PCM_INT_S32},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::MAT5_PCM_FLOAT_32), OutputFormat::MAT5_PCM_FLOAT_32},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::MAT5_PCM_FLOAT_64), OutputFormat::MAT5_PCM_FLOAT_64},

    /*! PVF (Portable Voice Format) */
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::PVF_PCM_INT_S8), OutputFormat::PVF_PCM_INT_S8},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::PVF_PCM_INT_S16), OutputFormat::PVF_PCM_INT_S16},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::PVF_PCM_INT_S32), OutputFormat::PVF_PCM_INT_S32},

    /*! XI (FastTracker 2) */
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::XI_DPCM_8), OutputFormat::XI_DPCM_8},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::XI_DPCM_16), OutputFormat::XI_DPCM_16},

    /*! HTK (HMM Tool Kit) */
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::HTK_PCM_INT_S16), OutputFormat::HTK_PCM_INT_S16},

    /*! SDS (Midi Sample Dump Standard) */
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::SDS_PCM_INT_S8), OutputFormat::SDS_PCM_INT_S8},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::SDS_PCM_INT_S16), OutputFormat::SDS_PCM_INT_S16},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::SDS_PCM_INT_S24), OutputFormat::SDS_PCM_INT_S24},

    /*! AVR (Audio Visual Research) */
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AVR_PCM_INT_U8), OutputFormat::AVR_PCM_INT_U8},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AVR_PCM_INT_S8), OutputFormat::AVR_PCM_INT_S8},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AVR_PCM_INT_S16), OutputFormat::AVR_PCM_INT_S16},

    /*! WAVEX (Microsoft) */
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::WAVEX_PCM_INT_U8), OutputFormat::WAVEX_PCM_INT_U8},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::WAVEX_PCM_INT_S16), OutputFormat::WAVEX_PCM_INT_S16},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::WAVEX_PCM_INT_S24), OutputFormat::WAVEX_PCM_INT_S24},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::WAVEX_PCM_INT_S32), OutputFormat::WAVEX_PCM_INT_S32},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::WAVEX_PCM_FLOAT_32), OutputFormat::WAVEX_PCM_FLOAT_32},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::WAVEX_PCM_FLOAT_64), OutputFormat::WAVEX_PCM_FLOAT_64},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::WAVEX_ULAW), OutputFormat::WAVEX_ULAW},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::WAVEX_ALAW), OutputFormat::WAVEX_ALAW},

    /*! SD2 (Sound Designer II) */
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::SD2_PCM_INT_S8), OutputFormat::SD2_PCM_INT_S8},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::SD2_PCM_INT_S16), OutputFormat::SD2_PCM_INT_S16},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::SD2_PCM_INT_S24), OutputFormat::SD2_PCM_INT_S24},

    /*! CAF (Apple Core Audio File) */
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::CAF_PCM_INT_S8), OutputFormat::CAF_PCM_INT_S8},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::CAF_PCM_INT_S16), OutputFormat::CAF_PCM_INT_S16},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::CAF_PCM_INT_S24), OutputFormat::CAF_PCM_INT_S24},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::CAF_PCM_INT_S32), OutputFormat::CAF_PCM_INT_S32},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::CAF_PCM_FLOAT_32), OutputFormat::CAF_PCM_FLOAT_32},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::CAF_PCM_FLOAT_64), OutputFormat::CAF_PCM_FLOAT_64},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::CAF_ULAW), OutputFormat::CAF_ULAW},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::CAF_ALAW), OutputFormat::CAF_ALAW},

    /*! WVE (Psion Series 3) */
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::WVE_ALAW), OutputFormat::WVE_ALAW},

    /*! MPC (Akai MPC 2k) */
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::MPC2K_PCM_INT_S16), OutputFormat::MPC2K_PCM_INT_S16},

    /*! RF64 (RIFF 64) */
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::RF64_PCM_INT_U8), OutputFormat::RF64_PCM_INT_U8},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::RF64_PCM_INT_S16), OutputFormat::RF64_PCM_INT_S16},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::RF64_PCM_INT_S24), OutputFormat::RF64_PCM_INT_S24},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::RF64_PCM_INT_S32), OutputFormat::RF64_PCM_INT_S32},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::RF64_PCM_FLOAT_32), OutputFormat::RF64_PCM_FLOAT_32},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::RF64_PCM_FLOAT_64), OutputFormat::RF64_PCM_FLOAT_64},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::RF64_ULAW), OutputFormat::RF64_ULAW},
    {SndFileEncoderProfile::output_format_to_text.at(OutputFormat::RF64_ALAW), OutputFormat::RF64_ALAW}
};

const std::unordered_map<const rusty::codecs::SndFileEncoderProfile::Option, std::string> rusty::codecs::SndFileEncoderProfile::option_to_text =
{
    {Option::OUPTPUT_FORMAT, "Output format"}
};

const std::unordered_map<std::string, const rusty::codecs::SndFileEncoderProfile::Option> rusty::codecs::SndFileEncoderProfile::text_to_option =
{
    {SndFileEncoderProfile::option_to_text.at(Option::OUPTPUT_FORMAT), Option::OUPTPUT_FORMAT}
};

const std::vector<std::string> rusty::codecs::SndFileEncoderProfile::options_and_selections[1] =
{
    {
        SndFileEncoderProfile::option_to_text.at(Option::OUPTPUT_FORMAT),
        /*! WAV (Microsoft) */
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::WAV_PCM_INT_U8),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::WAV_PCM_INT_S16),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::WAV_PCM_INT_S24),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::WAV_PCM_INT_S32),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::WAV_PCM_FLOAT_32),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::WAV_PCM_FLOAT_64),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::WAV_ULAW),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::WAV_ALAW),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::WAV_IMA_ADPACM),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::WAV_MS_ADPACM),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::WAV_GSM610),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::WAV_G721_32_ADPCM),

        /*! AIFF (Apple/SGI) */
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AIFF_PCM_INT_U8),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AIFF_PCM_INT_S8),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AIFF_PCM_INT_S16),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AIFF_PCM_INT_S24),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AIFF_PCM_INT_S32),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AIFF_PCM_FLOAT_32),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AIFF_PCM_FLOAT_64),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AIFF_ULAW),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AIFF_ALAW),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AIFF_IMA_ADPCM),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AIFF_GSM610),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AIFF_DWVW_12),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AIFF_DWVW_16),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AIFF_DWVW_24),

        /*! AU (Sun/NeXT) */
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AU_PCM_INT_S8),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AU_PCM_INT_S16),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AU_PCM_INT_S24),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AU_PCM_INT_S32),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AU_PCM_FLOAT_32),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AU_PCM_FLOAT_64),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AU_ULAW),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AU_ALAW),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AU_G721_32_ADPCM),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AU_G723_24_ADPCM),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AU_G723_40_ADPCM),

        /*! PAF (Ensoniq PARIS) */
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::PAF_PCM_INT_S8),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::PAF_PCM_INT_S16),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::PAF_PCM_INT_S24),

        /*! IFF (Amiga IFF/SVX8/SV16) */
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::SVX_PCM_INT_S8),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::SVX_PCM_INT_S16),

        /*! WAV (NIST Sphere) */
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::NIST_PCM_INT_S8),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::NIST_PCM_INT_S16),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::NIST_PCM_INT_S24),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::NIST_PCM_INT_S32),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::NIST_ULAW),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::NIST_ALAW),

        /*! VOC (Creative Labs) */
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::VOC_PCM_INT_U8),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::VOC_PCM_INT_S16),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::VOC_ULAW),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::VOC_ALAW),

        /*! SF (Berkeley/IRCAM/CARL) */
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::IRCAM_PCM_INT_S16),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::IRCAM_PCM_INT_S32),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::IRCAM_PCM_FLOAT_32),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::IRCAM_ULAW),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::IRCAM_ALAW),

        /*! W64 (SoundFoundry WAVE 64) */
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::W64_PCM_INT_U8),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::W64_PCM_INT_S16),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::W64_PCM_INT_S24),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::W64_PCM_INT_S32),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::W64_PCM_FLOAT_32),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::W64_PCM_FLOAT_64),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::W64_ULAW),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::W64_ALAW),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::W64_IMA_ADPCM),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::W64_MS_ADPCM),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::W64_GSM610),

        /*! MAT4 (GNU Octave 2.0 / Matlab 4.2) */
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::MAT4_PCM_INT_S16),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::MAT4_PCM_INT_S32),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::MAT4_PCM_FLOAT_32),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::MAT4_PCM_FLOAT_64),

        /*! MAT5 (GNU Octave 2.1 / Matlab 5.0) */
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::MAT5_PCM_INT_U8),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::MAT5_PCM_INT_S16),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::MAT5_PCM_INT_S32),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::MAT5_PCM_FLOAT_32),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::MAT5_PCM_FLOAT_64),

        /*! PVF (Portable Voice Format) */
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::PVF_PCM_INT_S8),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::PVF_PCM_INT_S16),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::PVF_PCM_INT_S32),

        /*! XI (FastTracker 2) */
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::XI_DPCM_8),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::XI_DPCM_16),

        /*! HTK (HMM Tool Kit) */
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::HTK_PCM_INT_S16),

        /*! SDS (Midi Sample Dump Standard) */
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::SDS_PCM_INT_S8),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::SDS_PCM_INT_S16),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::SDS_PCM_INT_S24),

        /*! AVR (Audio Visual Research) */
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AVR_PCM_INT_U8),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AVR_PCM_INT_S8),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::AVR_PCM_INT_S16),

        /*! WAVEX (Microsoft) */
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::WAVEX_PCM_INT_U8),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::WAVEX_PCM_INT_S16),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::WAVEX_PCM_INT_S24),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::WAVEX_PCM_INT_S32),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::WAVEX_PCM_FLOAT_32),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::WAVEX_PCM_FLOAT_64),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::WAVEX_ULAW),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::WAVEX_ALAW),

        /*! SD2 (Sound Designer II) */
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::SD2_PCM_INT_S8),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::SD2_PCM_INT_S16),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::SD2_PCM_INT_S24),

        /*! CAF (Apple Core Audio File) */
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::CAF_PCM_INT_S8),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::CAF_PCM_INT_S16),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::CAF_PCM_INT_S24),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::CAF_PCM_INT_S32),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::CAF_PCM_FLOAT_32),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::CAF_PCM_FLOAT_64),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::CAF_ULAW),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::CAF_ALAW),

        /*! WVE (Psion Series 3) */
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::WVE_ALAW),

        /*! MPC (Akai MPC 2k) */
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::MPC2K_PCM_INT_S16),

        /*! RF64 (RIFF 64) */
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::RF64_PCM_INT_U8),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::RF64_PCM_INT_S16),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::RF64_PCM_INT_S24),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::RF64_PCM_INT_S32),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::RF64_PCM_FLOAT_32),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::RF64_PCM_FLOAT_64),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::RF64_ULAW),
        SndFileEncoderProfile::output_format_to_text.at(OutputFormat::RF64_ALAW)
    }
};

rusty::codecs::SndFileEncoderProfile::SndFileEncoderProfile(void)
{
    LoadDefaultProfile(Profile::DEFAULT);
}

void rusty::codecs::SndFileEncoderProfile::LoadDefaultProfile(Profile default_profile)
{
    switch(default_profile)
    {
        case Profile::DEFAULT:
        {
            output_format = OutputFormat::WAV_PCM_FLOAT_32;
            break;
        }
        default:
            assert(false);
    }
}

void rusty::codecs::SndFileEncoderProfile::SetOutputFormat(SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE output_format)
{
    switch(output_format)
    {
        /*! WAV (Microsoft) */
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::WAV_PCM_INT_U8):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::WAV_PCM_INT_S16):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::WAV_PCM_INT_S24):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::WAV_PCM_INT_S32):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::WAV_PCM_FLOAT_32):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::WAV_PCM_FLOAT_64):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::WAV_ULAW):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::WAV_ALAW):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::WAV_IMA_ADPACM):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::WAV_MS_ADPACM):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::WAV_GSM610):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::WAV_G721_32_ADPCM):

        /*! AIFF (Apple/SGI) */
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::AIFF_PCM_INT_U8):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::AIFF_PCM_INT_S8):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::AIFF_PCM_INT_S16):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::AIFF_PCM_INT_S24):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::AIFF_PCM_INT_S32):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::AIFF_PCM_FLOAT_32):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::AIFF_PCM_FLOAT_64):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::AIFF_ULAW):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::AIFF_ALAW):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::AIFF_IMA_ADPCM):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::AIFF_GSM610):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::AIFF_DWVW_12):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::AIFF_DWVW_16):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::AIFF_DWVW_24):

        /*! AU (Sun/NeXT) */
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::AU_PCM_INT_S8):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::AU_PCM_INT_S16):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::AU_PCM_INT_S24):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::AU_PCM_INT_S32):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::AU_PCM_FLOAT_32):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::AU_PCM_FLOAT_64):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::AU_ULAW):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::AU_ALAW):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::AU_G721_32_ADPCM):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::AU_G723_24_ADPCM):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::AU_G723_40_ADPCM):

        /*! PAF (Ensoniq PARIS) */
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::PAF_PCM_INT_S8):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::PAF_PCM_INT_S16):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::PAF_PCM_INT_S24):

        /*! IFF (Amiga IFF/SVX8/SV16) */
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::SVX_PCM_INT_S8):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::SVX_PCM_INT_S16):

        /*! WAV (NIST Sphere) */
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::NIST_PCM_INT_S8):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::NIST_PCM_INT_S16):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::NIST_PCM_INT_S24):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::NIST_PCM_INT_S32):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::NIST_ULAW):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::NIST_ALAW):

        /*! VOC (Creative Labs) */
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::VOC_PCM_INT_U8):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::VOC_PCM_INT_S16):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::VOC_ULAW):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::VOC_ALAW):

        /*! SF (Berkeley/IRCAM/CARL) */
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::IRCAM_PCM_INT_S16):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::IRCAM_PCM_INT_S32):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::IRCAM_PCM_FLOAT_32):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::IRCAM_ULAW):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::IRCAM_ALAW):

        /*! W64 (SoundFoundry WAVE 64) */
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::W64_PCM_INT_U8):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::W64_PCM_INT_S16):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::W64_PCM_INT_S24):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::W64_PCM_INT_S32):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::W64_PCM_FLOAT_32):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::W64_PCM_FLOAT_64):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::W64_ULAW):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::W64_ALAW):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::W64_IMA_ADPCM):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::W64_MS_ADPCM):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::W64_GSM610):

        /*! MAT4 (GNU Octave 2.0 / Matlab 4.2) */
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::MAT4_PCM_INT_S16):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::MAT4_PCM_INT_S32):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::MAT4_PCM_FLOAT_32):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::MAT4_PCM_FLOAT_64):

        /*! MAT5 (GNU Octave 2.1 / Matlab 5.0) */
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::MAT5_PCM_INT_U8):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::MAT5_PCM_INT_S16):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::MAT5_PCM_INT_S32):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::MAT5_PCM_FLOAT_32):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::MAT5_PCM_FLOAT_64):

        /*! PVF (Portable Voice Format) */
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::PVF_PCM_INT_S8):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::PVF_PCM_INT_S16):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::PVF_PCM_INT_S32):

        /*! XI (FastTracker 2) */
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::XI_DPCM_8):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::XI_DPCM_16):

        /*! HTK (HMM Tool Kit) */
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::HTK_PCM_INT_S16):

        /*! SDS (Midi Sample Dump Standard) */
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::SDS_PCM_INT_S8):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::SDS_PCM_INT_S16):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::SDS_PCM_INT_S24):

        /*! AVR (Audio Visual Research) */
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::AVR_PCM_INT_U8):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::AVR_PCM_INT_S8):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::AVR_PCM_INT_S16):

        /*! WAVEX (Microsoft) */
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::WAVEX_PCM_INT_U8):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::WAVEX_PCM_INT_S16):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::WAVEX_PCM_INT_S24):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::WAVEX_PCM_INT_S32):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::WAVEX_PCM_FLOAT_32):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::WAVEX_PCM_FLOAT_64):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::WAVEX_ULAW):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::WAVEX_ALAW):

        /*! SD2 (Sound Designer II) */
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::SD2_PCM_INT_S8):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::SD2_PCM_INT_S16):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::SD2_PCM_INT_S24):

        /*! CAF (Apple Core Audio File) */
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::CAF_PCM_INT_S8):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::CAF_PCM_INT_S16):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::CAF_PCM_INT_S24):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::CAF_PCM_INT_S32):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::CAF_PCM_FLOAT_32):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::CAF_PCM_FLOAT_64):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::CAF_ULAW):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::CAF_ALAW):

        /*! WVE (Psion Series 3) */
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::WVE_ALAW):

        /*! MPC (Akai MPC 2k) */
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::MPC2K_PCM_INT_S16):

        /*! RF64 (RIFF 64) */
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::RF64_PCM_INT_U8):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::RF64_PCM_INT_S16):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::RF64_PCM_INT_S24):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::RF64_PCM_INT_S32):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::RF64_PCM_FLOAT_32):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::RF64_PCM_FLOAT_64):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::RF64_ULAW):
        case static_cast<SNDFILE_ENCODER_OUTPUT_FORMAT_DATA_TYPE>(OutputFormat::RF64_ALAW):
            break;
        default:
            throw core::InvalidArgumentException("SndFileEncoderProfile", "Invalid output format");
    }

    this->output_format = static_cast<OutputFormat>(output_format);
}

unsigned int rusty::codecs::SndFileEncoderProfile::GetOptionsCount(void) const
{
    return sizeof(options_and_selections) / sizeof(std::vector<const char *>);
}

std::string rusty::codecs::SndFileEncoderProfile::GetOptionsInString(unsigned int option_index) const
{
    return options_and_selections[option_index][0];
}

void rusty::codecs::SndFileEncoderProfile::GetCurrentValueForOptionInString(unsigned int option_index, std::string &option_value) const
{
    std::string option_text(options_and_selections[option_index][0]);

    GetCurrentValueForOptionInString(option_text, option_value);
}

void rusty::codecs::SndFileEncoderProfile::GetCurrentValueForOptionInString(std::string &option_text, std::string &option_value) const
{
    Option option = text_to_option.at(option_text);

    switch(option)
    {
        case Option::OUPTPUT_FORMAT:
            option_value = output_format_to_text.at(output_format);
            break;
    }
}

unsigned int rusty::codecs::SndFileEncoderProfile::GetSelectionCountForOption(unsigned int option_index) const
{
    return static_cast<unsigned int>(options_and_selections[option_index].size() - 1);
}

std::string rusty::codecs::SndFileEncoderProfile::GetSelectionForOptionInString(unsigned int option_index, unsigned int selection_index) const
{
    return options_and_selections[option_index][selection_index + 1];
}

void rusty::codecs::SndFileEncoderProfile::SetValueForOption(unsigned int option_index, std::string &value)
{
    std::string option_text(options_and_selections[option_index][0]);

    SetValueForOption(option_text, value);
}

void rusty::codecs::SndFileEncoderProfile::SetValueForOption(std::string &option_text, std::string &value)
{
    Option option = text_to_option.at(option_text);

    switch(option)
    {
        case Option::OUPTPUT_FORMAT:
            output_format = text_to_output_format.at(value);
            break;
    }
}
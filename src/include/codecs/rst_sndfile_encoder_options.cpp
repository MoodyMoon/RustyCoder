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
#include "rst_sndfile_encoder_options.h"

const std::map<const SndFileEncoderOptions::OutputFormat, std::string> SndFileEncoderOptions::output_format_to_file_extension =
{
    /*! WAV (Microsoft) */
    {OutputFormat::WAV_PCM_INT_U8, "wav"},
    {OutputFormat::WAV_PCM_INT_S16, "wav"},
    {OutputFormat::WAV_PCM_INT_S24, "wav"},
    {OutputFormat::WAV_PCM_INT_S32, "wav"},
    {OutputFormat::WAV_PCM_FLOAT_32, "wav"},
    {OutputFormat::WAV_PCM_FLOAT_64, "wav"},
    {OutputFormat::WAV_ULAW, "wav"},
    {OutputFormat::WAV_ALAW, "wav"},
    {OutputFormat::WAV_IMA_ADPACM, "wav"},
    {OutputFormat::WAV_MS_ADPACM, "wav"},
    {OutputFormat::WAV_GSM610, "wav"},
    {OutputFormat::WAV_G721_32_ADPCM, "wav"},

    /*! AIFF (Apple/SGI) */
    {OutputFormat::AIFF_PCM_INT_U8, "aiff"},
    {OutputFormat::AIFF_PCM_INT_S8, "aiff"},
    {OutputFormat::AIFF_PCM_INT_S16, "aiff"},
    {OutputFormat::AIFF_PCM_INT_S24, "aiff"},
    {OutputFormat::AIFF_PCM_INT_S32, "aiff"},
    {OutputFormat::AIFF_PCM_FLOAT_32, "aifc"},
    {OutputFormat::AIFF_PCM_FLOAT_64, "aiff"},
    {OutputFormat::AIFF_ULAW, "aiff"},
    {OutputFormat::AIFF_ALAW, "aiff"},
    {OutputFormat::AIFF_IMA_ADPCM, "aiff"},
    {OutputFormat::AIFF_GSM610, "aiff"},
    {OutputFormat::AIFF_DWVW_12, "aiff"},
    {OutputFormat::AIFF_DWVW_16, "aiff"},
    {OutputFormat::AIFF_DWVW_24, "aiff"},

    /*! AU (Sun/NeXT) */
    {OutputFormat::AU_PCM_INT_S8, "au"},
    {OutputFormat::AU_PCM_INT_S16, "au"},
    {OutputFormat::AU_PCM_INT_S24, "au"},
    {OutputFormat::AU_PCM_INT_S32, "au"},
    {OutputFormat::AU_PCM_FLOAT_32, "au"},
    {OutputFormat::AU_PCM_FLOAT_64, "au"},
    {OutputFormat::AU_ULAW, "au"},
    {OutputFormat::AU_ALAW, "au"},
    {OutputFormat::AU_G721_32_ADPCM, "au"},
    {OutputFormat::AU_G723_24_ADPCM, "au"},
    {OutputFormat::AU_G723_40_ADPCM, "au"},

    /*! PAF (Ensoniq PARIS) */
    {OutputFormat::PAF_PCM_INT_S8, "paf"},
    {OutputFormat::PAF_PCM_INT_S16, "paf"},
    {OutputFormat::PAF_PCM_INT_S24, "paf"},

    /*! IFF (Amiga IFF/SVX8/SV16) */
    {OutputFormat::SVX_PCM_INT_S8, "iff"},
    {OutputFormat::SVX_PCM_INT_S16, "iff"},

    /*! WAV (NIST Sphere) */
    {OutputFormat::NIST_PCM_INT_S8, "wav"},
    {OutputFormat::NIST_PCM_INT_S16, "wav"},
    {OutputFormat::NIST_PCM_INT_S24, "wav"},
    {OutputFormat::NIST_PCM_INT_S32, "wav"},
    {OutputFormat::NIST_ULAW, "wav"},
    {OutputFormat::NIST_ALAW, "wav"},

    /*! VOC (Creative Labs) */
    {OutputFormat::VOC_PCM_INT_U8, "voc"},
    {OutputFormat::VOC_PCM_INT_S16, "voc"},
    {OutputFormat::VOC_ULAW, "voc"},
    {OutputFormat::VOC_ALAW, "voc"},

    /*! SF (Berkeley/IRCAM/CARL) */
    {OutputFormat::IRCAM_PCM_INT_S16, "sf"},
    {OutputFormat::IRCAM_PCM_INT_S32, "sf"},
    {OutputFormat::IRCAM_PCM_FLOAT_32, "sf"},
    {OutputFormat::IRCAM_ULAW, "sf"},
    {OutputFormat::IRCAM_ALAW, "sf"},

    /*! W64 (SoundFoundry WAVE 64) */
    {OutputFormat::W64_PCM_INT_U8, "w64"},
    {OutputFormat::W64_PCM_INT_S16, "w64"},
    {OutputFormat::W64_PCM_INT_S24, "w64"},
    {OutputFormat::W64_PCM_INT_S32, "w64"},
    {OutputFormat::W64_PCM_FLOAT_32, "w64"},
    {OutputFormat::W64_PCM_FLOAT_64, "w64"},
    {OutputFormat::W64_ULAW, "w64"},
    {OutputFormat::W64_ALAW, "w64"},
    {OutputFormat::W64_IMA_ADPCM, "w64"},
    {OutputFormat::W64_MS_ADPCM, "w64"},
    {OutputFormat::W64_GSM610, "w64"},

    /*! MAT4 (GNU Octave 2.0 / Matlab 4.2) */
    {OutputFormat::MAT4_PCM_INT_S16, "mat"},
    {OutputFormat::MAT4_PCM_INT_S32, "mat"},
    {OutputFormat::MAT4_PCM_FLOAT_32, "mat"},
    {OutputFormat::MAT4_PCM_FLOAT_64, "mat"},

    /*! MAT5 (GNU Octave 2.1 / Matlab 5.0) */
    {OutputFormat::MAT5_PCM_INT_U8, "mat"},
    {OutputFormat::MAT5_PCM_INT_S16, "mat"},
    {OutputFormat::MAT5_PCM_INT_S32, "mat"},
    {OutputFormat::MAT5_PCM_FLOAT_32, "mat"},
    {OutputFormat::MAT5_PCM_FLOAT_64, "mat"},

    /*! PVF (Portable Voice Format) */
    {OutputFormat::PVF_PCM_INT_S8, "pvf"},
    {OutputFormat::PVF_PCM_INT_S16, "pvf"},
    {OutputFormat::PVF_PCM_INT_S32, "pvf"},

    /*! XI (FastTracker 2) */
    {OutputFormat::XI_DPCM_8, "xi"},
    {OutputFormat::XI_DPCM_16, "xi"},

    /*! HTK (HMM Tool Kit) */
    {OutputFormat::HTK_PCM_INT_S16, "htk"},

    /*! SDS (Midi Sample Dump Standard) */
    {OutputFormat::SDS_PCM_INT_S8, "sds"},
    {OutputFormat::SDS_PCM_INT_S16, "sds"},
    {OutputFormat::SDS_PCM_INT_S24, "sds"},

    /*! AVR (Audio Visual Research) */
    {OutputFormat::AVR_PCM_INT_U8, "avr"},
    {OutputFormat::AVR_PCM_INT_S8, "avr"},
    {OutputFormat::AVR_PCM_INT_S16, "avr"},

    /*! WAVEX (Microsoft) */
    {OutputFormat::WAVEX_PCM_INT_U8, "wav"},
    {OutputFormat::WAVEX_PCM_INT_S16, "wav"},
    {OutputFormat::WAVEX_PCM_INT_S24, "wav"},
    {OutputFormat::WAVEX_PCM_INT_S32, "wav"},
    {OutputFormat::WAVEX_PCM_FLOAT_32, "wav"},
    {OutputFormat::WAVEX_PCM_FLOAT_64, "wav"},
    {OutputFormat::WAVEX_ULAW, "wav"},
    {OutputFormat::WAVEX_ALAW, "wav"},

    /*! SD2 (Sound Designer II) */
    {OutputFormat::SD2_PCM_INT_S8, "sd2"},
    {OutputFormat::SD2_PCM_INT_S16, "sd2"},
    {OutputFormat::SD2_PCM_INT_S24, "sd2"},

    /*! CAF (Apple Core Audio File) */
    {OutputFormat::CAF_PCM_INT_S8, "caf"},
    {OutputFormat::CAF_PCM_INT_S16, "caf"},
    {OutputFormat::CAF_PCM_INT_S24, "caf"},
    {OutputFormat::CAF_PCM_INT_S32, "caf"},
    {OutputFormat::CAF_PCM_FLOAT_32, "caf"},
    {OutputFormat::CAF_PCM_FLOAT_64, "caf"},
    {OutputFormat::CAF_ULAW, "caf"},
    {OutputFormat::CAF_ALAW, "caf"},

    /*! WVE (Psion Series 3) */
    {OutputFormat::WVE_ALAW, "wve"},

    /*! MPC (Akai MPC 2k) Do not change the extension to "mpc" to prevent clash with Musepack format extension */
    {OutputFormat::MPC2K_PCM_INT_S16, "ampc"},

    /*! RF64 (RIFF 64) */
    {OutputFormat::RF64_PCM_INT_U8, "rf64"},
    {OutputFormat::RF64_PCM_INT_S16, "rf64"},
    {OutputFormat::RF64_PCM_INT_S24, "rf64"},
    {OutputFormat::RF64_PCM_INT_S32, "rf64"},
    {OutputFormat::RF64_PCM_FLOAT_32, "rf64"},
    {OutputFormat::RF64_PCM_FLOAT_64, "rf64"},
    {OutputFormat::RF64_ULAW, "rf64"},
    {OutputFormat::RF64_ALAW, "rf64"}
};

const char *SndFileEncoderOptions::profile_file_extension = "sndfe";

const std::map<const SndFileEncoderOptions::OutputFormat, std::string> SndFileEncoderOptions::output_format_to_text =
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

const std::map<std::string, const SndFileEncoderOptions::OutputFormat> SndFileEncoderOptions::text_to_output_format =
{
    /*! WAV (Microsoft) */
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::WAV_PCM_INT_U8), OutputFormat::WAV_PCM_INT_U8},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::WAV_PCM_INT_S16), OutputFormat::WAV_PCM_INT_S16},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::WAV_PCM_INT_S24), OutputFormat::WAV_PCM_INT_S24},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::WAV_PCM_INT_S32), OutputFormat::WAV_PCM_INT_S32},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::WAV_PCM_FLOAT_32), OutputFormat::WAV_PCM_FLOAT_32},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::WAV_PCM_FLOAT_64), OutputFormat::WAV_PCM_FLOAT_64},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::WAV_ULAW), OutputFormat::WAV_ULAW},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::WAV_ALAW), OutputFormat::WAV_ALAW},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::WAV_IMA_ADPACM), OutputFormat::WAV_IMA_ADPACM},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::WAV_MS_ADPACM), OutputFormat::WAV_MS_ADPACM},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::WAV_GSM610), OutputFormat::WAV_GSM610},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::WAV_G721_32_ADPCM), OutputFormat::WAV_G721_32_ADPCM},

    /*! AIFF (Apple/SGI) */
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AIFF_PCM_INT_U8), OutputFormat::AIFF_PCM_INT_U8},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AIFF_PCM_INT_S8), OutputFormat::AIFF_PCM_INT_S8},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AIFF_PCM_INT_S16), OutputFormat::AIFF_PCM_INT_S16},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AIFF_PCM_INT_S24), OutputFormat::AIFF_PCM_INT_S24},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AIFF_PCM_INT_S32), OutputFormat::AIFF_PCM_INT_S32},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AIFF_PCM_FLOAT_32), OutputFormat::AIFF_PCM_FLOAT_32},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AIFF_PCM_FLOAT_64), OutputFormat::AIFF_PCM_FLOAT_64},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AIFF_ULAW), OutputFormat::AIFF_ULAW},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AIFF_ALAW), OutputFormat::AIFF_ALAW},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AIFF_IMA_ADPCM), OutputFormat::AIFF_IMA_ADPCM},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AIFF_GSM610), OutputFormat::AIFF_GSM610},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AIFF_DWVW_12), OutputFormat::AIFF_DWVW_12},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AIFF_DWVW_16), OutputFormat::AIFF_DWVW_16},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AIFF_DWVW_24), OutputFormat::AIFF_DWVW_24},

    /*! AU (Sun/NeXT) */
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AU_PCM_INT_S8), OutputFormat::AU_PCM_INT_S8},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AU_PCM_INT_S16), OutputFormat::AU_PCM_INT_S16},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AU_PCM_INT_S24), OutputFormat::AU_PCM_INT_S24},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AU_PCM_INT_S32), OutputFormat::AU_PCM_INT_S32},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AU_PCM_FLOAT_32), OutputFormat::AU_PCM_FLOAT_32},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AU_PCM_FLOAT_64), OutputFormat::AU_PCM_FLOAT_64},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AU_ULAW), OutputFormat::AU_ULAW},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AU_ALAW), OutputFormat::AU_ALAW},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AU_G721_32_ADPCM), OutputFormat::AU_G721_32_ADPCM},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AU_G723_24_ADPCM), OutputFormat::AU_G723_24_ADPCM},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AU_G723_40_ADPCM), OutputFormat::AU_G723_40_ADPCM},

    /*! PAF (Ensoniq PARIS) */
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::PAF_PCM_INT_S8), OutputFormat::PAF_PCM_INT_S8},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::PAF_PCM_INT_S16), OutputFormat::PAF_PCM_INT_S16},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::PAF_PCM_INT_S24), OutputFormat::PAF_PCM_INT_S24},

    /*! IFF (Amiga IFF/SVX8/SV16) */
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::SVX_PCM_INT_S8), OutputFormat::SVX_PCM_INT_S8},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::SVX_PCM_INT_S16), OutputFormat::SVX_PCM_INT_S16},

    /*! WAV (NIST Sphere) */
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::NIST_PCM_INT_S8), OutputFormat::NIST_PCM_INT_S8},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::NIST_PCM_INT_S16), OutputFormat::NIST_PCM_INT_S16},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::NIST_PCM_INT_S24), OutputFormat::NIST_PCM_INT_S24},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::NIST_PCM_INT_S32), OutputFormat::NIST_PCM_INT_S32},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::NIST_ULAW), OutputFormat::NIST_ULAW},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::NIST_ALAW), OutputFormat::NIST_ALAW},

    /*! VOC (Creative Labs) */
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::VOC_PCM_INT_U8), OutputFormat::VOC_PCM_INT_U8},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::VOC_PCM_INT_S16), OutputFormat::VOC_PCM_INT_S16},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::VOC_ULAW), OutputFormat::VOC_ULAW},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::VOC_ALAW), OutputFormat::VOC_ALAW},

    /*! SF (Berkeley/IRCAM/CARL) */
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::IRCAM_PCM_INT_S16), OutputFormat::IRCAM_PCM_INT_S16},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::IRCAM_PCM_INT_S32), OutputFormat::IRCAM_PCM_INT_S32},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::IRCAM_PCM_FLOAT_32), OutputFormat::IRCAM_PCM_FLOAT_32},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::IRCAM_ULAW), OutputFormat::IRCAM_ULAW},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::IRCAM_ALAW), OutputFormat::IRCAM_ALAW},

    /*! W64 (SoundFoundry WAVE 64) */
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::W64_PCM_INT_U8), OutputFormat::W64_PCM_INT_U8},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::W64_PCM_INT_S16), OutputFormat::W64_PCM_INT_S16},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::W64_PCM_INT_S24), OutputFormat::W64_PCM_INT_S24},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::W64_PCM_INT_S32), OutputFormat::W64_PCM_INT_S32},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::W64_PCM_FLOAT_32), OutputFormat::W64_PCM_FLOAT_32},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::W64_PCM_FLOAT_64), OutputFormat::W64_PCM_FLOAT_64},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::W64_ULAW), OutputFormat::W64_ULAW},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::W64_ALAW), OutputFormat::W64_ALAW},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::W64_IMA_ADPCM), OutputFormat::W64_IMA_ADPCM},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::W64_MS_ADPCM), OutputFormat::W64_MS_ADPCM},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::W64_GSM610), OutputFormat::W64_GSM610},

    /*! MAT4 (GNU Octave 2.0 / Matlab 4.2) */
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::MAT4_PCM_INT_S16), OutputFormat::MAT4_PCM_INT_S16},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::MAT4_PCM_INT_S32), OutputFormat::MAT4_PCM_INT_S32},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::MAT4_PCM_FLOAT_32), OutputFormat::MAT4_PCM_FLOAT_32},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::MAT4_PCM_FLOAT_64), OutputFormat::MAT4_PCM_FLOAT_64},

    /*! MAT5 (GNU Octave 2.1 / Matlab 5.0) */
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::MAT5_PCM_INT_U8), OutputFormat::MAT5_PCM_INT_U8},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::MAT5_PCM_INT_S16), OutputFormat::MAT5_PCM_INT_S16},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::MAT5_PCM_INT_S32), OutputFormat::MAT5_PCM_INT_S32},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::MAT5_PCM_FLOAT_32), OutputFormat::MAT5_PCM_FLOAT_32},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::MAT5_PCM_FLOAT_64), OutputFormat::MAT5_PCM_FLOAT_64},

    /*! PVF (Portable Voice Format) */
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::PVF_PCM_INT_S8), OutputFormat::PVF_PCM_INT_S8},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::PVF_PCM_INT_S16), OutputFormat::PVF_PCM_INT_S16},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::PVF_PCM_INT_S32), OutputFormat::PVF_PCM_INT_S32},

    /*! XI (FastTracker 2) */
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::XI_DPCM_8), OutputFormat::XI_DPCM_8},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::XI_DPCM_16), OutputFormat::XI_DPCM_16},

    /*! HTK (HMM Tool Kit) */
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::HTK_PCM_INT_S16), OutputFormat::HTK_PCM_INT_S16},

    /*! SDS (Midi Sample Dump Standard) */
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::SDS_PCM_INT_S8), OutputFormat::SDS_PCM_INT_S8},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::SDS_PCM_INT_S16), OutputFormat::SDS_PCM_INT_S16},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::SDS_PCM_INT_S24), OutputFormat::SDS_PCM_INT_S24},

    /*! AVR (Audio Visual Research) */
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AVR_PCM_INT_U8), OutputFormat::AVR_PCM_INT_U8},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AVR_PCM_INT_S8), OutputFormat::AVR_PCM_INT_S8},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AVR_PCM_INT_S16), OutputFormat::AVR_PCM_INT_S16},

    /*! WAVEX (Microsoft) */
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::WAVEX_PCM_INT_U8), OutputFormat::WAVEX_PCM_INT_U8},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::WAVEX_PCM_INT_S16), OutputFormat::WAVEX_PCM_INT_S16},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::WAVEX_PCM_INT_S24), OutputFormat::WAVEX_PCM_INT_S24},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::WAVEX_PCM_INT_S32), OutputFormat::WAVEX_PCM_INT_S32},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::WAVEX_PCM_FLOAT_32), OutputFormat::WAVEX_PCM_FLOAT_32},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::WAVEX_PCM_FLOAT_64), OutputFormat::WAVEX_PCM_FLOAT_64},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::WAVEX_ULAW), OutputFormat::WAVEX_ULAW},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::WAVEX_ALAW), OutputFormat::WAVEX_ALAW},

    /*! SD2 (Sound Designer II) */
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::SD2_PCM_INT_S8), OutputFormat::SD2_PCM_INT_S8},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::SD2_PCM_INT_S16), OutputFormat::SD2_PCM_INT_S16},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::SD2_PCM_INT_S24), OutputFormat::SD2_PCM_INT_S24},

    /*! CAF (Apple Core Audio File) */
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::CAF_PCM_INT_S8), OutputFormat::CAF_PCM_INT_S8},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::CAF_PCM_INT_S16), OutputFormat::CAF_PCM_INT_S16},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::CAF_PCM_INT_S24), OutputFormat::CAF_PCM_INT_S24},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::CAF_PCM_INT_S32), OutputFormat::CAF_PCM_INT_S32},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::CAF_PCM_FLOAT_32), OutputFormat::CAF_PCM_FLOAT_32},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::CAF_PCM_FLOAT_64), OutputFormat::CAF_PCM_FLOAT_64},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::CAF_ULAW), OutputFormat::CAF_ULAW},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::CAF_ALAW), OutputFormat::CAF_ALAW},

    /*! WVE (Psion Series 3) */
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::WVE_ALAW), OutputFormat::WVE_ALAW},

    /*! MPC (Akai MPC 2k) */
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::MPC2K_PCM_INT_S16), OutputFormat::MPC2K_PCM_INT_S16},

    /*! RF64 (RIFF 64) */
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::RF64_PCM_INT_U8), OutputFormat::RF64_PCM_INT_U8},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::RF64_PCM_INT_S16), OutputFormat::RF64_PCM_INT_S16},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::RF64_PCM_INT_S24), OutputFormat::RF64_PCM_INT_S24},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::RF64_PCM_INT_S32), OutputFormat::RF64_PCM_INT_S32},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::RF64_PCM_FLOAT_32), OutputFormat::RF64_PCM_FLOAT_32},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::RF64_PCM_FLOAT_64), OutputFormat::RF64_PCM_FLOAT_64},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::RF64_ULAW), OutputFormat::RF64_ULAW},
    {SndFileEncoderOptions::output_format_to_text.at(OutputFormat::RF64_ALAW), OutputFormat::RF64_ALAW}
};

const std::map<const SndFileEncoderOptions::Option, std::string> SndFileEncoderOptions::option_to_text =
{
    {Option::OUPTPUT_FORMAT, "Output format"}
};

const std::map<std::string, const SndFileEncoderOptions::Option> SndFileEncoderOptions::text_to_option =
{
    {SndFileEncoderOptions::option_to_text.at(Option::OUPTPUT_FORMAT), Option::OUPTPUT_FORMAT}
};

const std::vector<std::string> SndFileEncoderOptions::options_and_selections[1] =
{
    {
        SndFileEncoderOptions::option_to_text.at(Option::OUPTPUT_FORMAT),
        /*! WAV (Microsoft) */
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::WAV_PCM_INT_U8),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::WAV_PCM_INT_S16),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::WAV_PCM_INT_S24),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::WAV_PCM_INT_S32),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::WAV_PCM_FLOAT_32),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::WAV_PCM_FLOAT_64),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::WAV_ULAW),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::WAV_ALAW),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::WAV_IMA_ADPACM),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::WAV_MS_ADPACM),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::WAV_GSM610),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::WAV_G721_32_ADPCM),

        /*! AIFF (Apple/SGI) */
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AIFF_PCM_INT_U8),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AIFF_PCM_INT_S8),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AIFF_PCM_INT_S16),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AIFF_PCM_INT_S24),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AIFF_PCM_INT_S32),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AIFF_PCM_FLOAT_32),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AIFF_PCM_FLOAT_64),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AIFF_ULAW),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AIFF_ALAW),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AIFF_IMA_ADPCM),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AIFF_GSM610),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AIFF_DWVW_12),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AIFF_DWVW_16),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AIFF_DWVW_24),

        /*! AU (Sun/NeXT) */
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AU_PCM_INT_S8),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AU_PCM_INT_S16),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AU_PCM_INT_S24),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AU_PCM_INT_S32),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AU_PCM_FLOAT_32),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AU_PCM_FLOAT_64),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AU_ULAW),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AU_ALAW),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AU_G721_32_ADPCM),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AU_G723_24_ADPCM),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AU_G723_40_ADPCM),

        /*! PAF (Ensoniq PARIS) */
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::PAF_PCM_INT_S8),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::PAF_PCM_INT_S16),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::PAF_PCM_INT_S24),

        /*! IFF (Amiga IFF/SVX8/SV16) */
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::SVX_PCM_INT_S8),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::SVX_PCM_INT_S16),

        /*! WAV (NIST Sphere) */
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::NIST_PCM_INT_S8),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::NIST_PCM_INT_S16),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::NIST_PCM_INT_S24),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::NIST_PCM_INT_S32),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::NIST_ULAW),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::NIST_ALAW),

        /*! VOC (Creative Labs) */
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::VOC_PCM_INT_U8),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::VOC_PCM_INT_S16),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::VOC_ULAW),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::VOC_ALAW),

        /*! SF (Berkeley/IRCAM/CARL) */
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::IRCAM_PCM_INT_S16),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::IRCAM_PCM_INT_S32),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::IRCAM_PCM_FLOAT_32),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::IRCAM_ULAW),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::IRCAM_ALAW),

        /*! W64 (SoundFoundry WAVE 64) */
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::W64_PCM_INT_U8),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::W64_PCM_INT_S16),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::W64_PCM_INT_S24),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::W64_PCM_INT_S32),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::W64_PCM_FLOAT_32),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::W64_PCM_FLOAT_64),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::W64_ULAW),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::W64_ALAW),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::W64_IMA_ADPCM),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::W64_MS_ADPCM),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::W64_GSM610),

        /*! MAT4 (GNU Octave 2.0 / Matlab 4.2) */
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::MAT4_PCM_INT_S16),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::MAT4_PCM_INT_S32),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::MAT4_PCM_FLOAT_32),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::MAT4_PCM_FLOAT_64),

        /*! MAT5 (GNU Octave 2.1 / Matlab 5.0) */
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::MAT5_PCM_INT_U8),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::MAT5_PCM_INT_S16),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::MAT5_PCM_INT_S32),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::MAT5_PCM_FLOAT_32),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::MAT5_PCM_FLOAT_64),

        /*! PVF (Portable Voice Format) */
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::PVF_PCM_INT_S8),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::PVF_PCM_INT_S16),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::PVF_PCM_INT_S32),

        /*! XI (FastTracker 2) */
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::XI_DPCM_8),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::XI_DPCM_16),

        /*! HTK (HMM Tool Kit) */
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::HTK_PCM_INT_S16),

        /*! SDS (Midi Sample Dump Standard) */
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::SDS_PCM_INT_S8),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::SDS_PCM_INT_S16),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::SDS_PCM_INT_S24),

        /*! AVR (Audio Visual Research) */
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AVR_PCM_INT_U8),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AVR_PCM_INT_S8),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::AVR_PCM_INT_S16),

        /*! WAVEX (Microsoft) */
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::WAVEX_PCM_INT_U8),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::WAVEX_PCM_INT_S16),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::WAVEX_PCM_INT_S24),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::WAVEX_PCM_INT_S32),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::WAVEX_PCM_FLOAT_32),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::WAVEX_PCM_FLOAT_64),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::WAVEX_ULAW),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::WAVEX_ALAW),

        /*! SD2 (Sound Designer II) */
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::SD2_PCM_INT_S8),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::SD2_PCM_INT_S16),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::SD2_PCM_INT_S24),

        /*! CAF (Apple Core Audio File) */
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::CAF_PCM_INT_S8),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::CAF_PCM_INT_S16),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::CAF_PCM_INT_S24),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::CAF_PCM_INT_S32),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::CAF_PCM_FLOAT_32),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::CAF_PCM_FLOAT_64),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::CAF_ULAW),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::CAF_ALAW),

        /*! WVE (Psion Series 3) */
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::WVE_ALAW),

        /*! MPC (Akai MPC 2k) */
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::MPC2K_PCM_INT_S16),

        /*! RF64 (RIFF 64) */
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::RF64_PCM_INT_U8),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::RF64_PCM_INT_S16),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::RF64_PCM_INT_S24),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::RF64_PCM_INT_S32),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::RF64_PCM_FLOAT_32),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::RF64_PCM_FLOAT_64),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::RF64_ULAW),
        SndFileEncoderOptions::output_format_to_text.at(OutputFormat::RF64_ALAW)
    }
};

SndFileEncoderOptions::SndFileEncoderOptions(void)
{
    LoadDefaultProfile(Profile::DEFAULT);
}

void SndFileEncoderOptions::LoadDefaultProfile(Profile default_profile)
{
    switch(default_profile)
    {
        case DEFAULT:
        {
            output_format = OutputFormat::WAV_PCM_FLOAT_32;
            break;
        }
    }
}

void SndFileEncoderOptions::SetOutputFormat(uint32_t output_format)
{
    switch(output_format)
    {
        /*! WAV (Microsoft) */
        case OutputFormat::WAV_PCM_INT_U8:
        case OutputFormat::WAV_PCM_INT_S16:
        case OutputFormat::WAV_PCM_INT_S24:
        case OutputFormat::WAV_PCM_INT_S32:
        case OutputFormat::WAV_PCM_FLOAT_32:
        case OutputFormat::WAV_PCM_FLOAT_64:
        case OutputFormat::WAV_ULAW:
        case OutputFormat::WAV_ALAW:
        case OutputFormat::WAV_IMA_ADPACM:
        case OutputFormat::WAV_MS_ADPACM:
        case OutputFormat::WAV_GSM610:
        case OutputFormat::WAV_G721_32_ADPCM:

            /*! AIFF (Apple/SGI) */
        case OutputFormat::AIFF_PCM_INT_U8:
        case OutputFormat::AIFF_PCM_INT_S8:
        case OutputFormat::AIFF_PCM_INT_S16:
        case OutputFormat::AIFF_PCM_INT_S24:
        case OutputFormat::AIFF_PCM_INT_S32:
        case OutputFormat::AIFF_PCM_FLOAT_32:
        case OutputFormat::AIFF_PCM_FLOAT_64:
        case OutputFormat::AIFF_ULAW:
        case OutputFormat::AIFF_ALAW:
        case OutputFormat::AIFF_IMA_ADPCM:
        case OutputFormat::AIFF_GSM610:
        case OutputFormat::AIFF_DWVW_12:
        case OutputFormat::AIFF_DWVW_16:
        case OutputFormat::AIFF_DWVW_24:

            /*! AU (Sun/NeXT) */
        case OutputFormat::AU_PCM_INT_S8:
        case OutputFormat::AU_PCM_INT_S16:
        case OutputFormat::AU_PCM_INT_S24:
        case OutputFormat::AU_PCM_INT_S32:
        case OutputFormat::AU_PCM_FLOAT_32:
        case OutputFormat::AU_PCM_FLOAT_64:
        case OutputFormat::AU_ULAW:
        case OutputFormat::AU_ALAW:
        case OutputFormat::AU_G721_32_ADPCM:
        case OutputFormat::AU_G723_24_ADPCM:
        case OutputFormat::AU_G723_40_ADPCM:

            /*! PAF (Ensoniq PARIS) */
        case OutputFormat::PAF_PCM_INT_S8:
        case OutputFormat::PAF_PCM_INT_S16:
        case OutputFormat::PAF_PCM_INT_S24:

            /*! IFF (Amiga IFF/SVX8/SV16) */
        case OutputFormat::SVX_PCM_INT_S8:
        case OutputFormat::SVX_PCM_INT_S16:

            /*! WAV (NIST Sphere) */
        case OutputFormat::NIST_PCM_INT_S8:
        case OutputFormat::NIST_PCM_INT_S16:
        case OutputFormat::NIST_PCM_INT_S24:
        case OutputFormat::NIST_PCM_INT_S32:
        case OutputFormat::NIST_ULAW:
        case OutputFormat::NIST_ALAW:

            /*! VOC (Creative Labs) */
        case OutputFormat::VOC_PCM_INT_U8:
        case OutputFormat::VOC_PCM_INT_S16:
        case OutputFormat::VOC_ULAW:
        case OutputFormat::VOC_ALAW:

            /*! SF (Berkeley/IRCAM/CARL) */
        case OutputFormat::IRCAM_PCM_INT_S16:
        case OutputFormat::IRCAM_PCM_INT_S32:
        case OutputFormat::IRCAM_PCM_FLOAT_32:
        case OutputFormat::IRCAM_ULAW:
        case OutputFormat::IRCAM_ALAW:

            /*! W64 (SoundFoundry WAVE 64) */
        case OutputFormat::W64_PCM_INT_U8:
        case OutputFormat::W64_PCM_INT_S16:
        case OutputFormat::W64_PCM_INT_S24:
        case OutputFormat::W64_PCM_INT_S32:
        case OutputFormat::W64_PCM_FLOAT_32:
        case OutputFormat::W64_PCM_FLOAT_64:
        case OutputFormat::W64_ULAW:
        case OutputFormat::W64_ALAW:
        case OutputFormat::W64_IMA_ADPCM:
        case OutputFormat::W64_MS_ADPCM:
        case OutputFormat::W64_GSM610:

            /*! MAT4 (GNU Octave 2.0 / Matlab 4.2) */
        case OutputFormat::MAT4_PCM_INT_S16:
        case OutputFormat::MAT4_PCM_INT_S32:
        case OutputFormat::MAT4_PCM_FLOAT_32:
        case OutputFormat::MAT4_PCM_FLOAT_64:

            /*! MAT5 (GNU Octave 2.1 / Matlab 5.0) */
        case OutputFormat::MAT5_PCM_INT_U8:
        case OutputFormat::MAT5_PCM_INT_S16:
        case OutputFormat::MAT5_PCM_INT_S32:
        case OutputFormat::MAT5_PCM_FLOAT_32:
        case OutputFormat::MAT5_PCM_FLOAT_64:

            /*! PVF (Portable Voice Format) */
        case OutputFormat::PVF_PCM_INT_S8:
        case OutputFormat::PVF_PCM_INT_S16:
        case OutputFormat::PVF_PCM_INT_S32:

            /*! XI (FastTracker 2) */
        case OutputFormat::XI_DPCM_8:
        case OutputFormat::XI_DPCM_16:

            /*! HTK (HMM Tool Kit) */
        case OutputFormat::HTK_PCM_INT_S16:

            /*! SDS (Midi Sample Dump Standard) */
        case OutputFormat::SDS_PCM_INT_S8:
        case OutputFormat::SDS_PCM_INT_S16:
        case OutputFormat::SDS_PCM_INT_S24:

            /*! AVR (Audio Visual Research) */
        case OutputFormat::AVR_PCM_INT_U8:
        case OutputFormat::AVR_PCM_INT_S8:
        case OutputFormat::AVR_PCM_INT_S16:

            /*! WAVEX (Microsoft) */
        case OutputFormat::WAVEX_PCM_INT_U8:
        case OutputFormat::WAVEX_PCM_INT_S16:
        case OutputFormat::WAVEX_PCM_INT_S24:
        case OutputFormat::WAVEX_PCM_INT_S32:
        case OutputFormat::WAVEX_PCM_FLOAT_32:
        case OutputFormat::WAVEX_PCM_FLOAT_64:
        case OutputFormat::WAVEX_ULAW:
        case OutputFormat::WAVEX_ALAW:

            /*! SD2 (Sound Designer II) */
        case OutputFormat::SD2_PCM_INT_S8:
        case OutputFormat::SD2_PCM_INT_S16:
        case OutputFormat::SD2_PCM_INT_S24:

            /*! CAF (Apple Core Audio File) */
        case OutputFormat::CAF_PCM_INT_S8:
        case OutputFormat::CAF_PCM_INT_S16:
        case OutputFormat::CAF_PCM_INT_S24:
        case OutputFormat::CAF_PCM_INT_S32:
        case OutputFormat::CAF_PCM_FLOAT_32:
        case OutputFormat::CAF_PCM_FLOAT_64:
        case OutputFormat::CAF_ULAW:
        case OutputFormat::CAF_ALAW:

            /*! WVE (Psion Series 3) */
        case OutputFormat::WVE_ALAW:

            /*! MPC (Akai MPC 2k) */
        case OutputFormat::MPC2K_PCM_INT_S16:

            /*! RF64 (RIFF 64) */
        case OutputFormat::RF64_PCM_INT_U8:
        case OutputFormat::RF64_PCM_INT_S16:
        case OutputFormat::RF64_PCM_INT_S24:
        case OutputFormat::RF64_PCM_INT_S32:
        case OutputFormat::RF64_PCM_FLOAT_32:
        case OutputFormat::RF64_PCM_FLOAT_64:
        case OutputFormat::RF64_ULAW:
        case OutputFormat::RF64_ALAW:
            break;
        default:
            throw InvalidArgumentException("SndFileEncoderOptions", "Invalid output format");
    }

    this->output_format = static_cast<OutputFormat>(output_format);
}

unsigned int SndFileEncoderOptions::GetOptionsCount(void) const
{
    return sizeof(options_and_selections) / sizeof(std::vector<const char *>);
}

std::string SndFileEncoderOptions::GetOptionsInString(unsigned int option_index) const
{
    return options_and_selections[option_index][0];
}

void SndFileEncoderOptions::GetCurrentValueForOptionInString(unsigned int option_index, std::string &option_value) const
{
    std::string option_text(options_and_selections[option_index][0]);

    GetCurrentValueForOptionInString(option_text, option_value);
}

void SndFileEncoderOptions::GetCurrentValueForOptionInString(std::string &option_text, std::string &option_value) const
{
    Option option = text_to_option.at(option_text);

    switch(option)
    {
        case Option::OUPTPUT_FORMAT:
            option_value = output_format_to_text.at(output_format);
            break;
    }
}

unsigned int SndFileEncoderOptions::GetSelectionCountForOption(unsigned int option_index) const
{
    return static_cast<unsigned int>(options_and_selections[option_index].size() - 1);
}

std::string SndFileEncoderOptions::GetSelectionForOptionInString(unsigned int option_index, unsigned int selection_index) const
{
    return options_and_selections[option_index][selection_index + 1];
}

void SndFileEncoderOptions::SetValueForOption(unsigned int option_index, std::string &value)
{
    std::string option_text(options_and_selections[option_index][0]);

    SetValueForOption(option_text, value);
}

void SndFileEncoderOptions::SetValueForOption(std::string &option_text, std::string &value)
{
    Option option = text_to_option.at(option_text);

    switch(option)
    {
        case Option::OUPTPUT_FORMAT:
            output_format = text_to_output_format.at(value);
            break;
    }
}
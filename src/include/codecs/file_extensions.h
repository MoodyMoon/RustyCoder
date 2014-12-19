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

#ifndef CODECS_FILE_EXTENSION_H
#define CODECS_FILE_EXTENSION_H

#define AUDIO_EXTENSION_DESCRIPTION_AUDIO_INTERCHANGE "Audio Interchange File Format"
#define AUDIO_EXTENSION_AIF "aif"
#define AUDIO_EXTENSION_AIFC "aifc"
#define AUDIO_EXTENSION_AIFF "aiff"

#define AUDIO_EXTENSION_DESCRIPTION_AKAI_MPC_2000 "Akai MPC 2000 Format"
#define AUDIO_EXTENSION_AMPC "ampc"

#define AUDIO_EXTENSION_DESCRIPTION_SUN_MICROSYSTEM "Sun Microsystem Audio Format"
#define AUDIO_EXTENSION_AU "au"

#define AUDIO_EXTENSION_DESCRIPTION_AUDIO_VISUAL_RESEARCH "Audio Visual Research Format"
#define AUDIO_EXTENSION_AVR "avr"

#define AUDIO_EXTENSION_DESCRIPTION_APPLE_CORE "Apple Core Audio File"
#define AUDIO_EXTENSION_CAF "caf"

#define AUDIO_EXTENSION_DESCRIPTION_HIDDEN_MARKOV_MODEL_TOOLKIT "Hidden Markov Model Toolkit Speech Recognition Format"
#define AUDIO_EXTENSION_HTK "htk"

#define AUDIO_EXTENSION_DESCRIPTION_AMIGA "Amiga Audio Format"
#define AUDIO_EXTENSION_IFF "iff"

#define AUDIO_EXTENSION_DESCRIPTION_GNU_OCTAVE_MATLAB "GNU Octave File / Matlab File"
#define AUDIO_EXTENSION_MAT "mat"

#define AUDIO_EXTENSION_DESCRIPTION_MPEG_AUDIO_LAYER_1 "MPEG Audio Layer I"
#define AUDIO_EXTENSION_MP1 "mp1"

#define AUDIO_EXTENSION_DESCRIPTION_MPEG_AUDIO_LAYER_2 "MPEG Audio Layer II"
#define AUDIO_EXTENSION_MP2 "mp2"

#define AUDIO_EXTENSION_DESCRIPTION_MPEG_AUDIO_LAYER_3 "MPEG Audio Layer III"
#define AUDIO_EXTENSION_MP3 "mp3"

#define AUDIO_EXTENSION_DESCRIPTION_ENSONIQ_PARIS "Ensoniq PARIS Audio Format"
#define AUDIO_EXTENSION_PAF "paf"

#define AUDIO_EXTENSION_DESCRIPTION_PORTABLE_VOICE "Portable Voice Format"
#define AUDIO_EXTENSION_PVF "pvf"

#define AUDIO_EXTENSION_DESCRIPTION_RIFF_64 "RIFF 64"
#define AUDIO_EXTENSION_RF64 "rf64"

#define AUDIO_EXTENSION_DESCRIPTION_SOUND_DESIGNER_II "Sound Designer II Audio File"
#define AUDIO_EXTENSION_SD2 "sd2"

#define AUDIO_EXTENSION_DESCRIPTION_MIDI_SAMPLE_DUMP "MIDI Sample Dump Standard Format"
#define AUDIO_EXTENSION_SDS "sds"

#define AUDIO_EXTENSION_DESCRIPTION_BERKELEY_IRCAM "Berkeley IRCAM CARL Sound File"
#define AUDIO_EXTENSION_SF "sf"

#define AUDIO_EXTENSION_DESCRIPTION_CREATIVE_LABS "Creative Labs Audio Format"
#define AUDIO_EXTENSION_VOC "voc"

#define AUDIO_EXTENSION_DESCRIPTION_WAV "WAV"
#define AUDIO_EXTENSION_WAV "wav"

#define AUDIO_EXTENSION_DESCRPTION_SOUNDFOUNDRY_WAVE_64 "SoundFoundry WAVE 64"
#define AUDIO_EXTENSION_W64 "w64"

#define AUDIO_EXTENSION_DESCRIPTION_PSION_SERIES_3 "Psion Series 3"
#define AUDIO_EXTENSION_WVE "wve"

#define AUDIO_EXTENSION_DESCRIPTION_FASTTRACKER "FastTracker's Extended Instrument"
#define AUDIO_EXTENSION_XI "xi"

#define PROFILE_EXTENSION_DESCRIPTION_LAME "LAME Profile"
#define PROFILE_EXTENSION_LAME "lame"

#define PROFILE_EXTENSION_DESCRIPTION_SNDFILEENCODER "Libsndfile Encoder Profile"
#define PROFILE_EXTENSION_SNDFILEENCODER "sndfe"

#define AUDIO_EXTENSION_DESCRIPTION_AUDIO_INTERCHANGE_W             WIDEN_STRING(AUDIO_EXTENSION_DESCRIPTION_AUDIO_INTERCHANGE)
#define AUDIO_EXTENSION_AIF_W                                       WIDEN_STRING(AUDIO_EXTENSION_AIF)
#define AUDIO_EXTENSION_AIFC_W                                      WIDEN_STRING(AUDIO_EXTENSION_AIFC)
#define AUDIO_EXTENSION_AIFF_W                                      WIDEN_STRING(AUDIO_EXTENSION_AIFF)

#define AUDIO_EXTENSION_DESCRIPTION_AKAI_MPC_2000_W                 WIDEN_STRING(AUDIO_EXTENSION_DESCRIPTION_AKAI_MPC_2000)
#define AUDIO_EXTENSION_AMPC_W                                      WIDEN_STRING(AUDIO_EXTENSION_AMPC)

#define AUDIO_EXTENSION_DESCRIPTION_SUN_MICROSYSTEM_W               WIDEN_STRING(AUDIO_EXTENSION_DESCRIPTION_SUN_MICROSYSTEM)
#define AUDIO_EXTENSION_AU_W                                        WIDEN_STRING(AUDIO_EXTENSION_AU)

#define AUDIO_EXTENSION_DESCRIPTION_AUDIO_VISUAL_RESEARCH_W         WIDEN_STRING(AUDIO_EXTENSION_DESCRIPTION_AUDIO_VISUAL_RESEARCH)
#define AUDIO_EXTENSION_AVR_W                                       WIDEN_STRING(AUDIO_EXTENSION_AVR)

#define AUDIO_EXTENSION_DESCRIPTION_APPLE_CORE_W                    WIDEN_STRING(AUDIO_EXTENSION_DESCRIPTION_APPLE_CORE)
#define AUDIO_EXTENSION_CAF_W                                       WIDEN_STRING(AUDIO_EXTENSION_CAF)

#define AUDIO_EXTENSION_DESCRIPTION_HIDDEN_MARKOV_MODEL_TOOLKIT_W   WIDEN_STRING(AUDIO_EXTENSION_DESCRIPTION_HIDDEN_MARKOV_MODEL_TOOLKIT)
#define AUDIO_EXTENSION_HTK_W                                       WIDEN_STRING(AUDIO_EXTENSION_HTK)

#define AUDIO_EXTENSION_DESCRIPTION_AMIGA_W                         WIDEN_STRING(AUDIO_EXTENSION_DESCRIPTION_AMIGA)
#define AUDIO_EXTENSION_IFF_W                                       WIDEN_STRING(AUDIO_EXTENSION_IFF)

#define AUDIO_EXTENSION_DESCRIPTION_GNU_OCTAVE_MATLAB_W             WIDEN_STRING(AUDIO_EXTENSION_DESCRIPTION_GNU_OCTAVE_MATLAB)
#define AUDIO_EXTENSION_MAT_W                                       WIDEN_STRING(AUDIO_EXTENSION_MAT)

#define AUDIO_EXTENSION_DESCRIPTION_MPEG_AUDIO_LAYER_1_W            WIDEN_STRING(AUDIO_EXTENSION_DESCRIPTION_MPEG_AUDIO_LAYER_1)
#define AUDIO_EXTENSION_MP1_W                                       WIDEN_STRING(AUDIO_EXTENSION_MP1)

#define AUDIO_EXTENSION_DESCRIPTION_MPEG_AUDIO_LAYER_2_W            WIDEN_STRING(AUDIO_EXTENSION_DESCRIPTION_MPEG_AUDIO_LAYER_2)
#define AUDIO_EXTENSION_MP2_W                                       WIDEN_STRING(AUDIO_EXTENSION_MP2)

#define AUDIO_EXTENSION_DESCRIPTION_MPEG_AUDIO_LAYER_3_W            WIDEN_STRING(AUDIO_EXTENSION_DESCRIPTION_MPEG_AUDIO_LAYER_3)
#define AUDIO_EXTENSION_MP3_W                                       WIDEN_STRING(AUDIO_EXTENSION_MP3)

#define AUDIO_EXTENSION_DESCRIPTION_ENSONIQ_PARIS_W                 WIDEN_STRING(AUDIO_EXTENSION_DESCRIPTION_ENSONIQ_PARIS)
#define AUDIO_EXTENSION_PAF_W                                       WIDEN_STRING(AUDIO_EXTENSION_PAF)

#define AUDIO_EXTENSION_DESCRIPTION_PORTABLE_VOICE_W                WIDEN_STRING(AUDIO_EXTENSION_DESCRIPTION_PORTABLE_VOICE)
#define AUDIO_EXTENSION_PVF_W                                       WIDEN_STRING(AUDIO_EXTENSION_PVF)

#define AUDIO_EXTENSION_DESCRIPTION_RIFF_64_W                       WIDEN_STRING(AUDIO_EXTENSION_DESCRIPTION_RIFF_64)
#define AUDIO_EXTENSION_RF64_W                                      WIDEN_STRING(AUDIO_EXTENSION_RF64)

#define AUDIO_EXTENSION_DESCRIPTION_SOUND_DESIGNER_II_W             WIDEN_STRING(AUDIO_EXTENSION_DESCRIPTION_SOUND_DESIGNER_II)
#define AUDIO_EXTENSION_SD2_W                                       WIDEN_STRING(AUDIO_EXTENSION_SD2)

#define AUDIO_EXTENSION_DESCRIPTION_MIDI_SAMPLE_DUMP_W              WIDEN_STRING(AUDIO_EXTENSION_DESCRIPTION_MIDI_SAMPLE_DUMP)
#define AUDIO_EXTENSION_SDS_W                                       WIDEN_STRING(AUDIO_EXTENSION_SDS)

#define AUDIO_EXTENSION_DESCRIPTION_BERKELEY_IRCAM_W                WIDEN_STRING(AUDIO_EXTENSION_DESCRIPTION_BERKELEY_IRCAM)
#define AUDIO_EXTENSION_SF_W                                        WIDEN_STRING(AUDIO_EXTENSION_SF)

#define AUDIO_EXTENSION_DESCRIPTION_CREATIVE_LABS_W                 WIDEN_STRING(AUDIO_EXTENSION_DESCRIPTION_CREATIVE_LABS)
#define AUDIO_EXTENSION_VOC_W                                       WIDEN_STRING(AUDIO_EXTENSION_VOC)

#define AUDIO_EXTENSION_DESCRIPTION_WAV_W                           WIDEN_STRING(AUDIO_EXTENSION_DESCRIPTION_WAV)
#define AUDIO_EXTENSION_WAV_W                                       WIDEN_STRING(AUDIO_EXTENSION_WAV)

#define AUDIO_EXTENSION_DESCRPTION_SOUNDFOUNDRY_WAVE_64_W           WIDEN_STRING(AUDIO_EXTENSION_DESCRPTION_SOUNDFOUNDRY_WAVE_64)
#define AUDIO_EXTENSION_W64_W                                       WIDEN_STRING(AUDIO_EXTENSION_W64)

#define AUDIO_EXTENSION_DESCRIPTION_PSION_SERIES_3_W                WIDEN_STRING(AUDIO_EXTENSION_DESCRIPTION_PSION_SERIES_3)
#define AUDIO_EXTENSION_WVE_W                                       WIDEN_STRING(AUDIO_EXTENSION_WVE)

#define AUDIO_EXTENSION_DESCRIPTION_FASTTRACKER_W                   WIDEN_STRING(AUDIO_EXTENSION_DESCRIPTION_FASTTRACKER)
#define AUDIO_EXTENSION_XI_W                                        WIDEN_STRING(AUDIO_EXTENSION_XI)

#define PROFILE_EXTENSION_DESCRIPTION_LAME_W                        WIDEN_STRING(PROFILE_EXTENSION_DESCRIPTION_LAME)
#define PROFILE_EXTENSION_LAME_W                                    WIDEN_STRING(PROFILE_EXTENSION_LAME)

#define PROFILE_EXTENSION_DESCRIPTION_SNDFILEENCODER_W              WIDEN_STRING(PROFILE_EXTENSION_DESCRIPTION_SNDFILEENCODER)
#define PROFILE_EXTENSION_SNDFILEENCODER_W                          WIDEN_STRING(PROFILE_EXTENSION_SNDFILEENCODER)

/*
class FileExtension
{
    public:
        enum AudioExtension
        {
            AIF,
            AIFC,
            AIFF,
            AMPC,
            AU,
            AVR,
            CAF,
            HTK,
            IFF,
            MAT,
            MP1,
            MP2,
            MP3,
            PAF,
            PVF,
            RF64,
            SD2,
            SDS,
            SF,
            VOC,
            W64,
            WAV,
            WVE,
            XI
        };

        enum ProfileExtension
        {
            LAME,
            SNDFE
        };

        static const std::unordered_map<AudioExtension, std::string> audio_format_to_text;
        static const std::unordered_map<std::string, AudioExtension> text_to_audio_format;

        static const std::unordered_map<ProfileExtension, std::string> profile_format_to_text;
        static const std::unordered_map<std::string, ProfileExtension> text_to_profile_format;
};
*/

/*
const std::unordered_map<FileExtension::AudioExtension, std::string> FileExtension::audio_format_to_text =
{
{AudioExtension::AIF, "aif"},
{AudioExtension::AIFC, "aifc"},
{AudioExtension::AIFF, "aiff"},
{AudioExtension::AMPC, "ampc"},
{AudioExtension::AU, "au"},
{AudioExtension::AVR, "avr"},
{AudioExtension::CAF, "caf"},
{AudioExtension::HTK, "htk"},
{AudioExtension::IFF, "iff"},
{AudioExtension::MAT, "mat"},
{AudioExtension::MP1, "mp1"},
{AudioExtension::MP2, "mp2"},
{AudioExtension::MP3, "mp3"},
{AudioExtension::PAF, "paf"},
{AudioExtension::PVF, "pvf"},
{AudioExtension::RF64, "rf64"},
{AudioExtension::SD2, "sd2"},
{AudioExtension::SDS, "sds"},
{AudioExtension::SF, "sf"},
{AudioExtension::VOC, "voc"},
{AudioExtension::W64, "w64"},
{AudioExtension::WAV, "wav"},
{AudioExtension::WVE, "wve"},
{AudioExtension::XI, "xi"}
};

const std::unordered_map<std::string, FileExtension::AudioExtension> FileExtension::text_to_audio_format =
{
{FileExtension::audio_format_to_text.at(AudioExtension::AIF), AudioExtension::AIF},
{FileExtension::audio_format_to_text.at(AudioExtension::AIFC), AudioExtension::AIFC},
{FileExtension::audio_format_to_text.at(AudioExtension::AIFF), AudioExtension::AIFF},
{FileExtension::audio_format_to_text.at(AudioExtension::AMPC), AudioExtension::AMPC},
{FileExtension::audio_format_to_text.at(AudioExtension::AU), AudioExtension::AU},
{FileExtension::audio_format_to_text.at(AudioExtension::AVR), AudioExtension::AVR},
{FileExtension::audio_format_to_text.at(AudioExtension::CAF), AudioExtension::CAF},
{FileExtension::audio_format_to_text.at(AudioExtension::HTK), AudioExtension::HTK},
{FileExtension::audio_format_to_text.at(AudioExtension::IFF), AudioExtension::IFF},
{FileExtension::audio_format_to_text.at(AudioExtension::MAT), AudioExtension::MAT},
{FileExtension::audio_format_to_text.at(AudioExtension::MP1), AudioExtension::MP1},
{FileExtension::audio_format_to_text.at(AudioExtension::MP2), AudioExtension::MP2},
{FileExtension::audio_format_to_text.at(AudioExtension::MP3), AudioExtension::MP3},
{FileExtension::audio_format_to_text.at(AudioExtension::PAF), AudioExtension::PAF},
{FileExtension::audio_format_to_text.at(AudioExtension::PVF), AudioExtension::PVF},
{FileExtension::audio_format_to_text.at(AudioExtension::RF64), AudioExtension::RF64},
{FileExtension::audio_format_to_text.at(AudioExtension::SD2), AudioExtension::SD2},
{FileExtension::audio_format_to_text.at(AudioExtension::SDS), AudioExtension::SDS},
{FileExtension::audio_format_to_text.at(AudioExtension::SF), AudioExtension::SF},
{FileExtension::audio_format_to_text.at(AudioExtension::VOC), AudioExtension::VOC},
{FileExtension::audio_format_to_text.at(AudioExtension::W64), AudioExtension::W64},
{FileExtension::audio_format_to_text.at(AudioExtension::WAV), AudioExtension::WAV},
{FileExtension::audio_format_to_text.at(AudioExtension::WVE), AudioExtension::WVE},
{FileExtension::audio_format_to_text.at(AudioExtension::XI), AudioExtension::XI}
};

const std::unordered_map<FileExtension::ProfileExtension, std::string> FileExtension::profile_format_to_text =
{
{ProfileExtension::LAME, "lame"},
{ProfileExtension::SNDFE, "sndfe"}
};

const std::unordered_map<std::string, FileExtension::ProfileExtension> FileExtension::text_to_profile_format =
{
{FileExtension::profile_format_to_text.at(ProfileExtension::LAME), ProfileExtension::LAME},
{FileExtension::profile_format_to_text.at(ProfileExtension::SNDFE), ProfileExtension::SNDFE}
};
*/

#endif
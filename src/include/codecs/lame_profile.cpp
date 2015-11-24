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
#include "lame_profile.h"

const std::unordered_map<const rusty::codecs::LameProfile::AlgorithmQuality, std::string> rusty::codecs::LameProfile::algorithm_quality_to_text =
{
    {AlgorithmQuality::Q0, "0"},
    {AlgorithmQuality::Q1, "1"},
    {AlgorithmQuality::Q2, "2"},
    {AlgorithmQuality::Q3, "3"},
    {AlgorithmQuality::Q4, "4"},
    {AlgorithmQuality::Q5, "5"},
    {AlgorithmQuality::Q6, "6"},
    {AlgorithmQuality::Q7, "7"},
    {AlgorithmQuality::Q8, "8"},
    {AlgorithmQuality::Q9, "9"}
};

const std::unordered_map<const rusty::codecs::LameProfile::Mode, std::string> rusty::codecs::LameProfile::mode_to_text =
{
    {Mode::STEREO, "Stereo"},
    {Mode::JOINT_STEREO, "Joint stereo"},
    {Mode::MONO, "Mono"}
};

const std::unordered_map<const rusty::codecs::LameProfile::ReplayGain, std::string> rusty::codecs::LameProfile::replaygain_mode_to_text =
{
    {ReplayGain::NONE, "None"},
    {ReplayGain::FAST, "Fast"},
    {ReplayGain::ACCURATE, "Accurate"}
};

const std::unordered_map<const rusty::codecs::LameProfile::BitrateEncoding, std::string> rusty::codecs::LameProfile::bitrate_encoding_to_text =
{
    {BitrateEncoding::CONSTANT, "Constant"},
    {BitrateEncoding::VARIABLE_OLD, "Old variable"},
    {BitrateEncoding::VARIABLE_NEW, "New variable"},
    {BitrateEncoding::AVERAGE, "Average"}
};

const std::unordered_map<const rusty::codecs::LameProfile::Bitrate, std::string> rusty::codecs::LameProfile::bitrate_to_text =
{
    {Bitrate::B_8, "8"},
    {Bitrate::B_16, "16"},
    {Bitrate::B_24, "24"},
    {Bitrate::B_32, "32"},
    {Bitrate::B_40, "40"},
    {Bitrate::B_48, "48"},
    {Bitrate::B_56, "56"},
    {Bitrate::B_64, "64"},
    {Bitrate::B_80, "80"},
    {Bitrate::B_96, "96"},
    {Bitrate::B_112, "112"},
    {Bitrate::B_128, "128"},
    {Bitrate::B_144, "144"},
    {Bitrate::B_160, "160"},
    {Bitrate::B_192, "192"},
    {Bitrate::B_224, "224"},
    {Bitrate::B_256, "256"},
    {Bitrate::B_320, "320"}
};

const std::unordered_map<std::string, const rusty::codecs::LameProfile::AlgorithmQuality> rusty::codecs::LameProfile::text_to_algorithm_quality =
{
    {LameProfile::algorithm_quality_to_text.at(AlgorithmQuality::Q0), AlgorithmQuality::Q0},
    {LameProfile::algorithm_quality_to_text.at(AlgorithmQuality::Q1), AlgorithmQuality::Q1},
    {LameProfile::algorithm_quality_to_text.at(AlgorithmQuality::Q2), AlgorithmQuality::Q2},
    {LameProfile::algorithm_quality_to_text.at(AlgorithmQuality::Q3), AlgorithmQuality::Q3},
    {LameProfile::algorithm_quality_to_text.at(AlgorithmQuality::Q4), AlgorithmQuality::Q4},
    {LameProfile::algorithm_quality_to_text.at(AlgorithmQuality::Q5), AlgorithmQuality::Q5},
    {LameProfile::algorithm_quality_to_text.at(AlgorithmQuality::Q6), AlgorithmQuality::Q6},
    {LameProfile::algorithm_quality_to_text.at(AlgorithmQuality::Q7), AlgorithmQuality::Q7},
    {LameProfile::algorithm_quality_to_text.at(AlgorithmQuality::Q8), AlgorithmQuality::Q8},
    {LameProfile::algorithm_quality_to_text.at(AlgorithmQuality::Q9), AlgorithmQuality::Q9}
};

const std::unordered_map<std::string, const rusty::codecs::LameProfile::Mode> rusty::codecs::LameProfile::text_to_mode =
{
    {LameProfile::mode_to_text.at(Mode::STEREO), Mode::STEREO},
    {LameProfile::mode_to_text.at(Mode::JOINT_STEREO), Mode::JOINT_STEREO},
    {LameProfile::mode_to_text.at(Mode::MONO), Mode::MONO}
};

const std::unordered_map<std::string, const rusty::codecs::LameProfile::ReplayGain> rusty::codecs::LameProfile::text_to_replaygain_mode =
{
    {LameProfile::replaygain_mode_to_text.at(ReplayGain::NONE), ReplayGain::NONE},
    {LameProfile::replaygain_mode_to_text.at(ReplayGain::FAST), ReplayGain::FAST},
    {LameProfile::replaygain_mode_to_text.at(ReplayGain::ACCURATE), ReplayGain::ACCURATE}
};

const std::unordered_map<std::string, const rusty::codecs::LameProfile::BitrateEncoding> rusty::codecs::LameProfile::text_to_bitrate_encoding =
{
    {LameProfile::bitrate_encoding_to_text.at(BitrateEncoding::CONSTANT), BitrateEncoding::CONSTANT},
    {LameProfile::bitrate_encoding_to_text.at(BitrateEncoding::VARIABLE_OLD), BitrateEncoding::VARIABLE_OLD},
    {LameProfile::bitrate_encoding_to_text.at(BitrateEncoding::VARIABLE_NEW), BitrateEncoding::VARIABLE_NEW},
    {LameProfile::bitrate_encoding_to_text.at(BitrateEncoding::AVERAGE), BitrateEncoding::AVERAGE}
};

const std::unordered_map<std::string, const rusty::codecs::LameProfile::Bitrate> rusty::codecs::LameProfile::text_to_bitrate =
{
    {LameProfile::bitrate_to_text.at(Bitrate::B_8), Bitrate::B_8},
    {LameProfile::bitrate_to_text.at(Bitrate::B_16), Bitrate::B_16},
    {LameProfile::bitrate_to_text.at(Bitrate::B_24), Bitrate::B_24},
    {LameProfile::bitrate_to_text.at(Bitrate::B_32), Bitrate::B_32},
    {LameProfile::bitrate_to_text.at(Bitrate::B_40), Bitrate::B_40},
    {LameProfile::bitrate_to_text.at(Bitrate::B_48), Bitrate::B_48},
    {LameProfile::bitrate_to_text.at(Bitrate::B_56), Bitrate::B_56},
    {LameProfile::bitrate_to_text.at(Bitrate::B_64), Bitrate::B_64},
    {LameProfile::bitrate_to_text.at(Bitrate::B_80), Bitrate::B_80},
    {LameProfile::bitrate_to_text.at(Bitrate::B_96), Bitrate::B_96},
    {LameProfile::bitrate_to_text.at(Bitrate::B_112), Bitrate::B_112},
    {LameProfile::bitrate_to_text.at(Bitrate::B_128), Bitrate::B_128},
    {LameProfile::bitrate_to_text.at(Bitrate::B_144), Bitrate::B_144},
    {LameProfile::bitrate_to_text.at(Bitrate::B_160), Bitrate::B_160},
    {LameProfile::bitrate_to_text.at(Bitrate::B_192), Bitrate::B_192},
    {LameProfile::bitrate_to_text.at(Bitrate::B_224), Bitrate::B_224},
    {LameProfile::bitrate_to_text.at(Bitrate::B_256), Bitrate::B_256},
    {LameProfile::bitrate_to_text.at(Bitrate::B_320), Bitrate::B_320}
};

const std::unordered_map<const rusty::codecs::LameProfile::Option, std::string> rusty::codecs::LameProfile::option_to_text =
{
    {LameProfile::Option::ALGORITHM_QUALITY, "Algorithm quality"},
    {LameProfile::Option::MODE, "Channel"},
    {LameProfile::Option::REPLAYGAIN, "ReplayGain mode"},
    {LameProfile::Option::COPYRIGHT, "Copyright"},
    {LameProfile::Option::USE_NAOKI_PSYTUNE, "Use Naoki's psychoacoustic"},
    {LameProfile::Option::BITRATE_ENCODING, "Bitrate encoding"},
    {LameProfile::Option::VBR_QUALITY, "VBR quality"},
    {LameProfile::Option::MIN_OR_MAX_BITRATE1, "Constant bitrate / min or max bitrate"},
    {LameProfile::Option::MIN_OR_MAX_BITRATE2, "Min or max bitrate"}
};

const std::unordered_map<std::string, const rusty::codecs::LameProfile::Option> rusty::codecs::LameProfile::text_to_option =
{
    {LameProfile::option_to_text.at(Option::ALGORITHM_QUALITY), Option::ALGORITHM_QUALITY},
    {LameProfile::option_to_text.at(Option::MODE), Option::MODE},
    {LameProfile::option_to_text.at(Option::REPLAYGAIN), Option::REPLAYGAIN},
    {LameProfile::option_to_text.at(Option::COPYRIGHT), Option::COPYRIGHT},
    {LameProfile::option_to_text.at(Option::USE_NAOKI_PSYTUNE), Option::USE_NAOKI_PSYTUNE},
    {LameProfile::option_to_text.at(Option::BITRATE_ENCODING), Option::BITRATE_ENCODING},
    {LameProfile::option_to_text.at(Option::VBR_QUALITY), Option::VBR_QUALITY},
    {LameProfile::option_to_text.at(Option::MIN_OR_MAX_BITRATE1), Option::MIN_OR_MAX_BITRATE1},
    {LameProfile::option_to_text.at(Option::MIN_OR_MAX_BITRATE2), Option::MIN_OR_MAX_BITRATE2},
};

const std::vector<std::string> rusty::codecs::LameProfile::options_and_selections[9] =
{
    {
        LameProfile::option_to_text.at(Option::ALGORITHM_QUALITY),
        LameProfile::algorithm_quality_to_text.at(AlgorithmQuality::Q0),
        LameProfile::algorithm_quality_to_text.at(AlgorithmQuality::Q1),
        LameProfile::algorithm_quality_to_text.at(AlgorithmQuality::Q2),
        LameProfile::algorithm_quality_to_text.at(AlgorithmQuality::Q3),
        LameProfile::algorithm_quality_to_text.at(AlgorithmQuality::Q4),
        LameProfile::algorithm_quality_to_text.at(AlgorithmQuality::Q5),
        LameProfile::algorithm_quality_to_text.at(AlgorithmQuality::Q6),
        LameProfile::algorithm_quality_to_text.at(AlgorithmQuality::Q7),
        LameProfile::algorithm_quality_to_text.at(AlgorithmQuality::Q8),
        LameProfile::algorithm_quality_to_text.at(AlgorithmQuality::Q9)
    },
    {
        LameProfile::option_to_text.at(Option::MODE),
        LameProfile::mode_to_text.at(Mode::STEREO),
        LameProfile::mode_to_text.at(Mode::JOINT_STEREO),
        LameProfile::mode_to_text.at(Mode::MONO)
    },
    {
        LameProfile::option_to_text.at(Option::REPLAYGAIN),
        LameProfile::replaygain_mode_to_text.at(ReplayGain::NONE),
        LameProfile::replaygain_mode_to_text.at(ReplayGain::FAST),
        LameProfile::replaygain_mode_to_text.at(ReplayGain::ACCURATE)
    },
    {
        LameProfile::option_to_text.at(Option::COPYRIGHT),
        EncoderProfile::bool_true_text,
        EncoderProfile::bool_false_text
    },
    {
        LameProfile::option_to_text.at(Option::USE_NAOKI_PSYTUNE),
        EncoderProfile::bool_true_text,
        EncoderProfile::bool_false_text
    },
    {
        LameProfile::option_to_text.at(Option::BITRATE_ENCODING),
        LameProfile::bitrate_encoding_to_text.at(BitrateEncoding::CONSTANT),
        LameProfile::bitrate_encoding_to_text.at(BitrateEncoding::VARIABLE_OLD),
        LameProfile::bitrate_encoding_to_text.at(BitrateEncoding::VARIABLE_NEW),
        LameProfile::bitrate_encoding_to_text.at(BitrateEncoding::AVERAGE)
    },
    {
        LameProfile::option_to_text.at(Option::VBR_QUALITY)
    },
    {
        LameProfile::option_to_text.at(Option::MIN_OR_MAX_BITRATE1),
        LameProfile::bitrate_to_text.at(Bitrate::B_8),
        LameProfile::bitrate_to_text.at(Bitrate::B_16),
        LameProfile::bitrate_to_text.at(Bitrate::B_24),
        LameProfile::bitrate_to_text.at(Bitrate::B_32),
        LameProfile::bitrate_to_text.at(Bitrate::B_40),
        LameProfile::bitrate_to_text.at(Bitrate::B_48),
        LameProfile::bitrate_to_text.at(Bitrate::B_56),
        LameProfile::bitrate_to_text.at(Bitrate::B_64),
        LameProfile::bitrate_to_text.at(Bitrate::B_80),
        LameProfile::bitrate_to_text.at(Bitrate::B_96),
        LameProfile::bitrate_to_text.at(Bitrate::B_112),
        LameProfile::bitrate_to_text.at(Bitrate::B_128),
        LameProfile::bitrate_to_text.at(Bitrate::B_144),
        LameProfile::bitrate_to_text.at(Bitrate::B_160),
        LameProfile::bitrate_to_text.at(Bitrate::B_192),
        LameProfile::bitrate_to_text.at(Bitrate::B_224),
        LameProfile::bitrate_to_text.at(Bitrate::B_256),
        LameProfile::bitrate_to_text.at(Bitrate::B_320)
    },
    {
        LameProfile::option_to_text.at(Option::MIN_OR_MAX_BITRATE2),
        LameProfile::bitrate_to_text.at(Bitrate::B_8),
        LameProfile::bitrate_to_text.at(Bitrate::B_16),
        LameProfile::bitrate_to_text.at(Bitrate::B_24),
        LameProfile::bitrate_to_text.at(Bitrate::B_32),
        LameProfile::bitrate_to_text.at(Bitrate::B_40),
        LameProfile::bitrate_to_text.at(Bitrate::B_48),
        LameProfile::bitrate_to_text.at(Bitrate::B_56),
        LameProfile::bitrate_to_text.at(Bitrate::B_64),
        LameProfile::bitrate_to_text.at(Bitrate::B_80),
        LameProfile::bitrate_to_text.at(Bitrate::B_96),
        LameProfile::bitrate_to_text.at(Bitrate::B_112),
        LameProfile::bitrate_to_text.at(Bitrate::B_128),
        LameProfile::bitrate_to_text.at(Bitrate::B_144),
        LameProfile::bitrate_to_text.at(Bitrate::B_160),
        LameProfile::bitrate_to_text.at(Bitrate::B_192),
        LameProfile::bitrate_to_text.at(Bitrate::B_224),
        LameProfile::bitrate_to_text.at(Bitrate::B_256),
        LameProfile::bitrate_to_text.at(Bitrate::B_320)
    }
};

rusty::codecs::LameProfile::LameProfile(void)
{
    LoadDefaultProfile(Profile::DEFAULT);
}

void rusty::codecs::LameProfile::LoadDefaultProfile(Profile default_profile)
{
    switch(default_profile)
    {
        case Profile::DEFAULT:
        {
            algorithm_quality = AlgorithmQuality::Q0;
            mode = Mode::JOINT_STEREO;
            replaygain_mode = ReplayGain::ACCURATE;
            copyright = false;
            use_naoki_psytune = true;
            bitrate_encoding = BitrateEncoding::VARIABLE_NEW;
            vbr_quality = 0.0f;
            min_or_max_bitrate1 = Bitrate::B_320;
            min_or_max_bitrate2 = Bitrate::B_32;
            break;
        }
        default:
            assert(false);
    }
}

float rusty::codecs::LameProfile::GetVbrQuality(void) const
{
    return vbr_quality;
}

void rusty::codecs::LameProfile::SetAlgorithmQuality(LAME_ALGORITHM_QUALITY_DATA_TYPE algorithm_quality)
{
    switch(algorithm_quality)
    {
        case static_cast<LAME_ALGORITHM_QUALITY_DATA_TYPE>(AlgorithmQuality::Q0):
        case static_cast<LAME_ALGORITHM_QUALITY_DATA_TYPE>(AlgorithmQuality::Q1):
        case static_cast<LAME_ALGORITHM_QUALITY_DATA_TYPE>(AlgorithmQuality::Q2):
        case static_cast<LAME_ALGORITHM_QUALITY_DATA_TYPE>(AlgorithmQuality::Q3):
        case static_cast<LAME_ALGORITHM_QUALITY_DATA_TYPE>(AlgorithmQuality::Q4):
        case static_cast<LAME_ALGORITHM_QUALITY_DATA_TYPE>(AlgorithmQuality::Q5):
        case static_cast<LAME_ALGORITHM_QUALITY_DATA_TYPE>(AlgorithmQuality::Q6):
        case static_cast<LAME_ALGORITHM_QUALITY_DATA_TYPE>(AlgorithmQuality::Q7):
        case static_cast<LAME_ALGORITHM_QUALITY_DATA_TYPE>(AlgorithmQuality::Q8):
        case static_cast<LAME_ALGORITHM_QUALITY_DATA_TYPE>(AlgorithmQuality::Q9):
            break;
        default:
            throw core::InvalidArgumentException("LameProfile", "Invalid algorithm quality");
    }

    this->algorithm_quality = static_cast<AlgorithmQuality>(algorithm_quality);
}

void rusty::codecs::LameProfile::SetMode(LAME_MODE_DATA_TYPE mode)
{
    switch(mode)
    {
        case static_cast<LAME_MODE_DATA_TYPE>(Mode::STEREO):
        case static_cast<LAME_MODE_DATA_TYPE>(Mode::JOINT_STEREO):
        case static_cast<LAME_MODE_DATA_TYPE>(Mode::MONO):
            break;
        default:
            throw core::InvalidArgumentException("LameProfile", "Invalid channel");
    }

    this->mode = static_cast<Mode>(mode);
}

void rusty::codecs::LameProfile::SetReplayGainMode(LAME_REPLAYGAIN_DATA_TYPE replaygain_mode)
{
    switch(replaygain_mode)
    {
        case static_cast<LAME_REPLAYGAIN_DATA_TYPE>(ReplayGain::NONE):
        case static_cast<LAME_REPLAYGAIN_DATA_TYPE>(ReplayGain::FAST):
        case static_cast<LAME_REPLAYGAIN_DATA_TYPE>(ReplayGain::ACCURATE):
            break;
        default:
            throw core::InvalidArgumentException("LameProfile", "Invalid ReplayGain mode");
    }

    this->replaygain_mode = static_cast<ReplayGain>(replaygain_mode);
}

void rusty::codecs::LameProfile::SetCopyright(bool copyright)
{
    this->copyright = copyright;
}

void rusty::codecs::LameProfile::SetUseNaokiPsytune(bool use_naoki_psytune)
{
    this->use_naoki_psytune = use_naoki_psytune;
}

void rusty::codecs::LameProfile::SetBitrateEncoding(LAME_BITRATE_ENCODING_DATA_TYPE bitrate_encoding)
{
    switch(bitrate_encoding)
    {
        case static_cast<LAME_BITRATE_ENCODING_DATA_TYPE>(BitrateEncoding::CONSTANT):
        case static_cast<LAME_BITRATE_ENCODING_DATA_TYPE>(BitrateEncoding::VARIABLE_OLD):
        case static_cast<LAME_BITRATE_ENCODING_DATA_TYPE>(BitrateEncoding::VARIABLE_NEW):
        case static_cast<LAME_BITRATE_ENCODING_DATA_TYPE>(BitrateEncoding::AVERAGE):
            break;
        default:
            throw core::InvalidArgumentException("LameProfile", "Invalid bitrate encoding");
    }

    this->bitrate_encoding = static_cast<BitrateEncoding>(bitrate_encoding);
}

void rusty::codecs::LameProfile::SetVbrQuality(float vbr_quality)
{
    if(vbr_quality >= 0.f && vbr_quality <= 9.999f)
        this->vbr_quality = vbr_quality;
    else
        throw core::InvalidArgumentException("LameProfile", "Invalid variable bitrate quality");
}

void rusty::codecs::LameProfile::SetMinOrMaxBitrate(LAME_BITRATE_DATA_TYPE min_or_max_bitrate, bool one)
{
    switch(min_or_max_bitrate)
    {
        case static_cast<LAME_BITRATE_DATA_TYPE>(Bitrate::B_8):
        case static_cast<LAME_BITRATE_DATA_TYPE>(Bitrate::B_16):
        case static_cast<LAME_BITRATE_DATA_TYPE>(Bitrate::B_24):
        case static_cast<LAME_BITRATE_DATA_TYPE>(Bitrate::B_32):
        case static_cast<LAME_BITRATE_DATA_TYPE>(Bitrate::B_40):
        case static_cast<LAME_BITRATE_DATA_TYPE>(Bitrate::B_48):
        case static_cast<LAME_BITRATE_DATA_TYPE>(Bitrate::B_56):
        case static_cast<LAME_BITRATE_DATA_TYPE>(Bitrate::B_64):
        case static_cast<LAME_BITRATE_DATA_TYPE>(Bitrate::B_80):
        case static_cast<LAME_BITRATE_DATA_TYPE>(Bitrate::B_96):
        case static_cast<LAME_BITRATE_DATA_TYPE>(Bitrate::B_112):
        case static_cast<LAME_BITRATE_DATA_TYPE>(Bitrate::B_128):
        case static_cast<LAME_BITRATE_DATA_TYPE>(Bitrate::B_144):
        case static_cast<LAME_BITRATE_DATA_TYPE>(Bitrate::B_160):
        case static_cast<LAME_BITRATE_DATA_TYPE>(Bitrate::B_192):
        case static_cast<LAME_BITRATE_DATA_TYPE>(Bitrate::B_224):
        case static_cast<LAME_BITRATE_DATA_TYPE>(Bitrate::B_256):
        case static_cast<LAME_BITRATE_DATA_TYPE>(Bitrate::B_320):
            break;
        default:
            throw core::InvalidArgumentException("LameProfile", "Invalid bitrate");
    }

    if(one)
        this->min_or_max_bitrate1 = static_cast<Bitrate>(min_or_max_bitrate);
    else
        this->min_or_max_bitrate2 = static_cast<Bitrate>(min_or_max_bitrate);
}

void rusty::codecs::LameProfile::SetMinOrMaxBitrate1(LAME_BITRATE_DATA_TYPE min_or_max_bitrate1)
{
    SetMinOrMaxBitrate(min_or_max_bitrate1, true);
}

void rusty::codecs::LameProfile::SetMinOrMaxBitrate2(LAME_BITRATE_DATA_TYPE min_or_max_bitrate2)
{
    SetMinOrMaxBitrate(min_or_max_bitrate2, false);
}

unsigned int rusty::codecs::LameProfile::GetOptionsCount(void) const
{
    return sizeof(options_and_selections) / sizeof(std::vector<const char *>);
}

std::string rusty::codecs::LameProfile::GetOptionsInString(unsigned int option_index) const
{
    return options_and_selections[option_index][0];
}

void rusty::codecs::LameProfile::GetCurrentValueForOptionInString(unsigned int option_index, std::string &option_value) const
{
    std::string option_text(options_and_selections[option_index][0]);

    GetCurrentValueForOptionInString(option_text, option_value);
}

void rusty::codecs::LameProfile::GetCurrentValueForOptionInString(std::string &option_text, std::string &option_value) const
{
    Option option = text_to_option.at(option_text.c_str());

    switch(option)
    {
        case Option::ALGORITHM_QUALITY:
            option_value = algorithm_quality_to_text.at(algorithm_quality);
            break;
        case Option::MODE:
            option_value = mode_to_text.at(mode);
            break;
        case Option::REPLAYGAIN:
            option_value = replaygain_mode_to_text.at(replaygain_mode);
            break;
        case Option::COPYRIGHT:
            option_value = copyright ? EncoderProfile::bool_true_text : EncoderProfile::bool_false_text;
            break;
        case Option::USE_NAOKI_PSYTUNE:
            option_value = use_naoki_psytune ? EncoderProfile::bool_true_text : EncoderProfile::bool_false_text;
            break;
        case Option::BITRATE_ENCODING:
            option_value = bitrate_encoding_to_text.at(bitrate_encoding);
            break;
        case Option::VBR_QUALITY:
            option_value = std::to_string(vbr_quality);
            break;
        case Option::MIN_OR_MAX_BITRATE1:
            option_value = bitrate_to_text.at(min_or_max_bitrate1);
            break;
        case Option::MIN_OR_MAX_BITRATE2:
            option_value = bitrate_to_text.at(min_or_max_bitrate2);
            break;
    }
}

unsigned int rusty::codecs::LameProfile::GetSelectionCountForOption(unsigned int option_index) const
{
    return static_cast<unsigned int>(options_and_selections[option_index].size() - 1);
}

std::string rusty::codecs::LameProfile::GetSelectionForOptionInString(unsigned int option_index, unsigned int selection_index) const
{
    return options_and_selections[option_index][selection_index + 1];
}

void rusty::codecs::LameProfile::SetValueForOption(unsigned int option_index, std::string &value)
{
    std::string option_text(options_and_selections[option_index][0]);

    SetValueForOption(option_text, value);
}

void rusty::codecs::LameProfile::SetValueForOption(std::string &option_text, std::string &value)
{
    Option option = text_to_option.at(option_text);

    switch(option)
    {
        case Option::ALGORITHM_QUALITY:
            algorithm_quality = text_to_algorithm_quality.at(value);
            break;
        case Option::MODE:
            mode = text_to_mode.at(value);
            break;
        case Option::REPLAYGAIN:
            replaygain_mode = text_to_replaygain_mode.at(value);
            break;
        case Option::COPYRIGHT:
        {
            std::string _value(value);

            if(_value == EncoderProfile::bool_true_text)
                copyright = true;
            else if(_value == EncoderProfile::bool_false_text)
                copyright = false;
            else
                throw core::InvalidArgumentException("LameProfile", "Invalid copyright value");
            break;
        }
        case Option::USE_NAOKI_PSYTUNE:
        {
            std::string _value(value);

            if(_value == EncoderProfile::bool_true_text)
                use_naoki_psytune = true;
            else if(_value == EncoderProfile::bool_false_text)
                use_naoki_psytune = false;
            else
                throw core::InvalidArgumentException("LameProfile", "Invalid naoki psytune value");
            break;
        }
        case Option::BITRATE_ENCODING:
            bitrate_encoding = text_to_bitrate_encoding.at(value);
            break;
        case Option::VBR_QUALITY:
        {
            try
            {
                SetVbrQuality(std::stof(value));
            }
            catch(std::invalid_argument &/* ex */)
            {
                throw core::InvalidArgumentException("LameProfile", "Invalid variable bitrate quality");
            }
            break;
        }
        case Option::MIN_OR_MAX_BITRATE1:
            min_or_max_bitrate1 = text_to_bitrate.at(value);
            break;
        case Option::MIN_OR_MAX_BITRATE2:
            min_or_max_bitrate2 = text_to_bitrate.at(value);
            break;
    }
}
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
#include "rst_lame_options.h"

const char *LameOptions::output_file_extension = "mp3";
const char *LameOptions::profile_file_extension = "lame";

const std::unordered_map<const LameOptions::AlgorithmQuality, std::string> LameOptions::algorithm_quality_to_text =
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

const std::unordered_map<const LameOptions::Mode, std::string> LameOptions::mode_to_text =
{
    {Mode::STEREO, "Stereo"},
    {Mode::JOINT_STEREO, "Joint stereo"},
    {Mode::MONO, "Mono"}
};

const std::unordered_map<const LameOptions::ReplayGain, std::string> LameOptions::replaygain_mode_to_text =
{
    {ReplayGain::NONE, "None"},
    {ReplayGain::FAST, "Fast"},
    {ReplayGain::ACCURATE, "Accurate"}
};

const std::unordered_map<const LameOptions::BitrateEncoding, std::string> LameOptions::bitrate_encoding_to_text =
{
    {BitrateEncoding::CONSTANT, "Constant"},
    {BitrateEncoding::VARIABLE_OLD, "Old variable"},
    {BitrateEncoding::VARIABLE_NEW, "New variable"},
    {BitrateEncoding::AVERAGE, "Average"}
};

const std::unordered_map<const LameOptions::Bitrate, std::string> LameOptions::bitrate_to_text =
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

const std::unordered_map<std::string, const LameOptions::AlgorithmQuality> LameOptions::text_to_algorithm_quality =
{
    {LameOptions::algorithm_quality_to_text.at(AlgorithmQuality::Q0), AlgorithmQuality::Q0},
    {LameOptions::algorithm_quality_to_text.at(AlgorithmQuality::Q1), AlgorithmQuality::Q1},
    {LameOptions::algorithm_quality_to_text.at(AlgorithmQuality::Q2), AlgorithmQuality::Q2},
    {LameOptions::algorithm_quality_to_text.at(AlgorithmQuality::Q3), AlgorithmQuality::Q3},
    {LameOptions::algorithm_quality_to_text.at(AlgorithmQuality::Q4), AlgorithmQuality::Q4},
    {LameOptions::algorithm_quality_to_text.at(AlgorithmQuality::Q5), AlgorithmQuality::Q5},
    {LameOptions::algorithm_quality_to_text.at(AlgorithmQuality::Q6), AlgorithmQuality::Q6},
    {LameOptions::algorithm_quality_to_text.at(AlgorithmQuality::Q7), AlgorithmQuality::Q7},
    {LameOptions::algorithm_quality_to_text.at(AlgorithmQuality::Q8), AlgorithmQuality::Q8},
    {LameOptions::algorithm_quality_to_text.at(AlgorithmQuality::Q9), AlgorithmQuality::Q9}
};

const std::unordered_map<std::string, const LameOptions::Mode> LameOptions::text_to_mode =
{
    {LameOptions::mode_to_text.at(Mode::STEREO), Mode::STEREO},
    {LameOptions::mode_to_text.at(Mode::JOINT_STEREO), Mode::JOINT_STEREO},
    {LameOptions::mode_to_text.at(Mode::MONO), Mode::MONO}
};

const std::unordered_map<std::string, const LameOptions::ReplayGain> LameOptions::text_to_replaygain_mode =
{
    {LameOptions::replaygain_mode_to_text.at(ReplayGain::NONE), ReplayGain::NONE},
    {LameOptions::replaygain_mode_to_text.at(ReplayGain::FAST), ReplayGain::FAST},
    {LameOptions::replaygain_mode_to_text.at(ReplayGain::ACCURATE), ReplayGain::ACCURATE}
};

const std::unordered_map<std::string, const LameOptions::BitrateEncoding> LameOptions::text_to_bitrate_encoding =
{
    {LameOptions::bitrate_encoding_to_text.at(BitrateEncoding::CONSTANT), BitrateEncoding::CONSTANT},
    {LameOptions::bitrate_encoding_to_text.at(BitrateEncoding::VARIABLE_OLD), BitrateEncoding::VARIABLE_OLD},
    {LameOptions::bitrate_encoding_to_text.at(BitrateEncoding::VARIABLE_NEW), BitrateEncoding::VARIABLE_NEW},
    {LameOptions::bitrate_encoding_to_text.at(BitrateEncoding::AVERAGE), BitrateEncoding::AVERAGE}
};

const std::unordered_map<std::string, const LameOptions::Bitrate> LameOptions::text_to_bitrate =
{
    {LameOptions::bitrate_to_text.at(Bitrate::B_8), Bitrate::B_8},
    {LameOptions::bitrate_to_text.at(Bitrate::B_16), Bitrate::B_16},
    {LameOptions::bitrate_to_text.at(Bitrate::B_24), Bitrate::B_24},
    {LameOptions::bitrate_to_text.at(Bitrate::B_32), Bitrate::B_32},
    {LameOptions::bitrate_to_text.at(Bitrate::B_40), Bitrate::B_40},
    {LameOptions::bitrate_to_text.at(Bitrate::B_48), Bitrate::B_48},
    {LameOptions::bitrate_to_text.at(Bitrate::B_56), Bitrate::B_56},
    {LameOptions::bitrate_to_text.at(Bitrate::B_64), Bitrate::B_64},
    {LameOptions::bitrate_to_text.at(Bitrate::B_80), Bitrate::B_80},
    {LameOptions::bitrate_to_text.at(Bitrate::B_96), Bitrate::B_96},
    {LameOptions::bitrate_to_text.at(Bitrate::B_112), Bitrate::B_112},
    {LameOptions::bitrate_to_text.at(Bitrate::B_128), Bitrate::B_128},
    {LameOptions::bitrate_to_text.at(Bitrate::B_144), Bitrate::B_144},
    {LameOptions::bitrate_to_text.at(Bitrate::B_160), Bitrate::B_160},
    {LameOptions::bitrate_to_text.at(Bitrate::B_192), Bitrate::B_192},
    {LameOptions::bitrate_to_text.at(Bitrate::B_224), Bitrate::B_224},
    {LameOptions::bitrate_to_text.at(Bitrate::B_256), Bitrate::B_256},
    {LameOptions::bitrate_to_text.at(Bitrate::B_320), Bitrate::B_320}
};

const std::unordered_map<const LameOptions::Option, std::string> LameOptions::option_to_text =
{
    {LameOptions::Option::ALGORITHM_QUALITY, "Algorithm quality"},
    {LameOptions::Option::MODE, "Channel"},
    {LameOptions::Option::REPLAYGAIN, "ReplayGain mode"},
    {LameOptions::Option::COPYRIGHT, "Copyright"},
    {LameOptions::Option::USE_NAOKI_PSYTUNE, "Use Naoki's psychoacoustic"},
    {LameOptions::Option::BITRATE_ENCODING, "Bitrate encoding"},
    {LameOptions::Option::VBR_QUALITY, "VBR quality"},
    {LameOptions::Option::MIN_OR_MAX_BITRATE1, "Constant bitrate / min or max bitrate"},
    {LameOptions::Option::MIN_OR_MAX_BITRATE2, "Min or max bitrate"}
};

const std::unordered_map<std::string, const LameOptions::Option> LameOptions::text_to_option =
{
    {LameOptions::option_to_text.at(Option::ALGORITHM_QUALITY), Option::ALGORITHM_QUALITY},
    {LameOptions::option_to_text.at(Option::MODE), Option::MODE},
    {LameOptions::option_to_text.at(Option::REPLAYGAIN), Option::REPLAYGAIN},
    {LameOptions::option_to_text.at(Option::COPYRIGHT), Option::COPYRIGHT},
    {LameOptions::option_to_text.at(Option::USE_NAOKI_PSYTUNE), Option::USE_NAOKI_PSYTUNE},
    {LameOptions::option_to_text.at(Option::BITRATE_ENCODING), Option::BITRATE_ENCODING},
    {LameOptions::option_to_text.at(Option::VBR_QUALITY), Option::VBR_QUALITY},
    {LameOptions::option_to_text.at(Option::MIN_OR_MAX_BITRATE1), Option::MIN_OR_MAX_BITRATE1},
    {LameOptions::option_to_text.at(Option::MIN_OR_MAX_BITRATE2), Option::MIN_OR_MAX_BITRATE2},
};

const std::vector<std::string> LameOptions::options_and_selections[9] =
{
    {
        LameOptions::option_to_text.at(Option::ALGORITHM_QUALITY),
        LameOptions::algorithm_quality_to_text.at(AlgorithmQuality::Q0),
        LameOptions::algorithm_quality_to_text.at(AlgorithmQuality::Q1),
        LameOptions::algorithm_quality_to_text.at(AlgorithmQuality::Q2),
        LameOptions::algorithm_quality_to_text.at(AlgorithmQuality::Q3),
        LameOptions::algorithm_quality_to_text.at(AlgorithmQuality::Q4),
        LameOptions::algorithm_quality_to_text.at(AlgorithmQuality::Q5),
        LameOptions::algorithm_quality_to_text.at(AlgorithmQuality::Q6),
        LameOptions::algorithm_quality_to_text.at(AlgorithmQuality::Q7),
        LameOptions::algorithm_quality_to_text.at(AlgorithmQuality::Q8),
        LameOptions::algorithm_quality_to_text.at(AlgorithmQuality::Q9)
    },
    {
        LameOptions::option_to_text.at(Option::MODE),
        LameOptions::mode_to_text.at(Mode::STEREO),
        LameOptions::mode_to_text.at(Mode::JOINT_STEREO),
        LameOptions::mode_to_text.at(Mode::MONO)
    },
    {
        LameOptions::option_to_text.at(Option::REPLAYGAIN),
        LameOptions::replaygain_mode_to_text.at(ReplayGain::NONE),
        LameOptions::replaygain_mode_to_text.at(ReplayGain::FAST),
        LameOptions::replaygain_mode_to_text.at(ReplayGain::ACCURATE)
    },
    {
        LameOptions::option_to_text.at(Option::COPYRIGHT),
        EncoderOptions::bool_true_text,
        EncoderOptions::bool_false_text
    },
    {
        LameOptions::option_to_text.at(Option::USE_NAOKI_PSYTUNE),
        EncoderOptions::bool_true_text,
        EncoderOptions::bool_false_text
    },
    {
        LameOptions::option_to_text.at(Option::BITRATE_ENCODING),
        LameOptions::bitrate_encoding_to_text.at(BitrateEncoding::CONSTANT),
        LameOptions::bitrate_encoding_to_text.at(BitrateEncoding::VARIABLE_OLD),
        LameOptions::bitrate_encoding_to_text.at(BitrateEncoding::VARIABLE_NEW),
        LameOptions::bitrate_encoding_to_text.at(BitrateEncoding::AVERAGE)
    },
    {
        LameOptions::option_to_text.at(Option::VBR_QUALITY)
    },
    {
        LameOptions::option_to_text.at(Option::MIN_OR_MAX_BITRATE1),
        LameOptions::bitrate_to_text.at(Bitrate::B_8),
        LameOptions::bitrate_to_text.at(Bitrate::B_16),
        LameOptions::bitrate_to_text.at(Bitrate::B_24),
        LameOptions::bitrate_to_text.at(Bitrate::B_32),
        LameOptions::bitrate_to_text.at(Bitrate::B_40),
        LameOptions::bitrate_to_text.at(Bitrate::B_48),
        LameOptions::bitrate_to_text.at(Bitrate::B_56),
        LameOptions::bitrate_to_text.at(Bitrate::B_64),
        LameOptions::bitrate_to_text.at(Bitrate::B_80),
        LameOptions::bitrate_to_text.at(Bitrate::B_96),
        LameOptions::bitrate_to_text.at(Bitrate::B_112),
        LameOptions::bitrate_to_text.at(Bitrate::B_128),
        LameOptions::bitrate_to_text.at(Bitrate::B_144),
        LameOptions::bitrate_to_text.at(Bitrate::B_160),
        LameOptions::bitrate_to_text.at(Bitrate::B_192),
        LameOptions::bitrate_to_text.at(Bitrate::B_224),
        LameOptions::bitrate_to_text.at(Bitrate::B_256),
        LameOptions::bitrate_to_text.at(Bitrate::B_320)
    },
    {
        LameOptions::option_to_text.at(Option::MIN_OR_MAX_BITRATE2),
        LameOptions::bitrate_to_text.at(Bitrate::B_8),
        LameOptions::bitrate_to_text.at(Bitrate::B_16),
        LameOptions::bitrate_to_text.at(Bitrate::B_24),
        LameOptions::bitrate_to_text.at(Bitrate::B_32),
        LameOptions::bitrate_to_text.at(Bitrate::B_40),
        LameOptions::bitrate_to_text.at(Bitrate::B_48),
        LameOptions::bitrate_to_text.at(Bitrate::B_56),
        LameOptions::bitrate_to_text.at(Bitrate::B_64),
        LameOptions::bitrate_to_text.at(Bitrate::B_80),
        LameOptions::bitrate_to_text.at(Bitrate::B_96),
        LameOptions::bitrate_to_text.at(Bitrate::B_112),
        LameOptions::bitrate_to_text.at(Bitrate::B_128),
        LameOptions::bitrate_to_text.at(Bitrate::B_144),
        LameOptions::bitrate_to_text.at(Bitrate::B_160),
        LameOptions::bitrate_to_text.at(Bitrate::B_192),
        LameOptions::bitrate_to_text.at(Bitrate::B_224),
        LameOptions::bitrate_to_text.at(Bitrate::B_256),
        LameOptions::bitrate_to_text.at(Bitrate::B_320)
    }
};

LameOptions::LameOptions(void)
{
    LoadDefaultProfile(Profile::DEFAULT);
}

void LameOptions::LoadDefaultProfile(Profile default_profile)
{
    switch(default_profile)
    {
        case DEFAULT:
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
    }
}

float LameOptions::GetVbrQuality(void) const
{
    return vbr_quality;
}

void LameOptions::SetAlgorithmQuality(uint8_t algorithm_quality)
{
    switch(algorithm_quality)
    {
        case AlgorithmQuality::Q0:
        case AlgorithmQuality::Q1:
        case AlgorithmQuality::Q2:
        case AlgorithmQuality::Q3:
        case AlgorithmQuality::Q4:
        case AlgorithmQuality::Q5:
        case AlgorithmQuality::Q6:
        case AlgorithmQuality::Q7:
        case AlgorithmQuality::Q8:
        case AlgorithmQuality::Q9:
            break;
        default:
            throw InvalidArgumentException("LameOptions", "Invalid algorithm quality");
    }

    this->algorithm_quality = static_cast<AlgorithmQuality>(algorithm_quality);
}

void LameOptions::SetMode(uint8_t mode)
{
    switch(mode)
    {
        case Mode::STEREO:
        case Mode::JOINT_STEREO:
        case Mode::MONO:
            break;
        default:
            throw InvalidArgumentException("LameOptions", "Invalid channel");
    }

    this->mode = static_cast<Mode>(mode);
}

void LameOptions::SetReplayGainMode(uint8_t replaygain_mode)
{
    switch(replaygain_mode)
    {
        case ReplayGain::NONE:
        case ReplayGain::FAST:
        case ReplayGain::ACCURATE:
            break;
        default:
            throw InvalidArgumentException("LameOptions", "Invalid ReplayGain mode");
    }

    this->replaygain_mode = static_cast<ReplayGain>(replaygain_mode);
}

void LameOptions::SetCopyright(bool copyright)
{
    this->copyright = copyright;
}

void LameOptions::SetUseNaokiPsytune(bool use_naoki_psytune)
{
    this->use_naoki_psytune = use_naoki_psytune;
}

void LameOptions::SetBitrateEncoding(uint8_t bitrate_encoding)
{
    switch(bitrate_encoding)
    {
        case BitrateEncoding::CONSTANT:
        case BitrateEncoding::VARIABLE_OLD:
        case BitrateEncoding::VARIABLE_NEW:
        case BitrateEncoding::AVERAGE:
            break;
        default:
            throw InvalidArgumentException("LameOptions", "Invalid bitrate encoding");
    }

    this->bitrate_encoding = static_cast<BitrateEncoding>(bitrate_encoding);
}

void LameOptions::SetVbrQuality(float vbr_quality)
{
    if(vbr_quality >= 0.f && vbr_quality <= 9.999f)
        this->vbr_quality = vbr_quality;
    else
        throw InvalidArgumentException("LameOptions", "Invalid variable bitrate quality");
}

void LameOptions::SetMinOrMaxBitrate(uint16_t min_or_max_bitrate, bool one)
{
    switch(min_or_max_bitrate)
    {
        case Bitrate::B_8:
        case Bitrate::B_16:
        case Bitrate::B_24:
        case Bitrate::B_32:
        case Bitrate::B_40:
        case Bitrate::B_48:
        case Bitrate::B_56:
        case Bitrate::B_64:
        case Bitrate::B_80:
        case Bitrate::B_96:
        case Bitrate::B_112:
        case Bitrate::B_128:
        case Bitrate::B_144:
        case Bitrate::B_160:
        case Bitrate::B_192:
        case Bitrate::B_224:
        case Bitrate::B_256:
        case Bitrate::B_320:
            break;
        default:
            throw InvalidArgumentException("LameOptions", "Invalid bitrate");
    }

    if(one)
        this->min_or_max_bitrate1 = static_cast<Bitrate>(min_or_max_bitrate);
    else
        this->min_or_max_bitrate2 = static_cast<Bitrate>(min_or_max_bitrate);
}

void LameOptions::SetMinOrMaxBitrate1(uint16_t min_or_max_bitrate1)
{
    SetMinOrMaxBitrate(min_or_max_bitrate1, true);
}

void LameOptions::SetMinOrMaxBitrate2(uint16_t min_or_max_bitrate2)
{
    SetMinOrMaxBitrate(min_or_max_bitrate2, false);
}

unsigned int LameOptions::GetOptionsCount(void) const
{
    return sizeof(options_and_selections) / sizeof(std::vector<const char *>);
}

std::string LameOptions::GetOptionsInString(unsigned int option_index) const
{
    return options_and_selections[option_index][0];
}

void LameOptions::GetCurrentValueForOptionInString(unsigned int option_index, std::string &option_value) const
{
    std::string option_text(options_and_selections[option_index][0]);

    GetCurrentValueForOptionInString(option_text, option_value);
}

void LameOptions::GetCurrentValueForOptionInString(std::string &option_text, std::string &option_value) const
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
            option_value = copyright ? EncoderOptions::bool_true_text : EncoderOptions::bool_false_text;
            break;
        case Option::USE_NAOKI_PSYTUNE:
            option_value = use_naoki_psytune ? EncoderOptions::bool_true_text : EncoderOptions::bool_false_text;
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

unsigned int LameOptions::GetSelectionCountForOption(unsigned int option_index) const
{
    return static_cast<unsigned int>(options_and_selections[option_index].size() - 1);
}

std::string LameOptions::GetSelectionForOptionInString(unsigned int option_index, unsigned int selection_index) const
{
    return options_and_selections[option_index][selection_index + 1];
}

void LameOptions::SetValueForOption(unsigned int option_index, std::string &value)
{
    std::string option_text(options_and_selections[option_index][0]);

    SetValueForOption(option_text, value);
}

void LameOptions::SetValueForOption(std::string &option_text, std::string &value)
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

            if(_value == EncoderOptions::bool_true_text)
                copyright = true;
            else if(_value == EncoderOptions::bool_false_text)
                copyright = false;
            else
                throw InvalidArgumentException("LameOptions", "Invalid copyright value");
            break;
        }
        case Option::USE_NAOKI_PSYTUNE:
        {
            std::string _value(value);

            if(_value == EncoderOptions::bool_true_text)
                use_naoki_psytune = true;
            else if(_value == EncoderOptions::bool_false_text)
                use_naoki_psytune = false;
            else
                throw InvalidArgumentException("LameOptions", "Invalid naoki psytune value");
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
                throw InvalidArgumentException("LameOptions", "Invalid variable bitrate quality");
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
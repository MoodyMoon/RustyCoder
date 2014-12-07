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

/*!
All enumerators with an assigned value cannot be reassigned to another in the future.
This is because \c the assigned value will be written to the profile file.
*/

#ifndef CODECS_RST_LAME_OPTIONS_H
#define CODECS_RST_LAME_OPTIONS_H

class LameOptions : public EncoderOptions
{
    public:
        /*!
        Similar to \c -q in lame command line
        */
        enum AlgorithmQuality
        {
            Q0 = 0, /*!< <tt>-q 0</tt> (Best quality, slowest) average 245kbps*/
            Q1 = 1, /*!< <tt>-q 1</tt> */
            Q2 = 2, /*!< <tt>-q 2</tt> average 190kbps */
            Q3 = 3, /*!< <tt>-q 3</tt> average 175kbps */
            Q4 = 4, /*!< <tt>-q 4</tt> average 165kbps */
            Q5 = 5, /*!< <tt>-q 5</tt> average 130kbps */
            Q6 = 6, /*!< <tt>-q 6</tt> */
            Q7 = 7, /*!< <tt>-q 7</tt> */
            Q8 = 8, /*!< <tt>-q 8</tt> */
            Q9 = 9  /*!< <tt>-q 9</tt> (Low quality, fastest) */
        };

        /*!
        Similar to \c -m in lame command line
        */
        enum Mode
        {
            STEREO = 0,       /*!< <tt>-m s</tt> */
            JOINT_STEREO = 1, /*!< <tt>-m j</tt> */
            MONO = 2          /*!< <tt>-m m</tt> */
        };

        /*!
        Similar to \c --*+replaygain*+ in lame command line
        */
        enum ReplayGain
        {
            NONE = 0,    /*!< <tt>\--noreplaygain</tt> */
            FAST = 1,    /*!< <tt>\--replaygain-fast</tt> */
            ACCURATE = 2 /*!< <tt>\--replaygain-accurate</tt> */
        };

        /*!
        Bitrate encoding selection
        */
        enum BitrateEncoding
        {
            CONSTANT = 0,     /*!< <tt>\--cbr -b \<bitrate\></tt> */
            VARIABLE_OLD = 1, /*!< <tt>\--vbr-old</tt> */
            VARIABLE_NEW = 2, /*!< <tt>\--vbr-new</tt> */
            AVERAGE = 3       /*!< <tt>\--abr \<bitrate\></tt> */
        };

        /*!
        For the option \c -b and \c -B in lame command line. Obtained from LAME USAGE.\n\n

        <tt>
        MPEG-1   layer III sample frequencies (kHz):  32  48  44.1\n
        bitrates (kbps): 32 40 48 56 64 80 96 112 128 160 192 224 256 320\n\n

        MPEG-2   layer III sample frequencies (kHz):  16  24  22.05\n
        bitrates (kbps):  8 16 24 32 40 48 56 64 80 96 112 128 144 160\n\n

        MPEG-2.5 layer III sample frequencies (kHz):   8  12  11.025\n
        bitrates (kbps):  8 16 24 32 40 48 56 64
        </tt>
        */
        enum Bitrate
        {
            B_8 = 8,
            B_16 = 16,
            B_24 = 24,
            B_32 = 32,
            B_40 = 40,
            B_48 = 48,
            B_56 = 56,
            B_64 = 64,
            B_80 = 80,
            B_96 = 96,
            B_112 = 112,
            B_128 = 128,
            B_144 = 144,
            B_160 = 160,
            B_192 = 192,
            B_224 = 224,
            B_256 = 256,
            B_320 = 320
        };

        enum Profile
        {
            DEFAULT
        };

    private:
        enum Option
        {
            ALGORITHM_QUALITY,
            MODE,
            REPLAYGAIN,
            COPYRIGHT,
            USE_NAOKI_PSYTUNE,
            BITRATE_ENCODING,
            VBR_QUALITY,
            MIN_OR_MAX_BITRATE1,
            MIN_OR_MAX_BITRATE2
        };

        static const std::map<const AlgorithmQuality, std::string> algorithm_quality_to_text;
        static const std::map<const Mode, std::string> mode_to_text;
        static const std::map<const ReplayGain, std::string> replaygain_mode_to_text;
        static const std::map<const BitrateEncoding, std::string> bitrate_encoding_to_text;
        static const std::map<const Bitrate, std::string> bitrate_to_text;

        static const std::map<std::string, const AlgorithmQuality> text_to_algorithm_quality;
        static const std::map<std::string, const Mode> text_to_mode;
        static const std::map<std::string, const ReplayGain> text_to_replaygain_mode;
        static const std::map<std::string, const BitrateEncoding> text_to_bitrate_encoding;
        static const std::map<std::string, const Bitrate> text_to_bitrate;

        static const std::map<const Option, std::string> option_to_text;
        static const std::map<std::string, const Option> text_to_option;

        void SetMinOrMaxBitrate(uint16_t min_or_max_bitrate, bool one);

    public:
        AlgorithmQuality algorithm_quality;
        Mode mode;
        ReplayGain replaygain_mode;
        bool copyright;
        bool use_naoki_psytune;
        BitrateEncoding bitrate_encoding;
    private:
        float vbr_quality;
    public:
        Bitrate min_or_max_bitrate1;
        Bitrate min_or_max_bitrate2;

        static const char *output_file_extension;
        static const char *profile_file_extension;

        static const std::vector<std::string> options_and_selections[9];

        LameOptions(void);

        void LoadDefaultProfile(Profile default_profile);

        float GetVbrQuality(void) const;
        void SetAlgorithmQuality(uint8_t algorithm_quality);
        void SetMode(uint8_t mode);
        void SetReplayGainMode(uint8_t replaygain_mode);
        void SetCopyright(bool copyright);
        void SetUseNaokiPsytune(bool use_naoki_psytune);
        void SetBitrateEncoding(uint8_t bitrate_encoding);
        void SetVbrQuality(float vbr_quality);
        void SetMinOrMaxBitrate1(uint16_t min_or_max_bitrate1);
        void SetMinOrMaxBitrate2(uint16_t min_or_max_bitrate2);

        virtual unsigned int GetOptionsCount(void) const;
        virtual std::string GetOptionsInString(unsigned int option_index) const;
        virtual void GetCurrentValueForOptionInString(unsigned int option_index, std::string &option_value) const;
        virtual void GetCurrentValueForOptionInString(std::string &option_text, std::string &option_value) const;

        virtual unsigned int GetSelectionCountForOption(unsigned int option_index) const;
        virtual std::string GetSelectionForOptionInString(unsigned int option_index, unsigned int selection_index) const;

        virtual void SetValueForOption(unsigned int option_index, std::string &value);
        virtual void SetValueForOption(std::string &option_text, std::string &value);
};

#endif
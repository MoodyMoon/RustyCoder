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

#ifndef CODECS_CODEC_CONTROLLER_H
#define CODECS_CODEC_CONTROLLER_H

template<class T>
class SndFileEncoderOptions;

template<class T>
class LameOptions;

class CodecController
{
    public:
        CodecController(const CodecController &) = delete;
        CodecController & operator=(const CodecController &) = delete;

        CodecController(void);
};

template<class T>
class SndFileOptions
{
    public:
        SndFileEncoder::OutputFormat format;
};

template<class T>
class LameOptions
{
    public:
        Lame::AlgorithmQuality algorithm_quality;
        Lame::Mode mode;
        Lame::ReplayGain replaygain_mode;
        bool copyright;
        bool use_naoki_psytune;
        Lame::BitrateEncoding bitrate_encoding;
        float vbr_quality;
        Lame::Bitrate min_or_max_bitrate1;
        Lame::Bitrate min_or_max_bitrate2;
};

#endif
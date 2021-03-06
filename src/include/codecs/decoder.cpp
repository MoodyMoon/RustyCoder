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
#include "decoder.h"

const std::unordered_map<rusty::codecs::Decoder<void>::ID, std::string> rusty::codecs::Decoder<void>::decoder_id_to_text =
{
    {ID::MPG123, MPG123_DECODER_NAME},
    {ID::SNDFILE_DECODER, SNDFILE_DECODER_NAME}
};
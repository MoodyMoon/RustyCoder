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

#ifndef GUI_COMMON_H
#define GUI_COMMON_H

#include "stdafx.h"

static COMDLG_FILTERSPEC input_format_filters[] =
{{L"Audio Interchange File Format", L"*.aiff;*.aif;*.aifc"},
{L"Akai MPC 2000 Format", L"*.ampc"},
{L"Sun Microsystem Audio Format", L"*.au"},
{L"Audio Visual Research Format", L"*.avr"},
{L"Apple Core Audio File", L"*.caf"},
{L"Hidden Markov Model Toolkit Speech Recognition Format", L"*.htk"},
{L"Amiga Audio Format", L"*.iff"},
{L"GNU Octave File / Matlab File", L"*.mat"},
{L"MPEG Audio Layer I", L"*.mp1"},
{L"MPEG Audio Layer II", L"*.mp2"},
{L"MPEG Audio Layer III", L"*.mp3"},
{L"Ensoniq PARIS Audio Format", L"*.paf"},
{L"Portable Voice Format", L"*.pvf"},
{L"RIFF 64", L"*.rf64"},
{L"MIDI Sample Dump Standard Format", L"*.sds"},
{L"Sound Designer II Audio File", L"*.sd2"},
{L"Berkeley IRCAM CARL Sound File", L"*.sf"},
{L"Creative Labs Audio Format", L"*.voc"},
{L"WAV", L"*.wav"},
{L"Psion Series 3 Audio Format", L"*.wve"},
{L"SoundFoundry WAVE 64", L"*.w64"},
{L"FastTracker's Extended Instrument", L"*.xi"}};

static COMDLG_FILTERSPEC input_profile_format_filters[] =
{{L"All supported types", L"*.lame;*.sndfe"},
{L"LAME Profile", L"*.lame"},
{L"Libsndfile Encoder Profile", L"*.sndfe"}};

#endif
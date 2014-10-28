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

#ifndef PCH_STDAFX_H
#define PCH_STDAFX_H

#define OEMRESOURCE /** Enable OEM resources */
#define STRICT
#define WIN32_LEAN_AND_MEAN

#ifdef _DEBUG
#define METHOD_ASSERT(left, compare_op, right) assert((left) compare_op (right))
#else
#define METHOD_ASSERT(left, compare_op, right) left
#endif

#ifdef _MSC_VER
#define NOMINMAX
#endif

/** C++ standard headers */
#include <cassert>
#include <exception>
#include <fstream>
#include <memory>
#include <string>
#include <typeinfo>
#ifdef _DEBUG
#include <limits>
#endif

/** Windows headers */
#include <Windows.h>
#include <windowsx.h>
#include <Commctrl.h>
#include <Shobjidl.h>

#ifdef _MSC_VER
typedef SSIZE_T ssize_t; /** mpg123 typedef */
#define noexcept _NOEXCEPT /** implementation didn't define noexcpt */
#endif

/** Windows defines */
#include "targetver.h"

/** Standard headers for MSVC */
#include "msinttypes/inttypes.h"

/** Third-party libraries */
#include "libsndfile/sndfile.h"  /** Sampled sound reader and writer */
#include "mpg123/mpg123.h"       /** MPEG decoder */
#include "lame/lame.h"           /** MPEG encoder */

/** Resources */
#include "resources/resource.h"

/** Core */
#include "core/common.h"
#include "core/exceptions.h"
#include "core/rst_lock.h"
#include "core/rst_thread.h"
#include "core/file_reader.h"
#include "core/file_writer.h"

/** Wrappers for third-party libraries */
#include "codecs/samples.h"
#include "codecs/decoder.h"
#include "codecs/encoder.h"
#include "codecs/rst_mpg123.h"
#include "codecs/rst_sndfile_decoder.h"
#include "codecs/rst_sndfile_encoder.h"
#include "codecs/rst_lame.h"

/* RustyCoder engine */
#include "engine/codec_controller.h"
#include "engine/settings_manager.h"
#include "engine/job.h"

/** Win32 control wrappers */
#include "controls/event_handler_interface.h"
#include "controls/global_window_procedure.h"
#include "controls/window.h"
#include "controls/msgbox.h"
#include "controls/button.h"
#include "controls/label.h"
#include "controls/menubar.h"
#include "controls/open_file_dialog.h"
#include "controls/open_folder_dialog.h"
#include "controls/panel.h"
#include "controls/report_list_view.h"
#include "controls/save_file_dialog.h"
#include "controls/single_line_text_box.h"
#include "controls/timer.h"
#include "controls/vertical_split_window.h"

/** Misc */
#include "core/win_utils.h"

#endif
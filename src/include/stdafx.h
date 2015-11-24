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

#ifndef PCH_STDAFX_H
#define PCH_STDAFX_H

#define WIDEN_STRING_HELPER(x, y) x##y
#define WIDEN_STRING(s) WIDEN_STRING_HELPER(L,s)

#define OEMRESOURCE /** Enable OEM resources */
#define STRICT
#define WIN32_LEAN_AND_MEAN

#ifdef _DEBUG
#define ASSERT_METHOD(left, compare_op, right) assert((left) compare_op (right))
#else
#define ASSERT_METHOD(left, compare_op, right) left
#endif

#ifdef _MSC_VER
#define NOMINMAX
#define _SCL_SECURE_NO_WARNINGS
#pragma warning(disable:4265)
#pragma warning(disable:4365)
#pragma warning(disable:4458)
#pragma warning(disable:4514)
#pragma warning(disable:4571)
#pragma warning(disable:4625)
#pragma warning(disable:4626)
#pragma warning(disable:4668)
#pragma warning(disable:4710)
#pragma warning(disable:4711)
#pragma warning(disable:4820)
#pragma warning(disable:4917)
#endif

/** C++ standard headers */
#include <array>
#include <atomic>
#include <cassert>
#include <chrono>
#include <exception>
#include <fstream>
#include <functional>
#include <memory>
#include <string>
#include <thread>
#include <typeinfo>
#include <unordered_map>
#include <vector>
#ifdef _DEBUG
#include <limits>
#endif

/** Windows headers */
#include <Windows.h>
#include <windowsx.h>
#include <Commctrl.h>
#include <Shlwapi.h>
#include <Shobjidl.h>
#include <Synchapi.h>

/** Boost Filesystem */
#include <boost/filesystem.hpp>

#ifdef _MSC_VER
#undef _SCL_SECURE_NO_WARNINGS
#endif

#ifdef _MSC_VER
typedef SSIZE_T ssize_t; /** mpg123 typedef */
#endif

/** Windows defines */
#include "targetver.h"

/** Third-party libraries */
#include "libsndfile/sndfile.h"  /** Sampled sound reader and writer */
#include "lame/lame.h"           /** MPEG encoder */
#include "mpg123/mpg123.h"       /** MPEG decoder */

/** Resources */
#include "resources/resource.h"

#ifdef _MSC_VER
#pragma warning(default:4265)
#pragma warning(default:4571)
#pragma warning(default:4625)
#pragma warning(default:4626)
#pragma warning(default:4668)
#pragma warning(default:4917)
#endif

#endif
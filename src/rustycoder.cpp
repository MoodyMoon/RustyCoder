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
#include "RustyCoder.h"

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE /* hPrevInstance */, LPSTR /* lpszArgument */, int nCmdShow)
{
    #ifdef _DEBUG
    assert(std::numeric_limits<char>::min() == -128);
    assert(std::numeric_limits<char>::max() == 127);
    assert(std::numeric_limits<unsigned char>::max() == 255u);
    assert(std::numeric_limits<short>::min() == -32768);
    assert(std::numeric_limits<short>::max() == 32767);
    assert(std::numeric_limits<unsigned short>::max() == 65535u);
    assert(std::numeric_limits<int>::min() == -2147483647l - 1);
    assert(std::numeric_limits<int>::max() == 2147483647l);
    assert(std::numeric_limits<unsigned int>::max() == 4294967295ul);
    assert(std::numeric_limits<long long>::min() == -9223372036854775807ll - 1);
    assert(std::numeric_limits<long long>::max() == 9223372036854775807ll);
    assert(std::numeric_limits<unsigned long long>::max() == 18446744073709551615ull);
    #endif
    
    MainForm mainform(hThisInstance, nCmdShow);
    msg_loop_start();
}

WPARAM msg_loop_start(void)
{
    while(GetMessage(&lpMsg, nullptr, 0u, 0u))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&lpMsg);
        /* Send message to WindowProcedure */
        DispatchMessage(&lpMsg);
    }

    return lpMsg.wParam;
}
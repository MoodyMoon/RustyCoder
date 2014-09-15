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
    try
    {
        MainForm mainform(hThisInstance, nCmdShow);
        msg_loop_start();
    }
    catch(const GuiGenericException &ex)
    {
        MsgBox::Show(ex.what());
    }
    
    return 0;
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
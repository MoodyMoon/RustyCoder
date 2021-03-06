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

#ifndef CONTROLS_OPEN_FOLDER_DIALOG_H
#define CONTROLS_OPEN_FOLDER_DIALOG_H

#include"file_dialog_events.h"

namespace rusty
{
namespace controls
{
class OpenFolderDialog
{
    private:
        IFileOpenDialog *pfd = nullptr;
        IFileDialogEvents *pfde = nullptr;
        DWORD dwCookie;

        boost::filesystem::path folder_path;

        bool got_result = false;

    public:
        OpenFolderDialog(const OpenFolderDialog &) = delete;
        OpenFolderDialog & operator=(const OpenFolderDialog &) = delete;

        OpenFolderDialog(HWND hWndParent, FileDialogEvents *events = nullptr);
        bool HasResult(void);
        boost::filesystem::path GetFolder();
        virtual ~OpenFolderDialog(void);
};
}
}

#endif
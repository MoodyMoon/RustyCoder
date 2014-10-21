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

#ifndef CONTROLS_SAVE_FILE_DIALOG
#define CONTROLS_SAVE_FILE_DIALOG

class SaveFileDialog
{
    private:
        IFileSaveDialog *pfd = nullptr;
        std::wstring output_file_full_path;
        std::wstring output_file_name_extension;

        bool got_result = false;

    public:
        enum File
        {
            FULL_PATH,
            NAME_AND_EXTENSION,
            PATH_AND_NAME,
            PATH,
            NAME,
            EXTENSION
        };

        SaveFileDialog(const SaveFileDialog &) = delete;
        SaveFileDialog & operator=(const SaveFileDialog &) = delete;

        SaveFileDialog(HWND hWndParent, const COMDLG_FILTERSPEC * const rgFilterSpec, unsigned int cFileTypes);
        bool HasResult(void);
        std::wstring GetFile(File flag);
        ~SaveFileDialog(void);
};

#endif
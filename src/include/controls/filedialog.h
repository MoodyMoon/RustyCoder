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

#ifndef CONTROLS_FILEDIALOG_H
#define CONTROLS_FILEDIALOG_H

class OpenFileDialog
{
    private:
        IFileOpenDialog *pfd = nullptr;
        IShellItemArray *ppenum = nullptr;

        bool got_result = false;
        unsigned long ref_count;

        void GetResult(IShellItem **ppsi, int dwIndex);
        void DestroyResult(IShellItem *ppsi);
        void GetFileNameExtension(IShellItem *ppsi, wchar_t **ppsz_name);
        void GetFullPath(IShellItem *ppsi, wchar_t **ppszName);

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

        OpenFileDialog(const OpenFileDialog &) = delete;
        OpenFileDialog & operator=(const OpenFileDialog &) = delete;

        OpenFileDialog(HWND hWndParent, const COMDLG_FILTERSPEC * const rgFilterSpec, unsigned int cFileTypes);
        bool HasResult(void);
        std::wstring GetFile(unsigned long dwIndex, File flag);
        ~OpenFileDialog(void);
};
#endif

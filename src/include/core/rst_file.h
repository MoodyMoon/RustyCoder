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

#ifndef CORE_RST_FILE_H
#define CORE_RST_FILE_H

class RustyFile
{
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

    RustyFile() = delete;
    RustyFile(const RustyFile &) = delete;
    RustyFile & operator=(const RustyFile &) = delete;

    static std::wstring GetFile(std::wstring file_full_path, File flag);
};

#endif
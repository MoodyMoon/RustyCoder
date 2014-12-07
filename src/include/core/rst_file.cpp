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
#include "rst_file.h"

std::wstring RustyFile::GetFile(std::wstring file_full_path, File flag)
{
    assert(file_full_path.empty() == false);

    while(file_full_path.back() == '.')
    {
        file_full_path.pop_back();
    }

    switch(flag)
    {
        case File::NAME_AND_EXTENSION:
        {
            std::wstring::size_type pos1 = file_full_path.find_last_of(L"/\\");
            file_full_path = file_full_path.substr(pos1 + 1u);
            break;
        }
        case File::PATH_AND_NAME:
        {
            std::wstring::size_type pos1 = file_full_path.find_last_of(L"/\\") + 1u;
            std::wstring::size_type pos2;

            std::wstring str1 = file_full_path.substr(0u, pos1);
            file_full_path = file_full_path.substr(pos1);

            pos1 = file_full_path.find_last_of(L'.');

            if(pos1 != file_full_path.npos)
            {
                pos2 = file_full_path.find(L' ', pos1 + 1u);
                if(pos2 == file_full_path.npos)
                    file_full_path = file_full_path.substr(0u, pos1);
            }

            file_full_path = str1.append(file_full_path);
            break;
        }
        case File::PATH:
        {
            file_full_path = file_full_path.substr(0u, file_full_path.find_last_of(L"/\\"));
            break;
        }
        case File::NAME:
        {
            std::wstring::size_type pos1 = file_full_path.find_last_of(L"/\\") + 1u;
            std::wstring::size_type pos2;

            file_full_path = file_full_path.substr(pos1);

            pos1 = file_full_path.find_last_of(L'.');

            if(pos1 != file_full_path.npos)
            {
                pos2 = file_full_path.find(L' ', pos1 + 1u);
                if(pos2 == file_full_path.npos)
                    file_full_path = file_full_path.substr(0u, pos1);
            }
            break;
        }
        case File::EXTENSION:
        {
            std::wstring::size_type pos1 = file_full_path.find_last_of(L"/\\") + 1u;
            std::wstring::size_type pos2;

            file_full_path = file_full_path.substr(pos1);
            pos1 = file_full_path.find_last_of(L'.');

            if(pos1 != file_full_path.npos)
            {
                pos2 = file_full_path.find(L' ', pos1 + 1u);
                if(pos2 == file_full_path.npos)
                    file_full_path = file_full_path.substr(pos1 + 1u);
                else
                    file_full_path.clear();
            }
            else
                file_full_path.clear();
            break;
        }
    }

    return file_full_path;
}

std::wstring RustyFile::GetFile(std::wstring file_name, FileName flag)
{
    assert(file_name.empty() == false);

    while(file_name.back() == '.')
    {
        file_name.pop_back();
    }

    switch(flag)
    {
        case FileName::NAME_ONLY:
        {
            std::wstring::size_type pos1 = file_name.find_last_of(L'.');
            std::wstring::size_type pos2;

            if(pos1 != file_name.npos)
            {
                pos2 = file_name.find(L' ', pos1 + 1u);
                if(pos2 == file_name.npos)
                    file_name = file_name.substr(0u, pos1);
            }
            break;
        }
        case FileName::EXTENSION_ONLY:
        {
            std::wstring::size_type pos1 = file_name.find_last_of(L'.');
            std::wstring::size_type pos2;

            pos1 = file_name.find_last_of(L'.');

            if(pos1 != file_name.npos)
            {
                pos2 = file_name.find(L' ', pos1 + 1u);
                if(pos2 == file_name.npos)
                    file_name = file_name.substr(pos1 + 1u);
                else
                    file_name.clear();
            }
            else
                file_name.clear();
            break;
        }
    }

    return file_name;
}
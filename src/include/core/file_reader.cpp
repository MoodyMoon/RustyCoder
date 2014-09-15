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
#include "file_reader.h"

FileReader::FileReader(const char * const file, bool seek_to_end)
{
    std::ifstream::openmode openmode = std::ifstream::in | std::ifstream::binary;

    if(seek_to_end)
        openmode |= std::ifstream::ate;

    ifs.open(file, openmode);

    if(ifs.fail())
        throw ReadFileException("FileReader", ifs.rdstate(), "Cannot open the specified file.");

    if(!seek_to_end)
    {
        ifs.seekg(0, std::ifstream::end);
        if(ifs.fail())
            throw SeekException("FileReader", ifs.rdstate(), "Cannot perform seeking on the file.");
    }

    file_size = ifs.tellg();
    if(ifs.fail())
        throw SeekException("FileReader", ifs.rdstate(), "Cannot get file size.");

    if(!seek_to_end)
    {
        ifs.seekg(0, std::ifstream::beg);
        if(ifs.fail())
            throw SeekException("FileReader", ifs.rdstate(), "Cannot perform seeking on the file.");
    }
}

uint64_t FileReader::GetFileLength() const noexcept
{
    return file_size;
}

uint64_t FileReader::Seek(SeekPosition position, int64_t offset)
{
    std::ifstream::seekdir way;
    switch(position)
    {
        case START:
            way = std::ifstream::beg;
            break;
        case CURRENT:
            way = std::ifstream::cur;
            break;
        default:
            way = std::ifstream::end;
    }

    ifs.seekg(offset, way);
    if(ifs.fail())
        throw SeekException("FileReader", ifs.rdstate(), "Cannot perform seeking on the file.");
    
    std::streampos pos = ifs.tellg();
    if(ifs.fail())
        throw SeekException("FileReader", ifs.rdstate(), "Cannot get the current seek position.");

    return pos;
}

uint64_t FileReader::Tell(void)
{
    std::streampos pos = ifs.tellg();
    if(ifs.fail())
        throw SeekException("FileReader", ifs.rdstate(), "Cannot get the current seek position.");

    return pos;
}

uint32_t FileReader::Read(char * const buffer, uint32_t read_count)
{
    ifs.read(buffer, read_count);
    if(ifs.fail())
        throw ReadFileException("FileReader", ifs.rdstate(), "Cannot read file.");

    return static_cast<uint32_t>(ifs.gcount());
}

FileReader::~FileReader()
{
    ifs.close();
}
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
#include "file_writer.h"

FileWriter::FileWriter(const char * const file)
{
    ofs.open(file, std::ofstream::out | std::ofstream::binary);

    if(ofs.fail())
        throw WriteFileException("FileWriter", ofs.rdstate(), "Cannot open the specified file.");
}

uint64_t FileWriter::Seek(SeekPosition position, int64_t offset)
{
    std::ofstream::seekdir way;

    switch(position)
    {
        case START:
            way = std::ofstream::beg;
            break;
        case CURRENT:
            way = std::ofstream::cur;
            break;
        default:
            way = std::ofstream::end;
    }

    ofs.seekp(offset, way);

    if(ofs.fail())
        throw SeekException("FileWriter", ofs.rdstate(), "Cannot perform seeking on the file.");

    std::streampos pos = ofs.tellp();
    if(ofs.fail())
        throw SeekException("FileWriter", ofs.rdstate(), "Cannot get the current seek position.");

    return pos;
}

uint64_t FileWriter::Tell(void)
{
    std::streampos pos = ofs.tellp();
    if(ofs.fail())
        throw SeekException("FileWriter", ofs.rdstate(), "Cannot get the current seek position.");

    return pos;
}

void FileWriter::Write(const char * const buffer, uint32_t write_count)
{
    ofs.write(buffer, write_count);
    if(ofs.fail())
        throw WriteFileException("FileWriter", ofs.rdstate(), "Cannot write to file.");
}

FileWriter::~FileWriter()
{
    ofs.close();
}
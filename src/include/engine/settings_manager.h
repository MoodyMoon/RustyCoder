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

#ifndef ENGINE_SETTINGS_MANAGER_H
#define ENGINE_SETTINGS_MANAGER_H

class SettingsManager
{
    private:
        enum DataTypeIdentifier
        {
            STRING = 1,
            INT_S8 = 2,
            INT_U8 = 3,
            INT_S16 = 4,
            INT_U16 = 5,
            INT_S32 = 6,
            INT_U32 = 7,
            INT_S64 = 8,
            INT_U64 = 9,
            FLOAT = 10,
            DOUBLE = 11,
            BOOL = 12
        };

        static void Rev1Read(LameOptions &profile, FileReader &reader, std::string &file_path);
        static void Rev1Read(SndFileEncoderOptions &profile, FileReader &reader, std::string &file_path);

        static void CorruptedFileThrow(std::string &file_path);

        static void Read(FileReader &reader, int8_t &value);
        static void Read(FileReader &reader, uint8_t &value);
        static void Read(FileReader &reader, int16_t &value);
        static void Read(FileReader &reader, uint16_t &value);
        static void Read(FileReader &reader, int32_t &value);
        static void Read(FileReader &reader, uint32_t &value);
        static void Read(FileReader &reader, int64_t &value);
        static void Read(FileReader &reader, uint64_t &value);
        static void Read(FileReader &reader, float &value);
        static void Read(FileReader &reader, double &value);
        static void Read(FileReader &reader, bool &value, std::string &file_path);
        static void Read(FileReader &reader, std::string &value, std::string &file_path);

        static void Write(FileWriter &writer, int8_t &value);
        static void Write(FileWriter &writer, uint8_t &value);
        static void Write(FileWriter &writer, int16_t &value);
        static void Write(FileWriter &writer, uint16_t &value);
        static void Write(FileWriter &writer, int32_t &value);
        static void Write(FileWriter &writer, uint32_t &value);
        static void Write(FileWriter &writer, int64_t &value);
        static void Write(FileWriter &writer, uint64_t &value);
        static void Write(FileWriter &writer, float &value);
        static void Write(FileWriter &writer, double &value);
        static void Write(FileWriter &writer, bool &value);
        static void Write(FileWriter &writer, std::string &value);

        static size_t HasElement(int8_t &value, int8_t value_array[], size_t value_array_size);
        static size_t HasElement(uint8_t &value, uint8_t value_array[], size_t value_array_size);
        static size_t HasElement(int16_t &value, int16_t value_array[], size_t value_array_size);
        static size_t HasElement(uint16_t &value, uint16_t value_array[], size_t value_array_size);
        static size_t HasElement(int32_t &value, int32_t value_array[], size_t value_array_size);
        static size_t HasElement(uint32_t &value, uint32_t value_array[], size_t value_array_size);
        static size_t HasElement(int64_t &value, int64_t value_array[], size_t value_array_size);
        static size_t HasElement(uint64_t &value, uint64_t value_array[], size_t value_array_size);
        static size_t HasElement(bool &value, bool value_array[], size_t value_array_size);
        static size_t HasElement(std::string &value, std::string value_array[], size_t value_array_size);

        static bool IsEqual(int8_t &value1, int8_t &value2);
        static bool IsEqual(uint8_t &value1, uint8_t &value2);
        static bool IsEqual(int16_t &value1, int16_t &value2);
        static bool IsEqual(uint16_t &value1, uint16_t &value2);
        static bool IsEqual(int32_t &value1, int32_t &value2);
        static bool IsEqual(uint32_t &value1, uint32_t &value2);
        static bool IsEqual(int64_t &value1, int64_t &value2);
        static bool IsEqual(uint64_t &value1, uint64_t &value2);
        static bool IsEqual(bool &value1, bool &value2);
        static bool IsEqual(std::string &value1, std::string &value2);

    public:
        SettingsManager(const SettingsManager &) = delete;
        SettingsManager & operator=(const SettingsManager &) = delete;

        static void Read(LameOptions &profile, std::string file_path);
        static void Read(SndFileEncoderOptions &profile, std::string file_path);
        static void Write(LameOptions &profile, std::string file_path);
        static void Write(SndFileEncoderOptions &profile, std::string file_path);
};

#endif
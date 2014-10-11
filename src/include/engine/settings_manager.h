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

template<class T>
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

        void Rev1Read(FileReader &reader);

        void CorruptedFileThrow(void);

        void Read(FileReader &reader, int8_t &value);
        void Read(FileReader &reader, uint8_t &value);
        void Read(FileReader &reader, int16_t &value);
        void Read(FileReader &reader, uint16_t &value);
        void Read(FileReader &reader, int32_t &value);
        void Read(FileReader &reader, uint32_t &value);
        void Read(FileReader &reader, int64_t &value);
        void Read(FileReader &reader, uint64_t &value);
        void Read(FileReader &reader, float &value);
        void Read(FileReader &reader, double &value);
        void Read(FileReader &reader, bool &value);
        void Read(FileReader &reader, std::string &value);

        void Write(FileWriter &writer, int8_t &value);
        void Write(FileWriter &writer, uint8_t &value);
        void Write(FileWriter &writer, int16_t &value);
        void Write(FileWriter &writer, uint16_t &value);
        void Write(FileWriter &writer, int32_t &value);
        void Write(FileWriter &writer, uint32_t &value);
        void Write(FileWriter &writer, int64_t &value);
        void Write(FileWriter &writer, uint64_t &value);
        void Write(FileWriter &writer, float &value);
        void Write(FileWriter &writer, double &value);
        void Write(FileWriter &writer, bool &value);
        void Write(FileWriter &writer, std::string &value);

        size_t HasElement(int8_t &value, int8_t value_array[], size_t value_array_size);
        size_t HasElement(uint8_t &value, uint8_t value_array[], size_t value_array_size);
        size_t HasElement(int16_t &value, int16_t value_array[], size_t value_array_size);
        size_t HasElement(uint16_t &value, uint16_t value_array[], size_t value_array_size);
        size_t HasElement(int32_t &value, int32_t value_array[], size_t value_array_size);
        size_t HasElement(uint32_t &value, uint32_t value_array[], size_t value_array_size);
        size_t HasElement(int64_t &value, int64_t value_array[], size_t value_array_size);
        size_t HasElement(uint64_t &value, uint64_t value_array[], size_t value_array_size);
        size_t HasElement(bool &value, bool value_array[], size_t value_array_size);
        size_t HasElement(std::string &value, std::string value_array[], size_t value_array_size);

        bool IsEqual(int8_t &value1, int8_t &value2);
        bool IsEqual(uint8_t &value1, uint8_t &value2);
        bool IsEqual(int16_t &value1, int16_t &value2);
        bool IsEqual(uint16_t &value1, uint16_t &value2);
        bool IsEqual(int32_t &value1, int32_t &value2);
        bool IsEqual(uint32_t &value1, uint32_t &value2);
        bool IsEqual(int64_t &value1, int64_t &value2);
        bool IsEqual(uint64_t &value1, uint64_t &value2);
        bool IsEqual(bool &value1, bool &value2);
        bool IsEqual(std::string &value1, std::string &value2);

    public:
        std::string input_file_path;
        std::string output_file_path;
        T profile;

        SettingsManager() = default;
        SettingsManager(const SettingsManager &) = delete;
        SettingsManager & operator=(const SettingsManager &) = delete;

        void Read(std::string file_path);
        void Write(std::string file_path);
};

#endif
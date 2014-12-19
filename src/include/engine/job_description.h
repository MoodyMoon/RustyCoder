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

#ifndef ENGINE_JOB_DESCRIPTION_H
#define ENGINE_JOB_DESCRIPTION_H

class JobDescription
{
    private:
        bool encoder_id_set = false;

        std::string source_file_full_path;
        std::string output_path;
        std::string output_file_name;
        std::string output_file_extension;
        std::string profile_full_path;
        Decoder<void>::ID decoder_id;
        Encoder<void>::ID encoder_id;
        Job::State state;

        void SetDecoderID(const std::string &source_file_full_path);
        void SetEncoderID(const std::string &profile_full_path);
        void SetOutputFileExtension(const std::string &profile_full_path, const std::string &output_file_extension);

    public:
        JobDescription(const std::string &source_file_full_path);

        const std::string & GetSourceFileFullPath(void) const noexcept;
        const std::string & GetOutputPath(void) const noexcept;
        const std::string & GetOutputFileName(void) const noexcept;
        const std::string & GetOutputFileExtension(void) const noexcept;
        const std::string & GetProfileFullPath(void) const noexcept;
        Decoder<void>::ID GetDecoderID(void) const noexcept;
        Encoder<void>::ID GetEncoderID(void) const noexcept;
        Job::State GetState(void) const noexcept;

        void SetOutputPath(const std::string &output_path);
        void SetOutputFileName(const std::string &output_file_name);
        void SetProfileFullPath(const std::string &profile_full_path);
        void SetState(Job::State state) noexcept;
};

#endif
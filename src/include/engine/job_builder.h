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

#ifndef ENGINE_JOB_BUILDER_H
#define ENGINE_JOB_BUILDER_H

#include "../controls/msg_box.h"
#include "../codecs/common.h"
#include "../codecs/decoder.h"
#include "../codecs/encoder.h"
#include "job_runner.h"

namespace rusty
{
namespace engine
{
class JobBuilder
{
    public:
        class CallbackInterface;

        class CompletedBuilder
        {
            friend class JobBuilder;

            private:
                boost::filesystem::path input_file_path;
                codecs::Decoder<void>::ID estimated_decoder_id;
                boost::filesystem::path encoder_profile_path;
                codecs::Encoder<void>::ID estimated_encoder_id;
                boost::filesystem::path output_file_path;

            public:
                CompletedBuilder(const boost::filesystem::path &input_file_path,
                                 const codecs::Decoder<void>::ID estimated_decoder_id,
                                 const boost::filesystem::path &encoder_profile_path,
                                 const codecs::Encoder<void>::ID estimated_encoder_id,
                                 const boost::filesystem::path &output_file_path);

                const boost::filesystem::path & GetInputFilePath(void) const;
                codecs::Decoder<void>::ID GetEstimatedDecoderID(void) const;
                const boost::filesystem::path & GetEncoderProfilePath(void) const;
                codecs::Encoder<void>::ID GetEstimatedEncoderID(void) const;
                const boost::filesystem::path & GetOutputFilePath(void) const;
        };

    private:
        static const std::unordered_map<std::string, codecs::Decoder<void>::ID> audio_file_extension_to_estimated_decoder_id;
        static const std::unordered_map<std::string, codecs::Encoder<void>::ID> profile_extension_to_estimated_encoder_id;

        boost::filesystem::path input_file_path;
        codecs::Decoder<void>::ID estimated_decoder_id;
        boost::filesystem::path encoder_profile_path;
        bool estimated_encoder_id_set = false;
        codecs::Encoder<void>::ID estimated_encoder_id;
        boost::filesystem::path output_file_path;

        CallbackInterface * const job_builder_callback_interface;

    public:
        JobBuilder(const JobBuilder &) = delete;
        JobBuilder & operator=(const JobBuilder &) = delete;

        JobBuilder(const boost::filesystem::path &input_file_path, CallbackInterface &job_builder_callback_interface);

        const boost::filesystem::path & GetInputFilePath(void) const;
        codecs::Decoder<void>::ID GetEstimatedDecoderID(void) const;
        const boost::filesystem::path & GetEncoderProfilePath(void) const;
        bool IsEstimatedEncoderIDSet(void) const;
        codecs::Encoder<void>::ID GetEstimatedEncoderID(void) const;
        const boost::filesystem::path & GetOutputFilePath(void) const;

        bool IsBuilderCompleted(void) const;
        CompletedBuilder GetCompletedBuilder(void);

        void SetEncoderProfilePath(const boost::filesystem::path &encoder_profile_path);
        void SetOutputFilePath(const boost::filesystem::path &output_file_path);
};

class JobBuilder::CallbackInterface
{
    protected:
        CallbackInterface(void) = default;

    public:
        CallbackInterface(const CallbackInterface &) = delete;
        CallbackInterface & operator=(const CallbackInterface &) = delete;

        virtual void OnInputFilePathChanged(const boost::filesystem::path &input_file_path) = 0;
        virtual void OnEstimatedDecoderIDChanged(codecs::Decoder<void>::ID estimated_decoder_id) = 0;
        virtual void OnEncoderProfilePathChanged(const boost::filesystem::path &encoder_profile_path) = 0;
        virtual void OnEstimatedEncoderIDChanged(codecs::Encoder<void>::ID estimated_encoder_id) = 0;
        virtual void OnOutputFilePathChanged(boost::filesystem::path output_file_path) = 0;

        virtual ~CallbackInterface() {}
};
}
}

#endif
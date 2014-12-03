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

#ifndef ENGINE_JOB_H
#define ENGINE_JOB_H

class Job : public RustyThreadCallbackInterface
{
    private:
        Decoder<void>::ID decoder_id;

        std::unique_ptr<EncoderOptions> encoder_options;
        std::unique_ptr<CodecController> codec_controller;
        RustyLock progress_lock;

        bool started = false;
        bool finished = false;
        bool error_occured = false;

        std::unique_ptr<Exception> error;
        std::unique_ptr<RustyThread> thread;

        virtual DWORD DoSync(void *);

    public:
        Job(const Job &) = delete;
        Job & operator=(const Job &) = delete;

        Job(std::string &source_file_full_path, std::string &output_file_full_path, Decoder<void>::ID decoder_id, SndFileEncoderOptions &options);
        Job(std::string &source_file_full_path, std::string &output_file_full_path, Decoder<void>::ID decoder_id, LameOptions &options);

        void StartAsync(void);
        void StopSync(void);
        bool IsStartedSync(void);
        bool IsFinishedSync(void);
        bool HasError(void);
        Exception * GetError(void);

        virtual ~Job(void);
};

#endif
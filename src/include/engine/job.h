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
    public:
        enum State
        {
            NOT_READY,
            READY,
            RUNNING,
            PAUSE,
            DONE,
            ERROR_OCCURED
        };

    private:
        std::unique_ptr<EncoderOptions> encoder_options;
        std::unique_ptr<CodecController> codec_controller;

        std::atomic<State> state = State::READY;

        std::atomic<uint64_t> written_frame_count = 0ull;
        std::atomic<uint64_t> total_frame_count;

        std::atomic<std::unique_ptr<Exception>> error;
        std::unique_ptr<RustyThread> thread;

        virtual DWORD DoSync(void *);

    public:
        static const std::unordered_map<State, std::string> state_to_string;

        Job(const Job &) = delete;
        Job & operator=(const Job &) = delete;

        Job(const std::string &source_file_full_path, const std::string &output_file_full_path, Decoder<void>::ID decoder_id, const LameOptions &lame_options);
        Job(const std::string &source_file_full_path, const std::string &output_file_full_path, Decoder<void>::ID decoder_id, const SndFileEncoderOptions &sndfileencoder_options);

        void StartAsync(void);
        void PauseSync(void);
        State GetStateSync(void) const noexcept;
        Exception * GetError(void) const noexcept;

        uint64_t GetWrittenFrameCount(void) const noexcept;
        uint64_t GetTotalFrameCount(void) const noexcept;

        virtual ~Job(void);
};

#endif
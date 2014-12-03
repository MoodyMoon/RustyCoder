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
#include "job.h"

Job::Job(std::string &source_file_full_path, std::string &output_file_full_path, Decoder<void>::ID decoder_id, SndFileEncoderOptions &options) : decoder_id(decoder_id), encoder_options(new SndFileEncoderOptions(options))
{
    SndFileEncoderOptions *_encoder_options = static_cast<SndFileEncoderOptions *>(encoder_options.get());

    codec_controller.reset(new CodecController(source_file_full_path, output_file_full_path, decoder_id, *_encoder_options));
}

Job::Job(std::string &source_file_full_path, std::string &output_file_full_path, Decoder<void>::ID decoder_id, LameOptions &options) : decoder_id(decoder_id), encoder_options(new LameOptions(options))
{
    LameOptions *_encoder_options = static_cast<LameOptions *>(encoder_options.get());

    codec_controller.reset(new CodecController(source_file_full_path, output_file_full_path, decoder_id, *_encoder_options));
}

void Job::StartAsync(void)
{
    bool do_not_continue = false;
    progress_lock.Lock();
    if(!started && !finished && !error)
        started = true;
    else
        do_not_continue = true;
    progress_lock.Unlock();

    if(do_not_continue)
        return;

    thread.reset(new RustyThread(this, nullptr, RustyThread::Priority::NORMAL));
}

void Job::StopSync(void)
{
    progress_lock.Lock();
    if(started)
        started = false;
    bool _started = started;
    progress_lock.Unlock();

    if(!_started)
        thread.reset();
}

bool Job::IsStartedSync(void)
{
    progress_lock.Lock();
    bool _started = started;
    progress_lock.Unlock();
    return _started;
}

bool Job::IsFinishedSync(void)
{
    progress_lock.Lock();
    bool _finished = finished;
    progress_lock.Unlock();
    return _finished;
}

bool Job::HasError(void)
{
    progress_lock.Lock();
    bool _error_occured = error_occured;
    progress_lock.Unlock();
    return _error_occured;
}

Exception * Job::GetError(void)
{
    progress_lock.Lock();
    Exception *_error = error.get();
    progress_lock.Unlock();
    return _error;
}

DWORD Job::DoSync(void *)
{
    CodecController *_codec_controller = codec_controller.get();

    try
    {
        do
        {
            progress_lock.Lock();
            if(_codec_controller->CanConvert())
                _codec_controller->Convert();
            else
            {
                finished = true;
                started = false;
                codec_controller.reset();
            }
            progress_lock.Unlock();
        }while(IsStartedSync());
    }
    catch(Exception &ex)
    {
        progress_lock.Lock();
        error_occured = true;
        error.reset(new Exception(ex));
        progress_lock.Unlock();
    }

    return 0ul;
}

Job::~Job()
{
    StopSync();
}
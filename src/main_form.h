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

#ifndef GUI_MAIN_FORM_H
#define GUI_MAIN_FORM_H

#include "include/controls/menu_bar.h"
#include "include/controls/open_file_dialog.h"
#include "include/controls/open_folder_dialog.h"
#include "include/core/windows_utilities.h"
#include "include/engine/job_queue.h"
#include "profile_form.h"

namespace rusty
{
namespace gui
{
class MainForm : public controls::EventHandlerInterface
{
    private:
        class MenuBarEvents;
        class JobReportListViewEvents;
        class BtnBrowseFolderEvents;
        class BtnAddFilesEvents;
        class BtnRemoveFilesEvents;
        class BtnLoadProfileEvents;
        class BtnCreateProfileEvents;
        class BtnStartQueueEvents;
        class BtnPauseQueueEvents;

    private:
        HINSTANCE hInstance = nullptr;

        bool form_loaded = false;

        std::unique_ptr<controls::Window> window;
        std::unique_ptr<controls::MenuBar> menu_bar;
        std::unique_ptr<MenuBarEvents> menu_bar_events;
        std::unique_ptr<controls::ReportListView> job_report_list_view;
        std::unique_ptr<JobReportListViewEvents> job_report_list_view_events;
        std::unique_ptr<controls::Button> btn_add_files;
        std::unique_ptr<BtnAddFilesEvents> btn_add_files_events;
        std::unique_ptr<controls::Button> btn_remove_files;
        std::unique_ptr<BtnRemoveFilesEvents> btn_remove_files_events;
        std::unique_ptr<controls::Button> btn_load_profile;
        std::unique_ptr<BtnLoadProfileEvents> btn_load_profile_events;
        std::unique_ptr<controls::Button> btn_create_profile;
        std::unique_ptr<BtnCreateProfileEvents> btn_create_profile_events;
        std::unique_ptr<controls::Button> btn_browse_folder;
        std::unique_ptr<BtnBrowseFolderEvents> btn_browse_folder_events;
        std::unique_ptr<controls::Button> btn_start_queue;
        std::unique_ptr<BtnStartQueueEvents> btn_start_queue_events;
        std::unique_ptr<controls::Button> btn_pause_queue;
        std::unique_ptr<BtnPauseQueueEvents> btn_pause_queue_events;

        std::unique_ptr<ProfileForm> profile_form;

        void OnCreate(HWND hWnd);
        void OnSize(WPARAM wParam, LPARAM lParam);
        void OnBeforeDestroy(void);

    public:
        MainForm(const MainForm &) = delete;
        MainForm & operator=(const MainForm &) = delete;

        MainForm(HINSTANCE hThisInstance, int nCmdShow);

        virtual LRESULT HandleEvent(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

class MainForm::MenuBarEvents
{
    friend class MainForm;

    private:
        MainForm * const main_form = nullptr;

        void File_AddFiles_OnClick(void);
        void File_Exit_OnClick(void);

    public:
        MenuBarEvents(const controls::MenuBar &) = delete;
        MenuBarEvents & operator=(const MenuBarEvents &) = delete;

        MenuBarEvents(MainForm * const main_form);
};

class MainForm::JobReportListViewEvents : public engine2::JobQueue::Callback
{
    friend class MainForm;

    private:
        MainForm * const main_form = nullptr;

        engine2::JobQueue job_queue;

        virtual void OnInputFilePathChanged(const boost::filesystem::path &input_file_path, unsigned int job_index);
        virtual void OnEstimatedDecoderIDChanged(codecs::Decoder<void>::ID estimated_decoder_id, unsigned int job_index);
        virtual void OnEncoderProfilePathChanged(const boost::filesystem::path &encoder_profile_path, unsigned int job_index);
        virtual void OnEstimatedEncoderIDChanged(codecs::Encoder<void>::ID estimated_encoder_id, unsigned int job_index);
        virtual void OnOutputFilePathChanged(boost::filesystem::path output_file_path, unsigned int job_index);

        virtual void OnStateChanged(engine2::Common::JobBuilderRunnerState state, unsigned int job_index);
        virtual void OnErrorOccurred(const core::Exception *error, unsigned int job_index);
        virtual void OnWrittenFrameCountChanged(uint64_t written_frame_count, unsigned int job_index);
        virtual void OnTotalFrameCountChanged(uint64_t total_frame_count, unsigned int job_index);

    public:
        JobReportListViewEvents(const JobReportListViewEvents &) = delete;
        JobReportListViewEvents & operator=(const JobReportListViewEvents &) = delete;

        JobReportListViewEvents(MainForm * const main_form);

        void AddJob(void);
        void SetEncoderProfilePath(void);
        void SetOutputPath(void);
        void RemoveJob(void);
        void StartQueue(void);
        void PauseQueue(void);

        ~JobReportListViewEvents(void);
};

class MainForm::BtnBrowseFolderEvents
{
    friend class MainForm;

    private:
        MainForm * const main_form = nullptr;

        void OnClick(void);

    public:
        BtnBrowseFolderEvents(const BtnBrowseFolderEvents &) = delete;
        BtnBrowseFolderEvents & operator=(const BtnBrowseFolderEvents &) = delete;

        BtnBrowseFolderEvents(MainForm * const main_form) : main_form(main_form) {}
};

class MainForm::BtnAddFilesEvents
{
    friend class MainForm;

    private:
        MainForm * const main_form = nullptr;

        void OnClick(void);

    public:
        BtnAddFilesEvents(const BtnAddFilesEvents &) = delete;
        BtnAddFilesEvents & operator=(const BtnAddFilesEvents &) = delete;

        BtnAddFilesEvents(MainForm * const main_form) : main_form(main_form) {}
};

class MainForm::BtnRemoveFilesEvents
{
    friend class MainForm;

    private:
        MainForm * const main_form = nullptr;

        void OnClick(void);

    public:
        BtnRemoveFilesEvents(const BtnRemoveFilesEvents &) = delete;
        BtnRemoveFilesEvents & operator=(const BtnRemoveFilesEvents &) = delete;

        BtnRemoveFilesEvents(MainForm * const main_form) : main_form(main_form) {}
};

class MainForm::BtnLoadProfileEvents
{
    friend class MainForm;

    private:
        MainForm * const main_form = nullptr;

        void OnClick(void);

    public:
        BtnLoadProfileEvents(const BtnLoadProfileEvents &) = delete;
        BtnLoadProfileEvents & operator=(const BtnLoadProfileEvents &) = delete;

        BtnLoadProfileEvents(MainForm * const main_form) : main_form(main_form) {}
};

class MainForm::BtnCreateProfileEvents
{
    friend class MainForm;

    private:
        MainForm * const main_form = nullptr;

        void OnClick(void);

    public:
        BtnCreateProfileEvents(const BtnCreateProfileEvents &) = delete;
        BtnCreateProfileEvents & operator=(const BtnCreateProfileEvents &) = delete;

        BtnCreateProfileEvents(MainForm * const main_form) : main_form(main_form) {}
};

class MainForm::BtnStartQueueEvents
{
    friend class MainForm;

    private:
        MainForm * const main_form = nullptr;

        void OnClick(void);

    public:
        BtnStartQueueEvents(const BtnStartQueueEvents &) = delete;
        BtnStartQueueEvents & operator=(const BtnStartQueueEvents &) = delete;

        BtnStartQueueEvents(MainForm * const main_form) : main_form(main_form) {}
};

class MainForm::BtnPauseQueueEvents
{
    friend class MainForm;

    private:
        MainForm * const main_form = nullptr;

        void OnClick(void);

    public:
        BtnPauseQueueEvents(const BtnPauseQueueEvents &) = delete;
        BtnPauseQueueEvents & operator=(const BtnPauseQueueEvents &) = delete;

        BtnPauseQueueEvents(MainForm * const main_form) : main_form(main_form) {}
};
}
}

#endif
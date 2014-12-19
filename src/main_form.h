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

#ifndef GUI_MAIN_FORM_H
#define GUI_MAIN_FORM_H

#include "file_extension_filters.h"
#include "profile_form.h"

class MainForm : public EventHandlerInterface
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

        HINSTANCE hInstance = nullptr;

        bool form_loaded = false;

        std::unique_ptr<Window> window;
        std::unique_ptr<MenuBar> menu_bar;
        std::unique_ptr<MenuBarEvents> menu_bar_events;
        std::unique_ptr<ReportListView> job_report_list_view;
        std::unique_ptr<JobReportListViewEvents> job_report_list_view_events;
        std::unique_ptr<Button> btn_add_files;
        std::unique_ptr<BtnAddFilesEvents> btn_add_files_events;
        std::unique_ptr<Button> btn_remove_files;
        std::unique_ptr<BtnRemoveFilesEvents> btn_remove_files_events;
        std::unique_ptr<Button> btn_load_profile;
        std::unique_ptr<BtnLoadProfileEvents> btn_load_profile_events;
        std::unique_ptr<Button> btn_create_profile;
        std::unique_ptr<BtnCreateProfileEvents> btn_create_profile_events;
        std::unique_ptr<Button> btn_browse_folder;
        std::unique_ptr<BtnBrowseFolderEvents> btn_browse_folder_events;
        std::unique_ptr<Button> btn_start_queue;
        std::unique_ptr<BtnStartQueueEvents> btn_start_queue_events;
        std::unique_ptr<Button> btn_pause_queue;
        std::unique_ptr<BtnPauseQueueEvents> btn_pause_queue_events;

        std::unique_ptr<Job> job;

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
        MenuBarEvents(const MenuBar &) = delete;
        MenuBarEvents & operator=(const MenuBarEvents &) = delete;

        MenuBarEvents(MainForm * const main_form);
};

class MainForm::JobReportListViewEvents
{
    friend class MainForm;

    private:
        MainForm * const main_form = nullptr;

        /*!
        Queue processor members;
        */

        TimerSync queue_processor;

        static const std::size_t max_simultaneous_jobs_count = 2;

        std::vector<JobDescription> job_descriptions;
        std::unique_ptr<Job> jobs[max_simultaneous_jobs_count];
        std::size_t job_indices_tracker[max_simultaneous_jobs_count];

        uint64_t total_frame_count_uint64[max_simultaneous_jobs_count];
        double total_frame_count_double[max_simultaneous_jobs_count];

        void OnTimerSyncTick(void);

        void ResumeJobsIfAny(void);
        void TryQueueJobs(void);
        void UpdateJobDescriptions(void);
        void CleanActiveQueue(void);
        void TryStopQueueProcessor(void);
        void PauseJobsIfAny(void);

        bool IsQueueFull(void);
        std::size_t GetFreeSlot(void);
        void CreateAndRunJob(const JobDescription *job_description, std::size_t free_slot_index);
        void SetErrorMessage(const Exception *exception, std::size_t row_index);
        std::wstring GetConversionProgress(std::size_t job_index);

    public:
        void AddJobs(HWND hWnd);
        void RemoveSelectedJobs(void);
        void LoadProfile(HWND hWnd);
        void SetOutputPath(HWND hWnd);

        /*!
        Queueing functions
        */
        void StartQueue(void);
        void PauseQueue(void);

        JobReportListViewEvents(const JobReportListViewEvents &) = delete;
        JobReportListViewEvents & operator=(const JobReportListViewEvents &) = delete;

        JobReportListViewEvents(MainForm * const main_form, HWND main_form_handle);

        ~JobReportListViewEvents(void);
};

class MainForm::BtnBrowseFolderEvents
{
    friend class MainForm;

    private:
        MainForm * const main_form = nullptr;

        void OnClick(HWND hWnd);

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

        void OnClick(HWND hWnd);

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

        void OnClick(HWND hWnd);

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

#endif
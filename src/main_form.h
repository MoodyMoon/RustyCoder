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

#include "profile_form.h"

class MainForm : public EventHandlerInterface
{
    private:
        class MenuBarEvents;
        class VerticalSplitWindow1Events;
        class Panel1Events;
        class JobReportListViewEvents;
        class BtnLoadProfileEvents;
        class Panel2Events;
        
        HINSTANCE hInstance = nullptr;

        bool form_loaded = false;

        std::unique_ptr<Window> window;
        std::unique_ptr<MenuBar> menu_bar;
        std::unique_ptr<MenuBarEvents> menu_bar_events;
        std::unique_ptr<VerticalSplitWindow> vertical_split_window1;
        std::unique_ptr<VerticalSplitWindow1Events> vertical_split_window1_events;
        std::unique_ptr<Panel> panel1;
        std::unique_ptr<Panel1Events> panel1_events;
        std::unique_ptr<ReportListView> job_report_list_view;
        std::unique_ptr<JobReportListViewEvents> job_report_list_view_events;
        std::unique_ptr<Label> lbl_file_destination;
        std::unique_ptr<SingleLineTextBox> sltxtbx_file_destination;
        std::unique_ptr<Button> btn_browse;
        std::unique_ptr<Button> btn_load_profile;
        std::unique_ptr<BtnLoadProfileEvents> btn_load_profile_events;
        std::unique_ptr<Button> btn_create_profile;
        std::unique_ptr<Button> btn_convert;
        std::unique_ptr<Panel> panel2;
        std::unique_ptr<Panel2Events> panel2_events;
        std::unique_ptr<Job> job;

        void OnCreate(HWND hWnd);
        void OnSize(HWND hWnd, WPARAM wParam);
        void OnGetMinMaxInfo(MINMAXINFO * const min_max_info);

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

        void File_AddFiles_OnClicked(void);
        void File_Exit_OnClicked(void);

    public:
        MenuBarEvents(const MenuBarEvents &) = delete;
        MenuBarEvents & operator=(const MenuBarEvents &) = delete;

        MenuBarEvents(MainForm * const main_form);
};

class MainForm::VerticalSplitWindow1Events
{
    friend class MainForm;

    private:
        MainForm * const main_form = nullptr;

    public:
        VerticalSplitWindow1Events(const VerticalSplitWindow1Events &) = delete;
        VerticalSplitWindow1Events & operator=(const VerticalSplitWindow1Events &) = delete;

        VerticalSplitWindow1Events(MainForm * const main_form);
};

class MainForm::Panel1Events : public EventHandlerInterface
{
    private:
        MainForm * const main_form = nullptr;
        bool form_loaded = false;

        void OnCreate(HWND hWnd);
        void OnSize(HWND hWnd);

    public:
        Panel1Events(const Panel1Events &) = delete;
        Panel1Events & operator=(const Panel1Events &) = delete;

        Panel1Events(MainForm * const main_form) : main_form(main_form) {}

        virtual LRESULT HandleEvent(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

class MainForm::JobReportListViewEvents
{
    friend class Panel1Events;

    private:
        MainForm * const main_form = nullptr;
        std::vector<std::string> source_file_full_paths;
        std::vector<std::string> output_file_full_paths;
        std::unique_ptr<ProfileForm> profile_form;

    public:
        void AddJobs(HWND hWnd);
        void LoadProfile(void);

        JobReportListViewEvents(const JobReportListViewEvents &) = delete;
        JobReportListViewEvents & operator=(const JobReportListViewEvents &) = delete;

        JobReportListViewEvents(MainForm * const main_form);
};

class MainForm::BtnLoadProfileEvents
{
    friend class Panel1Events;

    private:
        MainForm * const main_form = nullptr;
        void OnClicked(void);

    public:
        BtnLoadProfileEvents(const BtnLoadProfileEvents &) = delete;
        BtnLoadProfileEvents & operator=(const BtnLoadProfileEvents &) = delete;

        BtnLoadProfileEvents(MainForm * const main_form) : main_form(main_form) {}
};

class MainForm::Panel2Events : public EventHandlerInterface
{
    private:
        MainForm * const main_form = nullptr;

    public:
        Panel2Events(const Panel2Events &) = delete;
        Panel2Events & operator=(const Panel2Events &) = delete;

        Panel2Events(MainForm * const main_form) : main_form(main_form) {}

        virtual LRESULT HandleEvent(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

#endif
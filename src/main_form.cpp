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
#include "main_form.h"

MainForm::MainForm(HINSTANCE hThisInstance, int nCmdShow) : hInstance(hThisInstance)
{
    window.reset(new Window(hThisInstance, this, L"MainForm", L"RustyCoder", HWND_DESKTOP, WS_EX_LEFT, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_VISIBLE, nCmdShow, RUSTYCODER_ICON, CW_USEDEFAULT, CW_USEDEFAULT, 750, 550, true));
}

//InitCommonControlsEx is not needed to enabled new theme
void MainForm::OnCreate(HWND hWnd)
{
    menu_bar.reset(new MenuBar());
    menu_bar_events.reset(new MenuBarEvents(this));
    menu_bar->Attach(hWnd);

    const unsigned long window_client_width = Window::GetClientWidth(hWnd);
    const unsigned long window_client_height = Window::GetClientHeight(hWnd);

    job_report_list_view.reset(new ReportListView(hInstance, hWnd, MAINFORM_JOB_REPORT_LIST_VIEW, 0, 0, window_client_width, window_client_height - 40, WS_EX_LEFT, LVS_REPORT | LVS_SHOWSELALWAYS | WS_CHILD | WS_VISIBLE));
    job_report_list_view_events.reset(new JobReportListViewEvents(this, hWnd));

    btn_add_files.reset(new Button(hInstance, L"Add files", hWnd, MAINFORM_BTN_ADD_FILES, 5, window_client_height - 30, 90, 25));
    btn_add_files_events.reset(new BtnAddFilesEvents(this));

    btn_remove_files.reset(new Button(hInstance, L"Remove files", hWnd, MAINFORM_BTN_REMOVE_FILES, 100, window_client_height - 30, 90, 25));
    btn_remove_files_events.reset(new BtnRemoveFilesEvents(this));

    btn_load_profile.reset(new Button(hInstance, L"Load profile", hWnd, MAINFORM_BTN_LOAD_PROFILE, 195, window_client_height - 30, 90, 25));
    btn_load_profile_events.reset(new BtnLoadProfileEvents(this));

    btn_create_profile.reset(new Button(hInstance, L"Create profile", hWnd, MAINFORM_BTN_CREATE_PROFILE, 290, window_client_height - 30, 90, 25));
    btn_create_profile_events.reset(new BtnCreateProfileEvents(this));

    btn_browse_folder.reset(new Button(hInstance, L"Browse folder", hWnd, MAINFORM_BTN_BROWSE_FOLDER, 385, window_client_height - 30, 90, 25));
    btn_browse_folder_events.reset(new BtnBrowseFolderEvents(this));

    btn_start_queue.reset(new Button(hInstance, L"Start queue", hWnd, MAINFORM_BTN_START_QUEUE, window_client_width - 190, window_client_height - 30, 90, 25));
    btn_start_queue_events.reset(new BtnStartQueueEvents(this));

    btn_pause_queue.reset(new Button(hInstance, L"Pause queue", hWnd, MAINFORM_BTN_PAUSE_QUEUE, window_client_width - 95, window_client_height - 30, 90, 25));
    btn_pause_queue_events.reset(new BtnPauseQueueEvents(this));

    form_loaded = true;
}

void MainForm::OnSize(WPARAM wParam, LPARAM lParam)
{
    switch(wParam)
    {
        case SIZE_MAXIMIZED:
        case SIZE_MAXSHOW:
        case SIZE_RESTORED:
        {
            if(!form_loaded)
                return;

            const unsigned long window_client_width = LOWORD(lParam);
            const unsigned long window_client_height = HIWORD(lParam);

            job_report_list_view->ResizeTo(window_client_width, window_client_height - 40);

            btn_add_files->MoveTo(5, window_client_height - 30);

            btn_remove_files->MoveTo(100, window_client_height - 30);

            btn_load_profile->MoveTo(195, window_client_height - 30);

            btn_create_profile->MoveTo(290, window_client_height - 30);

            btn_browse_folder->MoveTo(385, window_client_height - 30);

            btn_start_queue->MoveTo(window_client_width - 190, window_client_height - 30);

            btn_pause_queue->MoveTo(window_client_width - 95, window_client_height - 30);

            break;
        }
    }
}

void MainForm::OnBeforeDestroy()
{
    job_report_list_view_events.reset();
}

MainForm::MenuBarEvents::MenuBarEvents(MainForm * const main_form) : main_form(main_form)
{
    HMENU sub_menu = main_form->menu_bar->CreateSubMenu(L"File", nullptr);
    main_form->menu_bar->CreateMenuItem(L"&Add files", MAINFORM_MENUBAR_FILE_ADDFILES, sub_menu);
    main_form->menu_bar->CreateMenuItem(L"&Exit", MAINFORM_MENUBAR_FILE_EXIT, sub_menu);
}

void MainForm::MenuBarEvents::File_AddFiles_OnClick()
{
    main_form->job_report_list_view_events->AddJobs(main_form->window->GetHandle());
}

void MainForm::MenuBarEvents::File_Exit_OnClick()
{
    main_form->window.reset();
}

MainForm::JobReportListViewEvents::JobReportListViewEvents(MainForm * const main_form, HWND main_form_handle) : main_form(main_form), queue_processor(main_form_handle, 0ull, 200u, false)
{
    std::wstring text(L"File name");
    main_form->job_report_list_view->InsertColumn(250u, 0u, text.c_str());

    text = L"Profile";
    main_form->job_report_list_view->InsertColumn(100u, 1u, text.c_str());

    text = L"Status";
    main_form->job_report_list_view->InsertColumn(100u, 2u, text.c_str());

    text = L"Progress";
    main_form->job_report_list_view->InsertColumn(100u, 3u, text.c_str());

    text = L"Save to";
    main_form->job_report_list_view->InsertColumn(150u, 4u, text.c_str());
}

void MainForm::JobReportListViewEvents::AddJobs(HWND hWnd)
{
    OpenFileDialog open_file_dialog(hWnd, FileExtensionFilters::input_audio_format_filters, sizeof(FileExtensionFilters::input_audio_format_filters) / sizeof(COMDLG_FILTERSPEC), true);

    if(open_file_dialog.HasResult())
    {
        unsigned long result_count = open_file_dialog.GetResultCount();

        unsigned int job_report_list_view_item_count = main_form->job_report_list_view->GetRowCount();
        unsigned int job_report_list_view_item_index;

        std::string source_file;
        std::wstring source_file_w;
        std::string source_file_name;
        std::string source_file_extension;

        main_form->job_report_list_view->SetRedraw(false);

        for(unsigned int i = 0ul; i < result_count; ++i)
        {
            source_file = WindowsUtilities::UTF8_Encode(open_file_dialog.GetFile(i, RustyFile::File::FULL_PATH));
            source_file_name = WindowsUtilities::UTF8_Encode(open_file_dialog.GetFile(i, RustyFile::File::NAME));
            source_file_extension = WindowsUtilities::UTF8_Encode(open_file_dialog.GetFile(i, RustyFile::File::EXTENSION));

            job_report_list_view_item_index = job_report_list_view_item_count + i;

            JobDescription job_description(source_file);

            try
            {
                job_description.SetOutputFileName(source_file_name);

                job_descriptions.push_back(job_description);

                source_file_w = open_file_dialog.GetFile(i, RustyFile::File::NAME_AND_EXTENSION);

                main_form->job_report_list_view->InsertRow(job_report_list_view_item_index, source_file_w.c_str());
                main_form->job_report_list_view->SetCellText(2, job_report_list_view_item_index, WindowsUtilities::UTF8_Decode(Job::state_to_string.at(job_description.GetState())).c_str());
            }
            catch(InvalidArgumentException &ex)
            {
                MsgBox::Show(ex.what(), hWnd);
            }
        }

        main_form->job_report_list_view->SetRedraw(true);

        main_form->job_report_list_view->Redraw();
    }
}

void MainForm::JobReportListViewEvents::RemoveSelectedJobs()
{
    int row_index = main_form->job_report_list_view->GetNextSelectedItem();

    bool needs_redraw = row_index > -1;

    if(needs_redraw)
        main_form->job_report_list_view->SetRedraw(false);

    while(row_index > -1)
    {
        switch(job_descriptions[row_index].GetState())
        {
            case Job::State::RUNNING:
            case Job::State::PAUSE:
            {
                for(std::size_t job_indices_tracker_index = 0ull; job_indices_tracker_index < max_simultaneous_jobs_count; ++job_indices_tracker_index)
                {
                    if(job_indices_tracker[job_indices_tracker_index] == row_index)
                    {
                        if(jobs[job_indices_tracker_index]->GetStateSync() == Job::State::RUNNING)
                        {
                            jobs[job_indices_tracker_index]->PauseSync();
                        }

                        jobs[job_indices_tracker_index].reset();

                        for(std::size_t job_indices_tracker_index2 = 0ull; job_indices_tracker_index2 < max_simultaneous_jobs_count; ++job_indices_tracker_index2)
                        {
                            if(job_indices_tracker[job_indices_tracker_index2] > row_index)
                            {
                                --job_indices_tracker[job_indices_tracker_index2];
                            }
                        }

                        break;
                    }
                }
                break;
            }
        }

        job_descriptions.erase(job_descriptions.begin() + row_index);

        main_form->job_report_list_view->RemoveRow(row_index);

        row_index = main_form->job_report_list_view->GetNextSelectedItem(row_index);
    }

    if(needs_redraw)
    {
        main_form->job_report_list_view->SetRedraw(true);
        main_form->job_report_list_view->Redraw();
    }
}

void MainForm::JobReportListViewEvents::LoadProfile(HWND hWnd)
{
    if(main_form->job_report_list_view->HasSelectedItems())
    {
        OpenFileDialog open_file_dialog(hWnd, FileExtensionFilters::input_profile_format_filters, sizeof(FileExtensionFilters::input_profile_format_filters) / sizeof(COMDLG_FILTERSPEC), false);

        if(open_file_dialog.HasResult())
        {
            std::string profile_full_path(WindowsUtilities::UTF8_Encode(open_file_dialog.GetFile(RustyFile::File::FULL_PATH)));
            std::wstring profile_file_name_extension(open_file_dialog.GetFile(RustyFile::File::NAME_AND_EXTENSION));
            std::string output_file_full_path;
            std::string output_path;

            int row_index = main_form->job_report_list_view->GetNextSelectedItem();

            bool needs_redraw = row_index > -1;

            if(needs_redraw)
                main_form->job_report_list_view->SetRedraw(false);

            while(row_index > -1)
            {
                switch(job_descriptions[row_index].GetState())
                {
                    case Job::State::NOT_READY:
                    case Job::State::READY:
                    {
                        try
                        {
                            job_descriptions[row_index].SetProfileFullPath(profile_full_path);
                            main_form->job_report_list_view->SetCellText(1, row_index, profile_file_name_extension.c_str());
                            main_form->job_report_list_view->SetCellText(2, row_index, WindowsUtilities::UTF8_Decode(Job::state_to_string.at(job_descriptions[row_index].GetState())).c_str());

                            output_path = job_descriptions[row_index].GetOutputPath();

                            if(!output_path.empty())
                            {
                                output_file_full_path = output_path + "\\" + job_descriptions[row_index].GetOutputFileName() + "." + job_descriptions[row_index].GetOutputFileExtension();
                                main_form->job_report_list_view->SetCellText(4, row_index, WindowsUtilities::UTF8_Decode(output_file_full_path).c_str());
                            }
                        }
                        catch(InvalidArgumentException &ex)
                        {
                            SetErrorMessage(&ex, row_index);
                        }
                        catch(ReadFileException &ex)
                        {
                            SetErrorMessage(&ex, row_index);
                        }

                        break;
                    }
                }

                ++row_index;
                row_index = main_form->job_report_list_view->GetNextSelectedItem(row_index);
            }

            if(needs_redraw)
            {
                main_form->job_report_list_view->SetRedraw(true);
                main_form->job_report_list_view->Redraw();
            }
        }
    }
}

void MainForm::JobReportListViewEvents::SetOutputPath(HWND hWnd)
{
    if(main_form->job_report_list_view->HasSelectedItems())
    {
        OpenFolderDialog open_folder_dialog(hWnd);

        if(open_folder_dialog.HasResult())
        {
            std::string output_folder(WindowsUtilities::UTF8_Encode(open_folder_dialog.GetFolder()));
            std::string output_file_extension;
            std::string output_file_full_path;

            int row_index = main_form->job_report_list_view->GetNextSelectedItem();

            bool needs_redraw = row_index > -1;

            if(needs_redraw)
                main_form->job_report_list_view->SetRedraw(false);

            while(row_index > -1)
            {
                switch(job_descriptions[row_index].GetState())
                {
                    case Job::State::NOT_READY:
                    case Job::State::READY:
                    {
                        try
                        {
                            job_descriptions[row_index].SetOutputPath(output_folder);

                            output_file_extension = job_descriptions[row_index].GetOutputFileExtension();

                            if(output_file_extension.empty())
                            {
                                main_form->job_report_list_view->SetCellText(4, row_index, WindowsUtilities::UTF8_Decode(output_folder).c_str());
                            }
                            else
                            {
                                output_file_full_path = output_folder + "\\" + job_descriptions[row_index].GetOutputFileName() + "." + output_file_extension;
                                main_form->job_report_list_view->SetCellText(4, row_index, WindowsUtilities::UTF8_Decode(output_file_full_path).c_str());
                            }

                            main_form->job_report_list_view->SetCellText(2, row_index, WindowsUtilities::UTF8_Decode(Job::state_to_string.at(job_descriptions[row_index].GetState())).c_str());
                        }
                        catch(InvalidArgumentException &ex)
                        {
                            SetErrorMessage(&ex, row_index);
                        }

                        break;
                    }
                }

                ++row_index;
                row_index = main_form->job_report_list_view->GetNextSelectedItem(row_index);
            }

            if(needs_redraw)
            {
                main_form->job_report_list_view->SetRedraw(true);
                main_form->job_report_list_view->Redraw();
            }
        }
    }
}

void MainForm::JobReportListViewEvents::StartQueue()
{
    if(!queue_processor.IsStarted())
    {
        queue_processor.Start();
    }
}

void MainForm::JobReportListViewEvents::PauseQueue()
{
    if(queue_processor.IsStarted())
    {
        PauseJobsIfAny();
        UpdateJobDescriptions();
        CleanActiveQueue();
        queue_processor.Stop();
    }
}

void MainForm::JobReportListViewEvents::OnTimerSyncTick()
{
    ResumeJobsIfAny();

    TryQueueJobs();

    UpdateJobDescriptions();

    CleanActiveQueue();

    TryStopQueueProcessor();
}

void MainForm::JobReportListViewEvents::PauseJobsIfAny()
{
    Job *job;

    for(std::size_t index = 0u; index < max_simultaneous_jobs_count; ++index)
    {
        job = jobs[index].get();

        if(job != nullptr && job->GetStateSync() == Job::State::RUNNING)
            job->PauseSync();
    }
}

void MainForm::JobReportListViewEvents::TryQueueJobs(void)
{
    if(!IsQueueFull())
    {
        std::size_t job_descriptions_count = job_descriptions.size();

        for(std::size_t index = 0u; index < job_descriptions_count; ++index)
        {
            if(job_descriptions[index].GetState() == Job::State::READY)
            {
                if(!IsQueueFull())
                {
                    std::size_t free_slot_index = GetFreeSlot();

                    JobDescription *_job_description = &job_descriptions[index];

                    try
                    {
                        CreateAndRunJob(_job_description, free_slot_index);
                        job_indices_tracker[free_slot_index] = index;
                    }
                    catch(Exception &ex)
                    {
                        _job_description->SetState(Job::State::ERROR_OCCURED);
                        SetErrorMessage(&ex, index);
                    }
                }
                else
                {
                    break;
                }
            }
        }
    }
}

void MainForm::JobReportListViewEvents::UpdateJobDescriptions(void)
{
    for(std::size_t index = 0u; index < max_simultaneous_jobs_count; ++index)
    {
        if(jobs[index].get() != nullptr)
        {
            Job *job = jobs[index].get();
            JobDescription *job_description = &job_descriptions[job_indices_tracker[index]];
            Job::State current_job_state = job->GetStateSync();

            if(job_description->GetState() != current_job_state)
            {
                job_description->SetState(current_job_state);

                if(current_job_state == Job::State::ERROR_OCCURED)
                    SetErrorMessage(job->GetError(), job_indices_tracker[index]);
                else
                    main_form->job_report_list_view->SetCellText(2, job_indices_tracker[index], WindowsUtilities::UTF8_Decode(Job::state_to_string.at(current_job_state)).c_str());
            }

            main_form->job_report_list_view->SetCellText(3, job_indices_tracker[index], GetConversionProgress(index).c_str());
        }
    }
}

void MainForm::JobReportListViewEvents::CleanActiveQueue(void)
{
    Job *job;
    Job::State state;

    for(std::size_t index = 0u; index < max_simultaneous_jobs_count; ++index)
    {
        job = jobs[index].get();

        if(job != nullptr)
        {
            state = job->GetStateSync();

            if(job_descriptions[job_indices_tracker[index]].GetState() == state)
            {
                if(state != Job::State::RUNNING && state != Job::State::PAUSE)
                {
                    jobs[index].reset();
                }
            }
        }
    }
}

void MainForm::JobReportListViewEvents::TryStopQueueProcessor(void)
{
    Job::State state;

    bool need_break_from_loop = false;

    std::size_t jobs_index = 0ull;

    for(; jobs_index < max_simultaneous_jobs_count; ++jobs_index)
    {
        if(jobs[jobs_index].get() != nullptr)
        {
            state = jobs[jobs_index]->GetStateSync();

            switch(state)
            {
                case Job::READY:
                case Job::RUNNING:
                case Job::PAUSE:
                    need_break_from_loop = true;
                    break;
            }

            if(need_break_from_loop)
                break;
        }
    }

    if(jobs_index < max_simultaneous_jobs_count)
    {
        return;
    }

    std::size_t job_descriptions_count = job_descriptions.size();

    need_break_from_loop = false;

    std::size_t job_descriptions_index = 0ull;

    for(; job_descriptions_index < job_descriptions_count; ++job_descriptions_index)
    {
        state = job_descriptions[job_descriptions_index].GetState();

        switch(state)
        {
            case Job::READY:
            case Job::RUNNING:
            case Job::PAUSE:
                need_break_from_loop = true;
                break;
        }

        if(need_break_from_loop)
            break;
    }

    if(job_descriptions_index == job_descriptions_count)
    {
        queue_processor.Stop();
    }
}

void MainForm::JobReportListViewEvents::ResumeJobsIfAny()
{
    Job *job;

    for(std::size_t index = 0u; index < max_simultaneous_jobs_count; ++index)
    {
        job = jobs[index].get();

        if(job != nullptr && job->GetStateSync() == Job::State::PAUSE)
            job->StartAsync();
    }
}

bool MainForm::JobReportListViewEvents::IsQueueFull()
{
    for(std::size_t index = 0ull; index < max_simultaneous_jobs_count; ++index)
    {
        if(jobs[index].get() == nullptr)
            return false;
    }

    return true;
}

std::size_t MainForm::JobReportListViewEvents::GetFreeSlot()
{
    for(std::size_t index = 0; index < max_simultaneous_jobs_count; ++index)
    {
        if(jobs[index].get() == nullptr)
            return index;
    }

    assert(false);
    throw OutOfRangeException("ActiveJobQueue", "Queue is full.");
}

void MainForm::JobReportListViewEvents::CreateAndRunJob(const JobDescription *job_description, std::size_t free_slot_index)
{
    switch(job_description->GetEncoderID())
    {
        case Encoder<void>::ID::LAME:
        {
            LameOptions lame_options;
            SettingsManager::Read(lame_options, job_description->GetProfileFullPath());
            jobs[free_slot_index].reset(new Job(job_description->GetSourceFileFullPath(), job_description->GetOutputPath() + "\\" + job_description->GetOutputFileName() + "." + job_description->GetOutputFileExtension(), job_description->GetDecoderID(), lame_options));
            break;
        }
        case Encoder<void>::ID::SNDFILEENCODER:
        {
            SndFileEncoderOptions sndfileencoder_options;
            SettingsManager::Read(sndfileencoder_options, job_description->GetProfileFullPath());
            jobs[free_slot_index].reset(new Job(job_description->GetSourceFileFullPath(), job_description->GetOutputPath() + "\\" + job_description->GetOutputFileName() + "." + job_description->GetOutputFileExtension(), job_description->GetDecoderID(), sndfileencoder_options));
            break;
        }
    }

    Job *job = jobs[free_slot_index].get();
    total_frame_count_uint64[free_slot_index] = job->GetTotalFrameCount();
    total_frame_count_double[free_slot_index] = static_cast<double>(total_frame_count_uint64[free_slot_index]);
    job->StartAsync();
}

void MainForm::JobReportListViewEvents::SetErrorMessage(const Exception *exception, std::size_t row_index)
{
    std::string error_message(Job::state_to_string.at(Job::State::ERROR_OCCURED) + ": " + exception->what());
    main_form->job_report_list_view->SetCellText(2, row_index, WindowsUtilities::UTF8_Decode(error_message).c_str());
}

std::wstring MainForm::JobReportListViewEvents::GetConversionProgress(std::size_t job_index)
{
    double progress = static_cast<double>(jobs[job_index]->GetWrittenFrameCount()) / total_frame_count_double[job_index] * 100.0;
    std::wstring progress_wstr(std::to_wstring(progress));
    std::wstring::size_type pos = progress_wstr.find_first_of(L'.') + 3u;
    return progress_wstr.substr(0u, pos) + L'%';
}

MainForm::JobReportListViewEvents::~JobReportListViewEvents(void)
{
    PauseQueue();
}

void MainForm::BtnBrowseFolderEvents::OnClick(HWND hWnd)
{
    main_form->job_report_list_view_events->SetOutputPath(hWnd);
}

void MainForm::BtnAddFilesEvents::OnClick(HWND hWnd)
{
    main_form->job_report_list_view_events->AddJobs(hWnd);
}

void MainForm::BtnRemoveFilesEvents::OnClick()
{
    main_form->job_report_list_view_events->RemoveSelectedJobs();
}

void MainForm::BtnLoadProfileEvents::OnClick(HWND hWnd)
{
    main_form->job_report_list_view_events->LoadProfile(hWnd);
}

void MainForm::BtnCreateProfileEvents::OnClick()
{
    if(main_form->profile_form.get() == nullptr)
        main_form->profile_form.reset(new ProfileForm(main_form->hInstance, main_form->window->GetHandle(), main_form->profile_form));
}

void MainForm::BtnStartQueueEvents::OnClick()
{
    main_form->job_report_list_view_events->StartQueue();
}

void MainForm::BtnPauseQueueEvents::OnClick()
{
    main_form->job_report_list_view_events->PauseQueue();
}

LRESULT MainForm::HandleEvent(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case MAINFORM_MENUBAR_FILE_ADDFILES:
                    switch(HIWORD(wParam))
                    {
                        case BN_CLICKED:
                            menu_bar_events->File_AddFiles_OnClick();
                            break;
                    }
                    break;
                case MAINFORM_MENUBAR_FILE_EXIT:
                    switch(HIWORD(wParam))
                    {
                        case BN_CLICKED:
                            menu_bar_events->File_Exit_OnClick();
                            break;
                    }
                    break;
                case MAINFORM_BTN_BROWSE_FOLDER:
                    switch(HIWORD(wParam))
                    {
                        case BN_CLICKED:
                            btn_browse_folder_events->OnClick(hWnd);
                            break;
                    }
                    break;
                case MAINFORM_BTN_ADD_FILES:
                    switch(HIWORD(wParam))
                    {
                        case BN_CLICKED:
                            btn_add_files_events->OnClick(hWnd);
                            break;
                    }
                    break;
                case MAINFORM_BTN_REMOVE_FILES:
                    switch(HIWORD(wParam))
                    {
                        case BN_CLICKED:
                            btn_remove_files_events->OnClick();
                            break;
                    }
                    break;
                case MAINFORM_BTN_LOAD_PROFILE:
                    switch(HIWORD(wParam))
                    {
                        case BN_CLICKED:
                            btn_load_profile_events->OnClick(hWnd);
                            break;
                    }
                    break;
                case MAINFORM_BTN_CREATE_PROFILE:
                    switch(HIWORD(wParam))
                    {
                        case BN_CLICKED:
                            btn_create_profile_events->OnClick();
                            break;
                    }
                    break;
                case MAINFORM_BTN_START_QUEUE:
                    switch(HIWORD(wParam))
                    {
                        case BN_CLICKED:
                            btn_start_queue_events->OnClick();
                            break;
                    }
                    break;
                case MAINFORM_BTN_PAUSE_QUEUE:
                    switch(HIWORD(wParam))
                    {
                        case BN_CLICKED:
                            btn_pause_queue_events->OnClick();
                            break;
                    }
                    break;
            }
            break;
        case WM_TIMER:
            job_report_list_view_events->OnTimerSyncTick();
            break;
        case WM_SIZE:
            OnSize(wParam, lParam);
            break;
        case WM_CREATE:
            OnCreate(hWnd);
            break;
        case WM_NCDESTROY:
            OnBeforeDestroy();
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return 0ll;
}
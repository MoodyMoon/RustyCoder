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

#include "stdafx.h"
#include "main_form.h"

rusty::gui::MainForm::MainForm(HINSTANCE hThisInstance, int nCmdShow) : hInstance(hThisInstance)
{
    window.reset(new controls::Window(hThisInstance, this, L"MainForm", L"RustyCoder", HWND_DESKTOP, WS_EX_LEFT, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_VISIBLE, nCmdShow, RUSTYCODER_ICON, CW_USEDEFAULT, CW_USEDEFAULT, 750, 550, true));
}

//InitCommonControlsEx is not needed to enabled new theme
void rusty::gui::MainForm::OnCreate(HWND hWnd)
{
    menu_bar.reset(new controls::MenuBar());
    menu_bar_events.reset(new MenuBarEvents(this));
    menu_bar->Attach(hWnd);

    const unsigned long window_client_width = controls::Window::GetClientWidth(hWnd);
    const unsigned long window_client_height = controls::Window::GetClientHeight(hWnd);

    job_report_list_view.reset(new controls::ReportListView(hInstance, hWnd, MAINFORM_JOB_REPORT_LIST_VIEW, 0, 0, window_client_width, window_client_height - 40, WS_EX_LEFT, LVS_REPORT | LVS_SHOWSELALWAYS | WS_CHILD | WS_VISIBLE));
    job_report_list_view_events.reset(new JobReportListViewEvents(this));

    btn_add_files.reset(new controls::Button(hInstance, L"Add files", hWnd, MAINFORM_BTN_ADD_FILES, 5, window_client_height - 30, 90, 25));
    btn_add_files_events.reset(new BtnAddFilesEvents(this));

    btn_remove_files.reset(new controls::Button(hInstance, L"Remove files", hWnd, MAINFORM_BTN_REMOVE_FILES, 100, window_client_height - 30, 90, 25));
    btn_remove_files_events.reset(new BtnRemoveFilesEvents(this));

    btn_load_profile.reset(new controls::Button(hInstance, L"Load profile", hWnd, MAINFORM_BTN_LOAD_PROFILE, 195, window_client_height - 30, 90, 25));
    btn_load_profile_events.reset(new BtnLoadProfileEvents(this));

    btn_create_profile.reset(new controls::Button(hInstance, L"Create profile", hWnd, MAINFORM_BTN_CREATE_PROFILE, 290, window_client_height - 30, 90, 25));
    btn_create_profile_events.reset(new BtnCreateProfileEvents(this));

    btn_browse_folder.reset(new controls::Button(hInstance, L"Browse folder", hWnd, MAINFORM_BTN_BROWSE_FOLDER, 385, window_client_height - 30, 90, 25));
    btn_browse_folder_events.reset(new BtnBrowseFolderEvents(this));

    btn_start_queue.reset(new controls::Button(hInstance, L"Start queue", hWnd, MAINFORM_BTN_START_QUEUE, window_client_width - 190, window_client_height - 30, 90, 25));
    btn_start_queue_events.reset(new BtnStartQueueEvents(this));

    btn_pause_queue.reset(new controls::Button(hInstance, L"Pause queue", hWnd, MAINFORM_BTN_PAUSE_QUEUE, window_client_width - 95, window_client_height - 30, 90, 25));
    btn_pause_queue_events.reset(new BtnPauseQueueEvents(this));

    form_loaded = true;
}

void rusty::gui::MainForm::OnSize(WPARAM wParam, LPARAM lParam)
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

void rusty::gui::MainForm::OnBeforeDestroy()
{
    job_report_list_view_events.reset();
}

rusty::gui::MainForm::MenuBarEvents::MenuBarEvents(MainForm * const main_form) : main_form(main_form)
{
    HMENU sub_menu = main_form->menu_bar->CreateSubMenu(L"File", nullptr);
    main_form->menu_bar->CreateMenuItem(L"&Add files", MAINFORM_MENUBAR_FILE_ADDFILES, sub_menu);
    main_form->menu_bar->CreateMenuItem(L"&Exit", MAINFORM_MENUBAR_FILE_EXIT, sub_menu);
}

void rusty::gui::MainForm::MenuBarEvents::File_AddFiles_OnClick()
{
    main_form->job_report_list_view_events->AddJob();
}

void rusty::gui::MainForm::MenuBarEvents::File_Exit_OnClick()
{
    main_form->window.reset();
}

rusty::gui::MainForm::JobReportListViewEvents::JobReportListViewEvents(MainForm * const main_form) : main_form(main_form)
{
    std::wstring text(L"File name");
    main_form->job_report_list_view->InsertColumn(250u, 0u, text.c_str());

    text = L"Decoder";
    main_form->job_report_list_view->InsertColumn(100u, 1u, text.c_str());

    text = L"Profile";
    main_form->job_report_list_view->InsertColumn(100u, 2u, text.c_str());

    text = L"Encoder";
    main_form->job_report_list_view->InsertColumn(100u, 3u, text.c_str());

    text = L"Status";
    main_form->job_report_list_view->InsertColumn(100u, 4u, text.c_str());

    text = L"Progress";
    main_form->job_report_list_view->InsertColumn(100u, 5u, text.c_str());

    text = L"Save to";
    main_form->job_report_list_view->InsertColumn(150u, 6u, text.c_str());
}

void rusty::gui::MainForm::JobReportListViewEvents::AddJob()
{
    controls::OpenFileDialog open_file_dialog(main_form->window->GetHandle(), FileExtensionFilters::input_audio_format_filters, sizeof(FileExtensionFilters::input_audio_format_filters) / sizeof(COMDLG_FILTERSPEC), true);

    if(open_file_dialog.HasResult())
    {
        main_form->job_report_list_view->SetRedraw(false);

        for(unsigned int item_index = 0u, item_count = open_file_dialog.GetResultCount(); item_index < item_count; ++item_index)
        {
            job_queue.AppendJob(open_file_dialog.GetFile(item_index), *this);
        }

        main_form->job_report_list_view->SetRedraw(true);
        main_form->job_report_list_view->Redraw();
    }
}

void rusty::gui::MainForm::JobReportListViewEvents::SetEncoderProfilePath()
{
    if(main_form->job_report_list_view->HasSelectedItems())
    {
        controls::OpenFileDialog open_file_dialog(main_form->window->GetHandle(), FileExtensionFilters::profile_format_filters, sizeof(FileExtensionFilters::profile_format_filters) / sizeof(COMDLG_FILTERSPEC), false);

        if(open_file_dialog.HasResult())
        {
            boost::filesystem::path encoder_profile_path(open_file_dialog.GetFile(0ul));

            int row_index = main_form->job_report_list_view->GetNextSelectedItem();

            std::vector<std::unique_ptr<engine2::JobBuilderRunner>>::const_iterator job_iterator;

            main_form->job_report_list_view->SetRedraw(false);

            while(row_index > -1)
            {
                job_iterator = job_queue.GetJobIterator(row_index);

                (*job_iterator)->SetEncoderProfilePath(encoder_profile_path);

                row_index = main_form->job_report_list_view->GetNextSelectedItem(++row_index);
            }

            main_form->job_report_list_view->SetRedraw(true);
            main_form->job_report_list_view->Redraw();
        }
    }
}

void rusty::gui::MainForm::JobReportListViewEvents::SetOutputPath()
{
    if(main_form->job_report_list_view->HasSelectedItems())
    {
        controls::OpenFolderDialog open_folder_dialog(main_form->window->GetHandle());

        if(open_folder_dialog.HasResult())
        {
            boost::filesystem::path output_file_path(open_folder_dialog.GetFolder());

            int row_index = main_form->job_report_list_view->GetNextSelectedItem();

            std::vector<std::unique_ptr<engine2::JobBuilderRunner>>::const_iterator job_iterator;

            main_form->job_report_list_view->SetRedraw(false);

            while(row_index > -1)
            {
                job_iterator = job_queue.GetJobIterator(row_index);

                (*job_iterator)->SetOutputFilePath(output_file_path);

                row_index = main_form->job_report_list_view->GetNextSelectedItem(++row_index);
            }

            main_form->job_report_list_view->SetRedraw(true);
            main_form->job_report_list_view->Redraw();
        }
    }
}

void rusty::gui::MainForm::JobReportListViewEvents::RemoveJob()
{
    if(main_form->job_report_list_view->HasSelectedItems())
    {
        int row_index = main_form->job_report_list_view->GetNextSelectedItem();

        std::vector<std::unique_ptr<engine2::JobBuilderRunner>>::const_iterator job_iterator;

        main_form->job_report_list_view->SetRedraw(false);

        while(row_index > -1)
        {
            job_iterator = job_queue.GetJobIterator(row_index);

            job_queue.RemoveJob(job_iterator, job_iterator + 1);

            main_form->job_report_list_view->RemoveRow(row_index);

            row_index = main_form->job_report_list_view->GetNextSelectedItem(row_index);

            main_form->job_report_list_view->SetRedraw(true);
            main_form->job_report_list_view->Redraw();
        }
    }
}

void rusty::gui::MainForm::JobReportListViewEvents::StartQueue()
{
    job_queue.Start();
}

void rusty::gui::MainForm::JobReportListViewEvents::PauseQueue()
{
    job_queue.Pause();
}

void rusty::gui::MainForm::JobReportListViewEvents::OnInputFilePathChanged(const boost::filesystem::path &input_file_path, unsigned int job_index)
{
    if(job_index < main_form->job_report_list_view->GetRowCount())
        main_form->job_report_list_view->SetCellText(0u, job_index, input_file_path.filename().wstring().c_str());
    else
        main_form->job_report_list_view->InsertRow(job_index, input_file_path.filename().wstring().c_str(), nullptr);
}

void rusty::gui::MainForm::JobReportListViewEvents::OnEstimatedDecoderIDChanged(codecs::Decoder<void>::ID estimated_decoder_id, unsigned int job_index)
{
    main_form->job_report_list_view->SetCellText(1u, job_index, core::WindowsUtilities::UTF8_Decode(codecs::Decoder<void>::decoder_id_to_text.at(estimated_decoder_id)).c_str());
}

void rusty::gui::MainForm::JobReportListViewEvents::OnEncoderProfilePathChanged(const boost::filesystem::path &encoder_profile_path, unsigned int job_index)
{
    main_form->job_report_list_view->SetCellText(2u, job_index, encoder_profile_path.filename().wstring().c_str());
}

void rusty::gui::MainForm::JobReportListViewEvents::OnEstimatedEncoderIDChanged(codecs::Encoder<void>::ID estimated_encoder_id, unsigned int job_index)
{
    main_form->job_report_list_view->SetCellText(3u, job_index, core::WindowsUtilities::UTF8_Decode(codecs::Encoder<void>::encoder_id_to_text.at(estimated_encoder_id)).c_str());
}

void rusty::gui::MainForm::JobReportListViewEvents::OnOutputFilePathChanged(boost::filesystem::path output_file_path, unsigned int job_index)
{
    main_form->job_report_list_view->SetCellText(6u, job_index, output_file_path.wstring().c_str());
}

void rusty::gui::MainForm::JobReportListViewEvents::OnStateChanged(engine2::Common::JobBuilderRunnerState state, unsigned int job_index)
{
    main_form->job_report_list_view->SetCellText(4u, job_index, core::WindowsUtilities::UTF8_Decode(engine2::Common::job_builder_runner_state_to_string.at(state)).c_str());
}

void rusty::gui::MainForm::JobReportListViewEvents::OnErrorOccurred(const core::Exception *error, unsigned int job_index)
{
    std::string error_message(error->GetErrorMessage());

    main_form->job_report_list_view->SetCellText(6u, job_index, core::WindowsUtilities::UTF8_Decode(error_message).c_str());
}

void rusty::gui::MainForm::JobReportListViewEvents::OnWrittenFrameCountChanged(uint64_t written_frame_count, unsigned int job_index)
{
    std::vector<std::unique_ptr<engine2::JobBuilderRunner>>::const_iterator job_iterator = job_queue.GetJobIterator(job_index);

    double total_frame_count = (*job_iterator)->GetTotalFrameCount();

    double percentage;

    if(total_frame_count == 0u)
    {
        percentage = 0;
    }
    else
    {
        percentage = written_frame_count / total_frame_count;
        percentage *= 100.0;
    }

    main_form->job_report_list_view->SetCellText(5u, job_index, std::to_wstring(percentage).append(L"%").c_str());
}

void rusty::gui::MainForm::JobReportListViewEvents::OnTotalFrameCountChanged(uint64_t /* total_frame_count */, unsigned int /* job_index */)
{

}

rusty::gui::MainForm::JobReportListViewEvents::~JobReportListViewEvents()
{
    PauseQueue();
}

void rusty::gui::MainForm::BtnBrowseFolderEvents::OnClick()
{
    main_form->job_report_list_view_events->SetOutputPath();
}

void rusty::gui::MainForm::BtnAddFilesEvents::OnClick()
{
    main_form->job_report_list_view_events->AddJob();
}

void rusty::gui::MainForm::BtnRemoveFilesEvents::OnClick()
{
    main_form->job_report_list_view_events->RemoveJob();
}

void rusty::gui::MainForm::BtnLoadProfileEvents::OnClick()
{
    main_form->job_report_list_view_events->SetEncoderProfilePath();
}

void rusty::gui::MainForm::BtnCreateProfileEvents::OnClick()
{
    if(main_form->profile_form.get() == nullptr)
        main_form->profile_form.reset(new ProfileForm(main_form->hInstance, main_form->window->GetHandle(), main_form->profile_form));
}

void rusty::gui::MainForm::BtnStartQueueEvents::OnClick()
{
    main_form->job_report_list_view_events->StartQueue();
}

void rusty::gui::MainForm::BtnPauseQueueEvents::OnClick()
{
    main_form->job_report_list_view_events->PauseQueue();
}

LRESULT rusty::gui::MainForm::HandleEvent(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
                            btn_browse_folder_events->OnClick();
                            break;
                    }
                    break;
                case MAINFORM_BTN_ADD_FILES:
                    switch(HIWORD(wParam))
                    {
                        case BN_CLICKED:
                            btn_add_files_events->OnClick();
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
                            btn_load_profile_events->OnClick();
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
        case WM_SIZE:
            OnSize(wParam, lParam);
            break;
        case WM_CREATE:
            OnCreate(hWnd);
            break;
        case WM_NCDESTROY:
            OnBeforeDestroy();
			break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return 0ll;
}
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

MainForm::MainForm(HINSTANCE hThisInstance, int nCmdShow)
{
    window.reset(new Window(hThisInstance, this, L"MainForm", L"RustyCoder", HWND_DESKTOP, WS_EX_LEFT, WS_OVERLAPPEDWINDOW | WS_VISIBLE, nCmdShow, RUSTYCODER_ICON, CW_USEDEFAULT, CW_USEDEFAULT, 750, 550, true));
}

//InitCommonControlsEx is not needed to enabled new theme
void MainForm::OnCreate(HWND hWnd)
{
    menu_bar.reset(new MenuBar());
    menu_bar_events.reset(new MenuBarEvents(this));
    menu_bar->Attach(hWnd);

    vertical_split_window1.reset(new VerticalSplitWindow(hInstance, L"MainForm_VerticalSplitWindow1", hWnd, MAINFORM_VERTICAL_SPLIT_WINDOW1, 0, 0, Window::GetClientWidth(hWnd), Window::GetClientHeight(hWnd), 550, 100, VerticalSplitWindow::MinWidthPanel::RIGHT, 0ul, WS_CHILD | WS_VISIBLE));
    vertical_split_window1_events.reset(new VerticalSplitWindow1Events(this));

    form_loaded = true;
}

void MainForm::OnSize(HWND hWnd, WPARAM wParam)
{
    switch(wParam)
    {
        case SIZE_MAXIMIZED:
        case SIZE_MAXSHOW:
        case SIZE_RESTORED:
        {
            if(form_loaded)
            {
                vertical_split_window1->ResizeTo(Window::GetClientWidth(hWnd), Window::GetClientHeight(hWnd));
            }
            break;
        }
    }
}

void MainForm::OnGetMinMaxInfo(MINMAXINFO *min_max_info)
{
    min_max_info->ptMinTrackSize.x = 750;
    min_max_info->ptMinTrackSize.y = 550;
}

MainForm::MenuBarEvents::MenuBarEvents(MainForm * const main_form) : main_form(main_form)
{
    HMENU sub_menu = main_form->menu_bar->CreateSubMenu(L"File", nullptr);
    main_form->menu_bar->CreateMenuItem(L"&Add files", MAINFORM_MENUBAR_FILE_ADDFILES, sub_menu);
    main_form->menu_bar->CreateMenuItem(L"&Exit", MAINFORM_MENUBAR_FILE_EXIT, sub_menu);
}

void MainForm::MenuBarEvents::File_AddFiles_OnClicked()
{
    main_form->job_report_list_view_events->AddJobs(main_form->window->GetHandle());
}

void MainForm::MenuBarEvents::File_Exit_OnClicked()
{
    main_form->window.reset();
}

MainForm::VerticalSplitWindow1Events::VerticalSplitWindow1Events(MainForm * const main_form) : main_form(main_form)
{
    HWND vertical_split_window1_handle = main_form->vertical_split_window1->GetHandle();

    main_form->panel1_events.reset(new Panel1Events(main_form));
    main_form->panel2_events.reset(new Panel2Events(main_form));

    RECT panel_rectangle;
    main_form->vertical_split_window1->GetSplitterLeftRectangle(panel_rectangle);
    main_form->panel1.reset(new Panel(main_form->hInstance, main_form->panel1_events.get(), L"MainForm_Panel1", vertical_split_window1_handle, MAINFORM_PANEL1, panel_rectangle.left, panel_rectangle.top, panel_rectangle.right + 1, panel_rectangle.bottom + 1, WS_EX_LEFT, WS_CHILD | WS_VISIBLE));

    main_form->vertical_split_window1->GetSplitterRightRectangle(panel_rectangle);
    main_form->panel2.reset(new Panel(main_form->hInstance, main_form->panel2_events.get(), L"MainForm_Panel2", vertical_split_window1_handle, MAINFORM_PANEL2, panel_rectangle.left, panel_rectangle.top, panel_rectangle.right - panel_rectangle.left + 1, panel_rectangle.bottom + 1, WS_EX_LEFT, WS_BORDER | WS_CHILD | WS_VISIBLE));

    main_form->vertical_split_window1->SetLeftPanel(main_form->panel1.get(), false);
    main_form->vertical_split_window1->SetRightPanel(main_form->panel2.get(), false);
}

void MainForm::Panel1Events::OnCreate(HWND hWnd)
{
    main_form->job_report_list_view.reset(new ReportListView(main_form->hInstance, hWnd, MAINFORM_PANEL1_JOB_REPORT_LIST_VIEW, 0, 0, Window::GetClientWidth(hWnd), Window::GetClientHeight(hWnd) - 70));
    main_form->job_report_list_view_events.reset(new JobReportListViewEvents(main_form));
    
    main_form->lbl_file_destination.reset(new Label(main_form->hInstance, L"File destination", hWnd, MAINFORM_PANEL1_LBL_FILE_DESTINATION, 5, Window::GetClientHeight(hWnd) - 57, 83, 18, 0ul, WS_VISIBLE | WS_CHILD | SS_LEFT | SS_LEFTNOWORDWRAP));

    main_form->sltxtbx_file_destination.reset(new SingleLineTextBox(main_form->hInstance, nullptr, hWnd, 110, Window::GetClientHeight(hWnd) - 60, Window::GetClientWidth(hWnd) - 145, 22, MAINFORM_PANEL1_SLTXTBX_FILE_DESTINATION, WS_EX_CLIENTEDGE));

    main_form->btn_browse.reset(new Button(main_form->hInstance, L"...", hWnd, MAINFORM_PANEL1_BTN_BROWSE, Window::GetClientWidth(hWnd) - 30, Window::GetClientHeight(hWnd) - 60, 30, 22));
    main_form->btn_load_profile_events.reset(new BtnLoadProfileEvents(main_form));

    main_form->btn_load_profile.reset(new Button(main_form->hInstance, L"Load profile", hWnd, MAINFORM_PANEL1_BTN_LOAD_PROFILE, 5, Window::GetClientHeight(hWnd) - 30, 90, 25));

    main_form->btn_create_profile.reset(new Button(main_form->hInstance, L"Create profile", hWnd, MAINFORM_PANEL1_BTN_CREATE_PROFILE, 100, Window::GetClientHeight(hWnd) - 30, 90, 25));

    main_form->btn_convert.reset(new Button(main_form->hInstance, L"Convert", hWnd, MAINFORM_PANEL1_BTN_CONVERT, Window::GetClientWidth(hWnd) - 90, Window::GetClientHeight(hWnd) - 30, 90, 25));

    form_loaded = true;
}

void MainForm::Panel1Events::OnSize(HWND hWnd)
{
    if(form_loaded)
    {
        main_form->job_report_list_view->ResizeTo(Window::GetClientWidth(hWnd), Window::GetClientHeight(hWnd) - 70);

        main_form->lbl_file_destination->MoveTo(5, Window::GetClientHeight(hWnd) - 57);

        main_form->sltxtbx_file_destination->MoveAndResizeTo(110, Window::GetClientHeight(hWnd) - 60, Window::GetClientWidth(hWnd) - 145, 22);

        main_form->btn_browse->MoveTo(Window::GetClientWidth(hWnd) - 30, Window::GetClientHeight(hWnd) - 60);

        main_form->btn_load_profile->MoveTo(5, Window::GetClientHeight(hWnd) - 30);

        main_form->btn_create_profile->MoveTo(100, Window::GetClientHeight(hWnd) - 30);

        main_form->btn_convert->MoveTo(Window::GetClientWidth(hWnd) - 90, Window::GetClientHeight(hWnd) - 30);
    }
}

MainForm::JobReportListViewEvents::JobReportListViewEvents(MainForm * const main_form) : main_form(main_form)
{
    std::wstring text(L"File name");
    main_form->job_report_list_view->InsertColumn(250u, 0u, text.c_str(), text.length() + 1);

    text = L"Output format";
    main_form->job_report_list_view->InsertColumn(50u, 1u, text.c_str(), text.length() + 1);

    text = L"Profile";
    main_form->job_report_list_view->InsertColumn(100u, 2u, text.c_str(), text.length() + 1);

    text = L"Status";
    main_form->job_report_list_view->InsertColumn(100u, 3u, text.c_str(), text.length() + 1);

    text = L"Save to";
    main_form->job_report_list_view->InsertColumn(150u, 4u, text.c_str(), text.length() + 1);
}

void MainForm::JobReportListViewEvents::AddJobs(HWND hWnd)
{
    COMDLG_FILTERSPEC filters[] = {{L"Audio Interchange File Format", L"*.aiff;*.aif;*.aifc"},
                                   {L"Akai MPC 2000 Format", L"*.ampc"},
                                   {L"Sun Microsystem Audio Format", L"*.au"},
                                   {L"Audio Visual Research Format", L"*.avr"},
                                   {L"Apple Core Audio File", L"*.caf"},
                                   {L"Hidden Markov Model Toolkit Speech Recognition Format", L"*.htk"},
                                   {L"Amiga Audio Format", L"*.iff"},
                                   {L"GNU Octave File / Matlab File", L"*.mat"},
                                   {L"MPEG Audio Layer I", L"*.mp1"},
                                   {L"MPEG Audio Layer II", L"*.mp2"},
                                   {L"MPEG Audio Layer III", L"*.mp3"},
                                   {L"Ensoniq PARIS Audio Format", L"*.paf"},
                                   {L"Portable Voice Format", L"*.pvf"},
                                   {L"RIFF 64", L"*.rf64"},
                                   {L"MIDI Sample Dump Standard Format", L"*.sds"},
                                   {L"Sound Designer II Audio File", L"*.sd2"},
                                   {L"Berkeley IRCAM CARL Sound File", L"*.sf"},
                                   {L"Creative Labs Audio Format", L"*.voc"},
                                   {L"WAV", L"*.wav"},
                                   {L"Psion Series 3 Audio Format", L"*.wve"},
                                   {L"SoundFoundry WAVE 64", L"*.w64"},
                                   {L"FastTracker's Extended Instrument", L"*.xi"}};

    OpenFileDialog ofd(hWnd, filters, sizeof(filters) / sizeof(COMDLG_FILTERSPEC));

    if(ofd.HasResult())
    {
        unsigned long result_count = ofd.GetResultCount();
        
        unsigned int job_report_list_view_item_count = main_form->job_report_list_view->GetRowCount();
        unsigned int job_report_list_view_item_index;
        std::wstring source_file_name;

        for(unsigned long i = 0ul; i < result_count; ++i)
        {
            source_file_full_paths.push_back(WindowsUtilities::UTF8_Encode(ofd.GetFile(i, OpenFileDialog::File::FULL_PATH)));
            
            job_report_list_view_item_index = job_report_list_view_item_count + i;

            main_form->job_report_list_view->InsertRow(job_report_list_view_item_index);

            source_file_name = ofd.GetFile(i, OpenFileDialog::File::NAME_AND_EXTENSION);
            main_form->job_report_list_view->EditCellText(0u, job_report_list_view_item_index, source_file_name.c_str(), source_file_name.length() + 1u);
        }
    }
}

void MainForm::JobReportListViewEvents::LoadProfile(void)
{
    profile_form.reset(new ProfileForm(main_form->hInstance, main_form->panel1->GetHandle(), profile_form));
}

void MainForm::BtnLoadProfileEvents::OnClicked()
{
    main_form->job_report_list_view_events->LoadProfile();
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
                            menu_bar_events->File_AddFiles_OnClicked();
                            break;
                    }
                    break;
                case MAINFORM_MENUBAR_FILE_EXIT:
                    switch(HIWORD(wParam))
                    {
                        case BN_CLICKED:
                            menu_bar_events->File_Exit_OnClicked();
                            break;
                    }
                    break;
            }
            break;
        case WM_SIZE:
            OnSize(hWnd, wParam);
            return 0;
        case WM_GETMINMAXINFO:
            OnGetMinMaxInfo(reinterpret_cast<MINMAXINFO *>(lParam));
            break;
        case WM_CREATE:
            OnCreate(hWnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return 0ll;
}

LRESULT MainForm::Panel1Events::HandleEvent(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case MAINFORM_PANEL1_BTN_LOAD_PROFILE:
                    switch(HIWORD(wParam))
                    {
                        case BN_CLICKED:
                            main_form->btn_load_profile_events->OnClicked();
                            break;
                    }
            }
        case WM_SIZE:
            OnSize(hWnd);
            break;
        case WM_CREATE:
            OnCreate(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return 0ll;
}

LRESULT MainForm::Panel2Events::HandleEvent(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_LBUTTONUP:
            main_form->job.reset();
            break;
        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return 0ll;
}
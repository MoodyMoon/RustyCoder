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

MainForm::MainForm(HINSTANCE hThisInstance, int /* nCmdShow */)
{
    main_form.reset(new Window(hThisInstance, this, class_name, class_name, RUSTYCODER_ICON, CW_USEDEFAULT, CW_USEDEFAULT, 750, 550, SW_SHOWNORMAL, WS_EX_LEFT, WS_OVERLAPPEDWINDOW));
}

//InitCommonControlsEx is not needed to enabled new theme
void MainForm::OnCreate(HWND hWnd)
{
    menu_bar.reset(new MenuBar());
    menu_bar_events.reset(new MenuBarEvents(this));
    menu_bar->Attach(hWnd);

    vertical_split_window1.reset(new VerticalSplitWindow(hInstance, hWnd, L"VerticalSplitWindow1", MAINFORM_VERTICAL_SPLIT_WINDOW1, 0, 0, Window::GetClientWidth(hWnd), Window::GetClientHeight(hWnd), 550, 100, VerticalSplitWindow::MinWidthPanel::RIGHT, 0ul, WS_CHILD | WS_VISIBLE));
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

void MainForm::MenuBarEvents::File_AddFiles_OnClick(HWND hWnd)
{
    COMDLG_FILTERSPEC filters[] = {{L"MPEG", L"*.mp1;*.mp2;*.mp3"},
    {L"Free Lossless Audio Codec", L"*.flac"},
    {L"WAVE", L"*.wav"}};

    OpenFileDialog ofd(hWnd, filters, sizeof(filters) / sizeof(COMDLG_FILTERSPEC));
    std::wstring source, destination;

    if(ofd.HasResult())
    {
        MsgBox::Show(ofd.GetFile(0ul, OpenFileDialog::File::FULL_PATH));

        source = ofd.GetFile(0ul, OpenFileDialog::File::FULL_PATH);
        destination = L"D:\\abc2.mp3";

        LameOptions options;
        options.algorithm_quality = LameOptions::AlgorithmQuality::Q0;
        options.mode = LameOptions::Mode::JOINT_STEREO;
        options.replaygain_mode = LameOptions::ReplayGain::ACCURATE;
        options.copyright = false;
        options.use_naoki_psytune = true;
        options.bitrate_encoding = LameOptions::BitrateEncoding::CONSTANT;
        options.vbr_quality = 0.;
        options.min_or_max_bitrate1 = LameOptions::Bitrate::B_128;
        /* CodecController codec(WindowsUtilities::UTF8_Encode(source), WindowsUtilities::UTF8_Encode(destination), Decoder<void>::ID::MPG123, options);
        do
        {
        codec.Convert();
        } while(codec.CanConvert());*/
        main_form->job.reset(new Job(source, destination, Decoder<void>::ID::MPG123, options));
        main_form->job->StartAsync();
    }
}

void MainForm::MenuBarEvents::File_Exit_OnClick(void)
{
    main_form->main_form.reset();
}

MainForm::VerticalSplitWindow1Events::VerticalSplitWindow1Events(MainForm * const main_form) : main_form(main_form)
{
    HWND vertical_split_window1_handle = main_form->vertical_split_window1->GetHandle();

    main_form->panel1_events.reset(new Panel1Events(main_form));
    main_form->panel2_events.reset(new Panel2Events(main_form));

    RECT panel_rectangle;
    main_form->vertical_split_window1->GetSplitterLeftRectangle(panel_rectangle);
    main_form->panel1.reset(new Panel(main_form->hInstance, main_form->panel1_events.get(), vertical_split_window1_handle, L"Panel1", MAINFORM_PANEL1, panel_rectangle.left, panel_rectangle.top, panel_rectangle.right + 1, panel_rectangle.bottom + 1, WS_EX_LEFT, WS_CHILD | WS_VISIBLE));

    main_form->vertical_split_window1->GetSplitterRightRectangle(panel_rectangle);
    main_form->panel2.reset(new Panel(main_form->hInstance, main_form->panel2_events.get(), vertical_split_window1_handle, L"Panel2", MAINFORM_PANEL2, panel_rectangle.left, panel_rectangle.top, panel_rectangle.right - panel_rectangle.left + 1, panel_rectangle.bottom + 1, WS_EX_LEFT, WS_BORDER | WS_CHILD | WS_VISIBLE));

    main_form->vertical_split_window1->SetLeftPanel(main_form->panel1.get(), false);
    main_form->vertical_split_window1->SetRightPanel(main_form->panel2.get(), false);
}

void MainForm::Panel1Events::OnCreate(HWND hWnd)
{
    main_form->job_report_list_view.reset(new ReportListView(main_form->hInstance, hWnd, 0, 0, Window::GetClientWidth(hWnd), Window::GetClientHeight(hWnd) - 70, MAINFORM_PANEL1_JOB_REPORT_LIST_VIEW));
    main_form->job_report_list_view_events.reset(new JobReportListViewEvents(main_form));
    
    main_form->lbl_file_destination.reset(new Label(main_form->hInstance, hWnd, L"File destination", 5, Window::GetClientHeight(hWnd) - 57, 83, 18, MAINFORM_PANEL1_LBL_FILE_DESTINATION, 0ul, WS_VISIBLE | WS_CHILD | SS_LEFT | SS_LEFTNOWORDWRAP));

    main_form->sltxtbx_file_destination.reset(new SingleLineTextBox(main_form->hInstance, hWnd, nullptr, 110, Window::GetClientHeight(hWnd) - 60, Window::GetClientWidth(hWnd) - 145, 22, MAINFORM_PANEL1_SLTXTBX_FILE_DESTINATION, WS_EX_CLIENTEDGE));

    main_form->btn_browse.reset(new Button(main_form->hInstance, hWnd, L"...", Window::GetClientWidth(hWnd) - 30, Window::GetClientHeight(hWnd) - 60, 30, 22, MAINFORM_PANEL1_BTN_BROWSE));

    main_form->btn_load_profile.reset(new Button(main_form->hInstance, hWnd, L"Load profile", 5, Window::GetClientHeight(hWnd) - 30, 90, 25, MAINFORM_PANEL1_BTN_LOAD_PROFILE));

    main_form->btn_create_profile.reset(new Button(main_form->hInstance, hWnd, L"Create profile", 100, Window::GetClientHeight(hWnd) - 30, 90, 25, MAINFORM_PANEL1_BTN_CREATE_PROFILE));

    main_form->btn_convert.reset(new Button(main_form->hInstance, hWnd, L"Convert", Window::GetClientWidth(hWnd) - 90, Window::GetClientHeight(hWnd) - 30, 90, 25, MAINFORM_PANEL1_BTN_CONVERT));

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

    text = L"Save to";
    main_form->job_report_list_view->InsertColumn(150u, 3u, text.c_str(), text.length() + 1);

    text = L"Hello";

    for(unsigned int i = 0u; i < 5u; ++i)
    {
        main_form->job_report_list_view->InsertRow(i);
        main_form->job_report_list_view->EditCellText(0u, i, text.c_str(), text.length() + 1);
        main_form->job_report_list_view->EditCellText(1u, i, text.c_str(), text.length() + 1);
    }
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
                            menu_bar_events->File_AddFiles_OnClick(hWnd);
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
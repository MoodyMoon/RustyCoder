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
#include "MainForm.h"

MainForm::MainForm(HINSTANCE hThisInstance, int /* nCmdShow */)
{
    this->hInstance = hInstance;
    events.reset(new MainFormEvents(this));
    
    panel2_events.reset(new MainFormPanel2Events(this));
    window.reset(new Window(hThisInstance, events.get(), class_name, class_name, RUSTYCODER_ICON, CW_USEDEFAULT, CW_USEDEFAULT, 750, 550, SW_SHOWNORMAL, WS_EX_LEFT, WS_OVERLAPPEDWINDOW));
}

MainFormEvents::MainFormEvents(MainForm * const mf) : mf(mf) {}
MainFormPanel1Events::MainFormPanel1Events(MainForm * const mf) : mf(mf) {}
MainFormPanel2Events::MainFormPanel2Events(MainForm * const mf) : mf(mf) {}

//InitCommonControlsEx is not needed to enabled new theme
void MainFormEvents::OnLoad(HWND hWnd)
{
    HFONT hFont = mf->window->GetDefaultFont();
    
    mf->menu.reset(new MenuBar());
    HMENU sub_menu = mf->menu->CreateSubMenu(L"File", nullptr);
    mf->menu->CreateMenuItem(L"&Add files", MAINFORM_FILE_ADD_FILES, sub_menu);
    mf->menu->CreateMenuItem(L"&Exit", MAINFORM_FILE_EXIT, sub_menu);
    mf->menu->Attach(hWnd);

    mf->vertical_split_window1.reset(new VerticalSplitWindow(mf->hInstance, hWnd, L"VerticalSplitWindow1", MAINFORM_VERTICAL_SPLIT_WINDOW1, 0, 0, Window::GetClientWidth(hWnd), Window::GetClientHeight(hWnd), 550, 100, VerticalSplitWindow::MinWidthPanel::RIGHT, 0ul, WS_CLIPCHILDREN | WS_CHILD | WS_VISIBLE));

    HWND vertical_split_window1_handle = mf->vertical_split_window1->GetHandle();

    mf->panel1_events.reset(new MainFormPanel1Events(mf));

    RECT panel_rectangle;
    mf->vertical_split_window1->GetLeftPanelClientRectangle(panel_rectangle);
    mf->panel1.reset(new Panel(mf->hInstance, mf->panel1_events.get(), vertical_split_window1_handle, L"Panel1", MAINFORM_PANEL1, panel_rectangle.left, panel_rectangle.top, panel_rectangle.right + 1, panel_rectangle.bottom + 1, WS_EX_LEFT, WS_CHILD | WS_VISIBLE));
    
    mf->vertical_split_window1->GetRightPanelClientRectangle(panel_rectangle);
    mf->panel2.reset(new Panel(mf->hInstance, mf->panel2_events.get(), vertical_split_window1_handle, L"Panel2", MAINFORM_PANEL2, panel_rectangle.left, panel_rectangle.top, panel_rectangle.right + 1, panel_rectangle.bottom + 1, WS_EX_LEFT, WS_BORDER | WS_CHILD | WS_VISIBLE));

    mf->vertical_split_window1->SetLeftPanel(mf->panel1.get(), false);
    mf->vertical_split_window1->SetRightPanel(mf->panel2.get(), false);

    form_loaded = true;
}

void MainFormEvents::OnSize(HWND hWnd)
{
    if(form_loaded)
    {
        mf->vertical_split_window1->ResizeTo(Window::GetClientWidth(hWnd), Window::GetClientHeight(hWnd));
    }
}

void MainFormEvents::OnGetMinMaxInfo(MINMAXINFO *min_max_info)
{
    min_max_info->ptMinTrackSize.x = 750;
    min_max_info->ptMinTrackSize.y = 550;
}

void MainFormEvents::Menu_File_AddFiles_OnClick(HWND hWnd)
{
    COMDLG_FILTERSPEC filters[] = {{L"MPEG",                      L"*.mp1;*.mp2;*.mp3"},
                                   {L"Free Lossless Audio Codec", L"*.flac"},
                                   {L"WAVE",                      L"*.wav"}};

    OpenFileDialog ofd(hWnd, filters, sizeof(filters) / sizeof(COMDLG_FILTERSPEC));
    std::wstring source, destination;

    if(ofd.HasResult())
    {
        MsgBox::Show(ofd.GetFile(0ul, OpenFileDialog::File::FULL_PATH));
        /*
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
        CodecController codec(WindowsUtilities::UTF8_Encode(source), WindowsUtilities::UTF8_Encode(destination), Decoder<void>::DecoderID::MPG123, options);
        */
    }
}

void MainFormEvents::Menu_File_Exit_OnClick(void)
{
    mf->window.reset();
}

LRESULT MainFormEvents::HandleEvent(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case MAINFORM_FILE_ADD_FILES:
                    switch(HIWORD(wParam))
                    {
                        case BN_CLICKED:
                            Menu_File_AddFiles_OnClick(hWnd);
                            break;
                    }
                    break;
                case MAINFORM_FILE_EXIT:
                    switch(HIWORD(wParam))
                    {
                        case BN_CLICKED:
                            Menu_File_Exit_OnClick();
                            break;
                    }
                    break;
            }
            break;
        case WM_SIZE:
        {
            OnSize(hWnd);
            return 0;
        }
        case WM_GETMINMAXINFO:
            OnGetMinMaxInfo(reinterpret_cast<MINMAXINFO *>(lParam));
            break;
        case WM_CREATE:
            OnLoad(hWnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return 0ll;
}

void MainFormPanel1Events::OnCreate(HWND hWnd)
{
    mf->list_view1.reset(new ListView(mf->hInstance, hWnd, 0, 0, Window::GetClientWidth(hWnd), Window::GetClientHeight(hWnd) - 100, MAINFORM_PANEL1_LIST_VIEW1));

    std::wstring column_title(L"File name");
    mf->list_view1->InsertColumn(100u, 0u, const_cast<wchar_t *>(column_title.c_str()), column_title.length() + 1);

    column_title = L"Output format";
    mf->list_view1->InsertColumn(100u, 1u, const_cast<wchar_t *>(column_title.c_str()), column_title.length() + 1);

    form_loaded = true;
}

void MainFormPanel1Events::OnSize(HWND hWnd)
{
    if(form_loaded)
    {
        mf->list_view1->ResizeTo(Window::GetClientWidth(hWnd), Window::GetClientHeight(hWnd) - 100);
    }
}

LRESULT MainFormPanel1Events::HandleEvent(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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

LRESULT MainFormPanel2Events::HandleEvent(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return 0ll;
}
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
    panel1_events.reset(new MainFormPanel1Events(this));
    window.reset(new Window(hThisInstance, events.get(), class_name, class_name, RUSTYCODER_ICON, CW_USEDEFAULT, CW_USEDEFAULT, 750, 550, SW_SHOWNORMAL, WS_EX_LEFT, WS_OVERLAPPEDWINDOW));
}

MainFormEvents::MainFormEvents(MainForm * const mf) : mf(mf) {}
MainFormPanel1Events::MainFormPanel1Events(MainForm * const mf) : mf(mf) {}

//InitCommonControlsEx is not needed to enabled new theme
void MainFormEvents::OnLoad(HWND hWnd)
{
    HFONT hFont = mf->window->GetDefaultFont();
    
    mf->button1.reset(new Button(mf->hInstance, hWnd, L"Click me!", 10, 10, 100, 30, MAINFRAME_BUTTON1, hFont));
    mf->button2.reset(new Button(mf->hInstance, hWnd, L"Bite me!", 120, 10, 100, 30, MAINFRAME_BUTTON2, hFont));
    
    mf->menu.reset(new MenuBar());
    MenuHandle sub_menu = mf->menu->CreateSubMenu(L"File", nullptr);
    mf->menu->CreateMenuItem(L"&Add files", MAINFRAME_FILE_ADD_FILES, sub_menu);
    mf->menu->CreateMenuItem(L"&Exit", MAINFRAME_FILE_EXIT, sub_menu);
    mf->menu->Attach(hWnd);

    mf->vertical_split_window1.reset(new VerticalSplitWindow(mf->hInstance, hWnd, L"VerticalSplitWindow1", MAINFRAME_VERTICAL_SPLIT_WINDOW1, 20, 45, 200, 200, 20, 0ul, WS_CLIPCHILDREN | WS_CHILD | WS_VISIBLE));

    ControlHandle handle = mf->vertical_split_window1->GetHandle();

    mf->panel1.reset(new Panel(mf->hInstance, mf->panel1_events.get(), &handle, L"Panel1", MAINFRAME_PANEL1, 0, 0, 2, 2, WS_EX_CLIENTEDGE, WS_CHILD | WS_VISIBLE));
    mf->panel2.reset(new Panel(mf->hInstance, mf->panel2_events.get(), &handle, L"Panel2", MAINFRAME_PANEL2, 10, 0, 2, 2, WS_EX_CLIENTEDGE, WS_CHILD | WS_VISIBLE));

    mf->vertical_split_window1->SetLeftPanel(mf->panel1.get());
    mf->vertical_split_window1->SetRightPanel(mf->panel2.get());
}

void MainFormEvents::OnGetMinMaxInfo(MINMAXINFO *min_max_info)
{
    min_max_info->ptMinTrackSize.x = 750;
    min_max_info->ptMinTrackSize.y = 550;
}

void MainFormEvents::Button1_OnClick(void)
{
    mf->window->ResizeTo(0, 0);
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
        MsgBox::Show(ofd.GetFile(0ul, OpenFileDialog::File::FULL_PATH).c_str());
        source = ofd.GetFile(0ul, OpenFileDialog::File::FULL_PATH);
        destination = L"D:\\abc2.mp3";

        int64_t frame_offset;
        int64_t buffer_valid_frames_count;
        float buffer[2000];
        Mpg123LifetimeHandler life;
        Mpg123<void> mpg1(WindowsUtilities::UTF8_Encode(source).c_str(), life);
        Mpg123<float> mpg2(WindowsUtilities::UTF8_Encode(source).c_str(), buffer, sizeof(buffer), life);
        //SndFileEncoder<float> snd(TypeConv::utf8_encode(destination).c_str(), mpg1.GetSampleRate(), mpg1.GetChannelCount(), SndFileEncoder<float>::OutputFormat::WAV_PCM_FLOAT_32, buffer, sizeof(buffer));
        Lame<float> lame(WindowsUtilities::UTF8_Encode(destination).c_str(), mpg1.GetSampleRate(), mpg1.GetChannelCount(), LameOptions::AlgorithmQuality::Q0, LameOptions::Mode::JOINT_STEREO, LameOptions::ReplayGain::ACCURATE, false, true, LameOptions::BitrateEncoding::VARIABLE_NEW, 0, LameOptions::Bitrate::B_224, LameOptions::Bitrate::B_320, buffer, sizeof(buffer));
        do
        {
            buffer_valid_frames_count = mpg2.ReadFrames();
            frame_offset = mpg2.GetCurrentFrameOffset();
            lame.WriteFrames(buffer_valid_frames_count);
        }while(buffer_valid_frames_count == 1000);
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
                case MAINFRAME_BUTTON1:
                    switch(HIWORD(wParam))
                    {
                        case BN_CLICKED:
                            Button1_OnClick();
                            break;
                    }
                    break;
                case MAINFRAME_FILE_ADD_FILES:
                    switch(HIWORD(wParam))
                    {
                        case BN_CLICKED:
                            Menu_File_AddFiles_OnClick(hWnd);
                            break;
                    }
                    break;
                case MAINFRAME_FILE_EXIT:
                    switch(HIWORD(wParam))
                    {
                        case BN_CLICKED:
                            Menu_File_Exit_OnClick();
                            break;
                    }
                    break;
            }
            break;
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

LRESULT MainFormPanel1Events::HandleEvent(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_LBUTTONDOWN:
            MsgBox::Show(L"Hello1");
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
        case WM_LBUTTONDOWN:
            MsgBox::Show(L"Hello2");
            break;
        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return 0ll;
}
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
#include "profile_form.h"

ProfileForm::ProfileForm(HINSTANCE hInstance, HWND hWndParent, std::unique_ptr<ProfileForm> &me) : hInstance(hInstance), hWndParent(hWndParent), me(&me)
{
    window.reset(new Window(hInstance, this, L"ProfileForm", L"Profile", hWndParent, WS_EX_DLGMODALFRAME, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_VISIBLE, -1, -1, CW_USEDEFAULT, CW_USEDEFAULT, 450, 550, true));
    window->Focus();
}

void ProfileForm::OnCreate(HWND hWnd)
{
    int x_padding = 5;

    lbl_encoder_sign.reset(new Label(hInstance, L"Encoder", hWnd, PROFILEFORM_LBL_ENCODER_SIGN, x_padding, 9, 50, 18, WS_EX_LEFT, WS_VISIBLE | WS_CHILD | SS_LEFT | SS_LEFTNOWORDWRAP));

    cmbbx_encoder.reset(new ComboBox(hInstance, hWnd, PROFILEFORM_CMBBX_ENCODER, 65, x_padding, Window::GetClientWidth(hWnd) - x_padding - 160, ComboBox::Type::DROP_DOWN_LIST));
    cmbbx_encoder_events.reset(new CmbBxEncoderEvents(this));

    btn_load_default.reset(new Button(hInstance, L"Load default", hWnd, PROFILEFORM_BTN_LOAD_DEFAULT, Window::GetClientRight(hWnd) - x_padding - 90, x_padding, 90, 22));
    btn_load_default_events.reset(new BtnLoadDefaultEvents(this));

    profile_report_list_view.reset(new ReportListView(hInstance, hWnd, PROFILEFORM_PROFILE_REPORT_LIST_VIEW, x_padding, 32, Window::GetClientWidth(hWnd) - x_padding * 2, Window::GetClientHeight(hWnd) - 100, WS_EX_LEFT, WS_BORDER | WS_CHILD | WS_VISIBLE, true, false, true));

    std::wstring text(L"Option");
    profile_report_list_view->InsertColumn(200u, 0u, text.c_str(), text.length() + 1);

    text = L"Value";
    profile_report_list_view->InsertColumn(200u, 1u, text.c_str(), text.length() + 1);

    btn_open.reset(new Button(hInstance, L"Open", hWnd, PROFILEFORM_BTN_OPEN, x_padding, Window::GetClientBottom(hWnd) - 30, 90, 25));
    btn_open_events.reset(new BtnOpenEvents(this));

    btn_save.reset(new Button(hInstance, L"Save", hWnd, PROFILEFORM_BTN_SAVE, 100, Window::GetClientBottom(hWnd) - 30, 90, 25));
    btn_save_events.reset(new BtnSaveEvents(this));

    btn_save_as.reset(new Button(hInstance, L"Save As", hWnd, PROFILEFORM_BTN_SAVE_AS, 195, Window::GetClientBottom(hWnd) - 30, 90, 25));
    btn_save_as_events.reset(new BtnSaveAsEvents(this));

    form_loaded = true;
}

ProfileForm::~ProfileForm()
{
    Window::Focus(hWndParent);
}

ProfileForm::CmbBxEncoderEvents::CmbBxEncoderEvents(ProfileForm *profile_form) : profile_form(profile_form)
{
    profile_form->cmbbx_encoder->AppendItem(L"LAME", Encoder<void>::ID::LAME);
    profile_form->cmbbx_encoder->AppendItem(L"Libsndfile Encoder", Encoder<void>::ID::SNDFILEENCODER);
}

bool ProfileForm::CmbBxEncoderEvents::IsSelectedEncoder(void)
{
    return profile_form->cmbbx_encoder->IsSelectedItem();
}

Encoder<void>::ID ProfileForm::CmbBxEncoderEvents::GetSelectedEncoderID(void)
{
    unsigned int selected_item_index = profile_form->cmbbx_encoder->GetSelectedItemIndex();

    return static_cast<Encoder<void>::ID>(profile_form->cmbbx_encoder->GetItemData(selected_item_index));
}

void ProfileForm::BtnLoadDefaultEvents::OnClick(void)
{
    if(profile_form->cmbbx_encoder_events->IsSelectedEncoder())
    {
        switch(profile_form->cmbbx_encoder_events->GetSelectedEncoderID())
        {
            case Encoder<void>::ID::LAME:
            {
                std::unique_ptr<ProfileReportListViewEvents<SndFileEncoderOptions>> *sndfileencoder_profile_report_list_view_events = &profile_form->sndfileencoder_profile_report_list_view_events;

                if(sndfileencoder_profile_report_list_view_events->get() != nullptr)
                    sndfileencoder_profile_report_list_view_events->reset();

                ProfileReportListViewEvents<LameOptions> *lame_profile_report_list_view_events = profile_form->lame_profile_report_list_view_events.get();

                if(lame_profile_report_list_view_events != nullptr)
                    lame_profile_report_list_view_events->LoadDefaultProfile();
                else
                    profile_form->lame_profile_report_list_view_events.reset(new ProfileReportListViewEvents<LameOptions>(profile_form));
                break;
            }
            case Encoder<void>::ID::SNDFILEENCODER:
            {
                std::unique_ptr<ProfileReportListViewEvents<LameOptions>> *lame_profile_report_list_view_events = &profile_form->lame_profile_report_list_view_events;

                if(lame_profile_report_list_view_events->get() != nullptr)
                    lame_profile_report_list_view_events->reset();

                ProfileReportListViewEvents<SndFileEncoderOptions> *sndfileencoder_profile_report_list_view_events = profile_form->sndfileencoder_profile_report_list_view_events.get();

                if(sndfileencoder_profile_report_list_view_events != nullptr)
                    sndfileencoder_profile_report_list_view_events->LoadDefaultProfile();
                else
                    profile_form->sndfileencoder_profile_report_list_view_events.reset(new ProfileReportListViewEvents<SndFileEncoderOptions>(profile_form));
                break;
            }
        }
    }
}

ProfileForm::ProfileReportListViewEvents<LameOptions>::ProfileReportListViewEvents(ProfileForm *profile_form) : profile_form(profile_form)
{
    profile_form->encoder_profile_loaded = true;
    profile_form->loaded_encoder_profile_id = Encoder<void>::ID::LAME;

    LoadDefaultProfile();
}

void ProfileForm::ProfileReportListViewEvents<LameOptions>::LoadDefaultProfile()
{
    encoder_options.LoadDefaultProfile(LameOptions::Profile::DEFAULT);

    std::wstring text;

    if(!loaded)
    {
        text = L"Algorithm quality";
        profile_form->profile_report_list_view->InsertRow(0u, text.c_str(), text.length() + 1);

        text = L"Channel";
        profile_form->profile_report_list_view->InsertRow(1u, text.c_str(), text.length() + 1);

        text = L"ReplayGain mode";
        profile_form->profile_report_list_view->InsertRow(2u, text.c_str(), text.length() + 1);

        text = L"Copyright";
        profile_form->profile_report_list_view->InsertRow(3u, text.c_str(), text.length() + 1);

        text = L"Use Naoki's psychoacoustic";
        profile_form->profile_report_list_view->InsertRow(4u, text.c_str(), text.length() + 1);

        text = L"Bitrate encoding";
        profile_form->profile_report_list_view->InsertRow(5u, text.c_str(), text.length() + 1);

        text = L"VBR quality";
        profile_form->profile_report_list_view->InsertRow(6u, text.c_str(), text.length() + 1);

        text = L"Constant bitrate / min or max bitrate";
        profile_form->profile_report_list_view->InsertRow(7u, text.c_str(), text.length() + 1);

        text = L"Min or max bitrate";
        profile_form->profile_report_list_view->InsertRow(8u, text.c_str(), text.length() + 1);

        loaded = true;
    }

    text = WindowsUtilities::UTF8_Decode(LameOptions::algorithm_quality_to_text.at(encoder_options.algorithm_quality));
    profile_form->profile_report_list_view->SetCellText(1u, 0u, text.c_str(), text.length() + 1);

    text = WindowsUtilities::UTF8_Decode(LameOptions::mode_to_text.at(encoder_options.mode));
    profile_form->profile_report_list_view->SetCellText(1u, 1u, text.c_str(), text.length() + 1);

    text = WindowsUtilities::UTF8_Decode(LameOptions::replaygain_mode_to_text.at(encoder_options.replaygain_mode));
    profile_form->profile_report_list_view->SetCellText(1u, 2u, text.c_str(), text.length() + 1);

    text = WindowsUtilities::UTF8_Decode(encoder_options.copyright ? EncoderOptions::bool_true_text : EncoderOptions::bool_false_text);
    profile_form->profile_report_list_view->SetCellText(1u, 3u, text.c_str(), text.length() + 1);

    text = WindowsUtilities::UTF8_Decode(encoder_options.use_naoki_psytune ? EncoderOptions::bool_true_text : EncoderOptions::bool_false_text);
    profile_form->profile_report_list_view->SetCellText(1u, 4u, text.c_str(), text.length() + 1);

    text = WindowsUtilities::UTF8_Decode(LameOptions::bitrate_encoding_to_text.at(encoder_options.bitrate_encoding));
    profile_form->profile_report_list_view->SetCellText(1u, 5u, text.c_str(), text.length() + 1);

    text = std::to_wstring(encoder_options.vbr_quality);
    profile_form->profile_report_list_view->SetCellText(1u, 6u, text.c_str(), text.length() + 1);

    text = WindowsUtilities::UTF8_Decode(LameOptions::bitrate_to_text.at(encoder_options.min_or_max_bitrate1));
    profile_form->profile_report_list_view->SetCellText(1u, 7u, text.c_str(), text.length() + 1);

    text = WindowsUtilities::UTF8_Decode(LameOptions::bitrate_to_text.at(encoder_options.min_or_max_bitrate2));
    profile_form->profile_report_list_view->SetCellText(1u, 8u, text.c_str(), text.length() + 1);
}

const LameOptions & ProfileForm::ProfileReportListViewEvents<LameOptions>::GetEncoderOptions(void)
{
    return encoder_options;
}

void ProfileForm::ProfileReportListViewEvents<LameOptions>::SetAlgorithmQuality(LameOptions::AlgorithmQuality algorithm_quality)
{
    encoder_options.algorithm_quality = algorithm_quality;
    std::wstring text = WindowsUtilities::UTF8_Decode(LameOptions::algorithm_quality_to_text.at(algorithm_quality));
    profile_form->profile_report_list_view->SetCellText(1u, 0u, text.c_str(), text.length() + 1);
}

void ProfileForm::ProfileReportListViewEvents<LameOptions>::SetMode(LameOptions::Mode mode)
{
    encoder_options.mode = mode;
    std::wstring text = WindowsUtilities::UTF8_Decode(LameOptions::mode_to_text.at(mode));
    profile_form->profile_report_list_view->SetCellText(1u, 1u, text.c_str(), text.length() + 1);
}

void ProfileForm::ProfileReportListViewEvents<LameOptions>::SetReplayGainMode(LameOptions::ReplayGain replaygain_mode)
{
    encoder_options.replaygain_mode = replaygain_mode;
    std::wstring text = WindowsUtilities::UTF8_Decode(LameOptions::replaygain_mode_to_text.at(replaygain_mode));
    profile_form->profile_report_list_view->SetCellText(1u, 2u, text.c_str(), text.length() + 1);
}

void ProfileForm::ProfileReportListViewEvents<LameOptions>::SetCopyright(bool copyright)
{
    encoder_options.copyright = copyright;
    std::wstring text = WindowsUtilities::UTF8_Decode(copyright ? EncoderOptions::bool_true_text : EncoderOptions::bool_false_text);
    profile_form->profile_report_list_view->SetCellText(1u, 3u, text.c_str(), text.length() + 1);
}

void ProfileForm::ProfileReportListViewEvents<LameOptions>::SetUseNaokiPsytune(bool use_naoki_psytune)
{
    encoder_options.use_naoki_psytune = use_naoki_psytune;
    std::wstring text = WindowsUtilities::UTF8_Decode(use_naoki_psytune ? EncoderOptions::bool_true_text : EncoderOptions::bool_false_text);
    profile_form->profile_report_list_view->SetCellText(1u, 4u, text.c_str(), text.length() + 1);
}

void ProfileForm::ProfileReportListViewEvents<LameOptions>::SetBitrateEncoding(LameOptions::BitrateEncoding bitrate_encoding)
{
    encoder_options.bitrate_encoding = bitrate_encoding;
    std::wstring text = WindowsUtilities::UTF8_Decode(LameOptions::bitrate_encoding_to_text.at(bitrate_encoding));
    profile_form->profile_report_list_view->SetCellText(1u, 5u, text.c_str(), text.length() + 1);
}

bool ProfileForm::ProfileReportListViewEvents<LameOptions>::SetVbrQuality(float vbr_quality)
{
    bool valid_value = encoder_options.SetVbrQuality(vbr_quality);

    if(valid_value)
    {
        std::wstring text = std::to_wstring(vbr_quality);
        profile_form->profile_report_list_view->SetCellText(1u, 6u, text.c_str(), text.length() + 1);
    }

    return valid_value;
}

void ProfileForm::ProfileReportListViewEvents<LameOptions>::SetMinOrMaxBitrate1(LameOptions::Bitrate min_or_max_bitrate1)
{
    encoder_options.min_or_max_bitrate1 = min_or_max_bitrate1;
    std::wstring text = WindowsUtilities::UTF8_Decode(LameOptions::bitrate_to_text.at(min_or_max_bitrate1));
    profile_form->profile_report_list_view->SetCellText(1u, 7u, text.c_str(), text.length() + 1);
}

void ProfileForm::ProfileReportListViewEvents<LameOptions>::SetMinOrMaxBitrate2(LameOptions::Bitrate min_or_max_bitrate2)
{
    encoder_options.min_or_max_bitrate2 = min_or_max_bitrate2;
    std::wstring text = WindowsUtilities::UTF8_Decode(LameOptions::bitrate_to_text.at(min_or_max_bitrate2));
    profile_form->profile_report_list_view->SetCellText(1u, 8u, text.c_str(), text.length() + 1);
}

ProfileForm::ProfileReportListViewEvents<LameOptions>::~ProfileReportListViewEvents(void)
{
    profile_form->profile_report_list_view->RemoveAllRows();
    this->profile_form->encoder_profile_loaded = false;
}

ProfileForm::CmbBxOptionsSetterEvents<LameOptions>::CmbBxOptionsSetterEvents(ProfileForm *profile_form)
{
    this->profile_form = profile_form;
}

ProfileForm::SLTxtBxOptionsSetterEvents<LameOptions>::SLTxtBxOptionsSetterEvents(ProfileForm *profile_form)
{
    this->profile_form = profile_form;
}

ProfileForm::ProfileReportListViewEvents<SndFileEncoderOptions>::ProfileReportListViewEvents(ProfileForm *profile_form)
{
    this->profile_form = profile_form;
    this->profile_form->encoder_profile_loaded = true;
    this->profile_form->loaded_encoder_profile_id = Encoder<void>::ID::SNDFILEENCODER;

    LoadDefaultProfile();
}

void ProfileForm::ProfileReportListViewEvents<SndFileEncoderOptions>::LoadDefaultProfile()
{
    encoder_options.LoadDefaultProfile(SndFileEncoderOptions::Profile::DEFAULT);

    std::wstring text;

    if(!loaded)
    {
        text = L"Output format";
        profile_form->profile_report_list_view->InsertRow(0u, text.c_str(), text.length() + 1);

        loaded = true;
    }

    text = WindowsUtilities::UTF8_Decode(SndFileEncoderOptions::output_format_to_text.at(encoder_options.output_format));
    profile_form->profile_report_list_view->SetCellText(1u, 0u, text.c_str(), text.length() + 1);
}

void ProfileForm::ProfileReportListViewEvents<SndFileEncoderOptions>::SetOutputFormat(SndFileEncoderOptions::OutputFormat output_format)
{
    encoder_options.output_format = output_format;
    std::wstring text = WindowsUtilities::UTF8_Decode(SndFileEncoderOptions::output_format_to_text.at(output_format));
    profile_form->profile_report_list_view->SetCellText(1u, 0u, text.c_str(), text.length() + 1);
}

ProfileForm::ProfileReportListViewEvents<SndFileEncoderOptions>::~ProfileReportListViewEvents()
{
    profile_form->profile_report_list_view->RemoveAllRows();
    this->profile_form->encoder_profile_loaded = false;
}

void ProfileForm::BtnOpenEvents::OnClick(HWND hWnd)
{
    COMDLG_FILTERSPEC filters[4] = {{L"All files", L"*"},
                                    {L"All supported types", L"*.lame;*.sndfe"},
                                    {L"LAME Profile", L"*.lame"},
                                    {L"Libsndfile Encoder Profile", L"*.sndfe"}};
    OpenFileDialogEvents ofde;
    OpenFileDialog ofd(hWnd, filters, sizeof(filters) / sizeof(COMDLG_FILTERSPEC), false, &ofde);

    if(ofd.HasResult())
    {
        //MsgBox::Show(ofd.GetFile(RustyFile::File::FULL_PATH));
    }

}

void ProfileForm::BtnSaveEvents::OnClick(HWND hWnd)
{

}

void ProfileForm::BtnSaveAsEvents::OnClick(HWND hWnd)
{
    if(profile_form->encoder_profile_loaded)
    {
        switch(profile_form->loaded_encoder_profile_id)
        {
            case Encoder<void>::ID::LAME:
            {
                COMDLG_FILTERSPEC filters[2] = {{L"All files", L"*"},
                                                {L"LAME Profile", L"*.lame"}};

                SaveFileDialog sfd(hWnd, filters, sizeof(filters) / sizeof(COMDLG_FILTERSPEC));

                if(sfd.HasResult())
                {
                    std::wstring file_path = sfd.GetFile(RustyFile::File::FULL_PATH);
                    try
                    {
                        SettingsManager::Write(profile_form->lame_profile_report_list_view_events->GetEncoderOptions(), WindowsUtilities::UTF8_Encode(file_path));
                    }
                    catch(WriteFileException ex)
                    {
                        MsgBox::Show(ex.GetErrorMessage());
                    }
                }
                break;
            }
            case Encoder<void>::ID::SNDFILEENCODER:
            {
                COMDLG_FILTERSPEC filters[2] = {{L"All files", L"*"},
                                                {L"Libsndfile Encoder Profile", L"*.sndfe"}};

                SaveFileDialog sfd(hWnd, filters, sizeof(filters) / sizeof(COMDLG_FILTERSPEC));

                if(sfd.HasResult())
                {
                    std::wstring file_path = sfd.GetFile(RustyFile::File::FULL_PATH);

                }
                break;
            }
        }
    }
}

LRESULT ProfileForm::HandleEvent(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_COMMAND:
        {
            switch(LOWORD(wParam))
            {
                case PROFILEFORM_BTN_OPEN:
                {
                    switch(HIWORD(wParam))
                    {
                        case BN_CLICKED:
                            btn_open_events->OnClick(hWnd);
                            break;
                    }
                    break;
                }
                case PROFILEFORM_BTN_SAVE:
                {
                    switch(HIWORD(wParam))
                    {
                        case BN_CLICKED:
                            btn_save_events->OnClick(hWnd);
                            break;
                    }
                    break;
                }
                case PROFILEFORM_BTN_SAVE_AS:
                {
                    switch(HIWORD(wParam))
                    {
                        case BN_CLICKED:
                            btn_save_as_events->OnClick(hWnd);
                            break;
                    }
                    break;
                }
                case PROFILEFORM_BTN_LOAD_DEFAULT:
                {
                    switch(HIWORD(wParam))
                    {
                        case BN_CLICKED:
                            btn_load_default_events->OnClick();
                            break;
                    }
                    break;
                }
            }
            break;
        }
        case WM_CREATE:
            OnCreate(hWnd);
            break;
        case WM_DESTROY:
            me->reset();
            break;
        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return 0ull;
}
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
    int y_padding = x_padding;

    lbl_encoder_sign.reset(new Label(hInstance, L"Encoder", hWnd, PROFILEFORM_LBL_ENCODER_SIGN, x_padding, y_padding + 4, 50, 18));

    cmbbx_encoder.reset(new ComboBox(hInstance, hWnd, PROFILEFORM_CMBBX_ENCODER, 65, y_padding, Window::GetClientWidth(hWnd) - x_padding - 160, ComboBox::Type::DROP_DOWN_LIST));
    cmbbx_encoder_events.reset(new CmbBxEncoderEvents(this));

    btn_load_default.reset(new Button(hInstance, L"Load default", hWnd, PROFILEFORM_BTN_LOAD_DEFAULT, Window::GetClientRight(hWnd) - x_padding - 90, y_padding, 90, 22));
    btn_load_default_events.reset(new BtnLoadDefaultEvents(this));

    profile_report_list_view.reset(new ReportListView(hInstance, hWnd, PROFILEFORM_PROFILE_REPORT_LIST_VIEW, x_padding, y_padding + 27, Window::GetClientWidth(hWnd) - y_padding * 2, Window::GetClientHeight(hWnd) - 95 - y_padding, WS_EX_LEFT, LVS_REPORT | LVS_SINGLESEL | LVS_SHOWSELALWAYS | WS_CHILD | WS_VISIBLE, true));
    profile_report_list_view_events.reset(new ProfileReportListViewEvents(this));

    lbl_option_value_sign.reset(new Label(hInstance, L"Value", hWnd, PROFILEFORM_LBL_OPTION_VALUE_SIGN, x_padding, Window::GetClientBottom(hWnd) - y_padding - 52, 32, 18, WS_EX_LEFT, SS_LEFT | SS_LEFTNOWORDWRAP | WS_CHILD | WS_VISIBLE));

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

bool ProfileForm::CmbBxEncoderEvents::IsSelectedEncoder()
{
    return profile_form->cmbbx_encoder->HasSelectedItems();
}

Encoder<void>::ID ProfileForm::CmbBxEncoderEvents::GetSelectedEncoderID()
{
    unsigned int selected_item_index = profile_form->cmbbx_encoder->GetSelectedItemIndex();

    return static_cast<Encoder<void>::ID>(profile_form->cmbbx_encoder->GetItemData(selected_item_index));
}

void ProfileForm::BtnLoadDefaultEvents::OnClick()
{
    if(profile_form->cmbbx_encoder_events->IsSelectedEncoder())
    {
        profile_form->profile_report_list_view_events->LoadDefaultProfile(profile_form->cmbbx_encoder_events->GetSelectedEncoderID());
    }
}

ProfileForm::ProfileReportListViewEvents::ProfileReportListViewEvents(ProfileForm *profile_form) : profile_form(profile_form)
{
    std::wstring text(L"Option");
    profile_form->profile_report_list_view->InsertColumn(200u, 0u, text.c_str());

    text = L"Value";
    profile_form->profile_report_list_view->InsertColumn(200u, 1u, text.c_str());
}

bool ProfileForm::ProfileReportListViewEvents::IsEncoderProfileLoaded()
{
    return loaded_encoder_profile;
}

bool ProfileForm::ProfileReportListViewEvents::HasUnsavedProfileChanges()
{
    return profile_has_unsaved_changes;
}

std::wstring ProfileForm::ProfileReportListViewEvents::GetCurrentProfileLastSavedFullPath()
{
    return current_profile_last_saved_full_path;
}

Encoder<void>::ID ProfileForm::ProfileReportListViewEvents::GetLoadedProfileEncoderID()
{
    return loaded_encoder_profile_id;
}

void ProfileForm::ProfileReportListViewEvents::SaveProfile(std::wstring profile_full_path)
{
    if(loaded_encoder_profile)
    {
        switch(loaded_encoder_profile_id)
        {
            case Encoder<void>::ID::LAME:
            {
                LameOptions *lame_options = static_cast<LameOptions *>(encoder_options.get());
                SettingsManager::Write(*lame_options, WindowsUtilities::UTF8_Encode(profile_full_path));
                break;
            }
            case Encoder<void>::ID::SNDFILEENCODER:
            {
                SndFileEncoderOptions *sndfileencoder_options = static_cast<SndFileEncoderOptions *>(encoder_options.get());
                SettingsManager::Write(*sndfileencoder_options, WindowsUtilities::UTF8_Encode(profile_full_path));
                break;
            }
        }

        profile_has_unsaved_changes = false;
        current_profile_last_saved_full_path = profile_full_path;
    }
}

void ProfileForm::ProfileReportListViewEvents::LoadProfile(HWND hWnd)
{
    OpenFileDialog open_file_dialog(hWnd, FileExtensionFilters::input_profile_format_filters, sizeof(FileExtensionFilters::input_profile_format_filters) / sizeof(COMDLG_FILTERSPEC), false);

    if(open_file_dialog.HasResult())
    {
        std::wstring profile_full_file_path = open_file_dialog.GetFile(RustyFile::File::FULL_PATH);
        std::wstring profile_file_extension = open_file_dialog.GetFile(RustyFile::File::EXTENSION);

        if(profile_file_extension == PROFILE_EXTENSION_LAME_W)
        {
            try
            {
                LameOptions lame_options;
                SettingsManager::Read(lame_options, WindowsUtilities::UTF8_Encode(profile_full_file_path));
                PopulateListView(Encoder<void>::ID::LAME, &lame_options);
            }
            catch(ReadFileException &ex)
            {
                MsgBox::Show(ex.what(), hWnd);
            }

            current_profile_last_saved_full_path = profile_full_file_path;
        }
        else if(profile_file_extension == PROFILE_EXTENSION_SNDFILEENCODER_W)
        {
            try
            {
                SndFileEncoderOptions sndfileencoder_options;
                SettingsManager::Read(sndfileencoder_options, WindowsUtilities::UTF8_Encode(profile_full_file_path));
                PopulateListView(Encoder<void>::ID::SNDFILEENCODER, &sndfileencoder_options);
            }
            catch(ReadFileException &ex)
            {
                MsgBox::Show(ex.what(), hWnd);
            }

            current_profile_last_saved_full_path = profile_full_file_path;
        }
    }
}

void ProfileForm::ProfileReportListViewEvents::LoadDefaultProfile(Encoder<void>::ID encoder_id)
{
    PopulateListView(encoder_id, nullptr);
}

void ProfileForm::ProfileReportListViewEvents::SetEncoderOption(std::string &value)
{
    unsigned int selected_item_index = profile_form->profile_report_list_view->GetNextSelectedItem();

    encoder_options->SetValueForOption(selected_item_index, value);

    encoder_options->GetCurrentValueForOptionInString(selected_item_index, value);

    profile_form->profile_report_list_view->SetCellText(1, selected_item_index, WindowsUtilities::UTF8_Decode(value).c_str());

    profile_has_unsaved_changes = true;
}

void ProfileForm::ProfileReportListViewEvents::PopulateListView(Encoder<void>::ID encoder_id, EncoderOptions *encoder_options)
{
    if(has_old_loaded_encoder_profile_id)
    {
        old_loaded_encoder_profile_id = loaded_encoder_profile_id;

        if(old_loaded_encoder_profile_id != encoder_id)
        {
            this->encoder_options.reset();
            current_profile_last_saved_full_path.clear();
            profile_form->profile_report_list_view->RemoveAllRows();
        }
    }

    loaded_encoder_profile_id = encoder_id;

    std::wstring wtext;
    std::string text;
    unsigned int option_count;

    EncoderOptions *_encoder_options;

    if(encoder_options != nullptr)
        _encoder_options = encoder_options;
    else
        _encoder_options = this->encoder_options.get();

    switch(encoder_id)
    {
        case Encoder<void>::ID::LAME:
        {
            if(encoder_options == nullptr)
                this->encoder_options.reset(new LameOptions());
            else
            {
                LameOptions *lame_options = static_cast<LameOptions *>(encoder_options);
                this->encoder_options.reset(new LameOptions(*lame_options));
            }
            break;
        }
        case Encoder<void>::ID::SNDFILEENCODER:
        {
            if(encoder_options == nullptr)
                this->encoder_options.reset(new SndFileEncoderOptions());
            else
            {
                SndFileEncoderOptions *sndfileencoder_options = static_cast<SndFileEncoderOptions *>(encoder_options);
                this->encoder_options.reset(new SndFileEncoderOptions(*sndfileencoder_options));
            }
            break;
        }
    }

    _encoder_options = this->encoder_options.get();

    if(has_old_loaded_encoder_profile_id == false || old_loaded_encoder_profile_id != encoder_id)
    {
        option_count = _encoder_options->GetOptionsCount();

        for(unsigned int index = 0u; index < option_count; ++index)
        {
            text = _encoder_options->GetOptionsInString(index);
            wtext = WindowsUtilities::UTF8_Decode(text);
            profile_form->profile_report_list_view->InsertRow(index, wtext.c_str());
        }
    }
    else
        option_count = _encoder_options->GetOptionsCount();

    has_old_loaded_encoder_profile_id = true;

    for(unsigned int index = 0u; index < option_count; ++index)
    {
        text = _encoder_options->GetOptionsInString(index);
        _encoder_options->GetCurrentValueForOptionInString(text, text);
        wtext = WindowsUtilities::UTF8_Decode(text);
        profile_form->profile_report_list_view->SetCellText(1u, index, wtext.c_str());
    }

    if(encoder_options == nullptr)
        profile_has_unsaved_changes = true;

    loaded_encoder_profile = true;
}

void ProfileForm::ProfileReportListViewEvents::OnItemChanged(NMLISTVIEW *list_view_notification_message)
{
    if(list_view_notification_message->uNewState == (LVIS_SELECTED | LVIS_FOCUSED) && list_view_notification_message->iItem >= 0)
    {
        style_change_count = 0u;

        unsigned int selection_count = encoder_options->GetSelectionCountForOption(list_view_notification_message->iItem);

        int value_text_length = 256;
        std::unique_ptr<wchar_t> value_text(new wchar_t[value_text_length]);
        wchar_t *_value_text = value_text.get();

        if(selection_count > 0u)
        {
            if(setter_control_created)
            {
                if(profile_form->sltxtbx_options_setter.get() != nullptr)
                {
                    profile_form->sltxtbx_options_setter.reset();
                    profile_form->btn_set_option.reset();
                    profile_form->btn_set_option_events.reset();
                    setter_control_created = false;
                }
            }

            if(profile_form->cmbbx_options_setter.get() == nullptr)
            {
                profile_form->cmbbx_options_setter.reset(new ComboBox(profile_form->hInstance, profile_form->window->GetHandle(), PROFILEFORM_CMBBX_OPTION_SETTER, 45, profile_form->window->GetClientBottom() - 60, profile_form->window->GetClientRight() - 50, ComboBox::Type::DROP_DOWN_LIST));
                profile_form->cmbbx_options_setter_events.reset(new CmbBxOptionsSetterEvents(profile_form));
                setter_control_created = true;
            }
            else
            {
                if(profile_form->cmbbx_options_setter->GetItemCount())
                    profile_form->cmbbx_options_setter->RemoveAllItems();
            }

            for(unsigned int index = 0; index < selection_count; ++index)
            {
                std::wstring selection(WindowsUtilities::UTF8_Decode(encoder_options->GetSelectionForOptionInString(list_view_notification_message->iItem, index)));
                profile_form->cmbbx_options_setter->AppendItem(selection.c_str());
            }

            profile_form->profile_report_list_view->GetCellText(1, list_view_notification_message->iItem, &_value_text, value_text_length);

            profile_form->cmbbx_options_setter->SelectItem(0, _value_text);
        }
        else
        {
            if(setter_control_created)
            {
                if(profile_form->cmbbx_options_setter.get() != nullptr)
                {
                    profile_form->cmbbx_options_setter.reset();
                    profile_form->cmbbx_options_setter_events.reset();
                    setter_control_created = false;
                }
            }

            if(profile_form->sltxtbx_options_setter.get() == nullptr)
            {
                profile_form->sltxtbx_options_setter.reset(new SingleLineTextBox(profile_form->hInstance, nullptr, profile_form->window->GetHandle(), PROFILEFORM_SLTXTBX_OPTION_SETTER, 45, profile_form->window->GetClientBottom() - 60, profile_form->window->GetClientRight() - 145, 23));
                profile_form->btn_set_option.reset(new Button(profile_form->hInstance, L"Set", profile_form->window->GetHandle(), PROFILEFORM_BTN_SET_OPTION, profile_form->window->GetClientRight() - 95, profile_form->window->GetClientBottom() - 60, 90, 23));
                profile_form->btn_set_option_events.reset(new BtnSetOptionEvents(profile_form));
                setter_control_created = true;
            }

            profile_form->profile_report_list_view->GetCellText(1, list_view_notification_message->iItem, &_value_text, value_text_length);

            profile_form->sltxtbx_options_setter->SetText(_value_text);
        }
    }
    else
    {
        // style_change_count == 1 when LVIS_FOCUSED is unset. Occurs when previous item selected is unselected and a new item is selected
        // style_change_count == 2 when only LVIS_SELECTED is unset. Occurs when blank space is clicked causing the previous item selected to be unselected.

        style_change_count |= list_view_notification_message->uOldState;

        if(style_change_count == 0x2)
        {
            if(profile_form->cmbbx_options_setter.get() != nullptr)
            {
                profile_form->cmbbx_options_setter.reset();
                profile_form->cmbbx_options_setter_events.reset();
            }

            if(profile_form->sltxtbx_options_setter.get() != nullptr)
            {
                profile_form->sltxtbx_options_setter.reset();
                profile_form->btn_set_option.reset();
                profile_form->btn_set_option_events.reset();
            }

            setter_control_created = false;
            style_change_count = 0;
        }
    }
}

void ProfileForm::ProfileReportListViewEvents::OnDeleteAllItems()
{
    if(profile_form->cmbbx_options_setter.get() != nullptr)
    {
        profile_form->cmbbx_options_setter.reset();
        profile_form->cmbbx_options_setter_events.reset();
    }

    if(profile_form->sltxtbx_options_setter.get() != nullptr)
    {
        profile_form->sltxtbx_options_setter.reset();
        profile_form->btn_set_option.reset();
        profile_form->btn_set_option_events.reset();
    }

    setter_control_created = false;
}

void ProfileForm::CmbBxOptionsSetterEvents::OnSelectionOk()
{
    std::string selected_item_text = WindowsUtilities::UTF8_Encode(profile_form->cmbbx_options_setter->GetItemText(profile_form->cmbbx_options_setter->GetSelectedItemIndex()));
    profile_form->profile_report_list_view_events->SetEncoderOption(selected_item_text);
}

void ProfileForm::BtnSetOptionEvents::OnClick(HWND hWnd)
{
    wchar_t sltxtbx_options_setter_text[256];
    profile_form->sltxtbx_options_setter->GetText(sltxtbx_options_setter_text, 256);

    std::string value(WindowsUtilities::UTF8_Encode(sltxtbx_options_setter_text));

    try
    {
        profile_form->profile_report_list_view_events->SetEncoderOption(value);
    }
    catch(InvalidArgumentException &ex)
    {
        MsgBox::Show(ex.what(), hWnd);
    }
}

void ProfileForm::BtnOpenEvents::OnClick(HWND hWnd)
{
    profile_form->profile_report_list_view_events->LoadProfile(hWnd);
}

void ProfileForm::BtnSaveEvents::OnClick()
{
    std::wstring current_profile_last_saved_full_path(profile_form->profile_report_list_view_events->GetCurrentProfileLastSavedFullPath());

    if(profile_form->profile_report_list_view_events->HasUnsavedProfileChanges() && !current_profile_last_saved_full_path.empty())
    {
        try
        {
            profile_form->profile_report_list_view_events->SaveProfile(current_profile_last_saved_full_path);
        }
        catch(WriteFileException &ex)
        {
            MsgBox::Show(ex.what(), profile_form->window->GetHandle());
        }
    }
}

void ProfileForm::BtnSaveAsEvents::OnClick(HWND hWnd)
{
    if(profile_form->profile_report_list_view_events->IsEncoderProfileLoaded())
    {
        Encoder<void>::ID encoder_id = profile_form->profile_report_list_view_events->GetLoadedProfileEncoderID();

        std::unique_ptr<COMDLG_FILTERSPEC> output_profile_format_filters;

        switch(encoder_id)
        {
            case Encoder<void>::ID::LAME:
            {
                output_profile_format_filters.reset(new COMDLG_FILTERSPEC[1]);
                COMDLG_FILTERSPEC *_output_profile_format_filters = output_profile_format_filters.get();
                _output_profile_format_filters[0] = {L"LAME Profile", L"*.lame"};
                break;
            }
            case Encoder<void>::ID::SNDFILEENCODER:
            {
                output_profile_format_filters.reset(new COMDLG_FILTERSPEC[1]);
                COMDLG_FILTERSPEC *_output_profile_format_filters = output_profile_format_filters.get();
                _output_profile_format_filters[0] = {L"Libsndfile Encoder Profile", L"*.sndfe"};
                break;
            }
        }

        SaveFileDialog save_file_dialog(hWnd, output_profile_format_filters.get(), 1);

        if(save_file_dialog.HasResult())
        {
            std::wstring profile_full_file_path(save_file_dialog.GetFile(RustyFile::File::FULL_PATH));
            std::wstring profile_file_extension(save_file_dialog.GetFile(RustyFile::File::EXTENSION));

            switch(encoder_id)
            {
                case Encoder<void>::ID::LAME:
                {
                    if(profile_file_extension.empty() || profile_file_extension != WindowsUtilities::UTF8_Decode(LameOptions::profile_file_extension))
                    {
                        profile_full_file_path.append(L".");
                        profile_full_file_path.append(WindowsUtilities::UTF8_Decode(LameOptions::profile_file_extension));
                    }
                    break;
                }
                case Encoder<void>::ID::SNDFILEENCODER:
                {
                    if(profile_file_extension.empty() || profile_file_extension != WindowsUtilities::UTF8_Decode(SndFileEncoderOptions::profile_file_extension))
                    {
                        profile_full_file_path.append(L".");
                        profile_full_file_path.append(WindowsUtilities::UTF8_Decode(SndFileEncoderOptions::profile_file_extension));
                    }
                    break;
                }
            }

            try
            {
                profile_form->profile_report_list_view_events->SaveProfile(profile_full_file_path);
            }
            catch(WriteFileException &ex)
            {
                MsgBox::Show(ex.what(), hWnd);
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
                case PROFILEFORM_CMBBX_OPTION_SETTER:
                {
                    switch(HIWORD(wParam))
                    {
                        case CBN_SELENDOK:
                        {
                            cmbbx_options_setter_events->OnSelectionOk();
                            break;
                        }
                    }
                    break;
                }
                case PROFILEFORM_BTN_SET_OPTION:
                {
                    switch(HIWORD(wParam))
                    {
                        case BN_CLICKED:
                            btn_set_option_events->OnClick(hWnd);
                            break;
                    }
                    break;
                }
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
                            btn_save_events->OnClick();
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
        case WM_NOTIFY:
        {
            NMHDR *notification_message = reinterpret_cast<NMHDR *>(lParam);
            switch(notification_message->idFrom)
            {
                case PROFILEFORM_PROFILE_REPORT_LIST_VIEW:
                {
                    switch(notification_message->code)
                    {
                        case LVN_ITEMCHANGED:
                        {
                            profile_report_list_view_events->OnItemChanged(reinterpret_cast<NMLISTVIEW *>(lParam));
                            break;
                        }
                        case LVN_DELETEALLITEMS:
                        {
                            if(!form_deleting)
                                profile_report_list_view_events->OnDeleteAllItems();
                            break;
                        }
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
            form_deleting = true;
            me->reset();
            break;
        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return 0ull;
}
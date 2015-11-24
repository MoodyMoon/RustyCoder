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

rusty::gui::ProfileForm::ProfileForm(HINSTANCE hInstance, HWND hWndParent, std::unique_ptr<ProfileForm> &me) : hInstance(hInstance), hWndParent(hWndParent), me(&me)
{
    window.reset(new controls::Window(hInstance, this, L"ProfileForm", L"Profile", hWndParent, WS_EX_DLGMODALFRAME, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_VISIBLE, -1, -1, CW_USEDEFAULT, CW_USEDEFAULT, 450, 550, true));
    window->Focus();
}

void rusty::gui::ProfileForm::OnCreate(HWND hWnd)
{
    int x_padding = 5;
    int y_padding = x_padding;

    lbl_encoder_sign.reset(new controls::Label(hInstance, L"Encoder", hWnd, PROFILEFORM_LBL_ENCODER_SIGN, x_padding, y_padding + 4, 50, 18));

    cmbbx_encoder.reset(new controls::ComboBox(hInstance, hWnd, PROFILEFORM_CMBBX_ENCODER, 65, y_padding, controls::Window::GetClientWidth(hWnd) - x_padding - 160, controls::ComboBox::Type::DROP_DOWN_LIST));
    cmbbx_encoder_events.reset(new CmbBxEncoderEvents(this));

    btn_load_default.reset(new controls::Button(hInstance, L"Load default", hWnd, PROFILEFORM_BTN_LOAD_DEFAULT, controls::Window::GetClientRight(hWnd) - x_padding - 90, y_padding, 90, 22));
    btn_load_default_events.reset(new BtnLoadDefaultEvents(this));

    profile_report_list_view.reset(new controls::ReportListView(hInstance, hWnd, PROFILEFORM_PROFILE_REPORT_LIST_VIEW, x_padding, y_padding + 27, controls::Window::GetClientWidth(hWnd) - y_padding * 2, controls::Window::GetClientHeight(hWnd) - 95 - y_padding, WS_EX_LEFT, LVS_REPORT | LVS_SINGLESEL | LVS_SHOWSELALWAYS | WS_CHILD | WS_VISIBLE, true));
    profile_report_list_view_events.reset(new ProfileReportListViewEvents(this));

    lbl_option_value_sign.reset(new controls::Label(hInstance, L"Value", hWnd, PROFILEFORM_LBL_OPTION_VALUE_SIGN, x_padding, controls::Window::GetClientBottom(hWnd) - y_padding - 52, 32, 18, WS_EX_LEFT, SS_LEFT | SS_LEFTNOWORDWRAP | WS_CHILD | WS_VISIBLE));

    btn_open.reset(new controls::Button(hInstance, L"Open", hWnd, PROFILEFORM_BTN_OPEN, x_padding, controls::Window::GetClientBottom(hWnd) - 30, 90, 25));
    btn_open_events.reset(new BtnOpenEvents(this));

    btn_save_as.reset(new controls::Button(hInstance, L"Save As", hWnd, PROFILEFORM_BTN_SAVE_AS, 100, controls::Window::GetClientBottom(hWnd) - 30, 90, 25));
    btn_save_as_events.reset(new BtnSaveAsEvents(this));

    form_loaded = true;
}

rusty::gui::ProfileForm::~ProfileForm()
{
    controls::Window::Focus(hWndParent);
}

rusty::gui::ProfileForm::CmbBxEncoderEvents::CmbBxEncoderEvents(ProfileForm *profile_form) : profile_form(profile_form)
{
    profile_form->cmbbx_encoder->AppendItem(PROFILE_EXTENSION_DESCRIPTION_LAME_W, static_cast<LPARAM>(codecs::Encoder<void>::ID::LAME));
    profile_form->cmbbx_encoder->AppendItem(PROFILE_EXTENSION_DESCRIPTION_SNDFILE_ENCODER_W, static_cast<LPARAM>(codecs::Encoder<void>::ID::SNDFILE_ENCODER));
}

bool rusty::gui::ProfileForm::CmbBxEncoderEvents::IsSelectedEncoder()
{
    return profile_form->cmbbx_encoder->HasSelectedItems();
}

rusty::codecs::Encoder<void>::ID rusty::gui::ProfileForm::CmbBxEncoderEvents::GetSelectedEncoderID()
{
    unsigned int selected_item_index = profile_form->cmbbx_encoder->GetSelectedItemIndex();

    return static_cast<codecs::Encoder<void>::ID>(profile_form->cmbbx_encoder->GetItemData(selected_item_index));
}

void rusty::gui::ProfileForm::CmbBxEncoderEvents::SetSelectedEncoderID(codecs::Encoder<void>::ID encoder_id)
{
    profile_form->cmbbx_encoder->SelectItem(-1, static_cast<LPARAM>(encoder_id));
}

void rusty::gui::ProfileForm::BtnLoadDefaultEvents::OnClick()
{
    if(profile_form->cmbbx_encoder_events->IsSelectedEncoder())
    {
        profile_form->profile_report_list_view_events->LoadDefaultProfile(profile_form->cmbbx_encoder_events->GetSelectedEncoderID());
    }
}

rusty::gui::ProfileForm::ProfileReportListViewEvents::ProfileReportListViewEvents(ProfileForm *profile_form) : profile_form(profile_form)
{
    std::wstring text(L"Option");
    profile_form->profile_report_list_view->InsertColumn(200u, 0u, text.c_str());

    text = L"Value";
    profile_form->profile_report_list_view->InsertColumn(200u, 1u, text.c_str());
}

bool rusty::gui::ProfileForm::ProfileReportListViewEvents::IsEncoderProfileLoaded()
{
    return loaded_encoder_profile;
}

bool rusty::gui::ProfileForm::ProfileReportListViewEvents::HasUnsavedProfileChanges()
{
    return profile_has_unsaved_changes;
}

boost::filesystem::path & rusty::gui::ProfileForm::ProfileReportListViewEvents::GetCurrentProfileLastSavedFullPath()
{
    return current_profile_last_saved_full_path;
}

rusty::codecs::Encoder<void>::ID rusty::gui::ProfileForm::ProfileReportListViewEvents::GetLoadedProfileEncoderID()
{
    return loaded_encoder_profile_id;
}

rusty::codecs::EncoderProfile * rusty::gui::ProfileForm::ProfileReportListViewEvents::GetEncoderProfile()
{
    return encoder_profile.get();
}

void rusty::gui::ProfileForm::ProfileReportListViewEvents::SaveProfile(const boost::filesystem::path &profile_full_path)
{
    if(loaded_encoder_profile)
    {
        try
        {
            engine::EncoderProfileWriter encoder_profile_writer;
            encoder_profile_writer.WriteFile(*encoder_profile.get(), loaded_encoder_profile_id, profile_full_path);

            profile_has_unsaved_changes = false;
        }
        catch(core::WriteFileException &ex)
        {
            controls::MsgBox::Show(ex.what(), profile_form->window->GetHandle());
        }

        current_profile_last_saved_full_path = profile_full_path;
    }
}

void rusty::gui::ProfileForm::ProfileReportListViewEvents::LoadProfile()
{
    controls::OpenFileDialog open_file_dialog(profile_form->window->GetHandle(), FileExtensionFilters::profile_format_filters, sizeof(FileExtensionFilters::profile_format_filters) / sizeof(COMDLG_FILTERSPEC), false);

    if(open_file_dialog.HasResult())
    {
        boost::filesystem::path profile_full_file_path(open_file_dialog.GetFile(0ul));

        try
        {
            engine::EncoderProfileReader encoder_profile_reader(profile_full_file_path);

            std::shared_ptr<codecs::EncoderProfile> encoder_profile(encoder_profile_reader.GetEncoderProfile());

            profile_form->cmbbx_encoder_events->SetSelectedEncoderID(encoder_profile_reader.GetEncoderID());

            PopulateListView(encoder_profile_reader.GetEncoderID(), encoder_profile.get());
        }
        catch(core::Exception &ex)
        {
            controls::MsgBox::Show(ex.what(), profile_form->window->GetHandle());
        }

        current_profile_last_saved_full_path = profile_full_file_path;
    }
}

void rusty::gui::ProfileForm::ProfileReportListViewEvents::LoadDefaultProfile(codecs::Encoder<void>::ID encoder_id)
{
    PopulateListView(encoder_id, nullptr);
}

void rusty::gui::ProfileForm::ProfileReportListViewEvents::SetEncoderOption(std::string &value)
{
    unsigned int selected_item_index = profile_form->profile_report_list_view->GetNextSelectedItem();

    encoder_profile->SetValueForOption(selected_item_index, value);

    encoder_profile->GetCurrentValueForOptionInString(selected_item_index, value);

    profile_form->profile_report_list_view->SetCellText(1, selected_item_index, core::WindowsUtilities::UTF8_Decode(value).c_str());

    profile_has_unsaved_changes = true;
}

void rusty::gui::ProfileForm::ProfileReportListViewEvents::PopulateListView(codecs::Encoder<void>::ID encoder_id, codecs::EncoderProfile *encoder_profile)
{
    if(has_old_loaded_encoder_profile_id)
    {
        old_loaded_encoder_profile_id = loaded_encoder_profile_id;

        if(old_loaded_encoder_profile_id != encoder_id)
        {
            this->encoder_profile.reset();
            current_profile_last_saved_full_path.clear();
            profile_form->profile_report_list_view->RemoveAllRows();
        }
    }

    loaded_encoder_profile_id = encoder_id;

    std::wstring wtext;
    std::string text;
    unsigned int option_count;

    codecs::EncoderProfile *_encoder_profile;

    if(encoder_profile != nullptr)
        _encoder_profile = encoder_profile;
    else
        _encoder_profile = this->encoder_profile.get();

    switch(encoder_id)
    {
        case codecs::Encoder<void>::ID::LAME:
        {
            if(encoder_profile == nullptr)
                this->encoder_profile.reset(new codecs::LameProfile());
            else
            {
                codecs::LameProfile *lame_profile = static_cast<codecs::LameProfile *>(encoder_profile);
                this->encoder_profile.reset(new codecs::LameProfile(*lame_profile));
            }
            break;
        }
        case codecs::Encoder<void>::ID::SNDFILE_ENCODER:
        {
            if(encoder_profile == nullptr)
                this->encoder_profile.reset(new codecs::SndFileEncoderProfile());
            else
            {
                codecs::SndFileEncoderProfile *sndfile_encoder_profile = static_cast<codecs::SndFileEncoderProfile *>(encoder_profile);
                this->encoder_profile.reset(new codecs::SndFileEncoderProfile(*sndfile_encoder_profile));
            }
            break;
        }
    }

    _encoder_profile = this->encoder_profile.get();

    if(has_old_loaded_encoder_profile_id == false || old_loaded_encoder_profile_id != encoder_id)
    {
        option_count = _encoder_profile->GetOptionsCount();

        for(unsigned int index = 0u; index < option_count; ++index)
        {
            text = _encoder_profile->GetOptionsInString(index);
            wtext = core::WindowsUtilities::UTF8_Decode(text);
            profile_form->profile_report_list_view->InsertRow(index, wtext.c_str(), nullptr);
        }
    }
    else
        option_count = _encoder_profile->GetOptionsCount();

    has_old_loaded_encoder_profile_id = true;

    for(unsigned int index = 0u; index < option_count; ++index)
    {
        text = _encoder_profile->GetOptionsInString(index);
        _encoder_profile->GetCurrentValueForOptionInString(text, text);
        wtext = core::WindowsUtilities::UTF8_Decode(text);
        profile_form->profile_report_list_view->SetCellText(1u, index, wtext.c_str());
    }

    if(encoder_profile == nullptr)
        profile_has_unsaved_changes = true;

    loaded_encoder_profile = true;
}

void rusty::gui::ProfileForm::ProfileReportListViewEvents::OnItemChanged(NMLISTVIEW *list_view_notification_message)
{
    if(list_view_notification_message->uNewState == (LVIS_SELECTED | LVIS_FOCUSED) && list_view_notification_message->iItem >= 0)
    {
        style_change_count = 0u;

        unsigned int selection_count = encoder_profile->GetSelectionCountForOption(list_view_notification_message->iItem);

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
                profile_form->cmbbx_options_setter.reset(new controls::ComboBox(profile_form->hInstance, profile_form->window->GetHandle(), PROFILEFORM_CMBBX_OPTION_SETTER, 45, profile_form->window->GetClientBottom() - 60, profile_form->window->GetClientRight() - 50, controls::ComboBox::Type::DROP_DOWN_LIST));
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
                std::wstring selection(core::WindowsUtilities::UTF8_Decode(encoder_profile->GetSelectionForOptionInString(list_view_notification_message->iItem, index)));
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
                profile_form->sltxtbx_options_setter.reset(new controls::SingleLineTextBox(profile_form->hInstance, nullptr, profile_form->window->GetHandle(), PROFILEFORM_SLTXTBX_OPTION_SETTER, 45, profile_form->window->GetClientBottom() - 60, profile_form->window->GetClientRight() - 145, 23));
                profile_form->btn_set_option.reset(new controls::Button(profile_form->hInstance, L"Set", profile_form->window->GetHandle(), PROFILEFORM_BTN_SET_OPTION, profile_form->window->GetClientRight() - 95, profile_form->window->GetClientBottom() - 60, 90, 23));
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

void rusty::gui::ProfileForm::ProfileReportListViewEvents::OnDeleteAllItems()
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

void rusty::gui::ProfileForm::CmbBxOptionsSetterEvents::OnSelectionOk()
{
    std::string selected_item_text = core::WindowsUtilities::UTF8_Encode(profile_form->cmbbx_options_setter->GetItemText(profile_form->cmbbx_options_setter->GetSelectedItemIndex()));
    profile_form->profile_report_list_view_events->SetEncoderOption(selected_item_text);
}

void rusty::gui::ProfileForm::BtnSetOptionEvents::OnClick(HWND hWnd)
{
    wchar_t sltxtbx_options_setter_text[256];
    profile_form->sltxtbx_options_setter->GetText(sltxtbx_options_setter_text, 256);

    std::string value(core::WindowsUtilities::UTF8_Encode(sltxtbx_options_setter_text));

    try
    {
        profile_form->profile_report_list_view_events->SetEncoderOption(value);
    }
    catch(core::InvalidArgumentException &ex)
    {
        controls::MsgBox::Show(ex.what(), hWnd);
    }
}

void rusty::gui::ProfileForm::BtnOpenEvents::OnClick()
{
    profile_form->profile_report_list_view_events->LoadProfile();
}

void rusty::gui::ProfileForm::BtnSaveAsEvents::OnClick(HWND hWnd)
{
    if(profile_form->profile_report_list_view_events->IsEncoderProfileLoaded())
    {
        codecs::Encoder<void>::ID encoder_id = profile_form->profile_report_list_view_events->GetLoadedProfileEncoderID();

        COMDLG_FILTERSPEC profile_format_filters[1];
        unsigned int profile_format_filters_size = 1;

        std::wstring filter_string;

        switch(encoder_id)
        {
            case codecs::Encoder<void>::ID::LAME:
            {
                profile_format_filters[0] = {PROFILE_EXTENSION_DESCRIPTION_LAME_W, ANYTHING_WILDCARD PROFILE_EXTENSION_LAME_MP3_W};
                break;
            }
            case codecs::Encoder<void>::ID::SNDFILE_ENCODER:
            {
                codecs::SndFileEncoderProfile *sndfile_encoder_profile = static_cast<codecs::SndFileEncoderProfile *>(profile_form->profile_report_list_view_events->GetEncoderProfile());

                filter_string = ANYTHING_WILDCARD PROFILE_EXTENSION_SNDFILE_ENCODER_W L"-";
                filter_string.append(core::WindowsUtilities::UTF8_Decode(codecs::SndFileEncoderProfile::output_format_to_file_extension.at(sndfile_encoder_profile->output_format)));
                profile_format_filters[0] = {PROFILE_EXTENSION_DESCRIPTION_SNDFILE_ENCODER_W,  filter_string.c_str()};
                break;
            }
        }

        controls::SaveFileDialog save_file_dialog(hWnd, profile_format_filters, profile_format_filters_size);

        if(save_file_dialog.HasResult())
        {
            boost::filesystem::path profile_full_file_path(save_file_dialog.GetFile());

            switch(encoder_id)
            {
                case codecs::Encoder<void>::ID::LAME:
                {
                    if(!profile_full_file_path.has_extension() || profile_full_file_path.extension() == "." || profile_full_file_path.extension() != "." PROFILE_EXTENSION_LAME_MP3)
                    {
                        profile_full_file_path.replace_extension(PROFILE_EXTENSION_LAME_MP3);
                    }
                    break;
                }
                case codecs::Encoder<void>::ID::SNDFILE_ENCODER:
                {
                    codecs::SndFileEncoderProfile *sndfile_encoder_profile = static_cast<codecs::SndFileEncoderProfile *>(profile_form->profile_report_list_view_events->GetEncoderProfile());

                    filter_string = L"." PROFILE_EXTENSION_SNDFILE_ENCODER_W L"-";

                    filter_string.append(core::WindowsUtilities::UTF8_Decode(codecs::SndFileEncoderProfile::output_format_to_file_extension.at(sndfile_encoder_profile->output_format)));

                    if(!profile_full_file_path.has_extension() || profile_full_file_path.extension() == "." || profile_full_file_path.extension() != filter_string)
                    {
                        profile_full_file_path.replace_extension(filter_string);
                    }
                    break;
                }
            }

            try
            {
                profile_form->profile_report_list_view_events->SaveProfile(profile_full_file_path);
            }
            catch(core::WriteFileException &ex)
            {
                controls::MsgBox::Show(ex.what(), hWnd);
            }
        }
    }
}

LRESULT rusty::gui::ProfileForm::HandleEvent(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
                            btn_open_events->OnClick();
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
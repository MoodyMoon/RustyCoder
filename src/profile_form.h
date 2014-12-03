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

#ifndef GUI_PROFILE_FORM_H
#define GUI_PROFILE_FORM_H

class ProfileForm : public EventHandlerInterface
{
    private:
        class CmbBxEncoderEvents;
        template<class T>
        class ProfileReportListViewEvents;
        template<>
        class ProfileReportListViewEvents<LameOptions>;
        template<>
        class ProfileReportListViewEvents<SndFileEncoderOptions>;
        template<class T>
        class CmbBxOptionsSetterEvents;
        template<>
        class CmbBxOptionsSetterEvents<LameOptions>;
        template<>
        class CmbBxOptionsSetterEvents<SndFileEncoderOptions>;
        template<class T>
        class SLTxtBxOptionsSetterEvents;
        template<>
        class SLTxtBxOptionsSetterEvents<LameOptions>;
        template<>
        class SLTxtBxOptionsSetterEvents<SndFileEncoderOptions>;
        class BtnOpenEvents;
        class BtnSaveEvents;
        class BtnSaveAsEvents;
        class BtnLoadDefaultEvents;

        HINSTANCE hInstance = nullptr;

        HWND hWndParent;

        bool form_loaded = false;
        bool encoder_profile_loaded;
        Encoder<void>::ID loaded_encoder_profile_id;

        std::unique_ptr<ProfileForm> *me;
        std::unique_ptr<Window> window;
        std::unique_ptr<Label> lbl_encoder_sign;
        std::unique_ptr<ComboBox> cmbbx_encoder;
        std::unique_ptr<CmbBxEncoderEvents> cmbbx_encoder_events;
        std::unique_ptr<Button> btn_load_default;
        std::unique_ptr<BtnLoadDefaultEvents> btn_load_default_events;
        std::unique_ptr<ReportListView> profile_report_list_view;
        std::unique_ptr<ProfileReportListViewEvents<LameOptions>> lame_profile_report_list_view_events;
        std::unique_ptr<ProfileReportListViewEvents<SndFileEncoderOptions>> sndfileencoder_profile_report_list_view_events;
        std::unique_ptr<ComboBox> cmbbx_options_setter;
        std::unique_ptr<CmbBxOptionsSetterEvents<LameOptions>> cmbbx_lame_options_setter_events;
        std::unique_ptr<CmbBxOptionsSetterEvents<SndFileEncoderOptions>> cmbbx_sndfileencoder_options_setter_events;
        std::unique_ptr<SingleLineTextBox> sltxtbx_options_setter;
        std::unique_ptr<SLTxtBxOptionsSetterEvents<LameOptions>> sltxtbx_lame_options_setter_events;
        std::unique_ptr<SLTxtBxOptionsSetterEvents<SndFileEncoderOptions>> sltxtbx_sndfileencoder_options_setter_events;
        std::unique_ptr<Button> btn_open;
        std::unique_ptr<BtnOpenEvents> btn_open_events;
        std::unique_ptr<Button> btn_save;
        std::unique_ptr<BtnSaveEvents> btn_save_events;
        std::unique_ptr<Button> btn_save_as;
        std::unique_ptr<BtnSaveAsEvents> btn_save_as_events;

        void OnCreate(HWND hWnd);

    public:
        ProfileForm(const ProfileForm &) = delete;
        ProfileForm & operator=(const ProfileForm &) = delete;

        ProfileForm(HINSTANCE hInstance, HWND hWndParent, std::unique_ptr<ProfileForm> &me);

        virtual LRESULT HandleEvent(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

        ~ProfileForm();
};

class ProfileForm::CmbBxEncoderEvents
{
    private:
        ProfileForm * const profile_form = nullptr;

    public:
        CmbBxEncoderEvents(const CmbBxEncoderEvents &) = delete;
        CmbBxEncoderEvents & operator=(const CmbBxEncoderEvents &) = delete;

        CmbBxEncoderEvents(ProfileForm * const profile_form);

        bool IsSelectedEncoder(void);
        Encoder<void>::ID GetSelectedEncoderID(void);
};

template<>
class ProfileForm::ProfileReportListViewEvents<LameOptions>
{
    private:
        ProfileForm *profile_form = nullptr;

        bool loaded = false;

        LameOptions encoder_options;

    public:
        ProfileReportListViewEvents(const ProfileReportListViewEvents &) = delete;
        ProfileReportListViewEvents & operator=(const ProfileReportListViewEvents &) = delete;

        ProfileReportListViewEvents(ProfileForm * const profile_form);

        void LoadDefaultProfile(void);

        const LameOptions & GetEncoderOptions(void);

        void SetAlgorithmQuality(LameOptions::AlgorithmQuality algorithm_quality);
        void SetMode(LameOptions::Mode mode);
        void SetReplayGainMode(LameOptions::ReplayGain replaygain_mode);
        void SetCopyright(bool copyright);
        void SetUseNaokiPsytune(bool use_naoki_psytune);
        void SetBitrateEncoding(LameOptions::BitrateEncoding bitrate_encoding);
        bool SetVbrQuality(float vbr_quality);
        void SetMinOrMaxBitrate1(LameOptions::Bitrate min_or_max_bitrate1);
        void SetMinOrMaxBitrate2(LameOptions::Bitrate min_or_max_bitrate2);

        ~ProfileReportListViewEvents(void);
};

template<>
class ProfileForm::ProfileReportListViewEvents<SndFileEncoderOptions>
{
    private:
        ProfileForm *profile_form = nullptr;

        bool loaded = false;

        SndFileEncoderOptions encoder_options;

    public:
        ProfileReportListViewEvents(const ProfileReportListViewEvents &) = delete;
        ProfileReportListViewEvents & operator=(const ProfileReportListViewEvents &) = delete;

        ProfileReportListViewEvents(ProfileForm * const profile_form);

        void LoadDefaultProfile(void);

        void SetOutputFormat(SndFileEncoderOptions::OutputFormat output_format);

        ~ProfileReportListViewEvents(void);
};

template<>
class ProfileForm::CmbBxOptionsSetterEvents<LameOptions>
{
    private:
        ProfileForm *profile_form = nullptr;

    public:
        CmbBxOptionsSetterEvents(const CmbBxOptionsSetterEvents &) = delete;
        CmbBxOptionsSetterEvents & operator=(const CmbBxOptionsSetterEvents &) = delete;

        CmbBxOptionsSetterEvents(ProfileForm * const profile_form);
};

template<>
class ProfileForm::CmbBxOptionsSetterEvents<SndFileEncoderOptions>
{
    private:
        ProfileForm *profile_form = nullptr;

    public:
        CmbBxOptionsSetterEvents(const CmbBxOptionsSetterEvents &) = delete;
        CmbBxOptionsSetterEvents & operator=(const CmbBxOptionsSetterEvents &) = delete;

        CmbBxOptionsSetterEvents(ProfileForm * const profile_form);
};

template<>
class ProfileForm::SLTxtBxOptionsSetterEvents<LameOptions>
{
    private:
        ProfileForm *profile_form = nullptr;

    public:
        SLTxtBxOptionsSetterEvents(const SLTxtBxOptionsSetterEvents &) = delete;
        SLTxtBxOptionsSetterEvents & operator=(const SLTxtBxOptionsSetterEvents &) = delete;

        SLTxtBxOptionsSetterEvents(ProfileForm * const profile_form);
};

template<>
class ProfileForm::SLTxtBxOptionsSetterEvents<SndFileEncoderOptions>
{
    private:
        ProfileForm *profile_form = nullptr;

    public:
        SLTxtBxOptionsSetterEvents(const SLTxtBxOptionsSetterEvents &) = delete;
        SLTxtBxOptionsSetterEvents & operator=(const SLTxtBxOptionsSetterEvents &) = delete;

        SLTxtBxOptionsSetterEvents(ProfileForm * const profile_form);
};

class ProfileForm::BtnOpenEvents
{
    friend class ProfileForm;

    class OpenFileDialogEvents;

    private:
        ProfileForm * const profile_form = nullptr;

        void OnClick(HWND hWnd);

    public:
        BtnOpenEvents(const BtnOpenEvents &) = delete;
        BtnOpenEvents & operator=(const BtnOpenEvents &) = delete;

        BtnOpenEvents(ProfileForm * const profile_form) : profile_form(profile_form) {}
};

class ProfileForm::BtnOpenEvents::OpenFileDialogEvents : public FileDialogEvents
{
    public:
        OpenFileDialogEvents() = default;
        OpenFileDialogEvents(const BtnSaveEvents &) = delete;
        OpenFileDialogEvents & operator=(const BtnSaveEvents &) = delete;
};

class ProfileForm::BtnSaveEvents
{
    friend class ProfileForm;

    private:
        ProfileForm * const profile_form = nullptr;

        void OnClick(HWND hWnd);

    public:
        BtnSaveEvents(const BtnSaveEvents &) = delete;
        BtnSaveEvents & operator=(const BtnSaveEvents &) = delete;

        BtnSaveEvents(ProfileForm * const profile_form) : profile_form(profile_form) {}
};

class ProfileForm::BtnSaveAsEvents
{
    friend class ProfileForm;

    private:
        ProfileForm * const profile_form = nullptr;

        void OnClick(HWND hWnd);

    public:
        BtnSaveAsEvents(const BtnSaveAsEvents &) = delete;
        BtnSaveAsEvents & operator=(const BtnSaveAsEvents &) = delete;

        BtnSaveAsEvents(ProfileForm * const profile_form) : profile_form(profile_form) {}
};

class ProfileForm::BtnLoadDefaultEvents
{
    friend class ProfileForm;

    private:
        ProfileForm * const profile_form = nullptr;

        void OnClick(void);

    public:
        BtnLoadDefaultEvents(const BtnLoadDefaultEvents &) = delete;
        BtnLoadDefaultEvents & operator=(const BtnLoadDefaultEvents &) = delete;

        BtnLoadDefaultEvents(ProfileForm * const profile_form) : profile_form(profile_form) {}
};

#endif
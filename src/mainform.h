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

#ifndef GUI_MAINFORM_H
#define GUI_MAINFORM_H

class MainFormEvents;
class MainFormPanel1Events;
class MainFormPanel2Events;

class MainForm
{
    friend class MainFormEvents;
    friend class MainFormPanel1Events;
    friend class MainFormPanel2Events;

    private:
        HINSTANCE hInstance = nullptr;
        const wchar_t * const class_name = L"RustyCoder";

        std::unique_ptr<Window> window;
        std::unique_ptr<MenuBar> menu;
        std::unique_ptr<VerticalSplitWindow> vertical_split_window1;
        std::unique_ptr<Panel> panel1;
        std::unique_ptr<Panel> panel2;
        std::unique_ptr<ReportListView> report_list_view1;

        std::unique_ptr<MainFormEvents> events;
        std::unique_ptr<MainFormPanel1Events> panel1_events;
        std::unique_ptr<MainFormPanel2Events> panel2_events;

    public:
        MainForm(const MainForm &) = delete;
        MainForm & operator=(const MainForm &) = delete;

        MainForm(HINSTANCE hThisInstance, int nCmdShow);
};

class MainFormEvents : public EventHandlerInterface
{
    private:
        bool form_loaded = false;

        MainForm * const mf;
        void OnLoad(HWND hWnd);
        void OnSize(HWND hWnd);
        void OnGetMinMaxInfo(MINMAXINFO * const min_max_info);
        void Menu_File_AddFiles_OnClick(HWND hWnd);
        void Menu_File_Exit_OnClick(void);
        
    public:
        MainFormEvents(const MainFormEvents &) = delete;
        MainFormEvents & operator=(const MainFormEvents &) = delete;

        MainFormEvents(MainForm * const mf);
        
        virtual LRESULT HandleEvent(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

class MainFormPanel1Events : public EventHandlerInterface
{
    private:
        bool form_loaded = false;

        MainForm * const mf;
        void OnCreate(HWND hWnd);
        void OnSize(HWND hWnd);

    public:
        MainFormPanel1Events(const MainFormPanel1Events &) = delete;
        MainFormPanel1Events & operator=(const MainFormPanel1Events &) = delete;

        MainFormPanel1Events(MainForm * const mf);

        virtual LRESULT HandleEvent(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

class MainFormPanel2Events : public EventHandlerInterface
{
    private:
        MainForm * const mf;

    public:
        MainFormPanel2Events(const MainFormPanel2Events &) = delete;
        MainFormPanel2Events & operator=(const MainFormPanel2Events &) = delete;

        MainFormPanel2Events(MainForm * const mf);

        virtual LRESULT HandleEvent(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

#endif
#ifndef MAIN_EVENT_H
#define MAIN_EVENT_H

#define WIN32_LEAN_AND_MEAN

#include <sstream>
#include <thread>

#include "listview.h"
#include "filedialog.h"
#include "res/resource.h"

class MainEvent
{
    private:
        static void start_stream_redirection(HWND hwnd);
        static bool create_child_process(HANDLE _standard_output_write);
        static void read_from_pipe(HWND hwnd, HANDLE _standard_output_read);
        static inline void textbox1_append_text(const HWND textbox, char _output_buffer[], unsigned long _text_length);
        static std::wstring get_file_name(const std::wstring& file_path);
        static long long get_file_size(const std::wstring& file_path);
        static std::wstring get_file_format(const std::wstring& file_path);
        static std::wstring get_file_directory(const std::wstring& file_path);
        static std::wstring long_long_to_wstr(long long number);
        static void show_error_msg(void);
    public:
        enum OS
        {
            OS_NOT_SUPPORTED,
            WIN_XP,
            WIN_VISTA_OR_LATER
        };

        static const unsigned int MAIN_CLIENT_WIDTH = 750;
        static const unsigned int MAIN_CLIENT_HEIGHT = 535;
        static OS supported_os;

        static OS main_os_is_supported(void);
        static void main_on_create(HWND hwnd);
        static void main_on_getminmaxinfo(LPARAM lParam);
        static void main_on_size_sizing(HWND hwnd);
        static LRESULT main_on_ctlcolorstatic(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
        static void button1_on_click(HWND hwnd);
        static void button2_on_click(HWND hwnd);
        static void menu_exit_on_click(HWND hwnd);
        static void menu_file_add_on_click(HWND hwnd);
};

#endif

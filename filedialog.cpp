#include "filedialog.h"

FileDialog::FileDialog(const HWND hwnd) : file_paths()
{
    if(MainEvent::supported_os != MainEvent::OS_NOT_SUPPORTED)
    {
        const unsigned int buffer_size = MAX_PATH * 1000u;
        unsigned long error = 0ul;
        bool can_open = false;
        wchar_t *buffer = new wchar_t[buffer_size];
        OPENFILENAME open_file;

        *buffer = {L'\0'};
        memset(&open_file, 0, sizeof(OPENFILENAME));
        open_file.lStructSize = sizeof(OPENFILENAME);
        open_file.hwndOwner = hwnd;
        open_file.lpstrFilter = L"All supported file types (*.mp3;*.mp4;*.aac;*.mkv;*avs)\0*.mp3;*.mp4;*.aac;*.mkv;*avs\0Audio Files (*.mp3;*.mp4;*.aac)\0*.mp3;*.mp4;*.aac\0";
        open_file.lpstrFile = buffer;
        open_file.nMaxFile = buffer_size;
        open_file.lpstrTitle = L"Add files";
        open_file.Flags = OFN_ALLOWMULTISELECT | OFN_DONTADDTORECENT | OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
        open_file.nFileOffset = 0;

        can_open = GetOpenFileName(&open_file);
        error = CommDlgExtendedError();

        switch(error)
        {
            case FNERR_BUFFERTOOSMALL:
            {
                MessageBox(nullptr, L"Selected file length too long", L"Error", MB_OK);
                break;
            }
            case FNERR_INVALIDFILENAME:
            {
                MessageBox(nullptr, L"Invalid filename", L"Error", MB_OK);
                break;
            }
            case FNERR_SUBCLASSFAILURE:
            case CDERR_DIALOGFAILURE:
            case CDERR_FINDRESFAILURE:
            case CDERR_INITIALIZATION:
            case CDERR_LOADRESFAILURE:
            case CDERR_LOADSTRFAILURE:
            case CDERR_LOCKRESFAILURE:
            case CDERR_MEMALLOCFAILURE:
            case CDERR_MEMLOCKFAILURE:
            case CDERR_NOHINSTANCE:
            case CDERR_NOHOOK:
            case CDERR_NOTEMPLATE:
            case CDERR_STRUCTSIZE:
            {
                MessageBox(nullptr, L"Failed to create open dialog", L"Error", MB_OK);
                break;
            }
            default:
            {
                if(can_open)
                {
                    unsigned int i1;
                    int i2;
                    int flag = 0;
                    wchar_t file_path[MAX_PATH];
                    wchar_t file_path_copy[MAX_PATH];

                    for(i1 = 0u, i2 = 0; i1 < buffer_size; ++i1, ++i2)
                    {
                        file_path[i2] = buffer[i1];
                        if(buffer[i1] == L'\0' && buffer[i1 + 1u] == L'\0')
                        {
                            if(flag == 0)
                                set_vector_element(file_path);
                            else
                                set_vector_element(file_path_copy, file_path);
                            break;
                        }
                        else if(buffer[i1] == L'\0')
                        {
                            if(flag == 0)
                            {
                                wmemcpy(file_path_copy, file_path, MAX_PATH);
                                ++flag;
                            }
                            else
                                set_vector_element(file_path_copy, file_path);
                            i2 = -1;
                        }
                    }
                }
            }
        }
        delete[] buffer;
    }
}

std::vector<std::wstring>& FileDialog::get_file_paths(void)
{
    return file_paths;
}

void FileDialog::print_all_paths(void)
{
    const int vec_size = file_paths.size();
    for(int i = 0; i < vec_size; ++i)
        MessageBox(nullptr, file_paths[i].c_str(), L"Testing", MB_OK);
}

void FileDialog::set_vector_element(const wchar_t fullpath[])
{
    const std::wstring temp(fullpath);
    file_paths.push_back(temp);
}

void FileDialog::set_vector_element(const wchar_t path[], const wchar_t filename[])
{
    const std::wstring temp1(path);
    const std::wstring temp2(filename);
    file_paths.push_back(temp1 + L'\\' + temp2);
}

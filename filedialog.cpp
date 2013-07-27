#include "filedialog.h"

FileDialog::FileDialog(HWND hwnd) : file_paths()
{
    if(MainEvent::supported_os != MainEvent::OS_NOT_SUPPORTED)
    {
        unsigned int buffer_size = MAX_PATH * 1000;
        unsigned long error = 0;
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
                    unsigned int index1;
                    short index2;
                    int flag = 0;
                    wchar_t file_path[MAX_PATH];
                    wchar_t file_path_copy[MAX_PATH];

                    for(index1 = 0, index2 = 0; index1 < buffer_size; ++index1, ++index2)
                    {
                        file_path[index2] = buffer[index1];
                        if(buffer[index1] == L'\0' && buffer[index1 + 1] == L'\0')
                        {
                            if(flag == 0)
                                set_vector_element(file_path);
                            else
                                set_vector_element(file_path_copy, file_path);
                            break;
                        }
                        else if(buffer[index1] == L'\0')
                        {
                            if(flag == 0)
                            {
                                wmemcpy(file_path_copy, file_path, MAX_PATH);
                                ++flag;
                            }
                            else
                                set_vector_element(file_path_copy, file_path);
                            index2 = -1;
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
    unsigned int size1 = file_paths.size();
    for(unsigned int index = 0; index < size1; ++index)
        MessageBox(nullptr, file_paths[index].c_str(), L"Testing", MB_OK);
}

void FileDialog::set_vector_element(const wchar_t* const fullpath)
{
    std::wstring temp(fullpath);
    file_paths.push_back(temp);
}

void FileDialog::set_vector_element(const wchar_t* const path, const wchar_t* const filename)
{
    std::wstring temp1(path);
    std::wstring temp2(filename);
    file_paths.push_back(temp1 + L'\\' + temp2);
}

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

#ifndef CONTROLS_FILE_DIALOG_EVENTS_H
#define CONTROLS_FILE_DIALOG_EVENTS_H

class FileDialogEvents : public IFileDialogEvents, public IFileDialogControlEvents
{
    private:
        volatile LONG reference_count = 1l;

    protected:
        void *data = nullptr;

        FileDialogEvents() = default;

        virtual IFACEMETHODIMP OnFileOk(IFileDialog *pfd);
        virtual IFACEMETHODIMP OnFolderChange(IFileDialog *pfd);
        virtual IFACEMETHODIMP OnFolderChanging(IFileDialog *pfd, IShellItem *psiFolder);
        virtual IFACEMETHODIMP OnOverwrite(IFileDialog *pfd, IShellItem *psi, FDE_OVERWRITE_RESPONSE *pResponse);
        virtual IFACEMETHODIMP OnSelectionChange(IFileDialog *pfd);
        virtual IFACEMETHODIMP OnShareViolation(IFileDialog *pfd, IShellItem *psi, FDE_SHAREVIOLATION_RESPONSE *pResponse);
        virtual IFACEMETHODIMP OnTypeChange(IFileDialog *pfd);

        virtual IFACEMETHODIMP OnButtonClicked(IFileDialogCustomize *pfdc, DWORD dwIDCtl);
        virtual IFACEMETHODIMP OnCheckButtonToggled(IFileDialogCustomize *pfdc, DWORD dwIDCtl, BOOL bChecked);
        virtual IFACEMETHODIMP OnControlActivating(IFileDialogCustomize *pfdc, DWORD dwIDCtl);
        virtual IFACEMETHODIMP OnItemSelected(IFileDialogCustomize *pfdc, DWORD dwIDCtl, DWORD dwIDItem);

    public:
        FileDialogEvents(const FileDialogEvents &) = delete;
        FileDialogEvents & operator=(const FileDialogEvents &) = delete;

        void SetData(void *data);

        virtual IFACEMETHODIMP_(ULONG) AddRef(void);
        virtual IFACEMETHODIMP QueryInterface(REFIID riid, void** ppv);
        virtual IFACEMETHODIMP_(ULONG) Release(void);

        ~FileDialogEvents();
};

#endif
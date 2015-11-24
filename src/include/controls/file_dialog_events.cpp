/*
RustyCoder

Copyright (C) 2012-2015 Chak Wai Yuan

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
#include "file_dialog_events.h"

void rusty::controls::FileDialogEvents::SetData(void *data)
{
    this->data = data;
}

IFACEMETHODIMP rusty::controls::FileDialogEvents::QueryInterface(REFIID riid, void** ppv)
{
    #ifdef _MSC_VER
    #pragma warning(push)
    #pragma warning(disable: 4838)
    #endif
    static const QITAB qit[] = {QITABENT(FileDialogEvents, IFileDialogEvents), QITABENT(FileDialogEvents, IFileDialogControlEvents), {0}};
    #ifdef _MSC_VER
    #pragma warning(pop)
    #endif
    return QISearch(this, qit, riid, ppv);
}

IFACEMETHODIMP_(ULONG) rusty::controls::FileDialogEvents::AddRef()
{
    return InterlockedIncrement(&reference_count);
}

IFACEMETHODIMP_(ULONG) rusty::controls::FileDialogEvents::Release()
{
    return InterlockedDecrement(&reference_count);
}

IFACEMETHODIMP rusty::controls::FileDialogEvents::OnFileOk(IFileDialog * /* pfd */)
{
    return E_NOTIMPL;
}

IFACEMETHODIMP rusty::controls::FileDialogEvents::OnFolderChange(IFileDialog * /* pfd */)
{
    return E_NOTIMPL;
}

IFACEMETHODIMP rusty::controls::FileDialogEvents::OnFolderChanging(IFileDialog * /* pfd */, IShellItem * /* psiFolder */)
{
    return E_NOTIMPL;
}

IFACEMETHODIMP rusty::controls::FileDialogEvents::OnOverwrite(IFileDialog * /* pfd */, IShellItem * /* psi */, FDE_OVERWRITE_RESPONSE * /* pResponse */)
{
    return E_NOTIMPL;
}

IFACEMETHODIMP rusty::controls::FileDialogEvents::OnSelectionChange(IFileDialog * /* pfd */)
{
    return E_NOTIMPL;
}

IFACEMETHODIMP rusty::controls::FileDialogEvents::OnShareViolation(IFileDialog * /* pfd */, IShellItem * /* psi */, FDE_SHAREVIOLATION_RESPONSE * /* pResponse */)
{
    return E_NOTIMPL;
}

IFACEMETHODIMP rusty::controls::FileDialogEvents::OnTypeChange(IFileDialog * /* pfd */)
{
    return E_NOTIMPL;
}

IFACEMETHODIMP rusty::controls::FileDialogEvents::OnButtonClicked(IFileDialogCustomize * /* pfdc */, DWORD /* dwIDCtl */)
{
    return E_NOTIMPL;
}

IFACEMETHODIMP rusty::controls::FileDialogEvents::OnCheckButtonToggled(IFileDialogCustomize * /* pfdc */, DWORD /* dwIDCtl */, BOOL /* bChecked */)
{
    return E_NOTIMPL;
}

IFACEMETHODIMP rusty::controls::FileDialogEvents::OnControlActivating(IFileDialogCustomize * /* pfdc */, DWORD /* dwIDCtl */)
{
    return E_NOTIMPL;
}

IFACEMETHODIMP rusty::controls::FileDialogEvents::OnItemSelected(IFileDialogCustomize * /* pfdc */, DWORD /* dwIDCtl */, DWORD /* dwIDItem */)
{
    return E_NOTIMPL;
}

rusty::controls::FileDialogEvents::~FileDialogEvents()
{
    assert(reference_count == 0);
}
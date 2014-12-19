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

#ifndef CONTROLS_COMBO_BOX_H
#define CONTROLS_COMBO_BOX_H

class ComboBox : public Window
{
    public:
        enum Type
        {
            SIMPLE = CBS_SIMPLE,
            DROP_DOWN = CBS_DROPDOWN,
            DROP_DOWN_LIST = CBS_DROPDOWNLIST
        };

        ComboBox(const ComboBox &) = delete;
        ComboBox & operator=(const ComboBox &) = delete;

        ComboBox(HINSTANCE hInstance, HWND hWndParent, int hMenu, int x, int y, int nWidth, Type combo_box_type, unsigned long dwExStyle = WS_EX_LEFT, unsigned long dwStyle = WS_VSCROLL | WS_CLIPSIBLINGS | WS_CHILD | WS_VISIBLE | CBS_AUTOHSCROLL | CBS_HASSTRINGS);

        unsigned int GetSelectedItemIndex(void);
        LPARAM GetItemData(unsigned int index);
        unsigned int GetItemCount(void);
        std::wstring GetItemText(unsigned int index);
        bool HasSelectedItems(void);
        bool HasItemData(unsigned int index);
        void SelectItem(unsigned int index);
        void SelectItem(int start_index, const wchar_t *text);
        void AppendItem(const wchar_t *text);
        void AppendItem(const wchar_t *text, LPARAM data);
        void SetItemData(unsigned int index, LPARAM data);
        void InsertItem(unsigned int index, const wchar_t *text);
        void InsertItem(unsigned int index, const wchar_t *text, LPARAM data);
        void RemoveItem(unsigned int index);
        void RemoveAllItems(void);

        virtual ~ComboBox(void) {}
};

#endif
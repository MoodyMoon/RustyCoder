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

#ifndef CODECS_ENCODER_OPTIONS_H
#define CODECS_ENCODER_OPTIONS_H

class EncoderOptions
{
    protected:
        EncoderOptions(void) = default;

    public:
        static const char *bool_true_text;
        static const char *bool_false_text;

        virtual unsigned int GetOptionsCount(void) const = 0;
        virtual std::string GetOptionsInString(unsigned int option_index) const = 0;
        virtual void GetCurrentValueForOptionInString(unsigned int option_index, std::string &option_value) const = 0;
        virtual void GetCurrentValueForOptionInString(std::string &option_text, std::string &option_value) const = 0;

        virtual unsigned int GetSelectionCountForOption(unsigned int option_index) const = 0;
        virtual std::string GetSelectionForOptionInString(unsigned int option_index, unsigned int selection_index) const = 0;

        virtual void SetValueForOption(unsigned int option_index, std::string &value) = 0;
        virtual void SetValueForOption(std::string &option_text, std::string &value) = 0;

        virtual ~EncoderOptions(void) {};
};

#endif
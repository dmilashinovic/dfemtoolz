/*
    This file is part of dfemtoolz software package.
*
    dfemtoolz software package is free software: 
*   you can redistribute it and/or modify it under the terms of the 
    GNU General Public License as published by the Free Software Foundation, 
*   either version 3 of the License, or (at your option) any later version.

*   dfemtoolz software package is distributed in the hope that 
    it will be useful, but WITHOUT ANY WARRANTY; without even the 
*   implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
    See the GNU General Public License for more details.
*
    You should have received a copy of the GNU General Public License
*   along with dfemtoolz software package.  
    If not, see <http://www.gnu.org/licenses/>.
*
    For any additional info contact author of this software:
*   
    Danko Milasinovic
*   dmilashinovic@gmail.com
    dmilashinovic@kg.ac.rs    
*/

#include "dReading.h"

namespace reading
{
    bool check_if_block_reading_is_ok(char line_read[])
    {
        int ID;
        sscanf(line_read, "%d", &ID);
        if ( ID != 1)
        {
            cout << " problem with file constants ! " << endl;
            cout << " this should be first node/element line read from file: " <<
            endl << line_read << endl << endl;
            press_any_key_2_continue();
            return false;
        }
        return true;
    }

    bool check_if_file_is_not_open(ifstream & file, string fileName)
    {
        if(!file.is_open())
        {
            Error * error_found = Error::errorExists();
            string error_text = " file " + fileName + " not found!";
            error_found->print_error(error_text);
            return 1;
        }
        else
            cout << endl << " using " << fileName << endl;
        return 0;
    }

    bool check_if_file_is_not_open_wo_using_cout(ifstream & file, string fileName)
    {
        if(!file.is_open())
        {
            Error * error_found = Error::errorExists();
            string error_text = " file " + fileName + " not found!";
            error_found->print_error(error_text);
            return 1;
        }
        return 0;
    }

    bool go_to_line_that_contains_this_string(string string_in_line, ifstream & file)
    {
        string line_str;
        char line[constants::no_of_line_characters];
        for (;;)
        {
            file.getline(line, constants::no_of_line_characters);
            line_str = line;
            if (strstr(line_str.c_str(), string_in_line.c_str()))
                return true;
        }
        return false;
    }

    bool get_line_that_contains_this_string_and_close_the_file(char the_line[], string string_in_line, string filename)
    {
        ifstream ifile;
        ifile.open(filename.c_str());

        if (reading::check_if_file_is_not_open_wo_using_cout(ifile, filename.c_str()))
            return false;

        string line_str;
        for (;!ifile.eof();)
        {
            ifile.getline(the_line, constants::no_of_line_characters);
            line_str = the_line;
            if (strstr(line_str.c_str(), string_in_line.c_str()))
                return true;
        }
        return false;
    }
}

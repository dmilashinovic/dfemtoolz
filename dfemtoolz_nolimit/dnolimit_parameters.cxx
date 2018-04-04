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

#include "dnolimit_parameters.h"


nolimit_Parameters::nolimit_Parameters()
{
    m_sPath_and_FileName = "input/parameters.cfg";

    calculate_surface = 1;
    print_pos_nodes = 1;
    print_pos_elements = 0;
    scale_facX = 1.0;
    scale_facY = 1.0;
    scale_facZ = 1.0;
    clear_previous_boundary = 1;
    chek_all_elements = 0;
    calculate_volume_of_the_model = 0;
    dat_or_sli_input = constants::sli;
}

nolimit_Parameters * nolimit_Parameters::m_pnolimit_ParametersSingleton = 0;
nolimit_Parameters * nolimit_Parameters::create_nolimit_Parameters()
{
    if (m_pnolimit_ParametersSingleton == 0)
        m_pnolimit_ParametersSingleton = new nolimit_Parameters();
    return m_pnolimit_ParametersSingleton;
}

nolimit_Parameters::~nolimit_Parameters()
{}

bool nolimit_Parameters::read_file()
{
    Info * info = Info::createInfo();
    info->print_info_message("reading parameters... ");

    char line[constants::no_of_line_characters];

    int tmp;

    if(!reading::get_line_that_contains_this_string_and_close_the_file(line, "calculate_surface", m_sPath_and_FileName))
        return false;
    sscanf(line, "%*s%d", &tmp);
    calculate_surface = (bool) tmp;

    if(!reading::get_line_that_contains_this_string_and_close_the_file(line, "posNodes", m_sPath_and_FileName))
        return false;
    sscanf(line, "%*s%d", &tmp);
    print_pos_nodes = (bool) tmp;

    if(!reading::get_line_that_contains_this_string_and_close_the_file(line, "posElements", m_sPath_and_FileName))
        return false;
    sscanf(line, "%*s%d", &tmp);
    print_pos_elements = (bool) tmp;

    if(!reading::get_line_that_contains_this_string_and_close_the_file(line, "scaleFacX", m_sPath_and_FileName))
        return false;
    sscanf(line, "%*s%d", &tmp);
    scale_facX = (bool) tmp;

    if(!reading::get_line_that_contains_this_string_and_close_the_file(line, "scaleFacY", m_sPath_and_FileName))
        return false;
    sscanf(line, "%*s%d", &tmp);
    scale_facY = (bool) tmp;

    if(!reading::get_line_that_contains_this_string_and_close_the_file(line, "scaleFacZ", m_sPath_and_FileName))
        return false;
    sscanf(line, "%*s%d", &tmp);
    scale_facZ = (bool) tmp;

    if(!reading::get_line_that_contains_this_string_and_close_the_file(line, "clearPreviousBoundary", m_sPath_and_FileName))
        return false;
    sscanf(line, "%*s%d", &tmp);
    clear_previous_boundary = (bool) tmp;

    if(!reading::get_line_that_contains_this_string_and_close_the_file(line, "chekAllElements", m_sPath_and_FileName))
        return false;
    sscanf(line, "%*s%d", &tmp);
    chek_all_elements = (bool) tmp;

    if(!reading::get_line_that_contains_this_string_and_close_the_file(line, "calculateVolumeOfTheModel", m_sPath_and_FileName))
        return false;
    sscanf(line, "%*s%d", &tmp);
    calculate_volume_of_the_model = (bool) tmp;

    reading::get_line_that_contains_this_string_and_close_the_file(line, "dat_or_sli_input", m_sPath_and_FileName);
    sscanf(line, "%*s%d", &tmp);
    if (tmp == 1)
        dat_or_sli_input = constants::dat;
    if (tmp != 1)
        dat_or_sli_input = constants::sli;

    return true;
}

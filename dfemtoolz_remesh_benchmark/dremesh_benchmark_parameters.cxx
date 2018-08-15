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

#include "dremesh_benchmark_parameters.h"


dremesh_benchmark_Parameters::dremesh_benchmark_Parameters()
{
    m_sPath_and_FileName = "input/parameters.cfg";

    submodule = 1;
    inheritBoundary = 0;
    print_pos_nodes = 1;
    print_pos_elements = 0;

    chekAllBrickElements = true;
    calculateVolumeOfTheModel = true;
}

dremesh_benchmark_Parameters * dremesh_benchmark_Parameters::m_pdremesh_benchmark_ParametersSingleton = 0;
dremesh_benchmark_Parameters * dremesh_benchmark_Parameters::create_dremesh_benchmark_Parameters()
{
    if (m_pdremesh_benchmark_ParametersSingleton == 0)
        m_pdremesh_benchmark_ParametersSingleton = new dremesh_benchmark_Parameters();
    return m_pdremesh_benchmark_ParametersSingleton;
}

dremesh_benchmark_Parameters::~dremesh_benchmark_Parameters()
{}

bool dremesh_benchmark_Parameters::read_file
()
{
    Info * info = Info::createInfo();
    info->print_info_message("reading parameters... ");

    char line[constants::no_of_line_characters];

    int tmp;

    if(!reading::get_line_that_contains_this_string_and_close_the_file(line, "submodule", m_sPath_and_FileName))
        return false;
    sscanf(line, "%*s%d", &tmp);
    submodule = tmp;

    if(!reading::get_line_that_contains_this_string_and_close_the_file(line, "inheritBoundary", m_sPath_and_FileName))
        return false;
    sscanf(line, "%*s%d", &tmp);
    inheritBoundary = (bool) tmp;

    if(!reading::get_line_that_contains_this_string_and_close_the_file(line, "posNodes", m_sPath_and_FileName))
        return false;
    sscanf(line, "%*s%d", &tmp);
    print_pos_nodes = (bool) tmp;

    if(!reading::get_line_that_contains_this_string_and_close_the_file(line, "posElements", m_sPath_and_FileName))
        return false;
    sscanf(line, "%*s%d", &tmp);
    print_pos_elements = (bool) tmp;

    if(!reading::get_line_that_contains_this_string_and_close_the_file(line, "chekAllBrickElements", m_sPath_and_FileName))
        return false;
    sscanf(line, "%*s%d", &tmp);
    chekAllBrickElements = (bool) tmp;

    if(!reading::get_line_that_contains_this_string_and_close_the_file(line, "calculateVolumeOfTheModel", m_sPath_and_FileName))
        return false;
    sscanf(line, "%*s%d", &tmp);
    calculateVolumeOfTheModel = (bool) tmp;

    return true;
}

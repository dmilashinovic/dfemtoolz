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

#include "dremesh_parameters.h"


dremesh_Parameters::dremesh_Parameters()
{
    m_sPath_and_FileName = "input/dremesh_parameters.cfg";

    submodule = 1;
    inheritBoundary = 0;
    print_pos_nodes = 1;
    print_pos_elements = 0;
    print_vtk_elements = 0;

    material_ID = 1;

    chekAllBrickElements = true;
    calculateVolumeOfTheModel = true;
}

dremesh_Parameters * dremesh_Parameters::m_pdremesh_ParametersSingleton = 0;
dremesh_Parameters * dremesh_Parameters::create_dremesh_Parameters()
{
    if (m_pdremesh_ParametersSingleton == 0)
        m_pdremesh_ParametersSingleton = new dremesh_Parameters();
    return m_pdremesh_ParametersSingleton;
}

dremesh_Parameters::~dremesh_Parameters()
{}

bool dremesh_Parameters::read_file()
{
    Info * info = Info::createInfo();
    info->print_info_message("reading parameters... ");

    char line[constants::no_of_line_characters];

    int tmp;

    if(!reading::get_line_that_contains_this_string_and_close_the_file(line, "submodule", m_sPath_and_FileName))
        return false;
    sscanf(line, "%*s%d", &tmp);
    submodule = tmp;

    if(!reading::get_line_that_contains_this_string_and_close_the_file(line, "material_ID", m_sPath_and_FileName))
        return false;
    sscanf(line, "%*s%d", &tmp);
    material_ID = tmp;

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

    if(!reading::get_line_that_contains_this_string_and_close_the_file(line, "vtkElements", m_sPath_and_FileName))
        return false;
    sscanf(line, "%*s%d", &tmp);
    print_vtk_elements = (bool) tmp;

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

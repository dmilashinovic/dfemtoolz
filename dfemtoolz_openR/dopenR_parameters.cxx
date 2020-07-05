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

#include "dopenR_parameters.h"

void openR_Parameters::set_params_filename(string filename)
{
    m_sPath_and_FileName = filename;
}

openR_Parameters::openR_Parameters()
{
    m_sPath_and_FileName = "input/dopenR_parameters.cfg";

    print_pos_nodes = 1;
    print_pos_elements = 0;
    print_pos_init_velocity = 0;
    print_pos_inlet_or_outlet = 0;
    print_pos_surface = 1;

    print_vtk_elements = 0;
    print_vtk_inlet_or_outlet = 0;
    print_vtk_surface = 0;

    plane_defined_with_nodes = 1;
    plane_nodeA = 1;
    plane_nodeB = 2;
    plane_nodeC = 3;
    Xplane_of_sym_for_outlet_or_inlet = 0;
    Xsym_defined_at = 0.;
    Yplane_of_sym_for_outlet_or_inlet = 0;
    Ysym_defined_at = 0.;
    Zplane_of_sym_for_outlet_or_inlet = 0;
    Zsym_defined_at = 0.;
    defined_plane = 0;
    plane_defined_at = 5.0;
    plane_coord_ID = 2;
    numzad_time_function = 1;
    numst_time_function = 0;
    velocity_invert0R = 1;
    parabolic_input = 1;
    use_all_inlet_or_outlet_faces = 0;
    use_all_inlet_or_outlet_nodes = 0;
    print_numzad_nodes_and_inlet_or_outlet_facets = 0;
    print_prescribed_pressure = 0;
    clear_and_set_this_boundary_to_nodes = 0;
    add_this_boundary_to_all_nodes_outlet_or_inlet_faces = 0;
    near_node_tol = 0.05;
    same_node_tol = 0.001;
    scale_facX = 1.0;
    scale_facY = 1.0;
    scale_facZ = 1.0;
    check_distance = 0;
    TOLdistance = 5.0;
    refNode = 1;
    dat_or_sli_input = constants::sli;
    stl_or_fal_input = constants::stl;
    materialID_of_outlet_or_inlet = 1;
}

openR_Parameters * openR_Parameters::m_popenR_ParametersSingleton = 0;
openR_Parameters * openR_Parameters::create_openR_Parameters()
{
    if (m_popenR_ParametersSingleton == 0)
        m_popenR_ParametersSingleton = new openR_Parameters();
    return m_popenR_ParametersSingleton;
}

openR_Parameters::~openR_Parameters()
{}

bool openR_Parameters::read_file()
{
    Info * info = Info::createInfo();
    info->print_info_message("reading parameters... ");

    char line[constants::no_of_line_characters];

    int tmp;
    double tmp_d;

    reading::get_line_that_contains_this_string_and_close_the_file(line, "posNodes", m_sPath_and_FileName);
    sscanf(line, "%*s%d", &tmp);
    print_pos_nodes = (bool) tmp;

    reading::get_line_that_contains_this_string_and_close_the_file(line, "posElements", m_sPath_and_FileName);
    sscanf(line, "%*s%d", &tmp);
    print_pos_elements = (bool) tmp;

    reading::get_line_that_contains_this_string_and_close_the_file(line, "vtkElements", m_sPath_and_FileName);
    sscanf(line, "%*s%d", &tmp);
    print_vtk_elements = (bool) tmp;

    reading::get_line_that_contains_this_string_and_close_the_file(line, "posInitVel", m_sPath_and_FileName);
    sscanf(line, "%*s%d", &tmp);
    print_pos_init_velocity = (bool) tmp;

    reading::get_line_that_contains_this_string_and_close_the_file(line, "posInletOrOutlet", m_sPath_and_FileName);
    sscanf(line, "%*s%d", &tmp);
    print_pos_inlet_or_outlet = (bool) tmp;

    reading::get_line_that_contains_this_string_and_close_the_file(line, "vtkInletOrOutlet", m_sPath_and_FileName);
    sscanf(line, "%*s%d", &tmp);
    print_vtk_inlet_or_outlet = (bool) tmp;

    reading::get_line_that_contains_this_string_and_close_the_file(line, "posSurface", m_sPath_and_FileName);
    sscanf(line, "%*s%d", &tmp);
    print_pos_surface = (bool) tmp;

    reading::get_line_that_contains_this_string_and_close_the_file(line, "vtkSurface", m_sPath_and_FileName);
    sscanf(line, "%*s%d", &tmp);
    print_vtk_surface = (bool) tmp;

    reading::get_line_that_contains_this_string_and_close_the_file(line, "plane_defined_with_nodes", m_sPath_and_FileName);
    sscanf(line, "%*s%d", &tmp);
    plane_defined_with_nodes = (bool) tmp;

    reading::get_line_that_contains_this_string_and_close_the_file(line, "plane_nodeA", m_sPath_and_FileName);
    sscanf(line, "%*s%d", &tmp);
    plane_nodeA = tmp;

    reading::get_line_that_contains_this_string_and_close_the_file(line, "plane_nodeB", m_sPath_and_FileName);
    sscanf(line, "%*s%d", &tmp);
    plane_nodeB = tmp;

    reading::get_line_that_contains_this_string_and_close_the_file(line, "plane_nodeC", m_sPath_and_FileName);
    sscanf(line, "%*s%d", &tmp);
    plane_nodeC = tmp;

    reading::get_line_that_contains_this_string_and_close_the_file(line, "Xplane_of_sym_for_outlet_or_inlet", m_sPath_and_FileName);
    sscanf(line, "%*s%d", &tmp);
    Xplane_of_sym_for_outlet_or_inlet = (bool) tmp;

    reading::get_line_that_contains_this_string_and_close_the_file(line, "Xsym_defined_at", m_sPath_and_FileName);
    sscanf(line, "%*s%lf", &tmp_d);
    Xsym_defined_at = tmp_d;

    reading::get_line_that_contains_this_string_and_close_the_file(line, "Yplane_of_sym_for_outlet_or_inlet", m_sPath_and_FileName);
    sscanf(line, "%*s%d", &tmp);
    Yplane_of_sym_for_outlet_or_inlet = (bool) tmp;

    reading::get_line_that_contains_this_string_and_close_the_file(line, "Ysym_defined_at", m_sPath_and_FileName);
    sscanf(line, "%*s%lf", &tmp_d);
    Ysym_defined_at = tmp_d;

    reading::get_line_that_contains_this_string_and_close_the_file(line, "Zplane_of_sym_for_outlet_or_inlet", m_sPath_and_FileName);
    sscanf(line, "%*s%d", &tmp);
    Zplane_of_sym_for_outlet_or_inlet = (bool) tmp;

    reading::get_line_that_contains_this_string_and_close_the_file(line, "Zsym_defined_at", m_sPath_and_FileName);
    sscanf(line, "%*s%lf", &tmp_d);
    Zsym_defined_at = tmp_d;

    reading::get_line_that_contains_this_string_and_close_the_file(line, "defined_plane", m_sPath_and_FileName);
    sscanf(line, "%*s%d", &tmp);
    defined_plane = (bool) tmp;

    reading::get_line_that_contains_this_string_and_close_the_file(line, "plane_defined_at", m_sPath_and_FileName);
    sscanf(line, "%*s%lf", &tmp_d);
    plane_defined_at = tmp_d;

    reading::get_line_that_contains_this_string_and_close_the_file(line, "plane_coord_ID", m_sPath_and_FileName);
    sscanf(line, "%*s%d", &tmp);
    plane_coord_ID = tmp;

    reading::get_line_that_contains_this_string_and_close_the_file(line, "numzad_time_function", m_sPath_and_FileName);
    sscanf(line, "%*s%d", &tmp);
    numzad_time_function = tmp;

    reading::get_line_that_contains_this_string_and_close_the_file(line, "numst_time_function", m_sPath_and_FileName);
    sscanf(line, "%*s%d", &tmp);
    numst_time_function = tmp;

    reading::get_line_that_contains_this_string_and_close_the_file(line, "velocity_invert0R", m_sPath_and_FileName);
    sscanf(line, "%*s%d", &tmp);
    velocity_invert0R = (bool) tmp;

    reading::get_line_that_contains_this_string_and_close_the_file(line, "parabolic_input", m_sPath_and_FileName);
    sscanf(line, "%*s%d", &tmp);
    parabolic_input = (bool) tmp;

    reading::get_line_that_contains_this_string_and_close_the_file(line, "use_all_inlet_or_outlet_faces", m_sPath_and_FileName);
    sscanf(line, "%*s%d", &tmp);
    use_all_inlet_or_outlet_faces = (bool) tmp;

    reading::get_line_that_contains_this_string_and_close_the_file(line, "use_all_inlet_or_outlet_nodes", m_sPath_and_FileName);
    sscanf(line, "%*s%d", &tmp);
    use_all_inlet_or_outlet_nodes = (bool) tmp;

    reading::get_line_that_contains_this_string_and_close_the_file(line, "print_numzad_nodes_and_inlet_or_outlet_facets", m_sPath_and_FileName);
    sscanf(line, "%*s%d", &tmp);
    print_numzad_nodes_and_inlet_or_outlet_facets = (bool) tmp;

    reading::get_line_that_contains_this_string_and_close_the_file(line, "print_prescribed_pressure", m_sPath_and_FileName);
    sscanf(line, "%*s%d", &tmp);
    print_prescribed_pressure = (bool) tmp;

    reading::get_line_that_contains_this_string_and_close_the_file(line, "clear_and_set_this_boundary_to_nodes", m_sPath_and_FileName);
    sscanf(line, "%*s%d", &tmp);
    clear_and_set_this_boundary_to_nodes = tmp;

    reading::get_line_that_contains_this_string_and_close_the_file(line, "add_this_boundary_to_all_nodes_outlet_or_inlet_faces", m_sPath_and_FileName);
    sscanf(line, "%*s%d", &tmp);
    add_this_boundary_to_all_nodes_outlet_or_inlet_faces = tmp;

    reading::get_line_that_contains_this_string_and_close_the_file(line, "nearNodeTol", m_sPath_and_FileName);
    sscanf(line, "%*s%lf", &tmp_d);
    near_node_tol = tmp_d;

    reading::get_line_that_contains_this_string_and_close_the_file(line, "sameNodeTol", m_sPath_and_FileName);
    sscanf(line, "%*s%lf", &tmp_d);
    same_node_tol = tmp_d;

    reading::get_line_that_contains_this_string_and_close_the_file(line, "scale_facX", m_sPath_and_FileName);
    sscanf(line, "%*s%lf", &tmp_d);
    scale_facX = tmp_d;

    reading::get_line_that_contains_this_string_and_close_the_file(line, "scale_facY", m_sPath_and_FileName);
    sscanf(line, "%*s%lf", &tmp_d);
    scale_facY = tmp_d;

    reading::get_line_that_contains_this_string_and_close_the_file(line, "scale_facZ", m_sPath_and_FileName);
    sscanf(line, "%*s%lf", &tmp_d);
    scale_facZ = tmp_d;

    reading::get_line_that_contains_this_string_and_close_the_file(line, "check_distance", m_sPath_and_FileName);
    sscanf(line, "%*s%d", &tmp);
    check_distance = (bool) tmp;

    reading::get_line_that_contains_this_string_and_close_the_file(line, "TOLdistance", m_sPath_and_FileName);
    sscanf(line, "%*s%lf", &tmp_d);
    TOLdistance = tmp_d;

    reading::get_line_that_contains_this_string_and_close_the_file(line, "refNode", m_sPath_and_FileName);
    sscanf(line, "%*s%d", &tmp);
    refNode = tmp;

    reading::get_line_that_contains_this_string_and_close_the_file(line, "materialID_of_outlet_or_inlet", m_sPath_and_FileName);
    sscanf(line, "%*s%d", &tmp);
    materialID_of_outlet_or_inlet = tmp;

    reading::get_line_that_contains_this_string_and_close_the_file(line, "dat_or_sli_input", m_sPath_and_FileName);
    sscanf(line, "%*s%d", &tmp);
    if (tmp == 1)
        dat_or_sli_input = constants::dat;
    if (tmp != 1)
        dat_or_sli_input = constants::sli;

    reading::get_line_that_contains_this_string_and_close_the_file(line, "stl_or_fal_input", m_sPath_and_FileName);
    sscanf(line, "%*s%d", &tmp);
    if (tmp == 3)
        stl_or_fal_input = constants::stl;
    if (tmp != 3)
        stl_or_fal_input = constants::fal;

    return true;
}

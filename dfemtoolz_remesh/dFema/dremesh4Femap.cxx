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

#include "dremesh4Femap.h"

int dremesh4Femap(bool inherit_boundary_and_loads, bool print_pos_nodes, bool print_pos_elements, bool print_vtk_elements, bool check_bricks, bool print_volume_of_the_model, int material_ID)
{
    Info * info = Info::createInfo();

    Timer * timer = Timer::createTimer();
    timer->set_start_time();

    Collection <Mesh_Node> nodez;
    Collection <Geom_Element>  elements;

    dremesh4FemapF(nodez, elements, inherit_boundary_and_loads, check_bricks, print_volume_of_the_model, material_ID);

    info->print_info_message("printing files");

    if (print_pos_nodes || print_pos_elements)
    {
        POS_Printer * pos_printer = POS_Printer::create_POS_Printer();

        if (print_pos_nodes)
        {
            pos_printer->print_nodes_using_node_position_in_collection_as_ID_to_pos_file(nodez, "output/nodes_ID.pos");
            pos_printer->print_nodes_boundary_to_pos_file(nodez, "output/nodes_boundary.pos");
        }
        if (print_pos_elements)
            pos_printer->print_bricks_from_15node_tetrahedrons_and_14node_prisms_to_pos_file
            (elements, nodez, "output/elements.pos");
    }


    if (print_vtk_elements)
    {
        VTK_Printer * vtk_printer = VTK_Printer::create_VTK_Printer();

        vtk_printer->print_bricks_from_15node_tetrahedrons_and_14node_prisms_to_vtk_file(
        elements, nodez, "output/elements.vtk");
    }


    info->print_info_message("----");
    info->print_info_message("Number of nodez in final mesh:       " +
    utos(nodez.get_size()));

    timer->print_time_interval_in_seconds_from_start_to_now();

    return 0;
}


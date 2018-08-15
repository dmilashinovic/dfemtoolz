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

#include "dremesh4Tetgen_tetra.h"

int dremesh4Tetgen_tetra(bool print_pos_nodes, bool print_pos_elements, int material_ID)
{
    Info * info = Info::createInfo();

    Collection <Mesh_Node> nodez;
    Collection <Geom_Element>  elements;

    UINT no_of_tetra_nodez = dremesh4Tetgen_tetraF(nodez, elements, material_ID);

    Timer * timer = Timer::createTimer();
    timer->set_start_time();

    for (UINT i = 1; i <= elements.get_size(); i++)
        elements[i].set_material_ID(material_ID);

    info->print_info_message("printing files");

    SLI_Printer * sli_printer = SLI_Printer::create_SLI_Printer();
    sli_printer->create_sli_file("output/simple_list.sli");
    sli_printer->first_block(no_of_tetra_nodez);
    sli_printer->set_how_many_nodes_2_print(no_of_tetra_nodez);
    sli_printer->print_nodes_using_node_position_in_collection_as_ID_into_sli(nodez);
    sli_printer->second_block(elements.get_size(), constants::TETRA);
    sli_printer->print_4tetras_from_15node_tetrahedrons(elements, nodez);
    sli_printer->third_block();

    if (print_pos_nodes || print_pos_elements)
    {
        POS_Printer * pos_printer = POS_Printer::create_POS_Printer();

        pos_printer->set_how_many_nodes_2_print(no_of_tetra_nodez);

        if (print_pos_nodes)
        {
            pos_printer->print_nodes_using_node_position_in_collection_as_ID_to_pos_file(nodez, "output/nodes_ID.pos");
            pos_printer->print_nodes_boundary_to_pos_file(nodez, "output/nodes_boundary.pos");
        }

        if (print_pos_elements)
        {
            pos_printer->set_elem_type(constants::TETRA);
            pos_printer->print_elems_to_pos_file(elements, constants::POS_TETRA, nodez, "output/elements.pos");
        }
    }

    info->print_info_message("----");
    info->print_info_message("Number of nodez in final mesh:       " +
    utos(no_of_tetra_nodez));

    timer->print_time_interval_in_seconds_from_start_to_now();

    return 0;
}


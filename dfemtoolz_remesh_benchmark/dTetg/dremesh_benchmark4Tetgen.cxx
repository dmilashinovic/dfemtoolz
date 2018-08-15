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

#include "dremesh_benchmark4Tetgen.h"

int dremesh_benchmark4Tetgen(bool print_pos_nodes, bool print_pos_elements, bool check_bricks, bool print_volume_of_the_model)
{

    Info * info = Info::createInfo();

    string node_fileName = "input/input.1.node";
    string elem_fileName = "input/input.1.ele";

    Timer * timer = Timer::createTimer();
    timer->set_start_time();

    info->print_info_message("\n reading phase / timer initialized");

    Tetgen_Reader * tetgen_reader = Tetgen_Reader::create_Tetgen_Reader();

    Collection <Mesh_Node> nodez;
    Collection <Geom_Element>  elements, trianglez;

    tetgen_reader->read_node_file(nodez,    node_fileName);
    tetgen_reader->read_elem_file(elements, elem_fileName);

    info->print_info_message("\n reading phase finished / timer re-initialized");

    timer->print_time_interval_in_miliseconds_from_start_to_now();
    timer->set_start_time();

    meshing::create_15nodal_from_4nodal_tetrahedrons(nodez, trianglez, elements);

    {
        UINT zero = 0;
        for (UINT i = 1; i <= nodez.get_size(); i++)
            nodez[i].set_ID(zero);
    }

    for (UINT i = 1; i <= trianglez.get_size(); i++)
    if (nodez[trianglez[i].get_node(4)].get_flag())
        boundary_and_loads::set_velocity_boundary_marker_2_all_nodes_in_element(trianglez[i], nodez);

    if (check_bricks)
    {
        bool all_elements_are_ok = true;

        vector <Geom_Element> bricks(4, Geom_Element(8));

        for (UINT i = 1; i <= elements.get_size(); i++)
        {
            meshing::get_4_bricks_from_15_tetrahedron(bricks, elements[i]);

            for (UINT j = 0; j < 4; j++)
            if (!this_brick_is_fine(bricks[j], nodez))
            {
                info->print_info_message("\n element number " + utos(i) + " has det less than zero");
                all_elements_are_ok = false;
            }
        }

        if (all_elements_are_ok)
            info->print_info_message("\n all elements are fine \n ");
    }

    if (print_volume_of_the_model)
    {
        double volume = 0.;

        vector <Geom_Element> bricks(4, Geom_Element(8));

        for (UINT i = 1; i <= elements.get_size(); i++)
        {
            meshing::get_4_bricks_from_15_tetrahedron(bricks, elements[i]);

            for (UINT j = 0; j < 4; j++)
                volume += get_brick_volume(bricks[j], nodez);
        }

        info->print_info_message("model volume is " + dtos(volume));
    }

    info->print_info_message("\n work completed / timer re-initialized");
    info->print_info_message("Number of nodez in final mesh:       " + utos(nodez.get_size()));
    info->print_info_message("Number of elements in final mesh:       " + utos(4*elements.get_size()));

    timer->print_time_interval_in_miliseconds_from_start_to_now();


    timer->set_start_time();

    info->print_info_message("\n do you want to continue to print phase? (y/N)");
    char pip; cin.get(pip);

    if (pip != 'y')
        return 0;

    info->print_info_message("printing files");

    SLI_Printer * sli_printer = SLI_Printer::create_SLI_Printer();
    sli_printer->create_sli_file("output/simple_list.sli");
    sli_printer->first_block(nodez.get_size());
    sli_printer->print_nodes_using_node_position_in_collection_as_ID_into_sli(nodez);
    sli_printer->second_block(4 * elements.get_size(), constants::BRICK);
    sli_printer->print_bricks_from_15node_tetrahedrons_and_14node_prisms(elements, nodez);
    sli_printer->third_block();

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

//    info->print_info_message("----");
//    info->print_info_message("Number of nodez in final mesh:       " +
//    utos(nodez.get_size()));

    timer->print_time_interval_in_seconds_from_start_to_now();

    return 0;
}

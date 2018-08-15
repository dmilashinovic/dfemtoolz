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

#include "case1-fluid-flow_program.h"


int main()
{
    /// program start

    /// info object created

    Info * info = Info::createInfo();
    info->print_software_header("case1-fluid-flow_program", 2018, 1);
    info->print_info_message("");


    /// timer created

    Timer * timer = Timer::createTimer();
    timer->set_start_time();


    /// POS printer created

    POS_Printer * pos_printer = POS_Printer::create_POS_Printer();


    /// collections for storing data created

    Collection <Mesh_Node> nodez;
    Collection <Geom_Element> elements, initial_faces, contact_faces, surface_facets, input_faces_from_fal;


    info->print_info_message("part I :: dfemtoolz_dremesh4Tetgen 1/1");

    /// dfemtoolz_remesh
    dremesh_get_elems(nodez, elements, "input/input.1.node", "input/input.1.ele", "");

    UINT no_of_nodez = nodez.get_size();

    if (elements[1].how_many_nodes_per_element() == constants::TETRA)
        meshing::clear_all_neighbours_lists(nodez);

    /// dfemtoolz_openR

    for (int i = 0; i <= 6; i++)
    {
        info->print_info_message("part II :: dfemtoolz_dopenR " + utos(i+1) + "/7 apply BCs");

        /// dfemtoolz_openR
        if (i == 0)
        dopenR(nodez, elements, initial_faces, contact_faces, surface_facets, input_faces_from_fal, "input/dopenR_parameters_inlet.cfg", "input/BC" + utos(i));
        if (i > 0)
        dopenR(nodez, elements, initial_faces, contact_faces, surface_facets, input_faces_from_fal, "input/dopenR_parameters_outlet.cfg", "input/BC" + utos(i));

        /// printing BC patch
        if (elements[1].how_many_nodes_per_element() == constants::BRICK)
            pos_printer->print_quads_from_quadrilateral_elements_as_lines_into_pos(true, surface_facets, nodez, "output/BC." + utos(i) + ".pos");
        if (elements[1].how_many_nodes_per_element() == constants::TETRA)
            pos_printer->print_triangles_from_triangle_elements_as_lines_into_pos(true, surface_facets, nodez, "output/BC." + utos(i) + ".pos");

        if (i != 6)
            surface_facets.clear_collection();
    }

    /// printing output files
    info->print_info_message("");
    info->print_info_message("");
    info->print_info_message("\n printing output files \n");

    /// POS nodes
    {
        pos_printer->set_how_many_nodes_2_print(no_of_nodez);
        pos_printer->print_nodes_using_node_position_in_collection_as_ID_to_pos_file(nodez, "output/nodes_ID.pos");
        pos_printer->print_nodes_boundary_to_pos_file(nodez, "output/nodes_boundary.pos");
    }

    /// POS elements
    {
        if (elements[1].how_many_nodes_per_element() == constants::BRICK)
            pos_printer->print_elems_to_pos_file(elements, constants::POS_BRICK, nodez, "output/elements.pos");
        if (elements[1].how_many_nodes_per_element() == constants::TETRA)
            pos_printer->print_elems_to_pos_file(elements, constants::POS_TETRA, nodez, "output/elements.pos");

        if (elements[1].how_many_nodes_per_element() == constants::BRICK)
            pos_printer->print_quads_from_quadrilateral_elements_as_lines_into_pos(false, surface_facets, nodez, "output/surface_of_material_you_picked.pos");
        if (elements[1].how_many_nodes_per_element() == constants::TETRA)
            pos_printer->print_triangles_from_triangle_elements_as_lines_into_pos(false, surface_facets, nodez, "output/surface_of_material_you_picked.pos");
    }


    /// SLI file
    SLI_Printer * sli_printer = SLI_Printer::create_SLI_Printer();
    sli_printer->set_how_many_nodes_2_print(no_of_nodez);
    sli_printer->create_sli_file("output/simple_list.sli");
    sli_printer->first_block(no_of_nodez);
    sli_printer->print_nodes_using_node_position_in_collection_as_ID_into_sli(nodez);

    if (elements[1].how_many_nodes_per_element() == constants::BRICK)
    {
        sli_printer->second_block(elements.get_size(), constants::BRICK);
        sli_printer->print_elems_using_elem_position_in_collection_as_ID_into_sli(elements, nodez);
        sli_printer->third_block(constants::QUAD, initial_faces, contact_faces, surface_facets);
    }

    if (elements[1].how_many_nodes_per_element() == constants::TETRA)
    {
        sli_printer->second_block(elements.get_size(), constants::TETRA);
        sli_printer->print_elems_using_elem_position_in_collection_as_ID_into_sli(elements, nodez);
        sli_printer->third_block(constants::TRIANGLE, initial_faces, contact_faces, surface_facets);
    }

    info->print_info_message("----");
    info->print_info_message("Number of nodez in final mesh:       " + utos(nodez.get_size()));
    info->print_info_message("Number of elementZ in final mesh:       " + utos(elements.get_size()));

    timer->print_time_interval_in_seconds_from_start_to_now();

    info->print_software_footer();
    press_any_key_2_continue();
    return 0;
}

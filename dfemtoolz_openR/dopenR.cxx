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

#include "dopenR.h"


int main()
{
    Info * info = Info::createInfo();
    info->print_software_header("openR", 2017, 180313);
    info->print_info_message("");

    Timer * timer = Timer::createTimer();
    timer->set_start_time();

    openR_Parameters * params =
    openR_Parameters::create_openR_Parameters();

    params->read_file();

    Collection <Mesh_Node> nodez;
    Collection <Geom_Element>  elements, initial_faces, contact_faces, surface_facets, input_faces_from_fal;

    {
        SLI_Reader * sli_reader = SLI_Reader::create_SLI_Reader();
        sli_reader->read_file(nodez, elements, "input/simple_list.sli");
    }

    UINT no_of_nodez = dopenR(nodez, elements, initial_faces, contact_faces, surface_facets, input_faces_from_fal, "input/dopenR_parameters.cfg", "input/input");

    if (params->print_pos_nodes || params->print_pos_elements ||
    params->print_pos_init_velocity || params->print_pos_inlet_or_outlet || params->print_pos_surface)
    {
        POS_Printer * pos_printer = POS_Printer::create_POS_Printer();

        if (params->print_pos_nodes)
        {
            pos_printer->set_how_many_nodes_2_print(no_of_nodez);
            pos_printer->print_nodes_using_node_position_in_collection_as_ID_to_pos_file(nodez, "output/nodes_ID.pos");
            pos_printer->print_nodes_boundary_to_pos_file(nodez, "output/nodes_boundary.pos");
        }

        if (params->print_pos_elements)
        {
            if (elements[1].how_many_nodes_per_element() == constants::BRICK)
                pos_printer->print_elems_to_pos_file(elements, constants::POS_BRICK, nodez, "output/elements.pos");
            if (elements[1].how_many_nodes_per_element() == constants::TETRA)
                pos_printer->print_elems_to_pos_file(elements, constants::POS_TETRA, nodez, "output/elements.pos");
        }

        if (params->print_pos_inlet_or_outlet)
        {
            if (params->stl_or_fal_input != constants::fal)
            if (elements[1].how_many_nodes_per_element() == constants::BRICK)
                pos_printer->print_quads_from_quadrilateral_elements_as_lines_into_pos(true, surface_facets, nodez, "output/outlet_or_inlet.pos");

            if (params->stl_or_fal_input != constants::fal)
            if (elements[1].how_many_nodes_per_element() == constants::TETRA)
                pos_printer->print_triangles_from_triangle_elements_as_lines_into_pos(true, surface_facets, nodez, "output/outlet_or_inlet.pos");

            if (params->stl_or_fal_input == constants::fal)
                pos_printer->print_quads_from_quadrilateral_elements_as_lines_into_pos(false, input_faces_from_fal, nodez, "output/outlet_or_inlet.pos");
        }

        if (params->print_pos_surface)
        if (!(params->stl_or_fal_input == constants::fal))
        {
            if (elements[1].how_many_nodes_per_element() == constants::BRICK)
                pos_printer->print_quads_from_quadrilateral_elements_as_lines_into_pos(false, surface_facets, nodez, "output/surface_of_material_you_picked.pos");
            if (elements[1].how_many_nodes_per_element() == constants::TETRA)
                pos_printer->print_triangles_from_triangle_elements_as_lines_into_pos(false, surface_facets, nodez, "output/surface_of_material_you_picked.pos");
        }
    }

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

    timer->print_time_interval_in_seconds_from_start_to_now();

    info->print_software_footer();
    press_any_key_2_continue();
    return 0;
}

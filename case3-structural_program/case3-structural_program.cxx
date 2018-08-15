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

#include "case3-structural_program.h"


int main()
{
    /// program start

    /// info object created

    Info * info = Info::createInfo();
    info->print_software_header("case3-structural_program", 2018, 1);
    info->print_info_message("");


    /// timer created

    Timer * timer = Timer::createTimer();
    timer->set_start_time();


    /// POS printer created

    POS_Printer * pos_printer = POS_Printer::create_POS_Printer();


    /// super-collections and collections for storing data created (for each material)

    SuperCollection <Mesh_Node> nodez;
    SuperCollection <Geom_Element> elements;
    Collection <Geom_Element> initial_faces, contact_faces, surface_facets, input_faces_from_fal;

    /// dfemtoolz_remesh

    {
        Collection <Mesh_Node> nodes_collection;
        Collection <Geom_Element>  elements_collection;


        /// dfemtoolz_remesh for each material (4)
        for (UINT i = 1; i <= 4; i++)
        {
            info->print_info_message("");
            info->print_info_message("");
            info->print_info_message("part I :: dfemtoolz_remesh " + utos(i) + "/4");

            nodez.insert(nodes_collection);
            elements.insert(elements_collection);
            dremesh_get_elems(nodez[i], elements[i], "input/" + utos(i)+ ".1.node", "input/" + utos(i)+ ".1.ele", "");
        }
    }

    /// dfemtoolz_multimaterial for each interface/contact between materials (3)

    {

        Collection <UINT> contact_facesIDper_material;
        contact_facesIDper_material.insert(0);

        for (UINT i = 2; i <= 4; i++)
        {
            info->print_info_message("");
            info->print_info_message("");
            info->print_info_message("part II :: dfemtoolz_multimaterial " + utos(i-1) + "/3");


            string
            contact_name ;
            contact_name = "output/contact" + utos(i-1) + ".pos";

            dmultimaterialF(nodez[1], nodez[i], elements[1], elements[i], initial_faces, contact_faces, "input/dmultimaterial_parameters.cfg");

            contact_facesIDper_material.insert(contact_faces.get_size());

            /// print interface/contact surface

            {
                if (elements[1][1].how_many_nodes_per_element() == constants::BRICK)
                    pos_printer->print_quads_from_quadrilateral_elements_as_lines_into_pos
                    (contact_facesIDper_material[i-1]+1, contact_facesIDper_material[i],
                    true, contact_faces, nodez[1], contact_name);

                if (elements[1][1].how_many_nodes_per_element() == constants::TETRA)
                    pos_printer->print_triangles_from_triangle_elements_as_lines_into_pos
                    (contact_facesIDper_material[i-1]+1, contact_facesIDper_material[i],
                    true, contact_faces, nodez[1], contact_name);
            }

            /// if needed - user can save each contact collection
    //        contact_faces.clear_collection();
        }
    }

    if (elements[1][1].how_many_nodes_per_element() == constants::TETRA)
        meshing::clear_all_neighbours_lists(nodez[1]);

    /// dfemtoolz_openR
    UINT no_of_nodez =
    dopenR(nodez[1], elements[1], initial_faces, contact_faces, surface_facets, input_faces_from_fal, "input/dopenR_parameters.cfg", "input/_pressureCircle");

    /// printing BC patch
    if (elements[1][1].how_many_nodes_per_element() == constants::BRICK)
        pos_printer->print_quads_from_quadrilateral_elements_as_lines_into_pos(true, surface_facets, nodez[1], "output/pressure_surface.pos");
    if (elements[1][1].how_many_nodes_per_element() == constants::TETRA)
        pos_printer->print_triangles_from_triangle_elements_as_lines_into_pos(true, surface_facets, nodez[1], "output/pressure_surface.pos");


    /// POS elements

    if (elements[1][1].how_many_nodes_per_element() == constants::BRICK)
        pos_printer->print_elems_with_material_to_pos_file
        (elements[1], constants::POS_BRICK, nodez[1], "output/elements_mat.pos");


    if (elements[1][1].how_many_nodes_per_element() == constants::TETRA)
        pos_printer->print_elems_with_material_to_pos_file
        (elements[1], constants::POS_TETRA, nodez[1], "output/elements_mat.pos");

    info->print_info_message("printing SLI file...");

    /// SLI file
    SLI_Printer * sli_printer = SLI_Printer::create_SLI_Printer();
    sli_printer->set_how_many_nodes_2_print(no_of_nodez);
    sli_printer->create_sli_file("output/simple_list.sli");
    sli_printer->first_block(no_of_nodez);
    sli_printer->print_nodes_using_node_position_in_collection_as_ID_into_sli(nodez[1]);

    if (elements[1][1].how_many_nodes_per_element() == constants::BRICK)
    {
        sli_printer->second_block(elements[1].get_size(), constants::BRICK);
        sli_printer->print_elems_using_elem_position_in_collection_as_ID_into_sli(elements[1], nodez[1]);
        sli_printer->third_block(constants::QUAD, initial_faces, contact_faces, surface_facets);
    }

    if (elements[1][1].how_many_nodes_per_element() == constants::TETRA)
    {
        sli_printer->second_block(elements.get_size(), constants::TETRA);
        sli_printer->print_elems_using_elem_position_in_collection_as_ID_into_sli(elements[1], nodez[1]);
        sli_printer->third_block(constants::TRIANGLE, initial_faces, contact_faces, surface_facets);
    }

    timer->print_time_interval_in_seconds_from_start_to_now();

    return 0;
}


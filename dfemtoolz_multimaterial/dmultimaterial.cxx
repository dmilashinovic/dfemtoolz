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

#include "dmultimaterial.h"


int main()
{
    Info * info = Info::createInfo();
    info->print_software_header("multimaterial", 2017, 180313);
    info->print_info_message("");

    Timer * timer = Timer::createTimer();
    timer->set_start_time();

    multimaterial_Parameters * params =
    multimaterial_Parameters::create_multimaterial_Parameters();

    params->read_file();

    SuperCollection <Mesh_Node> nodez;
    SuperCollection <Geom_Element> elements;
    Collection <Geom_Element> init_faces, contact_faces, contact_faces_side0, contact_faces_side1;
    SuperCollection <Geom_Element> contact_faces_supercol;
    Collection <UINT> contact_faces_supercol_checksums;

    SuperCollection <UINT> references_to_contact_surfaces;

    POS_Printer * pos_printer = POS_Printer::create_POS_Printer();

    VTK_Printer * vtk_printer = VTK_Printer::create_VTK_Printer();

    char buffer[10];

    UINT no_of_contact_surfaces = 0;

    {
        string names_of_sli_inputs;
        SLI_Reader * sli_reader = SLI_Reader::create_SLI_Reader();

        for (int i = 1; i <= 2 /* params->number_of_single_material_input_sli_files */ ; i++)
        {
            Collection <Mesh_Node> nodeztmp;
            Collection <Geom_Element>  elementstmp;

            names_of_sli_inputs = "input/simple_list";
            snprintf(buffer, 10, "%d", i);
            names_of_sli_inputs += buffer;
            names_of_sli_inputs += ".sli";

            if (i > 1)
                sli_reader->read_file(nodeztmp, elementstmp, names_of_sli_inputs);
            if (i == 1)
                sli_reader->read_file(nodeztmp, elementstmp, init_faces, contact_faces, names_of_sli_inputs);

            if (contact_faces.get_size() > 0)
            for (UINT x = 1; x <= contact_faces.get_size(); x++)
            {
                if (elementstmp[1].how_many_nodes_per_element() == constants::BRICK)
                if (no_of_contact_surfaces < contact_faces[x].get_node(5))
                    no_of_contact_surfaces = contact_faces[x].get_node(5);

                if (elementstmp[1].how_many_nodes_per_element() == constants::TETRA)
                if (no_of_contact_surfaces < contact_faces[x].get_node(4))
                    no_of_contact_surfaces = contact_faces[x].get_node(4);
            }

            nodez.insert(nodeztmp);
            elements.insert(elementstmp);
        }
    }

    int multimaterial_IDs_from_first_input = 1;

    for (UINT i = 1; i <= elements[1].get_size(); i++)
    if (elements[1][i].get_material_ID() > multimaterial_IDs_from_first_input)
        multimaterial_IDs_from_first_input = elements[1][i].get_material_ID();

    /// common surface node merging
    if (nodez.get_size() > 1)
    for (UINT i = 2; i <= nodez.get_size(); i++) /// for more than 2 materials at once i-max > 2
    for (UINT j = 1; j <= nodez[i].get_size(); j++)
    if (nodez[i][j].is_velocity_boundary())
    for (UINT k = 1; k <= nodez[i-1].get_size(); k++) /// this is the case where only i-1 materials have connection for general purpose must have yet another loop
    if (nodez[i-1][k].is_velocity_boundary())
    if (these_nodes_are_the_same(nodez[i][j], nodez[i-1][k], constants::same_node_tol))
    {
        nodez[i][j].set_ID(k);
        nodez[i-1][k].set_flag(true);
    }
    /// with id and flag are contact nodes - same nodes

    /// nodes supercollection to collection no 1
    for (UINT i = 2; i <= nodez.get_size(); i++)
    for (UINT j = 1; j <= nodez[i].get_size(); j++)
    if (nodez[i][j].get_ID() == 0)
    {
        nodez[1].insert(nodez[i][j]);
        UINT mid = nodez[1].get_size();
        nodez[i][j].set_ID(mid);
    }

    /// elements[2] renumbering
    if (elements.get_size() > 1)
    {
        for (UINT i = 2; i <= elements.get_size(); i++)
        for (UINT j = 1; j <= elements[i].get_size(); j++)
        {
            elements[i][j].set_material_ID(multimaterial_IDs_from_first_input + i - 1);

            for (int k = 1; k <= elements[i][j].how_many_nodes_per_element(); k++)
            if (nodez[i][elements[i][j].get_node(k)].get_ID() != 0)
            {
                UINT mid = elements[i][j].get_node(k);
                elements[i][j].set_node(nodez[i][mid].get_ID(), k);
            }
        }
    }


    {
        Collection <UINT> ref_2_contact_surface;

        ref_2_contact_surface.insert(0);
        ref_2_contact_surface.insert(0);
        ref_2_contact_surface.insert(no_of_contact_surfaces);

        references_to_contact_surfaces.insert(ref_2_contact_surface);
    }

    /// finding contact
    {
        UINT mat_from_el_col_02 = elements[2][1].get_material_ID();

        for (UINT z = 1; z <= 2; z++)
        for (UINT j = 1; j <= elements[z].get_size(); j++)
        {
            if (z == 1)
//                put_contact_edges_first(j, nodez[1], elements[z][j], contact_faces, mat_from_el_col_02, references_to_contact_surfaces);
                put_contact_edges_first(j, nodez[1], elements[z][j], contact_faces_side0, mat_from_el_col_02);

            if (z > 1)
//                put_contact_edges_second(j + elements[1].get_size(), nodez[1], elements[z][j], contact_faces, elements[1], references_to_contact_surfaces);
                put_contact_edges_second(j + elements[1].get_size(), nodez[1], elements[z][j], contact_faces_side1, elements[1]);
        }
    }


    if (contact_faces_side0.get_size() > 0)
    if (contact_faces_side1.get_size() > 0)
    {
//            SuperCollection <Geom_Element> con_fcs0, con_fcs1;
            Collection <Geom_Element> con_fcz; /// empty array

//            Collection <UINT> checksum0, checksum1;
            UINT checksum, arrayID = 0;


            {
//                checksum = contact_faces_side0[1].get_node(6) + contact_faces_side0[1].get_node(5);
//                contact_faces_supercol.insert(con_fcz);
//                contact_faces_supercol_checksums.insert(checksum);

                for (UINT chksb = 1; chksb <= contact_faces_side0.get_size(); chksb++)
                {
                    arrayID = 0;

                    if (elements[1][1].how_many_nodes_per_element() == 4)
                        checksum = contact_faces_side0[chksb].get_node(6) + contact_faces_side0[chksb].get_node(5);

                    if (elements[1][1].how_many_nodes_per_element() == 8)
                        checksum = contact_faces_side0[chksb].get_node(6) + contact_faces_side0[chksb].get_node(7);

                    for (UINT arrswitch = 1; arrswitch <= contact_faces_supercol.get_size(); arrswitch++)
                    if (checksum == contact_faces_supercol_checksums[arrswitch])
                    {
                        if (contact_faces_side0[chksb].get_node(6) !=
                        contact_faces_supercol[arrswitch][1].get_node(6))
                            continue;

                        arrayID = arrswitch;
                    }

                    if (arrayID == 0)
                    {
                        contact_faces_supercol.insert(con_fcz);
                        contact_faces_supercol_checksums.insert(checksum);

                        contact_faces_supercol[contact_faces_supercol_checksums.get_size()].
                        insert(contact_faces_side0[chksb]);
                    }

                    if (arrayID != 0)
                        contact_faces_supercol[arrayID].insert(contact_faces_side0[chksb]);

                }


                for (UINT chksb = 1; chksb <= contact_faces_side1.get_size(); chksb++)
                {
                    arrayID = 0;

                    if (elements[1][1].how_many_nodes_per_element() == 4)
                        checksum = contact_faces_side1[chksb].get_node(6) + contact_faces_side1[chksb].get_node(5);

                    if (elements[1][1].how_many_nodes_per_element() == 8)
                        checksum = contact_faces_side1[chksb].get_node(6) + contact_faces_side1[chksb].get_node(7);

                    for (UINT arrswitch = 1; arrswitch <= contact_faces_supercol.get_size(); arrswitch++)
                    if (checksum == contact_faces_supercol_checksums[arrswitch])
                    {
                        if (contact_faces_side1[chksb].get_node(6) !=
                        contact_faces_supercol[arrswitch][1].get_node(6))
                            continue;

                        arrayID = arrswitch;
                    }

                    if (arrayID == 0)
                    {
                        contact_faces_supercol.insert(con_fcz);
                        contact_faces_supercol_checksums.insert(checksum);

                        contact_faces_supercol[contact_faces_supercol_checksums.get_size()].
                        insert(contact_faces_side1[chksb]);
                    }

                    if (arrayID != 0)
                        contact_faces_supercol[arrayID].insert(contact_faces_side1[chksb]);
                }
            }
    }
//    }



    /// elements supercollection to collection
    for (UINT i = 2; i <= elements.get_size(); i++)
    for (UINT j = 1; j <= elements[i].get_size(); j++)
        elements[1].insert(elements[i][j]);

    if (params->chekAllBrickElements)
    if (elements[1][1].how_many_nodes_per_element() == constants::BRICK)
    {
        bool all_elements_are_ok = true;

            for (UINT j = 1; j <= 1; j++)
            for (UINT i = 1; i <= elements[j].get_size(); i++)
            if (!this_brick_is_fine(elements[j][i], nodez[1]))
            {
                info->print_info_message("\n element number " + utos(i) + " has det less than zero");
                all_elements_are_ok = false;
            }

            if (all_elements_are_ok)
                info->print_info_message("\n all elements are fine \n ");
    }

    pos_printer->print_nodes_using_nodeID_to_pos_file
    (nodez[1], "output/nodes_IDall.pos");

    if (elements[1][1].how_many_nodes_per_element() == constants::BRICK)
        pos_printer->print_elems_with_material_to_pos_file
        (elements[1], constants::POS_BRICK, nodez[1], "output/elements_mat.pos");

    if (elements[1][1].how_many_nodes_per_element() == constants::TETRA)
        pos_printer->print_elems_with_material_to_pos_file
        (elements[1], constants::POS_TETRA, nodez[1], "output/elements_mat.pos");

    if (elements[1][1].how_many_nodes_per_element() == constants::TETRA)
        vtk_printer->print_tetrahedron_elems_material_2_vtk_file(
        elements[1], nodez[1], "output/elements_mat.vtk");

    if (elements[1][1].how_many_nodes_per_element() == constants::BRICK)
        vtk_printer->print_brick_elems_material_2_vtk_file(
        elements[1], nodez[1], "output/elements_mat.vtk");



    info->print_info_message("\n\ncontacts printing\n");

    {
        char buffer[10];

        for (UINT i = 1; i <= contact_faces_supercol.get_size(); i++)
        if (contact_faces_supercol[i].get_size() >= 1)
        {
            string  contact_name_pos, contact_name_vtk, contact_name_txt;

            snprintf(buffer, 10, "%d", i);

            contact_name_pos = "output/contact-";
            contact_name_pos += buffer;

            contact_name_vtk = contact_name_pos;
            contact_name_txt = contact_name_pos;

            contact_name_vtk += ".vtk";
            contact_name_pos += ".pos";
            contact_name_txt += ".txt";

            if (elements[1][1].how_many_nodes_per_element() == constants::TETRA)
                pos_printer->print_triangles_from_triangle_elements_as_lines_into_pos
                (false, contact_faces_supercol[i], nodez[1], contact_name_pos);

            if (elements[1][1].how_many_nodes_per_element() == constants::BRICK)
                pos_printer->print_quads_from_quadrilateral_elements_as_lines_into_pos
                (false, contact_faces_supercol[i], nodez[1], contact_name_pos);

            if (elements[1][1].how_many_nodes_per_element() == constants::TETRA)
                vtk_printer->print_triangles_to_vtk_file
                (i, contact_faces_supercol[i], nodez[1], contact_name_vtk);

            if (elements[1][1].how_many_nodes_per_element() == constants::BRICK)
                vtk_printer->print_quads_to_vtk_file
                (i, contact_faces_supercol[i], nodez[1], contact_name_vtk);
        }
    }

    SLI_Printer * sli_printer = SLI_Printer::create_SLI_Printer();
    sli_printer->create_sli_file("output/simple_list.sli");
    sli_printer->first_block(nodez[1].get_size());
    sli_printer->print_nodes_using_node_position_in_collection_as_ID_into_sli(nodez[1]);
    sli_printer->second_block(elements[1].get_size(), elements[1][1].how_many_nodes_per_element());
    sli_printer->print_elems_using_elem_position_in_collection_as_ID_into_sli(elements[1], nodez[1]);

    if (elements[1][1].how_many_nodes_per_element() == constants::TETRA)
        sli_printer->third_block(constants::TRIANGLE, init_faces, contact_faces);

    if (elements[1][1].how_many_nodes_per_element() == constants::BRICK)
        sli_printer->third_block(constants::QUAD, init_faces, contact_faces);

    info->print_info_message("----");
    info->print_info_message("Number of nodez in final mesh:       " + utos(nodez[1].get_size()));

    timer->print_time_interval_in_seconds_from_start_to_now();

    info->print_software_footer();
//    press_any_key_2_continue();
    return 0;
}


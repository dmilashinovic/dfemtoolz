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

#include "dMeshing.h"

namespace meshing
{
    void clear_all_neighbours_lists(Collection <Mesh_Node> & node_col)
    {
        for (UINT i = 1; i <= node_col.get_size(); i++)
            node_col[i].clear_all_neighbours();
    }

    void create_27nodal_from_8nodal_bricks
    (Collection <Mesh_Node> & node_col, Collection <Geom_Element> & face_col, Collection <Geom_Element> & elem_col)
    {
        Info * info = Info::createInfo();
        info->newline();
        info->print_info_message("meshing");
        info->print_info_message_no_newline("8 nodal bricks -> 27 nodal tetrahedrons");

        Geom_Element face9(9);
        UINT face_ID;

        Percent * percenTrackR = Percent::createPercent();
        percenTrackR->set_percent_max_value(elem_col.get_size());

        for (UINT i = 1; i <= elem_col.get_size(); i++)
        {
            face_col.insert
            (create_face9(elem_col[i].get_node(1), elem_col[i].get_node(2),
            elem_col[i].get_node(3), elem_col[i].get_node(4), node_col));
            face_ID = face_col.get_size();
            elem_col[i].set_node(face_col[face_ID].get_node(6),  9);
            elem_col[i].set_node(face_col[face_ID].get_node(7), 10);
            elem_col[i].set_node(face_col[face_ID].get_node(8), 11);
            elem_col[i].set_node(face_col[face_ID].get_node(9), 12);
            elem_col[i].set_node(face_col[face_ID].get_node(5), 22);

            face_col.insert
            (create_face9(elem_col[i].get_node(5), elem_col[i].get_node(6),
            elem_col[i].get_node(7), elem_col[i].get_node(8), node_col));
            face_ID = face_col.get_size();
            elem_col[i].set_node(face_col[face_ID].get_node(6), 13);
            elem_col[i].set_node(face_col[face_ID].get_node(7), 14);
            elem_col[i].set_node(face_col[face_ID].get_node(8), 15);
            elem_col[i].set_node(face_col[face_ID].get_node(9), 16);
            elem_col[i].set_node(face_col[face_ID].get_node(5), 23);

            face_col.insert
            (create_face9(elem_col[i].get_node(1), elem_col[i].get_node(2),
            elem_col[i].get_node(6), elem_col[i].get_node(5), node_col));
            face_ID = face_col.get_size();
            elem_col[i].set_node(face_col[face_ID].get_node(7), 18);
            elem_col[i].set_node(face_col[face_ID].get_node(9), 17);
            elem_col[i].set_node(face_col[face_ID].get_node(5), 24);

            face_col.insert
            (create_face9(elem_col[i].get_node(2), elem_col[i].get_node(3),
            elem_col[i].get_node(7), elem_col[i].get_node(6), node_col));
            face_ID = face_col.get_size();
            elem_col[i].set_node(face_col[face_ID].get_node(5), 25);

            face_col.insert
            (create_face9(elem_col[i].get_node(3), elem_col[i].get_node(4),
            elem_col[i].get_node(8), elem_col[i].get_node(7), node_col));
            face_ID = face_col.get_size();
            elem_col[i].set_node(face_col[face_ID].get_node(7), 20);
            elem_col[i].set_node(face_col[face_ID].get_node(9), 19);
            elem_col[i].set_node(face_col[face_ID].get_node(5), 26);

            face_col.insert
            (create_face9(elem_col[i].get_node(4), elem_col[i].get_node(1),
            elem_col[i].get_node(5), elem_col[i].get_node(8), node_col));
            face_ID = face_col.get_size();
            elem_col[i].set_node(face_col[face_ID].get_node(5), 27);

            node_col.insert(get_gravitycenter(elem_col[i], 8, node_col));
            elem_col[i].set_node(node_col.get_size(), 21);
            percenTrackR->info_percentage(i);
        }
        info->newline();
    }

    Geom_Element create_face9(UINT n1, UINT n2, UINT n3, UINT n4, Collection <Mesh_Node> & node_col)
    {
        Geom_Element face9(9);

        face9.set_node(n1, 1);
        face9.set_node(n2, 2);
        face9.set_node(n3, 3);
        face9.set_node(n4, 4);

        face9.set_node(
        neighbours::calculate_edge_cog_and_add_neighbourz(face9.get_node(1), face9.get_node(2), node_col), 6);

        face9.set_node(
        neighbours::calculate_edge_cog_and_add_neighbourz(face9.get_node(2), face9.get_node(3), node_col), 7);

        face9.set_node(
        neighbours::calculate_edge_cog_and_add_neighbourz(face9.get_node(3), face9.get_node(4), node_col), 8);

        face9.set_node(
        neighbours::calculate_edge_cog_and_add_neighbourz(face9.get_node(4), face9.get_node(1), node_col), 9);

        face9.set_node(
        neighbours::calculate_quadrilateral_cog_and_add_neighbourz(face9, node_col), 5);

        return face9;
    }

    void create_15nodal_from_4nodal_tetrahedrons
    (Collection <Mesh_Node> & node_col, Collection <Geom_Element> & face_col, Collection <Geom_Element> & elem_col)
    {
        UINT nX;
        Mesh_Node node;

        Info * info = Info::createInfo();
        info->newline();
        info->print_info_message("meshing");
        info->print_info_message_no_newline("4 nodal tetrahedrons -> 15 nodal tetrahedrons");

        Percent * percenTrackR = Percent::createPercent();
        percenTrackR->set_percent_max_value(elem_col.get_size());

        for (UINT i = 1; i <= elem_col.get_size(); i++)
        if (elem_col[i].how_many_nodes_per_element() == 15)
        {
            nX = neighbours::calculate_edge_cog_and_add_neighbourz(elem_col[i].get_node(1), elem_col[i].get_node(2), node_col);
            elem_col[i].set_node(nX, 5);
            nX = neighbours::calculate_edge_cog_and_add_neighbourz(elem_col[i].get_node(2), elem_col[i].get_node(3), node_col);
            elem_col[i].set_node(nX, 6);
            nX = neighbours::calculate_edge_cog_and_add_neighbourz(elem_col[i].get_node(3), elem_col[i].get_node(1), node_col);
            elem_col[i].set_node(nX, 7);
            nX = neighbours::calculate_edge_cog_and_add_neighbourz(elem_col[i].get_node(1), elem_col[i].get_node(4), node_col);
            elem_col[i].set_node(nX, 8);
            nX = neighbours::calculate_edge_cog_and_add_neighbourz(elem_col[i].get_node(2), elem_col[i].get_node(4), node_col);
            elem_col[i].set_node(nX, 9);
            nX = neighbours::calculate_edge_cog_and_add_neighbourz(elem_col[i].get_node(3), elem_col[i].get_node(4), node_col);
            elem_col[i].set_node(nX, 10);

            neighbours::create_facetz_add_facet_cogz_2_tetra
            (elem_col[i], face_col, node_col);

            node = get_gravitycenter(
            node_col[elem_col[i].get_node(1)],
            node_col[elem_col[i].get_node(2)],
            node_col[elem_col[i].get_node(3)],
            node_col[elem_col[i].get_node(4)]);

            node_col.insert(node);
            elem_col[i].set_node(node_col.get_size(), 15);
            percenTrackR->info_percentage(i);
        }
        info->newline();
    }

    void create_15nodal_from_10nodal_tetrahedrons
    (Collection <Mesh_Node> & node_col, Collection <Geom_Element> & face_col, Collection <Geom_Element> & elem_col)
    {
        Mesh_Node node;

        Info * info = Info::createInfo();
        info->print_info_message("meshing:");
        info->print_info_message_no_newline("10 nodal tetrahedrons -> 15 nodal tetrahedrons");

        Percent * percenTrackR = Percent::createPercent();
        percenTrackR->set_percent_max_value(elem_col.get_size());

        for (UINT i = 1; i <= elem_col.get_size(); i++)
        if (elem_col[i].how_many_nodes_per_element() == 15)
        {
            neighbours::create_facetz_add_facet_cogz_2_tetra
            (elem_col[i], face_col, node_col);

            node = get_gravitycenter(
            node_col[elem_col[i].get_node(1)], node_col[elem_col[i].get_node(2)], node_col[elem_col[i].get_node(3)], node_col[elem_col[i].get_node(4)]);
            node_col.insert(node);
            elem_col[i].set_node(node_col.get_size(), 15);
            percenTrackR->info_percentage(i);
        }
        info->newline();
    }

    UINT create_14nodal_from_6nodal_prisms_and_15nodal_from_4nodal_tetrahedrons_and_return_no_of_bricks
    (Collection <Mesh_Node> & node_col, Collection <Geom_Element> & face_col, Collection <Geom_Element> & elem_col)
    {
        UINT nX;
        Mesh_Node node;

        UINT no_of_bricks = 0;

        Info * info = Info::createInfo();
        info->newline();
        info->print_info_message("meshing");
        info->print_info_message("4 nodal tetrahedrons -> 15 nodal tetrahedrons");
        info->print_info_message_no_newline("6 nodal prisms -> 14 nodal prisms");

        Percent * percenTrackR = Percent::createPercent();
        percenTrackR->set_percent_max_value(elem_col.get_size());

        for (UINT i = 1; i <= elem_col.get_size(); i++)
        {
            if (elem_col[i].how_many_nodes_per_element() == 14)
            {
                nX = neighbours::calculate_edge_cog_and_add_neighbourz(elem_col[i].get_node(1), elem_col[i].get_node(2), node_col);
                elem_col[i].set_node(nX, 7);
                nX = neighbours::calculate_edge_cog_and_add_neighbourz(elem_col[i].get_node(2), elem_col[i].get_node(3), node_col);
                elem_col[i].set_node(nX, 8);
                nX = neighbours::calculate_edge_cog_and_add_neighbourz(elem_col[i].get_node(3), elem_col[i].get_node(1), node_col);
                elem_col[i].set_node(nX, 9);
                nX = neighbours::calculate_edge_cog_and_add_neighbourz(elem_col[i].get_node(4), elem_col[i].get_node(5), node_col);
                elem_col[i].set_node(nX, 10);
                nX = neighbours::calculate_edge_cog_and_add_neighbourz(elem_col[i].get_node(5), elem_col[i].get_node(6), node_col);
                elem_col[i].set_node(nX, 11);
                nX = neighbours::calculate_edge_cog_and_add_neighbourz(elem_col[i].get_node(6), elem_col[i].get_node(4), node_col);
                elem_col[i].set_node(nX, 12);

                neighbours::create_facetz_add_facet_cogz_2_prism
                (elem_col[i], face_col, node_col);

                no_of_bricks += 3;
            }
            if (elem_col[i].how_many_nodes_per_element() == 15)
            {
                nX = neighbours::calculate_edge_cog_and_add_neighbourz(elem_col[i].get_node(1), elem_col[i].get_node(2), node_col);
                elem_col[i].set_node(nX, 5);
                nX = neighbours::calculate_edge_cog_and_add_neighbourz(elem_col[i].get_node(2), elem_col[i].get_node(3), node_col);
                elem_col[i].set_node(nX, 6);
                nX = neighbours::calculate_edge_cog_and_add_neighbourz(elem_col[i].get_node(3), elem_col[i].get_node(1), node_col);
                elem_col[i].set_node(nX, 7);
                nX = neighbours::calculate_edge_cog_and_add_neighbourz(elem_col[i].get_node(1), elem_col[i].get_node(4), node_col);
                elem_col[i].set_node(nX, 8);
                nX = neighbours::calculate_edge_cog_and_add_neighbourz(elem_col[i].get_node(2), elem_col[i].get_node(4), node_col);
                elem_col[i].set_node(nX, 9);
                nX = neighbours::calculate_edge_cog_and_add_neighbourz(elem_col[i].get_node(3), elem_col[i].get_node(4), node_col);
                elem_col[i].set_node(nX, 10);

                neighbours::create_facetz_add_facet_cogz_2_tetra
                (elem_col[i], face_col, node_col);

                node = get_gravitycenter(
                node_col[elem_col[i].get_node(1)],
                node_col[elem_col[i].get_node(2)],
                node_col[elem_col[i].get_node(3)],
                node_col[elem_col[i].get_node(4)]);

                node_col.insert(node);
                elem_col[i].set_node(node_col.get_size(), 15);
                no_of_bricks += 4;
            }
            percenTrackR->info_percentage(i);
        }

        info->newline();

        return no_of_bricks;
    }

    void get_8_bricks_from_27_brick
    (vector <Geom_Element> & eight_bricks, Geom_Element & brick)
    {
        eight_bricks[0].set_node(brick.get_node(1),  1);
        eight_bricks[0].set_node(brick.get_node(9),  2);
        eight_bricks[0].set_node(brick.get_node(22), 3);
        eight_bricks[0].set_node(brick.get_node(12), 4);
        eight_bricks[0].set_node(brick.get_node(17), 5);
        eight_bricks[0].set_node(brick.get_node(24), 6);
        eight_bricks[0].set_node(brick.get_node(21), 7);
        eight_bricks[0].set_node(brick.get_node(27), 8);

        eight_bricks[1].set_node(brick.get_node(2),  1);
        eight_bricks[1].set_node(brick.get_node(10), 2);
        eight_bricks[1].set_node(brick.get_node(22), 3);
        eight_bricks[1].set_node(brick.get_node(9),  4);
        eight_bricks[1].set_node(brick.get_node(18), 5);
        eight_bricks[1].set_node(brick.get_node(25), 6);
        eight_bricks[1].set_node(brick.get_node(21), 7);
        eight_bricks[1].set_node(brick.get_node(24), 8);

        eight_bricks[2].set_node(brick.get_node(3),  1);
        eight_bricks[2].set_node(brick.get_node(11), 2);
        eight_bricks[2].set_node(brick.get_node(22), 3);
        eight_bricks[2].set_node(brick.get_node(10), 4);
        eight_bricks[2].set_node(brick.get_node(19), 5);
        eight_bricks[2].set_node(brick.get_node(26), 6);
        eight_bricks[2].set_node(brick.get_node(21), 7);
        eight_bricks[2].set_node(brick.get_node(25), 8);

        eight_bricks[3].set_node(brick.get_node(4),  1);
        eight_bricks[3].set_node(brick.get_node(12), 2);
        eight_bricks[3].set_node(brick.get_node(22), 3);
        eight_bricks[3].set_node(brick.get_node(11), 4);
        eight_bricks[3].set_node(brick.get_node(20), 5);
        eight_bricks[3].set_node(brick.get_node(27), 6);
        eight_bricks[3].set_node(brick.get_node(21), 7);
        eight_bricks[3].set_node(brick.get_node(26), 8);

        eight_bricks[4].set_node(brick.get_node(17), 1);
        eight_bricks[4].set_node(brick.get_node(24), 2);
        eight_bricks[4].set_node(brick.get_node(21), 3);
        eight_bricks[4].set_node(brick.get_node(27), 4);
        eight_bricks[4].set_node(brick.get_node(5),  5);
        eight_bricks[4].set_node(brick.get_node(13), 6);
        eight_bricks[4].set_node(brick.get_node(23), 7);
        eight_bricks[4].set_node(brick.get_node(16), 8);

        eight_bricks[5].set_node(brick.get_node(18), 1);
        eight_bricks[5].set_node(brick.get_node(25), 2);
        eight_bricks[5].set_node(brick.get_node(21), 3);
        eight_bricks[5].set_node(brick.get_node(24), 4);
        eight_bricks[5].set_node(brick.get_node(6),  5);
        eight_bricks[5].set_node(brick.get_node(14), 6);
        eight_bricks[5].set_node(brick.get_node(23), 7);
        eight_bricks[5].set_node(brick.get_node(13), 8);

        eight_bricks[6].set_node(brick.get_node(19), 1);
        eight_bricks[6].set_node(brick.get_node(26), 2);
        eight_bricks[6].set_node(brick.get_node(21), 3);
        eight_bricks[6].set_node(brick.get_node(25), 4);
        eight_bricks[6].set_node(brick.get_node(7),  5);
        eight_bricks[6].set_node(brick.get_node(15), 6);
        eight_bricks[6].set_node(brick.get_node(23), 7);
        eight_bricks[6].set_node(brick.get_node(14), 8);

        eight_bricks[7].set_node(brick.get_node(20), 1);
        eight_bricks[7].set_node(brick.get_node(27), 2);
        eight_bricks[7].set_node(brick.get_node(21), 3);
        eight_bricks[7].set_node(brick.get_node(26), 4);
        eight_bricks[7].set_node(brick.get_node(8),  5);
        eight_bricks[7].set_node(brick.get_node(16), 6);
        eight_bricks[7].set_node(brick.get_node(23), 7);
        eight_bricks[7].set_node(brick.get_node(15), 8);
    }

    int get_3_or_4_bricks_from_14_prism_or_15_tetrahedron(
    vector <Geom_Element> & four_bricks,
    Geom_Element & element)
    {
        if (element.how_many_nodes_per_element() == 14)
        {
            get_3_bricks_from_14_prism(four_bricks, element);
            return constants::PRISM;
        }

        if (element.how_many_nodes_per_element() == 15)
            get_4_bricks_from_15_tetrahedron(four_bricks, element);
        return constants::TETRA;
    }

    void get_4_bricks_from_15_tetrahedron
    (vector <Geom_Element> & four_bricks, Geom_Element & tetrahedron)
    {
        four_bricks[0].set_node(tetrahedron.get_node(8),  1);
        four_bricks[0].set_node(tetrahedron.get_node(11), 2);
        four_bricks[0].set_node(tetrahedron.get_node(15), 3);
        four_bricks[0].set_node(tetrahedron.get_node(13), 4);
        four_bricks[0].set_node(tetrahedron.get_node(1),  5);
        four_bricks[0].set_node(tetrahedron.get_node(5),  6);
        four_bricks[0].set_node(tetrahedron.get_node(14), 7);
        four_bricks[0].set_node(tetrahedron.get_node(7),  8);

        four_bricks[1].set_node(tetrahedron.get_node(9),  1);
        four_bricks[1].set_node(tetrahedron.get_node(12), 2);
        four_bricks[1].set_node(tetrahedron.get_node(15), 3);
        four_bricks[1].set_node(tetrahedron.get_node(11), 4);
        four_bricks[1].set_node(tetrahedron.get_node(2),  5);
        four_bricks[1].set_node(tetrahedron.get_node(6),  6);
        four_bricks[1].set_node(tetrahedron.get_node(14), 7);
        four_bricks[1].set_node(tetrahedron.get_node(5),  8);

        four_bricks[2].set_node(tetrahedron.get_node(10), 1);
        four_bricks[2].set_node(tetrahedron.get_node(13), 2);
        four_bricks[2].set_node(tetrahedron.get_node(15), 3);
        four_bricks[2].set_node(tetrahedron.get_node(12), 4);
        four_bricks[2].set_node(tetrahedron.get_node(3),  5);
        four_bricks[2].set_node(tetrahedron.get_node(7),  6);
        four_bricks[2].set_node(tetrahedron.get_node(14), 7);
        four_bricks[2].set_node(tetrahedron.get_node(6),  8);

        four_bricks[3].set_node(tetrahedron.get_node(10), 1);
        four_bricks[3].set_node(tetrahedron.get_node(12), 2);
        four_bricks[3].set_node(tetrahedron.get_node(15), 3);
        four_bricks[3].set_node(tetrahedron.get_node(13), 4);
        four_bricks[3].set_node(tetrahedron.get_node(4),  5);
        four_bricks[3].set_node(tetrahedron.get_node(9),  6);
        four_bricks[3].set_node(tetrahedron.get_node(11), 7);
        four_bricks[3].set_node(tetrahedron.get_node(8),  8);
    }

    void get_3_bricks_from_14_prism
    (vector <Geom_Element> & three_bricks, Geom_Element & prism)
    {
        three_bricks[0].set_node(prism.get_node(4),  1);
        three_bricks[0].set_node(prism.get_node(10), 4);
        three_bricks[0].set_node(prism.get_node(14), 3);
        three_bricks[0].set_node(prism.get_node(12), 2);
        three_bricks[0].set_node(prism.get_node(1),  5);
        three_bricks[0].set_node(prism.get_node(7),  8);
        three_bricks[0].set_node(prism.get_node(13), 7);
        three_bricks[0].set_node(prism.get_node(9),  6);

        three_bricks[1].set_node(prism.get_node(10), 1);
        three_bricks[1].set_node(prism.get_node(5),  4);
        three_bricks[1].set_node(prism.get_node(11), 3);
        three_bricks[1].set_node(prism.get_node(14), 2);
        three_bricks[1].set_node(prism.get_node(7),  5);
        three_bricks[1].set_node(prism.get_node(2),  8);
        three_bricks[1].set_node(prism.get_node(8),  7);
        three_bricks[1].set_node(prism.get_node(13), 6);

        three_bricks[2].set_node(prism.get_node(12), 1);
        three_bricks[2].set_node(prism.get_node(14), 4);
        three_bricks[2].set_node(prism.get_node(11), 3);
        three_bricks[2].set_node(prism.get_node(6),  2);
        three_bricks[2].set_node(prism.get_node(9),  5);
        three_bricks[2].set_node(prism.get_node(13), 8);
        three_bricks[2].set_node(prism.get_node(8),  7);
        three_bricks[2].set_node(prism.get_node(3),  6);
    }

    void get_6_quads_from_8_brick
    (vector <Geom_Element> & six_quads, Geom_Element & brick)
    {
        six_quads[0].set_node(brick.get_node(1), 1);
        six_quads[0].set_node(brick.get_node(2), 2);
        six_quads[0].set_node(brick.get_node(3), 3);
        six_quads[0].set_node(brick.get_node(4), 4);

        six_quads[1].set_node(brick.get_node(8), 1);
        six_quads[1].set_node(brick.get_node(7), 2);
        six_quads[1].set_node(brick.get_node(6), 3);
        six_quads[1].set_node(brick.get_node(5), 4);

        six_quads[2].set_node(brick.get_node(1), 1);
        six_quads[2].set_node(brick.get_node(4), 2);
        six_quads[2].set_node(brick.get_node(8), 3);
        six_quads[2].set_node(brick.get_node(5), 4);

        six_quads[3].set_node(brick.get_node(2), 1);
        six_quads[3].set_node(brick.get_node(1), 2);
        six_quads[3].set_node(brick.get_node(5), 3);
        six_quads[3].set_node(brick.get_node(6), 4);

        six_quads[4].set_node(brick.get_node(3), 1);
        six_quads[4].set_node(brick.get_node(2), 2);
        six_quads[4].set_node(brick.get_node(6), 3);
        six_quads[4].set_node(brick.get_node(7), 4);

        six_quads[5].set_node(brick.get_node(4), 1);
        six_quads[5].set_node(brick.get_node(3), 2);
        six_quads[5].set_node(brick.get_node(7), 3);
        six_quads[5].set_node(brick.get_node(8), 4);
    }
}

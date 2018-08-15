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

#include "dremesh4TetgenF.h"



UINT dremesh4TetgenF(Collection <Mesh_Node> & node_col, Collection <Geom_Element> & elem_col, bool check_bricks, bool print_volume_of_the_model, int material_ID)
{

    string node_fileName = "input/input.1.node";
    string elem_fileName = "input/input.1.ele";

    Timer * timer = Timer::createTimer();
    timer->set_start_time();

    Tetgen_Reader * tetgen_reader = Tetgen_Reader::create_Tetgen_Reader();

    Collection <Geom_Element>  trianglez;

    tetgen_reader->read_node_file(node_col,    node_fileName);
    tetgen_reader->read_elem_file(elem_col, elem_fileName);

    meshing::create_15nodal_from_4nodal_tetrahedrons(node_col, trianglez, elem_col);

    {
        UINT zero = 0;
        for (UINT i = 1; i <= node_col.get_size(); i++)
            node_col[i].set_ID(zero);
    }

    for (UINT i = 1; i <= trianglez.get_size(); i++)
    if (node_col[trianglez[i].get_node(4)].get_flag())
        boundary_and_loads::set_velocity_boundary_marker_2_all_nodes_in_element(trianglez[i], node_col);

    Info * info = Info::createInfo();

    if (check_bricks)
    {
        bool all_elements_are_ok = true;

        vector <Geom_Element> bricks(4, Geom_Element(8));

        for (UINT i = 1; i <= elem_col.get_size(); i++)
        {
            meshing::get_4_bricks_from_15_tetrahedron(bricks, elem_col[i]);

            for (UINT j = 0; j < 4; j++)
            if (!this_brick_is_fine(bricks[j], node_col))
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

        for (UINT i = 1; i <= elem_col.get_size(); i++)
        {
            meshing::get_4_bricks_from_15_tetrahedron(bricks, elem_col[i]);

            for (UINT j = 0; j < 4; j++)
                volume += get_brick_volume(bricks[j], node_col);
        }

        info->print_info_message("model volume is " + dtos(volume));
    }

    for (UINT i = 1; i <= elem_col.get_size(); i++)
        elem_col[i].set_material_ID(material_ID);

    timer->print_time_interval_in_seconds_from_start_to_now();

    return 0;
}

UINT dremesh4TetgenF_get_bricks(Collection <Mesh_Node> & node_col, Collection <Geom_Element> & bricks_col, bool check_bricks, bool print_volume_of_the_model, int material_ID, string Tetgen_node_fileName, string Tetgen_elem_fileName)
{

    string node_fileName = Tetgen_node_fileName;
    string elem_fileName = Tetgen_elem_fileName;

//    Timer * timer = Timer::createTimer();
//    timer->set_start_time();

    Tetgen_Reader * tetgen_reader = Tetgen_Reader::create_Tetgen_Reader();

    Collection <Geom_Element>  trianglez;
    Collection <Geom_Element>  elem_col;

    tetgen_reader->read_node_file(node_col,    node_fileName);
    tetgen_reader->read_elem_file(elem_col, elem_fileName);

    meshing::create_15nodal_from_4nodal_tetrahedrons(node_col, trianglez, elem_col);

    {
        UINT zero = 0;
        for (UINT i = 1; i <= node_col.get_size(); i++)
            node_col[i].set_ID(zero);
    }

    for (UINT i = 1; i <= trianglez.get_size(); i++)
    if (node_col[trianglez[i].get_node(4)].get_flag())
        boundary_and_loads::set_velocity_boundary_marker_2_all_nodes_in_element(trianglez[i], node_col);

    Info * info = Info::createInfo();

    bool bricks_inserted = false;

    if (check_bricks)
    {
        bool all_elements_are_ok = true;

        vector <Geom_Element> bricks(4, Geom_Element(8));

        for (UINT m = 0; m < 4; m++)
            bricks[m].set_material_ID(material_ID);

        for (UINT i = 1; i <= elem_col.get_size(); i++)
        {
            meshing::get_4_bricks_from_15_tetrahedron(bricks, elem_col[i]);

            for (UINT j = 0; j < 4; j++)
            {
                if (!this_brick_is_fine(bricks[j], node_col))
                {
                    info->print_info_message("\n element number " + utos(i) + " has det less than zero");
                    all_elements_are_ok = false;
                }
                bricks_col.insert(bricks[j]);
            }
        }

        bricks_inserted = true;

        if (all_elements_are_ok)
            info->print_info_message("\n all elements are fine \n ");
    }

    if (print_volume_of_the_model)
    {
        double volume = 0.;

        vector <Geom_Element> bricks(4, Geom_Element(8));

        for (UINT m = 0; m < 4; m++)
            bricks[m].set_material_ID(material_ID);

        if (!bricks_inserted)
        for (UINT i = 1; i <= elem_col.get_size(); i++)
        {
            meshing::get_4_bricks_from_15_tetrahedron(bricks, elem_col[i]);

            for (UINT j = 0; j < 4; j++)
            {
                volume += get_brick_volume(bricks[j], node_col);
                bricks_col.insert(bricks[j]);
            }
        }

        if (bricks_inserted)
        for (UINT i = 1; i <= elem_col.get_size(); i++)
        {
            meshing::get_4_bricks_from_15_tetrahedron(bricks, elem_col[i]);

            for (UINT j = 0; j < 4; j++)
                volume += get_brick_volume(bricks[j], node_col);
        }
        bricks_inserted = true;

        info->print_info_message("model volume is " + dtos(volume));
    }

    if (!bricks_inserted)
    {
        vector <Geom_Element> bricks(4, Geom_Element(8));

        for (UINT m = 0; m < 4; m++)
            bricks[m].set_material_ID(material_ID);

        for (UINT i = 1; i <= elem_col.get_size(); i++)
        {
            meshing::get_4_bricks_from_15_tetrahedron(bricks, elem_col[i]);

            for (UINT j = 0; j < 4; j++)
                bricks_col.insert(bricks[j]);
        }
    }

    int nodes_per_elem = bricks_col[1].how_many_nodes_per_element();

    if (bricks_inserted)
    for (UINT i = 1; i <= bricks_col.get_size(); i++)
    for (int j = 1; j <= nodes_per_elem; j++)
    {
        if ((node_col[bricks_col[i].get_node(j)].get_boundary() &
        constants::IS_BOUNDARY_V) == constants::IS_BOUNDARY_V)
            bricks_col[i].set_boundary(1);

    }

//    timer->print_time_interval_in_seconds_from_start_to_now();

    return 0;
}

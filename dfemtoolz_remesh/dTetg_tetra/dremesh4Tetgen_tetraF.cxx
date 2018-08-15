
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

#include "dremesh4Tetgen_tetraF.h"

UINT dremesh4Tetgen_tetraF(Collection <Mesh_Node> & node_col, Collection <Geom_Element> & elem_col, int material_ID)
{

    string node_fileName = "input/input.1.node";
    string elem_fileName = "input/input.1.ele";

    Timer * timer = Timer::createTimer();
    timer->set_start_time();

    Tetgen_Reader * tetgen_reader = Tetgen_Reader::create_Tetgen_Reader();

    Collection <Geom_Element>  trianglez;

    tetgen_reader->read_node_file(node_col,    node_fileName);
    tetgen_reader->read_elem_file(elem_col, elem_fileName);

    UINT no_of_tetra_node_col = node_col.get_size();

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

    if (1)
    {
        bool all_elements_are_ok = true;
        double volume = 0., one_elem_volume = 0.;


        for (UINT i = 1; i <= elem_col.get_size(); i++)
        {
            one_elem_volume = get_tetra_volume(elem_col[i], node_col);
            if (one_elem_volume <= 0.)
            {
                info->print_info_message("\n element number " + utos(i) + " has zero or less volume");
                all_elements_are_ok = false;
            }

            volume += one_elem_volume;
        }

        info->print_info_message("model volume is " + dtos(volume));

        if (all_elements_are_ok)
            info->print_info_message("\n all elements are fine \n ");
    }

    timer->print_time_interval_in_seconds_from_start_to_now();

    return no_of_tetra_node_col;
}

UINT dremesh4Tetgen_tetraF_get_tetras(Collection <Mesh_Node> & node_col, Collection <Geom_Element> & tetras_col, int material_ID, string Tetgen_node_fileName, string Tetgen_elem_fileName)
{

    string node_fileName = Tetgen_node_fileName;
    string elem_fileName = Tetgen_elem_fileName;

//    Timer * timer = Timer::createTimer();
//    timer->set_start_time();

    Tetgen_Reader * tetgen_reader = Tetgen_Reader::create_Tetgen_Reader();

    Collection <Mesh_Node>  nodez;
    Collection <Geom_Element>  elem_col, trianglez;

    tetgen_reader->read_node_file(nodez,    node_fileName);
    tetgen_reader->read_elem_file(elem_col, elem_fileName);

    UINT no_of_tetra_node_col = nodez.get_size();

    meshing::create_15nodal_from_4nodal_tetrahedrons(nodez, trianglez, elem_col);

    {
        UINT zero = 0;
        for (UINT i = 1; i <= nodez.get_size(); i++)
            nodez[i].set_ID(zero);
    }

    for (UINT i = 1; i <= trianglez.get_size(); i++)
    if (nodez[trianglez[i].get_node(4)].get_flag())
        boundary_and_loads::set_velocity_boundary_marker_2_all_nodes_in_element(trianglez[i], nodez);

    Info * info = Info::createInfo();

    if (1)
    {
        bool all_elements_are_ok = true;
        double volume = 0., one_elem_volume = 0.;


        for (UINT i = 1; i <= elem_col.get_size(); i++)
        {
            one_elem_volume = get_tetra_volume(elem_col[i], nodez);
            if (one_elem_volume <= 0.)
            {
                info->print_info_message("\n element number " + utos(i) + " has zero or less volume");
                all_elements_are_ok = false;
            }

            volume += one_elem_volume;
        }

        info->print_info_message("model volume is " + dtos(volume));

        if (all_elements_are_ok)
            info->print_info_message("\n all elements are fine \n ");
    }

    {
        for (UINT i = 1; i <= no_of_tetra_node_col; i++)
            node_col.insert(nodez[i]);
    }

    {
        Geom_Element tetra(4);
        tetra.set_material_ID(material_ID);

        for (UINT i = 1; i <= elem_col.get_size(); i++)
        {
            for (UINT j = 1; j <= 4; j++)
            {
                if ((node_col[elem_col[i].get_node(j)].get_boundary() &
                constants::IS_BOUNDARY_V) == constants::IS_BOUNDARY_V)
                    tetra.set_boundary(1);
                tetra.set_node((elem_col[i].get_node(j)), j);
            }

            tetras_col.insert(tetra);
            tetra.set_boundary(0);
        }
    }

//    timer->print_time_interval_in_seconds_from_start_to_now();

    return no_of_tetra_node_col;
}

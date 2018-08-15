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

#include "dremesh4FemapF.h"

UINT dremesh4FemapF(Collection <Mesh_Node> & node_col, Collection <Geom_Element> & elem_col, bool inherit_boundary_and_loads, bool check_bricks, bool print_volume_of_the_model, int material_ID)
{
    string femap_fileName = "input/femap.dat";

    Timer * timer = Timer::createTimer();
    timer->set_start_time();

    Femap_Reader * femap_reader = Femap_Reader::create_Femap_Reader();

    Collection <Geom_Element> trianglez;

    if (!inherit_boundary_and_loads)
        femap_reader->read_file(15, node_col, elem_col, femap_fileName);
    if (inherit_boundary_and_loads)
        femap_reader->read_file_inherit_loads(15, node_col, elem_col, femap_fileName);

    UINT no_of_brick_elem_col = 0;
    UINT no_of_surface_facets = 0;

    no_of_brick_elem_col +=
    meshing::create_14nodal_from_6nodal_prisms_and_15nodal_from_4nodal_tetrahedrons_and_return_no_of_bricks(node_col, trianglez, elem_col);

    if (!inherit_boundary_and_loads)
    for (UINT i = 1; i <= trianglez.get_size(); i++)
    if (node_col[trianglez[i].get_node(4)].get_flag())
    {
        boundary_and_loads::set_velocity_boundary_marker_2_all_nodes_in_element(trianglez[i], node_col);
        no_of_surface_facets++;
    }

    if (inherit_boundary_and_loads)
    for (UINT i = 1; i <= trianglez.get_size(); i++)
    if (node_col[trianglez[i].get_node(4)].get_flag())
        boundary_and_loads::set_triangle_nodes_boundary_and_loads_pakf(trianglez[i], node_col);

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

UINT dremesh4FemapF_get_bricks(Collection <Mesh_Node> & node_col, Collection <Geom_Element> & bricks_col, bool inherit_boundary_and_loads, bool check_bricks, bool print_volume_of_the_model, int material_ID, string Femap_dat_fileName)
{
    string femap_fileName = Femap_dat_fileName;

//    Timer * timer = Timer::createTimer();
//    timer->set_start_time();

    Femap_Reader * femap_reader = Femap_Reader::create_Femap_Reader();

    Collection <Geom_Element> trianglez, elem_col;

    if (!inherit_boundary_and_loads)
        femap_reader->read_file(15, node_col, elem_col, femap_fileName);
    if (inherit_boundary_and_loads)
        femap_reader->read_file_inherit_loads(15, node_col, elem_col, femap_fileName);

    UINT no_of_brick_elem_col = 0;
    UINT no_of_surface_facets = 0;

    no_of_brick_elem_col +=
    meshing::create_14nodal_from_6nodal_prisms_and_15nodal_from_4nodal_tetrahedrons_and_return_no_of_bricks(node_col, trianglez, elem_col);

    if (!inherit_boundary_and_loads)
    for (UINT i = 1; i <= trianglez.get_size(); i++)
    if (node_col[trianglez[i].get_node(4)].get_flag())
    {
        boundary_and_loads::set_velocity_boundary_marker_2_all_nodes_in_element(trianglez[i], node_col);
        no_of_surface_facets++;
    }

    if (inherit_boundary_and_loads)
    for (UINT i = 1; i <= trianglez.get_size(); i++)
    if (node_col[trianglez[i].get_node(4)].get_flag())
        boundary_and_loads::set_triangle_nodes_boundary_and_loads_pakf(trianglez[i], node_col);

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
            int eletype = meshing::get_3_or_4_bricks_from_14_prism_or_15_tetrahedron(bricks, elem_col[i]);

            if (eletype == constants::PRISM)
            for (UINT j = 0; j < 3; j++)
            {
                if (!this_brick_is_fine(bricks[j], node_col))
                {
                    info->print_info_message("\n element number " + utos(i) + " has det less than zero");
                    all_elements_are_ok = false;
                }
                bricks_col.insert(bricks[j]);
            }

            if (eletype == constants::TETRA)
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
            int eletype = meshing::get_3_or_4_bricks_from_14_prism_or_15_tetrahedron(bricks, elem_col[i]);

            if (eletype == constants::PRISM)
            for (UINT j = 0; j < 3; j++)
            {
                volume += get_brick_volume(bricks[j], node_col);
                bricks_col.insert(bricks[j]);
            }

            if (eletype == constants::TETRA)
            for (UINT j = 0; j < 4; j++)
            {
                volume += get_brick_volume(bricks[j], node_col);
                bricks_col.insert(bricks[j]);
            }
        }

        if (bricks_inserted)
        for (UINT i = 1; i <= elem_col.get_size(); i++)
        {
            int eletype = meshing::get_3_or_4_bricks_from_14_prism_or_15_tetrahedron(bricks, elem_col[i]);

            if (eletype == constants::PRISM)
            for (UINT j = 0; j < 3; j++)
                volume += get_brick_volume(bricks[j], node_col);

            if (eletype == constants::TETRA)
            for (UINT j = 0; j < 4; j++)
                volume += get_brick_volume(bricks[j], node_col);
        }

        bricks_inserted = true;

        info->print_info_message("model volume is " + dtos(volume));
    }

    if (!print_volume_of_the_model)
    {
        vector <Geom_Element> bricks(4, Geom_Element(8));

        for (UINT m = 0; m < 4; m++)
            bricks[m].set_material_ID(material_ID);

        for (UINT i = 1; i <= elem_col.get_size(); i++)
        {
            int eletype = meshing::get_3_or_4_bricks_from_14_prism_or_15_tetrahedron(bricks, elem_col[i]);

            if (eletype == constants::PRISM)
            for (UINT j = 0; j < 3; j++)
                bricks_col.insert(bricks[j]);

            if (eletype == constants::TETRA)
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


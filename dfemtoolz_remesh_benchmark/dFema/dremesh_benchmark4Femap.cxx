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

#include "dremesh_benchmark4Femap.h"


int dremesh_benchmark4Femap(bool inherit_boundary_and_loads, bool print_pos_nodes, bool print_pos_elements, bool check_bricks, bool print_volume_of_the_model)
{
    string femap_fileName = "input/femap.dat";

    Timer * timer = Timer::createTimer();
    timer->set_start_time();

    Femap_Reader * femap_reader = Femap_Reader::create_Femap_Reader();

    Collection <Mesh_Node> nodez;
    Collection <Geom_Element>  elements, trianglez;

    if (!inherit_boundary_and_loads)
        femap_reader->read_file(15, nodez, elements, femap_fileName);
    if (inherit_boundary_and_loads)
        femap_reader->read_file_inherit_loads(15, nodez, elements, femap_fileName);

    UINT no_of_brick_elements = 0;
    UINT no_of_surface_facets = 0;

    no_of_brick_elements +=
    meshing::create_14nodal_from_6nodal_prisms_and_15nodal_from_4nodal_tetrahedrons_and_return_no_of_bricks(nodez, trianglez, elements);

    if (!inherit_boundary_and_loads)
    for (UINT i = 1; i <= trianglez.get_size(); i++)
    if (nodez[trianglez[i].get_node(4)].get_flag())
    {
        boundary_and_loads::set_velocity_boundary_marker_2_all_nodes_in_element(trianglez[i], nodez);
        no_of_surface_facets++;
    }

    if (inherit_boundary_and_loads)
    for (UINT i = 1; i <= trianglez.get_size(); i++)
    if (nodez[trianglez[i].get_node(4)].get_flag())
        boundary_and_loads::set_triangle_nodes_boundary_and_loads_pakf(trianglez[i], nodez);

    Info * info = Info::createInfo();

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

    timer->print_time_interval_in_seconds_from_start_to_now();

    info->print_info_message("printing files");

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

    info->print_info_message("----");
    info->print_info_message("Number of nodez in final mesh:       " +
    utos(nodez.get_size()));

    timer->print_time_interval_in_seconds_from_start_to_now();

    return 0;
}

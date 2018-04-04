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

#include "dMesh_Boundary_and_Loads.h"

namespace boundary_and_loads
{
    void set_triangle_nodes_boundary_and_loads
    (Geom_Element & triangle, Collection <Mesh_Node> & node_col)
    {
        if (!(bool)node_col[triangle.get_node(4)].get_boundary())
        node_col[triangle.get_node(4)].set_boundary(boundary_and_loads::get_boundary_and_loads_from_nodes(
        node_col[triangle.get_node(1)], node_col[triangle.get_node(2)], node_col[triangle.get_node(3)]));


        int j, k;
        for (int i = 1; i <= 3; i++)
        {
            j = i + 4;
            k = i + 1;
            if (k == 4) k = 1;

            if (!(bool)node_col[triangle.get_node(j)].get_boundary())
            node_col[triangle.get_node(j)].set_boundary(boundary_and_loads::get_boundary_and_loads_from_nodes(
            node_col[triangle.get_node(i)], node_col[triangle.get_node(k)]));
        }
    }

    void set_triangle_nodes_boundary_and_loads_pakf
    (Geom_Element & triangle, Collection <Mesh_Node> & node_col)
    {
        if (!(bool)node_col[triangle.get_node(4)].get_boundary())
        node_col[triangle.get_node(4)].set_boundary(boundary_and_loads::get_boundary_and_loads_from_nodes_pakf(
        node_col[triangle.get_node(1)], node_col[triangle.get_node(2)], node_col[triangle.get_node(3)]));


        int j, k;
        for (int i = 1; i <= 3; i++)
        {
            j = i + 4;
            k = i + 1;
            if (k == 4) k = 1;

            if (!(bool)node_col[triangle.get_node(j)].get_boundary())
            node_col[triangle.get_node(j)].set_boundary(boundary_and_loads::get_boundary_and_loads_from_nodes_pakf(
            node_col[triangle.get_node(i)], node_col[triangle.get_node(k)]));
        }
    }

    void set_quadrilateral_nodes_boundary_and_loads
    (Geom_Element & quad, Collection <Mesh_Node> & node_col)
    {
        if (!(bool)node_col[quad.get_node(5)].get_boundary())
        node_col[quad.get_node(5)].set_boundary(boundary_and_loads::get_boundary_and_loads_from_nodes(
        node_col[quad.get_node(1)], node_col[quad.get_node(2)],
        node_col[quad.get_node(3)], node_col[quad.get_node(4)]));

        int j, k;
        for (int i = 1; i <= 4; i++)
        {
            j = i + 5;
            k = i + 1;
            if (k == 5) k = 1;

            if (!(bool)node_col[quad.get_node(j)].get_boundary())
            node_col[quad.get_node(j)].set_boundary(boundary_and_loads::get_boundary_and_loads_from_nodes(
            node_col[quad.get_node(i)], node_col[quad.get_node(k)]));
        }
    }

    void set_quadrilateral_nodes_boundary_and_loads_pakf
    (Geom_Element & quad, Collection <Mesh_Node> & node_col)
    {
        if (!(bool)node_col[quad.get_node(5)].get_boundary())
        node_col[quad.get_node(5)].set_boundary(boundary_and_loads::get_boundary_and_loads_from_nodes_pakf(
        node_col[quad.get_node(1)], node_col[quad.get_node(2)],
        node_col[quad.get_node(3)], node_col[quad.get_node(4)]));

        int j, k;
        for (int i = 1; i <= 4; i++)
        {
            j = i + 5;
            k = i + 1;
            if (k == 5) k = 1;

            if (!(bool)node_col[quad.get_node(j)].get_boundary())
            node_col[quad.get_node(j)].set_boundary(boundary_and_loads::get_boundary_and_loads_from_nodes_pakf(
            node_col[quad.get_node(i)], node_col[quad.get_node(k)]));
        }
    }

    char get_boundary_and_loads_from_nodes
    (Mesh_Node & node1, Mesh_Node & node2, Mesh_Node & node3, Mesh_Node & node4)
    {
        return (node1.get_boundary() & node2.get_boundary() & node3.get_boundary() & node4.get_boundary());
    }

    char get_boundary_and_loads_from_nodes_pakf
    (Mesh_Node & node1, Mesh_Node & node2, Mesh_Node & node3, Mesh_Node & node4)
    {
        if (
        (node1.get_boundary() & constants::IS_ON_INLET) ||
        (node2.get_boundary() & constants::IS_ON_INLET) ||
        (node3.get_boundary() & constants::IS_ON_INLET) ||
        (node4.get_boundary() & constants::IS_ON_INLET))
        if (
        (((node1.get_boundary() & constants::IS_BOUNDARY_V) == constants::IS_BOUNDARY_V) || (node1.get_boundary() & constants::IS_ON_INLET)) &&
        (((node2.get_boundary() & constants::IS_BOUNDARY_V) == constants::IS_BOUNDARY_V) || (node2.get_boundary() & constants::IS_ON_INLET)) &&
        (((node3.get_boundary() & constants::IS_BOUNDARY_V) == constants::IS_BOUNDARY_V) || (node3.get_boundary() & constants::IS_ON_INLET)) &&
        (((node4.get_boundary() & constants::IS_BOUNDARY_V) == constants::IS_BOUNDARY_V) || (node4.get_boundary() & constants::IS_ON_INLET)))
            return constants::IS_ON_INLET;
        return (node1.get_boundary() & node2.get_boundary() & node3.get_boundary() & node4.get_boundary());
    }

    char get_boundary_and_loads_from_nodes
    (Mesh_Node & node1, Mesh_Node & node2, Mesh_Node & node3)
    {
        return (node1.get_boundary() & node2.get_boundary() & node3.get_boundary());
    }

    char get_boundary_and_loads_from_nodes_pakf
    (Mesh_Node & node1, Mesh_Node & node2, Mesh_Node & node3)
    {
        if (
        (node1.get_boundary() & constants::IS_ON_INLET) ||
        (node2.get_boundary() & constants::IS_ON_INLET) ||
        (node3.get_boundary() & constants::IS_ON_INLET))
        if (
        (((node1.get_boundary() & constants::IS_BOUNDARY_V) == constants::IS_BOUNDARY_V) || (node1.get_boundary() & constants::IS_ON_INLET)) &&
        (((node2.get_boundary() & constants::IS_BOUNDARY_V) == constants::IS_BOUNDARY_V) || (node2.get_boundary() & constants::IS_ON_INLET)) &&
        (((node3.get_boundary() & constants::IS_BOUNDARY_V) == constants::IS_BOUNDARY_V) || (node3.get_boundary() & constants::IS_ON_INLET)))
            return constants::IS_ON_INLET;
        return (node1.get_boundary() & node2.get_boundary() & node3.get_boundary());
    }

    char get_boundary_and_loads_from_nodes
    (Mesh_Node & node1, Mesh_Node & node2)
    {
        return (node1.get_boundary() & node2.get_boundary());
    }

    char get_boundary_and_loads_from_nodes_pakf
    (Mesh_Node & node1, Mesh_Node & node2)
    {
        if ((node2.get_boundary() & constants::IS_ON_INLET) || (node1.get_boundary() & constants::IS_ON_INLET))
        if (
        (((node1.get_boundary() & constants::IS_BOUNDARY_V) == constants::IS_BOUNDARY_V) || (node1.get_boundary() & constants::IS_ON_INLET)) &&
        (((node2.get_boundary() & constants::IS_BOUNDARY_V) == constants::IS_BOUNDARY_V) || (node2.get_boundary() & constants::IS_ON_INLET)))
            return constants::IS_ON_INLET;
        return (node1.get_boundary() & node2.get_boundary());
    }

    void set_velocity_boundary_marker_2_all_nodes_in_element
    (Geom_Element & one_element, Collection<Mesh_Node> & nodez)
    {
        for (int j = 1; j <= one_element.how_many_nodes_per_element(); j++)
            nodez[one_element.get_node(j)].set_boundary(constants::IS_BOUNDARY_V);
    }

    void set_this_boundary_marker_2_all_nodes_in_element
    (char bmarker, Geom_Element & one_element, Collection<Mesh_Node> & nodez)
    {
        for (int j = 1; j <= one_element.how_many_nodes_per_element(); j++)
            nodez[one_element.get_node(j)].set_boundary(bmarker);
    }

    void clear_velocity_boundary_marker_from_all_nodes_in_element
    (Geom_Element & one_element, Collection<Mesh_Node> & nodez)
    {
        for (int j = 1; j <= one_element.how_many_nodes_per_element(); j++)
            nodez[one_element.get_node(j)].clear_boundary(constants::IS_BOUNDARY_V);
    }
}

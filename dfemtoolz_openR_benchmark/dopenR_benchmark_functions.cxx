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

#include "dopenR_benchmark_functions.h"

Geom_Node find_initial_velocity_vector
(Mesh_Node & a, Mesh_Node & b, Mesh_Node & c, bool invert)
{
    Geom_Node first_vector, second_vector, resulting_vector;

    double temp, intensity, invert0r;

    if (invert) invert0r = -1;
    else invert0r = 1;

    first_vector  = get_vector_difference_vecA_minus_vecB(a, b);
    second_vector = get_vector_difference_vecA_minus_vecB(a, c);

    resulting_vector = cross_product(first_vector, second_vector);

    intensity = get_the_vector_intensity(resulting_vector);

    temp = invert0r * resulting_vector.get_coordinate_X() / intensity;
    resulting_vector.set_coordinate_X(temp);
    temp = invert0r * resulting_vector.get_coordinate_Y() / intensity;
    resulting_vector.set_coordinate_Y(temp);
    temp = invert0r * resulting_vector.get_coordinate_Z() / intensity;
    resulting_vector.set_coordinate_Z(temp);

    return resulting_vector;
}

void set_initial_velocity_to_nodes
(bool parabolic, Geom_Node & init_velocity_vector, Collection <Init_Node> & init_nodes)
{
    if (parabolic)
    {
        Mesh_Node inlet_pseudo_gravitycentR(get_gravitycenter(init_nodes));
        double
        R = get_max_distance_point_2_pointset(inlet_pseudo_gravitycentR, init_nodes),
        r, vel_dec_factor;

        for(UINT i = 1; i <= init_nodes.get_size(); i++)
        {
            r = get_lenght(inlet_pseudo_gravitycentR, init_nodes[i]);
            vel_dec_factor = 2 * (1 - ((r / R) * (r / R)));

            for (int j = 1; j <= 3; j++)
                init_nodes[i].initial_velocity.set_coordinate(vel_dec_factor * init_velocity_vector.get_coordinate(j), j);
        }
    }
    else
    {
        for(UINT i = 1; i <= init_nodes.get_size(); i++)
        for (int j = 1; j <= 3; j++)
            init_nodes[i].initial_velocity.set_coordinate(init_velocity_vector.get_coordinate(j), j);
    }
}

bool nodes_on_this_quad_are_on_positioned_plane
(Geom_Element & face, double plane_position, int planeID, double near_tol, Collection <Mesh_Node> & node_col)
{
    if (node_col[face.get_node(1)].get_coordinate(planeID) >= plane_position - near_tol)
    if (node_col[face.get_node(1)].get_coordinate(planeID) <= plane_position + near_tol)
    if (node_col[face.get_node(2)].get_coordinate(planeID) >= plane_position - near_tol)
    if (node_col[face.get_node(2)].get_coordinate(planeID) <= plane_position + near_tol)
    if (node_col[face.get_node(3)].get_coordinate(planeID) >= plane_position - near_tol)
    if (node_col[face.get_node(3)].get_coordinate(planeID) <= plane_position + near_tol)
    if (node_col[face.get_node(4)].get_coordinate(planeID) >= plane_position - near_tol)
    if (node_col[face.get_node(4)].get_coordinate(planeID) <= plane_position + near_tol)
        return true;

    return false;
}

bool nodes_on_this_quad_are_on_this_plane
(Geom_Plane & the_plane, Geom_Element & face, Collection <Mesh_Node> & node_col)
{
    if (
    the_plane.this_node_is_near_the_plane(node_col[face.get_node(1)]) &&
    the_plane.this_node_is_near_the_plane(node_col[face.get_node(2)]) &&
    the_plane.this_node_is_near_the_plane(node_col[face.get_node(3)]) &&
    the_plane.this_node_is_near_the_plane(node_col[face.get_node(4)]))
        return true;

    return false;
}

UINT neighbourz_flag_switchR
(Geom_Element & edge, Collection<Mesh_Node> & node_c)
{
    UINT all2neighbour_ID =
    neighbours::get_nodez_neighbour
    (node_c[edge.get_node(1)], node_c[edge.get_node(2)]);

    if (all2neighbour_ID != 0)
        node_c[all2neighbour_ID].set_flag();

    return all2neighbour_ID;
}

bool these_edges_are_same
(Geom_Element & edge1, Geom_Element & edge2)
{
    if (edge1.get_node(1) == edge2.get_node(1)
        &&
        edge1.get_node(2) == edge2.get_node(2))
        return true;
    if (edge1.get_node(2) == edge2.get_node(1)
        &&
        edge1.get_node(1) == edge2.get_node(2))
        return true;
    return false;
}

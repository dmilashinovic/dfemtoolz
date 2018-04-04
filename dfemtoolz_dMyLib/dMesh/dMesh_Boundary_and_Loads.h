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

/*
 * File:   dMesh_Boundary_and_Loads.h
 *
 *
 *
 *
 *
 */


#ifndef _DMESH_BOUNDARY_AND_LOADS_H
#define	_DMESH_BOUNDARY_AND_LOADS_H

#include "../dBase/dCollection.h"

#include "../dGeom/dGeom_Node.h"
#include "../dGeom/dGeom_Element.h"

#include "../dMesh/dMesh_Node.h"


namespace boundary_and_loads
{
    void set_triangle_nodes_boundary_and_loads
    (Geom_Element & triangle, Collection <Mesh_Node> & node_col);
    void set_triangle_nodes_boundary_and_loads_pakf
    (Geom_Element & triangle, Collection <Mesh_Node> & node_col);
    void set_quadrilateral_nodes_boundary_and_loads
    (Geom_Element & quad, Collection <Mesh_Node> & node_col);
    void set_quadrilateral_nodes_boundary_and_loads_pakf
    (Geom_Element & quad, Collection <Mesh_Node> & node_col);
    char get_boundary_and_loads_from_nodes
    (Mesh_Node & node1, Mesh_Node & node2, Mesh_Node & node3, Mesh_Node & node4);
    char get_boundary_and_loads_from_nodes_pakf
    (Mesh_Node & node1, Mesh_Node & node2, Mesh_Node & node3, Mesh_Node & node4);
    char get_boundary_and_loads_from_nodes
    (Mesh_Node & node1, Mesh_Node & node2, Mesh_Node & node3);
    char get_boundary_and_loads_from_nodes_pakf
    (Mesh_Node & node1, Mesh_Node & node2, Mesh_Node & node3);
    char get_boundary_and_loads_from_nodes
    (Mesh_Node & node1, Mesh_Node & node2);
    char get_boundary_and_loads_from_nodes_pakf
    (Mesh_Node & node1, Mesh_Node & node2);

    void set_velocity_boundary_marker_2_all_nodes_in_element
    (Geom_Element & one_element, Collection<Mesh_Node> & nodez);
    void set_this_boundary_marker_2_all_nodes_in_element
    (char bmarker, Geom_Element & one_element, Collection<Mesh_Node> & nodez);
    void clear_velocity_boundary_marker_from_all_nodes_in_element
    (Geom_Element & one_element, Collection<Mesh_Node> & nodez);
}

#endif	/* _DMESH_BOUNDARY_AND_LOADS_H */



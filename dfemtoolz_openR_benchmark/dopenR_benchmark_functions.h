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
 * File:   dopenR_benchmark_functions.h
 *
 *
 *
 *
 *
 */


#ifndef _OPENR_FUNCTIONS_H
#define	_OPENR_FUNCTIONS_H


#include "../dfemtoolz_dMyLib/dfemtoolz_dMyLib.h"

#include "../dfemtoolz_dMyLib/dBase/dCollection.h"
#include "../dfemtoolz_dMyLib/dBase/dConstants.h"

#include "../dfemtoolz_dMyLib/dGeom/dGeom_Node.h"
#include "../dfemtoolz_dMyLib/dGeom/dGeom_Plane.h"
#include "../dfemtoolz_dMyLib/dGeom/dGeom_Element.h"
#include "../dfemtoolz_dMyLib/dGeom/dGeom_Functions.h"
#include "../dfemtoolz_dMyLib/dGeom/dGeom_TFunctions.h"

#include "../dfemtoolz_dMyLib/dMesh/dMesh_Node.h"
#include "../dfemtoolz_dMyLib/dMesh/dMesh_Neighbours.h"

#include "../dfemtoolz_dMyLib/dInit/dInit_Node.h"


Geom_Node find_initial_velocity_vector
(Mesh_Node & a, Mesh_Node & b, Mesh_Node & c, bool invert);

void set_initial_velocity_to_nodes
(bool parabolic, Geom_Node & init_velocity_vector, Collection <Init_Node> & init_nodes);

bool nodes_on_this_quad_are_on_positioned_plane
(Geom_Element & face, double plane_position, int planeID, double near_tol, Collection <Mesh_Node> & node_col);

bool nodes_on_this_quad_are_on_this_plane
(Geom_Plane & the_plane, Geom_Element & face, Collection <Mesh_Node> & node_col);

UINT neighbourz_flag_switchR
(Geom_Element & edge, Collection<Mesh_Node> & node_c);

bool these_edges_are_same
(Geom_Element & edge1, Geom_Element & edge2);

#endif	/* _OPENR_FUNCTIONS_H */


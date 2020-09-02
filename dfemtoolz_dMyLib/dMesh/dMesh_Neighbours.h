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
 * File:   dMesh_Neighbours.h
 *
 *
 *
 *
 *
 */

#ifndef _DMESH_NEIGHBOURS_H
#define	_DMESH_NEIGHBOURS_H

#include "../dfemtoolz_dMyLib.h"

#include "../dBase/dCollection.h"

#include "../dGeom/dGeom_Element.h"
#include "../dGeom/dGeom_Functions.h"

#include "../dMesh/dMesh_Node.h"

#include "../dMisc/dMisc_Functionz.h"

namespace neighbours
{
    UINT get_nodez_neighbour(Mesh_Node & node1, Mesh_Node & node2, Mesh_Node & node3, Mesh_Node & node4);
    UINT get_nodez_neighbour(Mesh_Node & node1, Mesh_Node & node2, Mesh_Node & node3);
    UINT get_nodez_neighbour(Mesh_Node & node1, Mesh_Node & node2);


    void create_facetz_add_facet_cogz_2_tetra
    (Geom_Element & tetra, Collection<Geom_Element> & facetz, Collection<Mesh_Node> & node_col);

    void create_facetz_add_facet_cogz_2_tetra_simple
    (Geom_Element & tetra, Collection<Geom_Element> & facetz, Collection<Mesh_Node> & node_col);

    void create_facetz_add_facet_cogz_2_brick
    (Geom_Element & brick, Collection<Geom_Element> & facetz, Collection<Mesh_Node> & node_col);

    void create_facetz_add_facet_cogz_2_prism
    (Geom_Element & prism, Collection<Geom_Element> & facetz, Collection<Mesh_Node> & node_col);

    UINT calculate_face_cog_and_add_neighbourz
    (Geom_Element & triangle, Collection<Mesh_Node> & node_c);

    UINT calculate_triangle_cog_and_add_neighbourz
    (Geom_Element & triangle, Collection<Mesh_Node> & node_c);

    UINT calculate_edge_cog_and_add_neighbourz
    (Geom_Element & edge, Collection<Mesh_Node> & node_c);

    UINT calculate_edge_cog_and_add_neighbourz
    (UINT & nodeA, UINT & nodeB, Collection<Mesh_Node> & node_c);

    UINT calculate_quadrilateral_cog_and_add_neighbourz
    (Geom_Element & quad, Collection<Mesh_Node> & node_c);
}

#endif	/* _DMESH_NEIGHBOURS_H */



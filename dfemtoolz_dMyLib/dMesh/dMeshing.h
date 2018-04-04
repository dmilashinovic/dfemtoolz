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
 * File:   dMeshing.h
 *
 *
 *
 *
 *
 */


#ifndef _DMESHING_H
#define	_DMESHING_H


#include "../dfemtoolz_dMyLib.h"

#include "../dBase/dConstants.h"
#include "../dBase/dCollection.h"

#include "../dGeom/dGeom_Element.h"
#include "../dGeom/dGeom_Functions.h"
#include "../dGeom/dGeom_TFunctions.h"

#include "../dMesh/dMesh_Node.h"

#include "../dMisc/dMisc_Functionz.h"
#include "../dMisc/dPercent.h"

#include "../dPrin/dInfo.h"

#include "dMesh_Neighbours.h"

namespace meshing
{
    void create_27nodal_from_8nodal_bricks
    (Collection <Mesh_Node> & node_col, Collection <Geom_Element> & face_col, Collection <Geom_Element> & elem_col);
    Geom_Element create_face9
    (UINT n1, UINT n2, UINT n3, UINT n4, Collection <Mesh_Node> & node_col);
    void create_15nodal_from_4nodal_tetrahedrons
    (Collection <Mesh_Node> & node_col, Collection <Geom_Element> & face_col, Collection <Geom_Element> & elem_col);
    void create_15nodal_from_10nodal_tetrahedrons
    (Collection <Mesh_Node> & node_col, Collection <Geom_Element> & face_col, Collection <Geom_Element> & elem_col);
    UINT create_14nodal_from_6nodal_prisms_and_15nodal_from_4nodal_tetrahedrons_and_return_no_of_bricks
    (Collection <Mesh_Node> & node_col, Collection <Geom_Element> & face_col, Collection <Geom_Element> & elem_col);

    void get_8_bricks_from_27_brick
    (vector <Geom_Element> & eight_bricks, Geom_Element & brick);
    void get_4_bricks_from_15_tetrahedron
    (vector <Geom_Element> & four_bricks, Geom_Element & tetrahedron);
    void get_3_bricks_from_14_prism
    (vector <Geom_Element> & three_bricks, Geom_Element & prism);

    void get_6_quads_from_8_brick
    (vector <Geom_Element> & six_quads, Geom_Element & brick);
}

#endif	/* _DMESHING_H */


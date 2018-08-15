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
 * File:   dmultimaterial_functions.h
 *
 *
 *
 *
 *
 */


#ifndef _MULTIMATERIAL_FUNCTIONS_H
#define	_MULTIMATERIAL_FUNCTIONS_H


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


bool put_contact_edges(
UINT elementID,
Collection <Mesh_Node> & nodez_col,
Geom_Element & one_brick_element,
Collection <Geom_Element> & contact_faces_col,
UINT & current_no_of_contact_surfaces);

#endif	/* _MULTIMATERIAL_FUNCTIONS_H */


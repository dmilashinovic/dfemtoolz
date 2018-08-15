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
 * File:   dremesh_PrismSplit.h
 *
 *
 *
 *
 *
 */

#ifndef _DREMESH4FEMAPF_H
#define	_DREMESH4FEMAPF_H

#include "../../dfemtoolz_dMyLib/dfemtoolz_dMyLib.h"

#include "../../dfemtoolz_dMyLib/dBase/dCollection.h"
#include "../../dfemtoolz_dMyLib/dBase/dConstants.h"

#include "../../dfemtoolz_dMyLib/dGeom/dGeom_Element.h"
#include "../../dfemtoolz_dMyLib/dGeom/dGeom_Functions.h"

#include "../../dfemtoolz_dMyLib/dMesh/dMesh_Neighbours.h"
#include "../../dfemtoolz_dMyLib/dMesh/dMeshing.h"
#include "../../dfemtoolz_dMyLib/dMesh/dTMeshing.h"
#include "../../dfemtoolz_dMyLib/dMesh/dMesh_Boundary_and_Loads.h"
#include "../../dfemtoolz_dMyLib/dMesh/dMesh_Node.h"

#include "../../dfemtoolz_dMyLib/dMisc/dTimer.h"
#include "../../dfemtoolz_dMyLib/dMisc/dMisc_Functionz.h"

#include "../../dfemtoolz_dMyLib/dPrin/dPrinting.h"
#include "../../dfemtoolz_dMyLib/dPrin/dPOS_Printer.h"
#include "../../dfemtoolz_dMyLib/dPrin/dSLI_Printer.h"
#include "../../dfemtoolz_dMyLib/dPrin/dInfo.h"

#include "../../dfemtoolz_dMyLib/dRead/dFemap_Reader.h"

#include "dremesh4FemapF.h"

UINT dremesh4FemapF(Collection <Mesh_Node> & node_col, Collection <Geom_Element> & elem_col, bool inherit_boundary_and_loads, bool check_bricks, bool print_volume_of_the_model, int material_ID);
UINT dremesh4FemapF_get_bricks(Collection <Mesh_Node> & node_col, Collection <Geom_Element> & bricks_col, bool inherit_boundary_and_loads, bool check_bricks, bool print_volume_of_the_model, int material_ID, string Femap_dat_fileName);

#endif	/* _DREMESH4FEMAPF_H */



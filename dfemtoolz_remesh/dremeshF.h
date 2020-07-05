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
 * File:   dremesh.h
 *
 *
 *
 *
 *
 */

#ifndef _REMESHF_H
#define	_REMESHF_H

#include "../dfemtoolz_dMyLib/dPrin/dInfo.h"

#include "../dfemtoolz_dMyLib/dMisc/dMisc_Functionz.h"


#include "dFema/dremesh4Femap.h"
#include "dTetg/dremesh4Tetgen.h"
#include "dTetg_tetra/dremesh4Tetgen_tetra.h"

/// #include "dFema/dremesh4Femap.h"
#include "dTetg/dremesh4TetgenF.h"
#include "dTetg_tetra/dremesh4Tetgen_tetraF.h"

#include "dremesh_parameters.h"


int dremesh_get_elems
(Collection <Mesh_Node> & nodes_collection,
Collection <Geom_Element>  & elements_collection,
string Tetgen_node_fileName, string Tetgen_elem_fileName, string Femap_dat_fileName);

int dremesh_get_elemsF(
int mesh_element_type,
Collection <Mesh_Node> & nodes_collection,
Collection <Geom_Element>  & elements_collection,
string Tetgen_node_fileName,
string Tetgen_elem_fileName,
string Femap_dat_fileName);


#endif	/* _REMESHF_H */



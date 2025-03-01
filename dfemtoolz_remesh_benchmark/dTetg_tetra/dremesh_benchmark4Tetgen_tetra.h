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
 * File:   d4Tetgen.h
 *
 *
 *
 *
 *
 */

#ifndef _D4TETGEN_TETRA_H
#define	_D4TETGEN_TETRA_H

#include "../../dfemtoolz_dMyLib/dfemtoolz_dMyLib.h"

#include "../../dfemtoolz_dMyLib/dBase/dCollection.h"
#include "../../dfemtoolz_dMyLib/dBase/dConstants.h"

#include "../../dfemtoolz_dMyLib/dGeom/dGeom_Element.h"
#include "../../dfemtoolz_dMyLib/dGeom/dGeom_Functions.h"

#include "../../dfemtoolz_dMyLib/dMesh/dMesh_Neighbours.h"
#include "../../dfemtoolz_dMyLib/dMesh/dMeshing.h"
#include "../../dfemtoolz_dMyLib/dMesh/dMesh_Boundary_and_Loads.h"
#include "../../dfemtoolz_dMyLib/dMesh/dMesh_Node.h"

#include "../../dfemtoolz_dMyLib/dMisc/dTimer.h"
#include "../../dfemtoolz_dMyLib/dMisc/dMisc_Functionz.h"

#include "../../dfemtoolz_dMyLib/dPrin/dPrinting.h"
#include "../../dfemtoolz_dMyLib/dPrin/dPOS_Printer.h"
#include "../../dfemtoolz_dMyLib/dPrin/dSLI_Printer.h"
#include "../../dfemtoolz_dMyLib/dPrin/dInfo.h"

#include "../../dfemtoolz_dMyLib/dRead/dTetgen_Reader.h"


int dremesh_benchmark4Tetgen_tetra(bool print_pos_nodes, bool print_pos_elements);

#endif	/* _D4TETGEN_TETRA_H */


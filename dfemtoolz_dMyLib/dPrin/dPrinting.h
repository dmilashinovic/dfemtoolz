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
 * File:   dPrinting.h
 *
 *
 *
 *
 *
 */

#ifndef _DPRINTING_H
#define	_DPRINTING_H

#include "../dfemtoolz_dMyLib.h"

#include "../dBase/dCollection.h"
#include "../dBase/dConstants.h"

#include "../dGeom/dGeom_Node.h"
#include "../dGeom/dGeom_Element.h"
#include "../dGeom/dGeom_Functions.h"

#include "../dMisc/dMisc_Functionz.h"

#include <fstream>


namespace printing
{
    void print_triangle_into_stl
    (Geom_Node & node1, Geom_Node & node2, Geom_Node & node3, fstream & stl_file);

    void print_triangle_into_stl
    (Geom_Node & node1, Geom_Node & node2, Geom_Node & node3, ofstream & stl_file);
}

#endif	/* _DPRINTING_H */



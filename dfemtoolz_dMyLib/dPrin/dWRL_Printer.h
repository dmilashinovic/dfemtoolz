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
 * File:   dWRL_Printer.h
 *
 *
 *
 *
 *
 */

#ifndef _DWRL_PRINTER_H
#define	_DWRL_PRINTER_H

#include "../dfemtoolz_dMyLib.h"

#include "../dBase/dCollection.h"
#include "../dBase/dConstants.h"

#include "../dMisc/dSTL_Triangle.h"

#include <fstream>

#include "dInfo.h"


class WRL_Printer
{
private:
    static WRL_Printer * m_pWRL_PrinterSingleton;

    void print_stl_triangle_nodes_to_wrl_file
    (STL_Triangle & triangle, ofstream & wrl_file);


protected:
    WRL_Printer();

public:

    void print_stl_triangles_to_wrl_file
    (Collection <STL_Triangle> & triangle_col, string path_and_fileName);

    static WRL_Printer * create_WRL_Printer();
    ~WRL_Printer();
};



#endif	/* _DWRL_PRINTER_H */

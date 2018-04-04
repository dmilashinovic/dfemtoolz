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
 * File:   dremesh_parameters.h
 *
 *
 *
 *
 *
 */

#ifndef _REMESH_PARAMETERS_H
#define	_REMESH_PARAMETERS_H

#include "../dfemtoolz_dMyLib/dfemtoolz_dMyLib.h"

#include "../dfemtoolz_dMyLib/dBase/dConstants.h"

#include "../dfemtoolz_dMyLib/dPrin/dInfo.h"

#include "../dfemtoolz_dMyLib/dRead/dReading.h"


class dremesh_Parameters
{
private:
    static dremesh_Parameters * m_pdremesh_ParametersSingleton;
    string m_sPath_and_FileName;

protected:
    dremesh_Parameters();

public:

    int submodule;
    bool inheritBoundary;
    bool print_pos_nodes;
    bool print_pos_elements;
    bool chekAllBrickElements;
    bool calculateVolumeOfTheModel;


    bool read_file();

    static dremesh_Parameters * create_dremesh_Parameters();
    ~dremesh_Parameters();
};




#endif	/* _REMESH_PARAMETERS_H */



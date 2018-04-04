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
 *
 * File:   dnolimit_parameters.h
 *
 *
 *
 *
 *
 */

#ifndef _NOLIMIT_PARAMETERS_H
#define	_NOLIMIT_PARAMETERS_H

#include "../dfemtoolz_dMyLib/dfemtoolz_dMyLib.h"

#include "../dfemtoolz_dMyLib/dBase/dConstants.h"

#include "../dfemtoolz_dMyLib/dPrin/dInfo.h"

#include "../dfemtoolz_dMyLib/dRead/dReading.h"

class nolimit_Parameters
{
private:
    static nolimit_Parameters * m_pnolimit_ParametersSingleton;
    string m_sPath_and_FileName;

protected:
    nolimit_Parameters();

public:

    bool   calculate_surface;
    bool   print_pos_nodes;
    bool   print_pos_elements;
    double scale_facX;
    double scale_facY;
    double scale_facZ;
    bool   clear_previous_boundary;
    bool   chek_all_elements;
    bool   calculate_volume_of_the_model;
    int    dat_or_sli_input;

    bool read_file();

    static nolimit_Parameters * create_nolimit_Parameters();
    ~nolimit_Parameters();
};




#endif	/* _NOLIMIT_PARAMETERS_H */



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
 * File:   dReading.h
 *
 *
 *
 *
 *
 */


#ifndef _DREADING_H
#define	_DREADING_H

#include "../dfemtoolz_dMyLib.h"

#include "../dBase/dError.h"
#include "../dBase/dConstants.h"

#include "../dMisc/dMisc_Functionz.h"

#include <fstream>

namespace reading
{

    bool check_if_block_reading_is_ok(char line_read[]);
    bool check_if_file_is_not_open(ifstream & file, string fileName);
    bool check_if_file_is_not_open_wo_using_cout(ifstream & file, string fileName);
    bool go_to_line_that_contains_this_string(string string_in_line, ifstream & file);
    bool get_line_that_contains_this_string_and_close_the_file(char the_line[], string string_in_line, string filename);

}

#endif	/* _DREADING_H */



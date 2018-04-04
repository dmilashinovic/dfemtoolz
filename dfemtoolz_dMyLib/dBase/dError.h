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
 * File:   dError.h
 *
 *
 *
 *
 *
 */

#ifndef _DERROR_H
#define	_DERROR_H

#include "../dfemtoolz_dMyLib.h"

class Error
{
private:
    static Error * m_pErrorSingleton;

protected:
    Error();

public:
    static bool m_bError;

    void print_error(string & error);
    void can_not_find_file(string file_path_and_name);

    static Error * errorExists();
    ~Error();
};

#endif	/* _DERROR_H */

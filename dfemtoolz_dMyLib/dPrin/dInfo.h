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
 * File:   dInfo.h
 *
 *
 *
 *
 *
 */

#ifndef _INFO_H
#define	_INFO_H

#include "../dfemtoolz_dMyLib.h"
#include <time.h>

class Info
{
private:
    static Info * m_pInfoSingleton;

protected:
    Info();

public:
    static bool m_bInfoHeader;

    void print_info_message(string message);
    void print_info_message_no_newline(string message);
    void newline();
    void print_software_header(string header, UINT year, UINT build = 100000);
    void print_software_footer();

    static Info * createInfo();

    ~Info();
};

#endif	/* _INFO_H */




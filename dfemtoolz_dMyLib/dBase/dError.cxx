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

#include "dError.h"

bool Error::m_bError = false;
Error::Error()
{
    cout << " \n\n     oups!\n";
}
Error * Error::m_pErrorSingleton = 0;
Error * Error::errorExists()
{
    if (m_pErrorSingleton == 0)
	m_pErrorSingleton = new Error;
    return m_pErrorSingleton;
}

Error::~Error()
{
}

void Error::print_error(string & error)
{
    if (!m_bError)
        cout << "  error found \n  " <<
        error << endl;
}

void Error::can_not_find_file(string file_path_and_name)
{
    if (!m_bError)
        cout << "  can not find file:\n  " <<
        file_path_and_name.c_str() << endl;
}

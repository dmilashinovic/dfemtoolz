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

#include "dSTL_Triangle.h"

void STL_Triangle::set_ID(UINT & ID)
{
    m_uID = ID;
}

UINT STL_Triangle::get_ID()
{
    return m_uID;
}

STL_Triangle &STL_Triangle::operator =(const STL_Triangle &otherSTL_Triangle)
{
    m_uID = otherSTL_Triangle.m_uID;

    node1 = otherSTL_Triangle.node1;
    node2 = otherSTL_Triangle.node2;
    node3 = otherSTL_Triangle.node3;

    return (*this );
}


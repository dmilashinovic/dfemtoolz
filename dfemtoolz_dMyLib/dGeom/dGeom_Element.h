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
 * File:   dGeom_Element.h
 *
 *
 *
 *
 *
 */

#ifndef _DGEOM_ELEMENT_H
#define	_DGEOM_ELEMENT_H

#include "../dfemtoolz_dMyLib.h"

class Geom_Element
{
protected:
    UINT m_uID;
    int m_iNodesPerElement;
    bool m_bBoundary;
    bool m_bFlag;
    UINT * m_pNode;
    int m_iMaterialID;

public:
    int how_many_nodes_per_element();
    void set_nodes_per_element(int no_of_nodes_per_element);

    void set_ID(UINT ID);
    UINT get_ID();

    void set_node(UINT node, int node_position);
    UINT & get_node(int node_position);

    void set_boundary();
    void set_boundary(bool boundary);
    bool get_boundary();

    void set_flag();
    void set_flag(bool flag);
    bool get_flag();

    void set_material_ID(int materialID);
    int get_material_ID();

    Geom_Element & operator =(const Geom_Element &otherGeom_Element);

    Geom_Element();
    Geom_Element(int nodes_per_element);
    Geom_Element(const Geom_Element & element);

    ~Geom_Element();
};

#endif	/* _DGEOM_ELEMENT_H */

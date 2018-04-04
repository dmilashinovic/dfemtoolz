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
 * File:   dPost_Node.h
 *
 *
 *
 *
 *
 */


#ifndef _DPOST_NODE_H
#define	_DPOST_NODE_H

#include "../dGeom/dGeom_Node.h"

class Post_Node : public Geom_Node
{
private:
    UINT m_uID;
    char m_cBoundary;
    double m_dScalar;
    bool m_bFlag;

public:
    void set_ID(UINT & ID);
    UINT get_ID();

    void set_flag();
    void set_flag(bool flag);
    bool get_flag();

    void set_boundary(char boundary);
    void clear_boundary(char boundary);
    void clear_boundary();
    char get_boundary() const;

    void   set_scalar_physical_quantity(double & quantity);
    double get_scalar_physical_quantity();

    Geom_Node vector_physical_quantity;

    Post_Node & operator =(const Post_Node &otherPost_Node);

    Post_Node();
    Post_Node(const Geom_Node & node);
    Post_Node(const Post_Node & node);
    ~Post_Node();
};



#endif	/* _DPOST_NODE_H */



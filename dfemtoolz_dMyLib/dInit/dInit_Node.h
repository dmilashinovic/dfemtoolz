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
 * File:   dInit_Node.h
 *
 *
 *
 *
 *
 */

#ifndef _DINIT_NODE_H
#define	_DINIT_NODE_H

#include "../dMesh/dMesh_Node.h"


class Init_Node : public Mesh_Node
{
private:
    bool m_bVelocityIsSet;
    UINT m_uTimeFunction;

public:
    Geom_Node initial_velocity;

    void set_velocity_switch(bool velocity_is_set);
    bool get_velocity_switch();

    void set_time_function(UINT time_function);
    UINT get_time_function();

    void get_data_from_this_node(Mesh_Node & node);

    Init_Node & operator =(const Init_Node & otherInit_Node);
    Init_Node & operator =(const Mesh_Node & otherMesh_Node);

    Init_Node();
    Init_Node(const Mesh_Node & node);
    Init_Node(const Init_Node & node);
    ~Init_Node();
};



#endif	/* _DINIT_NODE_H */




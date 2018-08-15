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
 * File:   dMesh_Node.h
 *
 *
 *
 *
 *
 */

#ifndef _DMESH_NODE_H
#define	_DMESH_NODE_H

#include "../dBase/dCollection.h"
#include "../dBase/dConstants.h"

#include "../dGeom/dGeom_Node.h"


class Mesh_Node : public Geom_Node
{
protected:
    UINT m_uID;

    bool m_bFlag;
    char m_cBoundary;

    Collection <UINT> m_collNeighbourNodes;

public:
    void set_ID(UINT & ID);
    UINT get_ID() const;

    void set_flag();
    void set_flag(bool flag);
    bool get_flag() const;

    void set_boundary(char boundary);
    void clear_boundary(char boundary);
    void clear_boundary();
    char get_boundary() const;
    bool is_velocity_boundary();

    void add_neighbour_node(UINT nodeID);
    UINT get_neighbour_node(UINT & neighbour_node);
    UINT how_many_neighbours();
    void clear_all_neighbours();

    Mesh_Node & operator =(const Mesh_Node &otherMesh_Node);

    Mesh_Node();
    Mesh_Node(const Geom_Node & node);
    Mesh_Node(const Mesh_Node & node);
    ~Mesh_Node();
};



#endif	/* _DMESH_NODE_H */



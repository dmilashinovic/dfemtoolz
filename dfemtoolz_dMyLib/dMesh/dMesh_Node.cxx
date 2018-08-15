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

#include "dMesh_Node.h"

Mesh_Node::Mesh_Node()
{
    m_cBoundary = 0;
    m_bFlag = 0;
    m_uID = 0;
}

Mesh_Node::Mesh_Node(const Geom_Node & node)
{
    for (int i = 1; i <= 3; i++)
        m_dCoordinates[i-1] = node.get_coordinate(i);

    m_cBoundary = 0;
    m_bFlag = 0;
}

Mesh_Node::Mesh_Node(const Mesh_Node & node):
m_uID(node.m_uID),
m_bFlag(node.m_bFlag),
m_cBoundary(node.m_cBoundary)
{
    for (int i = 1; i <= 3; i++)
        this->set_coordinate(node.get_coordinate(i), i);
    m_collNeighbourNodes = node.m_collNeighbourNodes;
}

Mesh_Node::~Mesh_Node()
{}

UINT Mesh_Node::get_ID() const
{
    return m_uID;
}

void Mesh_Node::set_ID(UINT & ID)
{
    m_uID = ID;
}

void Mesh_Node::set_flag()
{
    m_bFlag = !m_bFlag;
}

void Mesh_Node::set_flag(bool flag)
{
    m_bFlag = flag;
}

bool Mesh_Node::get_flag() const
{
    return m_bFlag;
}

void Mesh_Node::set_boundary(char boundary)
{
    m_cBoundary = m_cBoundary | boundary;
}

void Mesh_Node::clear_boundary(char boundary)
{
    boundary = ~boundary;
    m_cBoundary = m_cBoundary & boundary;
}

void Mesh_Node::clear_boundary()
{
    m_cBoundary = 0;
}

char Mesh_Node::get_boundary() const
{
    return m_cBoundary;
}

bool Mesh_Node::is_velocity_boundary()
{
    if (m_cBoundary & constants::IS_BOUNDARY_VX)
    if (m_cBoundary & constants::IS_BOUNDARY_VY)
    if (m_cBoundary & constants::IS_BOUNDARY_VZ)
        return true;
    return false;
}

void Mesh_Node::add_neighbour_node(UINT nodeID)
{
    m_collNeighbourNodes.insert(nodeID);
}

UINT Mesh_Node::get_neighbour_node(UINT & neighbour_node)
{
    return m_collNeighbourNodes[neighbour_node];
}

UINT Mesh_Node::how_many_neighbours()
{
    return m_collNeighbourNodes.get_size();
}

void Mesh_Node::clear_all_neighbours()
{
    m_collNeighbourNodes.clear_collection();
}

Mesh_Node &Mesh_Node::operator =(const Mesh_Node &otherMesh_Node)
{
    m_uID = otherMesh_Node.m_uID;

    for (int i = 1; i <= 3; i++)
        this->set_coordinate(otherMesh_Node.get_coordinate(i), i);

    m_bFlag = otherMesh_Node.m_bFlag;
    m_cBoundary = otherMesh_Node.m_cBoundary;

    m_collNeighbourNodes = otherMesh_Node.m_collNeighbourNodes;

    return (*this);
}

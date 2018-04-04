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

#include "dPost_Node.h"

void Post_Node::set_ID(UINT & ID)
{
    m_uID = ID;
}

UINT Post_Node::get_ID()
{
    return m_uID;
}

void Post_Node::set_flag()
{
    m_bFlag = !m_bFlag;
}

void Post_Node::set_flag(bool flag)
{
    m_bFlag = flag;
}

bool Post_Node::get_flag()
{
    return m_bFlag;
}

void Post_Node::set_boundary(char boundary)
{
    m_cBoundary = m_cBoundary | boundary;
}

void Post_Node::clear_boundary(char boundary)
{
    boundary = ~boundary;
    m_cBoundary = m_cBoundary & boundary;
}

void Post_Node::clear_boundary()
{
    m_cBoundary = 0;
}

char Post_Node::get_boundary() const
{
    return m_cBoundary;
}

void Post_Node::set_scalar_physical_quantity(double & quantity)
{
    m_dScalar = quantity;
}

double Post_Node::get_scalar_physical_quantity()
{
    return m_dScalar;
}

Post_Node::Post_Node()
{
    m_uID = 0;
    m_cBoundary = 0;
    m_dScalar = 0;
    m_bFlag = false;
}

Post_Node::Post_Node(const Geom_Node & node)
{
    for (int i = 1; i <= 3; i++)
        m_dCoordinates[i-1] = node.get_coordinate(i);

    m_uID = 0;
    m_cBoundary = 0;
    m_dScalar = 0;
    m_bFlag = false;
}

Post_Node::Post_Node(const Post_Node & node):
m_uID(node.m_uID),
m_cBoundary(node.m_cBoundary),
m_dScalar(node.m_dScalar)
{
    for (int i = 1; i <= 3; i++)
        this->set_coordinate(node.get_coordinate(i), i);

    vector_physical_quantity = node.vector_physical_quantity;
    m_bFlag = node.m_bFlag;
}

Post_Node::~Post_Node()
{}

Post_Node &Post_Node::operator =(const Post_Node &otherPost_Node)
{
    m_uID = otherPost_Node.m_uID;
    m_cBoundary = otherPost_Node.m_cBoundary;
    m_dScalar = otherPost_Node.m_dScalar;

    vector_physical_quantity = otherPost_Node.vector_physical_quantity;

    for (int i = 1; i <= 3; i++)
        this->set_coordinate(otherPost_Node.get_coordinate(i), i);

    m_bFlag = otherPost_Node.m_bFlag;

    return (*this);
}


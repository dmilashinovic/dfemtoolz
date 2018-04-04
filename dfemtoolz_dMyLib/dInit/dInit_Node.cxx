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

#include "dInit_Node.h"

bool Init_Node::get_velocity_switch()
{
    return m_bVelocityIsSet;
}

void Init_Node::set_velocity_switch(bool velocity_is_set)
{
    m_bVelocityIsSet = velocity_is_set;
}

void Init_Node::set_time_function(UINT time_function)
{
    m_uTimeFunction = time_function;
}

UINT Init_Node::get_time_function()
{
    return m_uTimeFunction;
}

Init_Node &Init_Node::operator =(const Init_Node & otherInit_Node)
{
    m_uID = otherInit_Node.get_ID();

    for (int i = 1; i <= 3; i++)
        m_dCoordinates[i-1] = otherInit_Node.get_coordinate(i);

    m_bFlag = otherInit_Node.get_flag();
    m_cBoundary = otherInit_Node.get_boundary();

    m_bVelocityIsSet = otherInit_Node.m_bVelocityIsSet;
    m_uTimeFunction = otherInit_Node.m_uTimeFunction;
    initial_velocity = otherInit_Node.initial_velocity;

    return (*this );
}

Init_Node &Init_Node::operator =(const Mesh_Node & otherMesh_Node)
{
    m_uID = otherMesh_Node.get_ID();

    for (int i = 1; i <= 3; i++)
        m_dCoordinates[i-1] = otherMesh_Node.get_coordinate(i);

    m_bFlag = otherMesh_Node.get_flag();
    m_cBoundary = otherMesh_Node.get_boundary();

    m_bVelocityIsSet = false;

    return (*this );
}

Init_Node::Init_Node()
{
    m_bVelocityIsSet = 1.0;
}

Init_Node::Init_Node(const Mesh_Node & node)
{
    m_uID = node.get_ID();

    for (int i = 1; i <= 3; i++)
        m_dCoordinates[i-1] = node.get_coordinate(i);

    m_bFlag = node.get_flag();
    m_cBoundary = node.get_boundary();

    m_bVelocityIsSet = false;
}

Init_Node::Init_Node(const Init_Node & node)
{
    m_uID = node.get_ID();

    for (int i = 1; i <= 3; i++)
        m_dCoordinates[i-1] = node.get_coordinate(i);

    m_bFlag = node.get_flag();
    m_cBoundary = node.get_boundary();

    m_bVelocityIsSet = node.m_bVelocityIsSet;
    m_uTimeFunction = node.m_uTimeFunction;
    initial_velocity = node.initial_velocity;
}

Init_Node::~Init_Node()
{}

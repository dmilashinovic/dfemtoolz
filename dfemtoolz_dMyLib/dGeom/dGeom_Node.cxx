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

#include "dGeom_Node.h"


Geom_Node::Geom_Node()
{}

Geom_Node::Geom_Node(const Geom_Node & node)
{
    for (int i = 1; i <= 3; i++)
        this->set_coordinate(node.get_coordinate(i), i);
}

Geom_Node::~Geom_Node()
{}

Geom_Node &Geom_Node::operator =(const Geom_Node &otherGeom_Node)
{
    for (int i = 1; i <= 3; i++)
        this->set_coordinate(otherGeom_Node.get_coordinate(i), i);

    return (*this );
}

Geom_Node &Geom_Node::operator +(const Geom_Node & otherGeom_Node)
{
    for (int i = 0; i < 3; i++)
        m_dCoordinates[i] += otherGeom_Node.m_dCoordinates[i];

    return (*this );
}

Geom_Node &Geom_Node::operator -(const Geom_Node & otherGeom_Node)
{
    for (int i = 0; i < 3; i++)
        m_dCoordinates[i] -= otherGeom_Node.m_dCoordinates[i];

    return (*this );
}

void Geom_Node::set_coordinate(double coordinate_value, int coordinate)
{
    m_dCoordinates[coordinate - 1] = coordinate_value;
}

void Geom_Node::set_coordinate_X(double Xcoordinate)
{
    m_dCoordinates[0] = Xcoordinate;
}

void Geom_Node::set_coordinate_Y(double Ycoordinate)
{
    m_dCoordinates[1] = Ycoordinate;
}

void Geom_Node::set_coordinate_Z(double Zcoordinate)
{
    m_dCoordinates[2] = Zcoordinate;
}

double Geom_Node::get_coordinate(int & coordinate) const
{
    return m_dCoordinates[coordinate - 1];
}

double Geom_Node::get_coordinate_X() const
{
    return m_dCoordinates[0];
}

double Geom_Node::get_coordinate_Y() const
{
    return m_dCoordinates[1];
}

double Geom_Node::get_coordinate_Z() const
{
    return m_dCoordinates[2];
}


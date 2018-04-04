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

#include "dGeom_Element.h"

int Geom_Element::how_many_nodes_per_element()
{
    return m_iNodesPerElement;
}

void Geom_Element::set_nodes_per_element(int no_of_nodes_per_element)
{
    m_iNodesPerElement = no_of_nodes_per_element;
}

void Geom_Element::set_ID(UINT ID)
{
    m_uID = ID;
}

UINT Geom_Element::get_ID()
{
    return m_uID;
}

void Geom_Element::set_node(UINT node, int node_position)
{
    m_pNode[node_position - 1] = node;
}

UINT & Geom_Element::get_node(int node_position)
{
    return m_pNode[node_position - 1];
}

void Geom_Element::set_boundary()
{
    m_bBoundary = !m_bBoundary;
}

void Geom_Element::set_boundary(bool boundary)
{
    m_bBoundary = boundary;
}

bool Geom_Element::get_boundary()
{
    return m_bBoundary;
}

void Geom_Element::set_flag()
{
    m_bFlag = !m_bFlag;
}

void Geom_Element::set_flag(bool flag)
{
    m_bFlag = flag;
}

bool Geom_Element::get_flag()
{
    return m_bFlag;
}

void Geom_Element::set_material_ID(int materialID)
{
    m_iMaterialID = materialID;
}

int Geom_Element::get_material_ID()
{
    return m_iMaterialID;
}

Geom_Element &Geom_Element::operator =(const Geom_Element &otherGeom_Element)
{
    if (this == &otherGeom_Element)
        return *this;
    else
    {
        delete [] m_pNode;
        m_pNode = new UINT [otherGeom_Element.m_iNodesPerElement];
        m_iNodesPerElement = otherGeom_Element.m_iNodesPerElement;
        m_bBoundary = otherGeom_Element.m_bBoundary;
        m_bFlag = otherGeom_Element.m_bFlag;
        m_uID = otherGeom_Element.m_uID;

        for (int i = 0; i < otherGeom_Element.m_iNodesPerElement; i++)
            m_pNode[i] = otherGeom_Element.m_pNode[i];
    }
    return (*this );
}

Geom_Element::Geom_Element(int nodes_per_element):
m_iNodesPerElement(nodes_per_element),
m_bBoundary(false),
m_bFlag(false),
m_pNode(new UINT[nodes_per_element]),
m_iMaterialID(1)
{}

Geom_Element::Geom_Element():
m_iNodesPerElement(10),
m_bBoundary(false),
m_bFlag(false),
m_pNode(new UINT[10]),
m_iMaterialID(1)
{}

Geom_Element::Geom_Element(const Geom_Element & element):
m_iNodesPerElement(element.m_iNodesPerElement),
m_bBoundary(element.m_bBoundary),
m_pNode(new UINT [element.m_iNodesPerElement])
{
    m_bFlag = element.m_bFlag;
    m_uID = element.m_uID;
    m_iMaterialID = element.m_iMaterialID;
    for (int k = 0; k < m_iNodesPerElement; k++)
        m_pNode[k] = element.m_pNode[k];
}

Geom_Element::~Geom_Element()
{
    delete [] m_pNode;
}


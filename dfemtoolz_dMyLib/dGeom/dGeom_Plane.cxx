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

#include "dGeom_Plane.h"

Geom_Plane::Geom_Plane()
{
    m_dNear_node_tol = 0.05;
    m_dA = 0.;
    m_dB = 0.;
    m_dC = 0.;
    m_dD = 1001.0;
}

void Geom_Plane::set_parameter_A(double parameter)
{
    m_dA = parameter;
}

double Geom_Plane::get_parameter_A()
{
    return m_dA;
}

void Geom_Plane::set_parameter_B(double parameter)
{
    m_dB = parameter;
}

double Geom_Plane::get_parameter_B()
{
    return m_dB;
}

void Geom_Plane::set_parameter_C(double parameter)
{
    m_dC = parameter;
}

double Geom_Plane::get_parameter_C()
{
    return m_dC;
}

void Geom_Plane::set_parameter_D(double parameter)
{
    m_dD = parameter;
}

double Geom_Plane::get_parameter_D()
{
    return m_dD;
}

void Geom_Plane::calculate_A_B_C_plane_parameters
(Geom_Node & node1, Geom_Node & node2, Geom_Node & node3)
{
    double Det =
    node1.get_coordinate_X() * (node2.get_coordinate_Y() * node3.get_coordinate_Z() - node2.get_coordinate_Z() * node3.get_coordinate_Y()) - node1.get_coordinate_Y() * (node2.get_coordinate_X() * node3.get_coordinate_Z() - node2.get_coordinate_Z() * node3.get_coordinate_X()) + node1.get_coordinate_Z() * (node2.get_coordinate_X() * node3.get_coordinate_Y() - node2.get_coordinate_Y() * node3.get_coordinate_X());

    m_dA = -(m_dD / Det)*(1 * (node2.get_coordinate_Y() * node3.get_coordinate_Z() - node2.get_coordinate_Z() * node3.get_coordinate_Y()) - node1.get_coordinate_Y() * (1 * node3.get_coordinate_Z() - node2.get_coordinate_Z() * 1) + node1.get_coordinate_Z() * (1 * node3.get_coordinate_Y() - node2.get_coordinate_Y() * 1));
    m_dB = -(m_dD / Det)*(node1.get_coordinate_X() * (1 * node3.get_coordinate_Z() - node2.get_coordinate_Z() * 1) - 1 * (node2.get_coordinate_X() * node3.get_coordinate_Z() - node2.get_coordinate_Z() * node3.get_coordinate_X()) + node1.get_coordinate_Z() * (node2.get_coordinate_X() * 1 - 1 * node3.get_coordinate_X()));
    m_dC = -(m_dD / Det)*(node1.get_coordinate_X() * (node2.get_coordinate_Y() * 1 - 1 * node3.get_coordinate_Y()) - node1.get_coordinate_Y() * (node2.get_coordinate_X() * 1 - 1 * node3.get_coordinate_X()) + 1 * (node2.get_coordinate_X() * node3.get_coordinate_Y() - node2.get_coordinate_Y() * node3.get_coordinate_X()));
}

void Geom_Plane::set_near_tol(double tol)
{
    m_dNear_node_tol = tol;
}

bool Geom_Plane::this_node_is_near_the_plane(Geom_Node & node)
{
    double up = fabs(m_dA * node.get_coordinate_X() + m_dB * node.get_coordinate_Y() + m_dC * node.get_coordinate_Z() + m_dD);
    double down = sqrt(m_dA * m_dA + m_dB * m_dB + m_dC * m_dC);
    if (up / down > m_dNear_node_tol)
        return false;
    return true;
}

void Geom_Plane::set_near_radius_and_reference_node(double radius, Geom_Node & refNode)
{
    m_dNear_node_radius = radius;
    m_uRef_node = refNode;
}

bool Geom_Plane::this_node_is_near_the_plane_and_in_the_radius(Geom_Node & node)
{
    if (get_lenght(node, m_uRef_node) > m_dNear_node_radius)
        return false;
    if(this_node_is_near_the_plane(node))
        return true;
    return false;
}

bool Geom_Plane::this_node_is_near_plane_X_eq_0(Geom_Node & node)
{
    if (node.get_coordinate_X() == 0)
        return true;
    return false;
}

bool Geom_Plane::this_node_is_near_plane_Y_eq_0(Geom_Node & node)
{
    if (node.get_coordinate_Y() == 0)
        return true;
    return false;
}

bool Geom_Plane::this_node_is_near_plane_Z_eq_0(Geom_Node & node)
{
    if (node.get_coordinate_Z() == 0)
        return true;
    return false;
}

bool Geom_Plane::this_node_is_near_plane_X_eq_0_and_in_the_radius(Geom_Node & node)
{
    if (get_lenght(node, m_uRef_node) > m_dNear_node_radius)
        return false;
    if (node.get_coordinate_X() == 0)
        return true;
    return false;
}

bool Geom_Plane::this_node_is_near_plane_Y_eq_0_and_in_the_radius(Geom_Node & node)
{
    if (get_lenght(node, m_uRef_node) > m_dNear_node_radius)
        return false;
    if (node.get_coordinate_Y() == 0)
        return true;
    return false;
}

bool Geom_Plane::this_node_is_near_plane_Z_eq_0_and_in_the_radius(Geom_Node & node)
{
    if (get_lenght(node, m_uRef_node) > m_dNear_node_radius)
        return false;
    if (node.get_coordinate_Z() == 0)
        return true;
    return false;
}

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
 * File:   dGeom_Node.h
 *
 *
 *
 *
 *
 */

#ifndef _DGEOM_PLANE_H
#define	_DGEOM_PLANE_H

#include "../dfemtoolz_dMyLib.h"
#include "../dBase/dCollection.h"
#include "dGeom_Node.h"
#include "dGeom_Functions.h"


class Geom_Plane
{
private:
    double m_dA, m_dB, m_dC, m_dD;
    double m_dNear_node_tol;
    double m_dNear_node_radius;
    Geom_Node m_uRef_node;

public:
    void set_parameter_A(double parameter);
    double get_parameter_A();

    void set_parameter_B(double parameter);
    double get_parameter_B();

    void set_parameter_C(double parameter);
    double get_parameter_C();

    void set_parameter_D(double parameter);
    double get_parameter_D();

    void set_near_tol(double tol);
    void set_near_radius_and_reference_node(double radius, Geom_Node & refNode);

    void calculate_A_B_C_plane_parameters
    (Geom_Node & node1, Geom_Node & node2, Geom_Node & node3);

    bool this_node_is_near_the_plane(Geom_Node & node);
    bool this_node_is_near_the_plane_and_in_the_radius(Geom_Node & node);
    bool this_node_is_near_plane_X_eq_0(Geom_Node & node);
    bool this_node_is_near_plane_Y_eq_0(Geom_Node & node);
    bool this_node_is_near_plane_Z_eq_0(Geom_Node & node);
    bool this_node_is_near_plane_X_eq_0_and_in_the_radius(Geom_Node & node);
    bool this_node_is_near_plane_Y_eq_0_and_in_the_radius(Geom_Node & node);
    bool this_node_is_near_plane_Z_eq_0_and_in_the_radius(Geom_Node & node);

    Geom_Plane();
};

#endif	/* _DGEOM_PLANE_H */

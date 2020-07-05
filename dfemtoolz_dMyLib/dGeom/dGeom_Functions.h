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
 * File:   dGeom_Functions.h
 *
 *
 *
 *
 *
 */

#ifndef _DGEOM_FUNCTIONS_H
#define	_DGEOM_FUNCTIONS_H

#include "../dfemtoolz_dMyLib.h"

#include "../dBase/dCollection.h"
#include "../dBase/dConstants.h"

#include "../dMisc/dSTL_Triangle.h"

#include "dGeom_Node.h"
#include "dGeom_Element.h"


/// GET LENGHT
double get_lenght(double & Ax, double & Ay, double & Az, double & Bx, double & By, double & Bz);
double get_lenght(Geom_Node & node1, Geom_Node & node2);
double get_lenght(Geom_Element & edge, Collection<Geom_Element> & node_col);


/// SAME NODES
bool these_nodes_are_the_same(Geom_Node & node1, Geom_Node & node2);
bool these_nodes_are_the_same(Geom_Node & node1, Geom_Node & node2, double diff_tol);


/// SAME EDGES
bool these_edges_are_same
(Geom_Element & edge1, Geom_Element & edge2, Collection<Geom_Node> & node_c);


/// GET AREA
double get_area(Geom_Node & node1, Geom_Node & node2, Geom_Node & node3);
double get_area(Geom_Node & node1, Geom_Node & node2, Geom_Node & node3, Geom_Node & node4);


/// GET GRAVITYCENTER
Geom_Node get_gravitycenter
(Geom_Node & node1, Geom_Node & node2);
Geom_Node get_gravitycenter
(Geom_Node & node1, Geom_Node & node2, Geom_Node & node3);
Geom_Node get_gravitycenter
(Geom_Node & node1, Geom_Node & node2, Geom_Node & node3, Geom_Node & node4);
Geom_Node get_gravitycenter
(Geom_Node & node1, Geom_Node & node2, Geom_Node & node3, Geom_Node & node4,
Geom_Node & node5, Geom_Node & node6, Geom_Node & node7, Geom_Node & node8);


/// NODE POSITION CHECK
bool node_is_in_rectangular_prism(Geom_Node & node, Geom_Node & min, Geom_Node & max);


/// GET VECTOR INTENSITY
double get_the_vector_intensity(double & a, double & b, double & c);
double get_the_vector_intensity(Geom_Node & vector);


/// GET NORMAL VECTOR
Geom_Node get_normal_vector_coordinates(Geom_Node & node1, Geom_Node & node2, Geom_Node & node3);
Geom_Node get_normal_vector_coordinates(Collection <STL_Triangle> & triangle_col);


/// VECTOR UNARY OPERATIONS
void transform_2_1value_vector(Geom_Node & vec);


/// VECTOR BINARY OPERATIONS
Geom_Node get_vector_projection(Geom_Node & vector2project, Geom_Node other_vector);
Geom_Node get_vector_difference_vecA_minus_vecB(Geom_Node & vecA, Geom_Node & vecB);
Geom_Node get_vector_sum_vecA_plus_vecB(Geom_Node & vecA, Geom_Node & vecB);
Geom_Node get_product_scalar_vector(double & numbR, Geom_Node & vec);
Geom_Node cross_product(Geom_Node & vecA, Geom_Node & vecB);
double dot_product(Geom_Node & vecA, Geom_Node & vecB);
double get_cos_of_angle_4_vectors(Geom_Node & vecA, Geom_Node & vecB);
Geom_Node get_average_vector_of_vecA_and_vecB(Geom_Node & vecA, Geom_Node & vecB);


/// CHECK ELEMENT

void InterpolationFunctionRSTDerive(double rst[], double HD[][3]);


#endif	/* _DGEOM_FUNCTIONS_H */


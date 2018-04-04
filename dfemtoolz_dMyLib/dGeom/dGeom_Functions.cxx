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

#include "dGeom_Functions.h"

/// GET LENGHT /// /// ///

double get_lenght
(double & Ax, double & Ay, double & Az, double & Bx, double & By, double & Bz)
{
    return fabs(sqrt(
            ((Ax - Bx)
            *(Ax - Bx)) +
            ((Ay - By)
            *(Ay - By)) +
            ((Az - Bz)
            *(Az - Bz))));
}

double get_lenght(Geom_Node & node1, Geom_Node & node2)
{
    return fabs(sqrt(
            ((node1.get_coordinate_X() - node2.get_coordinate_X())
            *(node1.get_coordinate_X() - node2.get_coordinate_X())) +
            ((node1.get_coordinate_Y() - node2.get_coordinate_Y())
            *(node1.get_coordinate_Y() - node2.get_coordinate_Y())) +
            ((node1.get_coordinate_Z() - node2.get_coordinate_Z())
            *(node1.get_coordinate_Z() - node2.get_coordinate_Z()))));
}

double get_lenght(Geom_Element & edge, Collection<Geom_Node> & node_col)
{
    return fabs(sqrt(
            ((node_col[edge.get_node(1)].get_coordinate_X() - node_col[edge.get_node(2)].get_coordinate_X())
            *(node_col[edge.get_node(1)].get_coordinate_X() - node_col[edge.get_node(2)].get_coordinate_X())) +
            ((node_col[edge.get_node(1)].get_coordinate_Y() - node_col[edge.get_node(2)].get_coordinate_Y())
            *(node_col[edge.get_node(1)].get_coordinate_Y() - node_col[edge.get_node(2)].get_coordinate_Y())) +
            ((node_col[edge.get_node(1)].get_coordinate_Z() - node_col[edge.get_node(2)].get_coordinate_Z())
            *(node_col[edge.get_node(1)].get_coordinate_Z() - node_col[edge.get_node(2)].get_coordinate_Z()))));
}


/// SAME NODES

bool these_nodes_are_the_same(Geom_Node & node1, Geom_Node & node2)
{
    if (get_lenght(node1, node2) < constants::same_node_tol)
        return true;
    return false;
}

bool these_nodes_are_the_same(Geom_Node & node1, Geom_Node & node2, double diff_tol)
{
    if (get_lenght(node1, node2) < diff_tol)
        return true;
    return false;
}


/// SAME EDGES

bool these_edges_are_same
(Geom_Element & edge1, Geom_Element & edge2, Collection<Geom_Node> & node_c)
{
    if (
        (get_lenght(
        node_c[edge1.get_node(1)],
        node_c[edge2.get_node(2)]) < constants::same_node_tol)
        &&
        (get_lenght(
        node_c[edge1.get_node(2)],
        node_c[edge2.get_node(1)]) < constants::same_node_tol))
        return true;
    if (
        (get_lenght(
        node_c[edge1.get_node(1)],
        node_c[edge2.get_node(1)]) < constants::same_node_tol)
        &&
        (get_lenght(
        node_c[edge1.get_node(2)],
        node_c[edge2.get_node(2)]) < constants::same_node_tol))
        return true;
    return false;
}


/// GET AREA /// /// ///

double get_area(Geom_Node & node1, Geom_Node & node2, Geom_Node & node3)
{
    double a, b, c, s;

    a = get_lenght(node1, node2);
    b = get_lenght(node2, node3);
    c = get_lenght(node3, node1);

    s = .5 * (a + b + c);

    return(sqrt(s * (s - a) * (s - b) * (s - c)));
}

double get_area(Geom_Node & node1, Geom_Node & node2, Geom_Node & node3, Geom_Node & node4)
{
    double a, b, c, s1, s2;

    a = get_lenght(node1, node2);
    b = get_lenght(node2, node3);
    c = get_lenght(node3, node1);

    s1 = .5 * (a + b + c);
    s1 = (sqrt(s1 * (s1 - a) * (s1 - b) * (s1 - c)));

    a = get_lenght(node3, node4);
    b = get_lenght(node4, node1);

    s2 = .5 * (a + b + c);
    s2 = (sqrt(s2 * (s2 - a) * (s2 - b) * (s2 - c)));

    return (s1 + s2);
}


/// GET GRAVITYCENTER /// /// ///

Geom_Node get_gravitycenter(Geom_Node & node1, Geom_Node & node2)
{
    Geom_Node gravitycenter;
    double gravitycenter_coordinate;

    for (int i = 1; i <= 3; i++)
    {
        gravitycenter_coordinate = (
                node1.get_coordinate(i) +
                node2.get_coordinate(i)) / 2;
        gravitycenter.set_coordinate(gravitycenter_coordinate, i);
    }
    return gravitycenter;
}

Geom_Node get_gravitycenter(Geom_Node & node1, Geom_Node & node2, Geom_Node & node3)
{
    Geom_Node gravitycenter;
    double gravitycenter_coordinate;

    for (int i = 1; i <= 3; i++)
    {
        gravitycenter_coordinate = (
                node1.get_coordinate(i) +
                node2.get_coordinate(i) +
                node3.get_coordinate(i)) / 3;
        gravitycenter.set_coordinate(gravitycenter_coordinate, i);
    }

    return gravitycenter;
}

Geom_Node get_gravitycenter
(Geom_Node & node1, Geom_Node & node2, Geom_Node & node3, Geom_Node & node4)
{
    Geom_Node gravitycenter;
    double gravitycenter_coordinate;

    for (int i = 1; i <= 3; i++)
    {
        gravitycenter_coordinate = (
                node1.get_coordinate(i) +
                node2.get_coordinate(i) +
                node3.get_coordinate(i) +
                node4.get_coordinate(i)) / 4;
        gravitycenter.set_coordinate(gravitycenter_coordinate, i);
    }

    return gravitycenter;
}

Geom_Node get_gravitycenter
(Geom_Node & node1, Geom_Node & node2, Geom_Node & node3, Geom_Node & node4, Geom_Node & node5, Geom_Node & node6, Geom_Node & node7, Geom_Node & node8)
{
    Geom_Node gravitycenter;
    double gravitycenter_coordinate;

    for (int i = 1; i <= 3; i++)
    {
        gravitycenter_coordinate = (
                node1.get_coordinate(i) +
                node2.get_coordinate(i) +
                node3.get_coordinate(i) +
                node4.get_coordinate(i) +
                node5.get_coordinate(i) +
                node6.get_coordinate(i) +
                node7.get_coordinate(i) +
                node8.get_coordinate(i)) / 8;
        gravitycenter.set_coordinate(gravitycenter_coordinate, i);
    }

    return gravitycenter;
}


/// NODE POSITION CHECK
bool node_is_in_rectangular_prism(Geom_Node & node, Geom_Node & min, Geom_Node & max)
{
    if ((node.get_coordinate_X() > min.get_coordinate_X()) && (node.get_coordinate_X() < max.get_coordinate_X()))
    if ((node.get_coordinate_Y() > min.get_coordinate_Y()) && (node.get_coordinate_Y() < max.get_coordinate_Y()))
    if ((node.get_coordinate_Z() > min.get_coordinate_Z()) && (node.get_coordinate_Z() < max.get_coordinate_Z()))
        return true;
    return false;
}


/// GET VECTOR INTENSITY /// /// ///

double get_the_vector_intensity(double & a, double & b, double & c)
{
    return sqrt( a*a + b*b + c*c);
}

double get_the_vector_intensity(Geom_Node & vector)
{
    return sqrt(
    (vector.get_coordinate_X() * vector.get_coordinate_X()) +
    (vector.get_coordinate_Y() * vector.get_coordinate_Y()) +
    (vector.get_coordinate_Z() * vector.get_coordinate_Z()));
}


/// GET NORMAL VECTOR /// /// ///

Geom_Node get_normal_vector_coordinates
(Geom_Node & node1, Geom_Node & node2, Geom_Node & node3)
{
    Geom_Node a, b, normal_vector;

    double coord[4];

    for (int i = 1; i <= 3; i++)
    {
        coord[i] = node2.get_coordinate(i) - node1.get_coordinate(i);
        a.set_coordinate(coord[i], i);
        coord[i] = node3.get_coordinate(i) - node1.get_coordinate(i);
        b.set_coordinate(coord[i], i);
    }

    coord[1] =   a.get_coordinate_Y() * b.get_coordinate_Z() - b.get_coordinate_Y() * a.get_coordinate_Z();
    coord[2] = -(a.get_coordinate_X() * b.get_coordinate_Z() - b.get_coordinate_X() * a.get_coordinate_Z());
    coord[3] =   a.get_coordinate_X() * b.get_coordinate_Y() - b.get_coordinate_X() * a.get_coordinate_Y();

    normal_vector.set_coordinate_X(coord[1]);
    normal_vector.set_coordinate_Y(coord[2]);
    normal_vector.set_coordinate_Z(coord[3]);
    return normal_vector;
}


/// VECTOR UNARY OPERATIONS /// /// ///

void transform_2_1value_vector(Geom_Node & vec)
{
    double coord[4];

    for (int i = 1; i <= 3; i++)
        coord[i] = vec.get_coordinate(i);

    coord[0] = sqrt(pow(coord[1], 2) + pow(coord[2], 2) + pow(coord[3], 2));

    for (int i = 1; i <= 3; i++)
    {
        coord[i] = coord[i] / coord[0];
        vec.set_coordinate(coord[i], i);
    }
}


/// VECTOR BINARY OPERATIONS /// /// ///

Geom_Node get_vector_projection
(Geom_Node & vector2project, Geom_Node other_vector)
{
    Geom_Node projection;
    transform_2_1value_vector(other_vector);
    double tmp, intensity =
    other_vector.get_coordinate_X() * vector2project.get_coordinate_X() +
    other_vector.get_coordinate_Y() * vector2project.get_coordinate_Y() +
    other_vector.get_coordinate_Z() * vector2project.get_coordinate_Z();

    for (int i = 1; i <= 3; i++)
    {
        tmp = intensity * other_vector.get_coordinate(i);
        projection.set_coordinate(tmp, i);
    }

    return projection;
}

Geom_Node get_vector_difference_vecA_minus_vecB(Geom_Node & vecA, Geom_Node & vecB)
{
    Geom_Node node;
    double coord;

    for (int i = 1; i <= 3; i++)
    {
        coord = vecA.get_coordinate(i) - vecB.get_coordinate(i);
        node.set_coordinate(coord, i);
    }

    return node;
}

Geom_Node get_vector_sum_vecA_plus_vecB(Geom_Node & vecA, Geom_Node & vecB)
{
    Geom_Node node;
    double coord;

    for (int i = 1; i <= 3; i++)
    {
        coord = vecA.get_coordinate(i) + vecB.get_coordinate(i);
        node.set_coordinate(coord, i);
    }

    return node;
}

Geom_Node get_product_scalar_vector(double & numbR, Geom_Node & vec)
{
    Geom_Node node;
    double coord;

    for (int i = 1; i <= 3; i++)
    {
        coord = vec.get_coordinate(i) * numbR;
        node.set_coordinate(coord, i);
    }

    return node;
}

Geom_Node cross_product(Geom_Node & vecA, Geom_Node & vecB)
{
    Geom_Node product;
    double temp;

    temp = vecA.get_coordinate_Y() * vecB.get_coordinate_Z()
    - vecA.get_coordinate_Z() * vecB.get_coordinate_Y();
    product.set_coordinate_X(temp);

    temp = vecA.get_coordinate_Z() * vecB.get_coordinate_X()
    - vecA.get_coordinate_X() * vecB.get_coordinate_Z();
    product.set_coordinate_Y(temp);

    temp = vecA.get_coordinate_X() * vecB.get_coordinate_Y()
    - vecA.get_coordinate_Y() * vecB.get_coordinate_X();
    product.set_coordinate_Z(temp);

    return product;
}

double dot_product(Geom_Node & vecA, Geom_Node & vecB)
{
    return
        (vecA.get_coordinate_X() * vecB.get_coordinate_X()) +
        (vecA.get_coordinate_Y() * vecB.get_coordinate_Y()) +
        (vecA.get_coordinate_Z() * vecB.get_coordinate_Z());
}

double get_cos_of_angle_4_vectors(Geom_Node & vecA, Geom_Node & vecB)
{
    return
    dot_product(vecA, vecB) / (get_the_vector_intensity(vecA) * get_the_vector_intensity(vecB));
}


/// CHECK ELEMENT


void InterpolationFunctionRSTDerive(double rst[], double HD[][3])
{
    HD[0][0] = -0.125 * (1. - rst[1]) * (1. + rst[2]);
    HD[1][0] =  0.125 * (1. - rst[1]) * (1. + rst[2]);
    HD[2][0] =  0.125 * (1. + rst[1]) * (1. + rst[2]);
    HD[3][0] = -0.125 * (1. + rst[1]) * (1. + rst[2]);
    HD[4][0] = -0.125 * (1. - rst[1]) * (1. - rst[2]);
    HD[5][0] =  0.125 * (1. - rst[1]) * (1. - rst[2]);
    HD[6][0] =  0.125 * (1. + rst[1]) * (1. - rst[2]);
    HD[7][0] = -0.125 * (1. + rst[1]) * (1. - rst[2]);

    HD[0][1] = -0.125 * (1. - rst[0]) * (1. + rst[2]);
    HD[1][1] = -0.125 * (1. + rst[0]) * (1. + rst[2]);
    HD[2][1] =  0.125 * (1. + rst[0]) * (1. + rst[2]);
    HD[3][1] =  0.125 * (1. - rst[0]) * (1. + rst[2]);
    HD[4][1] = -0.125 * (1. - rst[0]) * (1. - rst[2]);
    HD[5][1] = -0.125 * (1. + rst[0]) * (1. - rst[2]);
    HD[6][1] =  0.125 * (1. + rst[0]) * (1. - rst[2]);
    HD[7][1] =  0.125 * (1. - rst[0]) * (1. - rst[2]);

    HD[0][2] =  0.125 * (1. - rst[0]) * (1. - rst[1]);
    HD[1][2] =  0.125 * (1. + rst[0]) * (1. - rst[1]);
    HD[2][2] =  0.125 * (1. + rst[0]) * (1. + rst[1]);
    HD[3][2] =  0.125 * (1. - rst[0]) * (1. + rst[1]);
    HD[4][2] = -0.125 * (1. - rst[0]) * (1. - rst[1]);
    HD[5][2] = -0.125 * (1. + rst[0]) * (1. - rst[1]);
    HD[6][2] = -0.125 * (1. + rst[0]) * (1. + rst[1]);
    HD[7][2] = -0.125 * (1. - rst[0]) * (1. + rst[1]);
}



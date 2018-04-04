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
 * File:   dGeom_TFunctions.h
 *
 *
 *
 *
 *
 */

#ifndef _DGEOM_TFUNCTIONS_H
#define	_DGEOM_TFUNCTIONS_H

#include "../dfemtoolz_dMyLib.h"

#include "../dBase/dCollection.h"
#include "../dBase/dConstants.h"

#include "../dMisc/dMisc_Functionz.h"

#include "../dPrin/dInfo.h"

#include "dGeom_Node.h"
#include "dGeom_Element.h"
#include "dGeom_Functions.h"


/// GET LENGHT
template <class T>
double get_lenght(Collection <T> & polyLine)
{
    double lenght = 0;
    if (polyLine.get_size() > 1)
    for (UINT i = 1; i < polyLine.get_size() - 1; i++)
    {
        lenght += fabs(sqrt(
            ((polyLine[i].get_coordinate_X() - polyLine[i + 1].get_coordinate_X())
            *(polyLine[i].get_coordinate_X() - polyLine[i + 1].get_coordinate_X())) +
            ((polyLine[i].get_coordinate_Y() - polyLine[i + 1].get_coordinate_Y())
            *(polyLine[i].get_coordinate_Y() - polyLine[i + 1].get_coordinate_Y())) +
            ((polyLine[i].get_coordinate_Z() - polyLine[i + 1].get_coordinate_Z())
            *(polyLine[i].get_coordinate_Z() - polyLine[i + 1].get_coordinate_Z()))));
    }

    return lenght;
}


/// GET AREA
template <class T>
double get_area(Geom_Element & triangle_or_quadrilateral, Collection<T> & node_col)
{
    if (triangle_or_quadrilateral.how_many_nodes_per_element() == 3)
    {
        double a, b, c, s;

        a = get_lenght(node_col[triangle_or_quadrilateral.get_node(1)], node_col[triangle_or_quadrilateral.get_node(2)]);
        b = get_lenght(node_col[triangle_or_quadrilateral.get_node(2)], node_col[triangle_or_quadrilateral.get_node(3)]);
        c = get_lenght(node_col[triangle_or_quadrilateral.get_node(3)], node_col[triangle_or_quadrilateral.get_node(1)]);

        s = .5 * (a + b + c);

        return (sqrt(s * (s - a) * (s - b) * (s - c)));
    }
    if (triangle_or_quadrilateral.how_many_nodes_per_element() == 4)
    {
        double a, b, c, s1, s2;

        a = get_lenght(node_col[triangle_or_quadrilateral.get_node(1)], node_col[triangle_or_quadrilateral.get_node(2)]);
        b = get_lenght(node_col[triangle_or_quadrilateral.get_node(2)], node_col[triangle_or_quadrilateral.get_node(3)]);
        c = get_lenght(node_col[triangle_or_quadrilateral.get_node(3)], node_col[triangle_or_quadrilateral.get_node(1)]);

        s1 = .5 * (a + b + c);
        s1 = (sqrt(s1 * (s1 - a) * (s1 - b) * (s1 - c)));

        a = get_lenght(node_col[triangle_or_quadrilateral.get_node(3)], node_col[triangle_or_quadrilateral.get_node(4)]);
        b = get_lenght(node_col[triangle_or_quadrilateral.get_node(4)], node_col[triangle_or_quadrilateral.get_node(1)]);

        s2 = .5 * (a + b + c);
        s2 = (sqrt(s2 * (s2 - a) * (s2 - b) * (s2 - c)));

        return (s1 + s2);
    }
    return 0;
}


/// GET GRAVITYCENTER
template <class T>
Geom_Node get_gravitycenter(Collection<T> & node_col)
{
    Geom_Node gravity_centR;
    double cgX = 0.0, cgY = 0.0, cgZ = 0.0;
    for (UINT i = 1; i <= node_col.get_size(); i++)
    {
        cgX += node_col[i].get_coordinate_X();
        cgY += node_col[i].get_coordinate_Y();
        cgZ += node_col[i].get_coordinate_Z();
    }
    cgX = cgX / node_col.get_size();
    cgY = cgY / node_col.get_size();
    cgZ = cgZ / node_col.get_size();

    gravity_centR.set_coordinate_X(cgX);
    gravity_centR.set_coordinate_Y(cgY);
    gravity_centR.set_coordinate_Z(cgZ);

    return gravity_centR;
}

template <class T>
Geom_Node get_gravitycenter(Geom_Element & element, Collection<T> & node_col)
{
    Geom_Node gravitycenter;
    int nodes_per_elem = element.how_many_nodes_per_element();

    double
    gravitycenter_coordinate = 0;
    for (int i = 1; i <= nodes_per_elem; i++)
        gravitycenter_coordinate += node_col[element.get_node(i)].get_coordinate_X();
    gravitycenter_coordinate = gravitycenter_coordinate / nodes_per_elem;
    gravitycenter.set_coordinate_X(gravitycenter_coordinate);

    gravitycenter_coordinate = 0;
    for (int i = 1; i <= nodes_per_elem; i++)
        gravitycenter_coordinate += node_col[element.get_node(i)].get_coordinate_Y();
    gravitycenter_coordinate = gravitycenter_coordinate / nodes_per_elem;
    gravitycenter.set_coordinate_Y(gravitycenter_coordinate);

    gravitycenter_coordinate = 0;
    for (int i = 1; i <= nodes_per_elem; i++)
        gravitycenter_coordinate += node_col[element.get_node(i)].get_coordinate_Z();
    gravitycenter_coordinate = gravitycenter_coordinate / nodes_per_elem;
    gravitycenter.set_coordinate_Z(gravitycenter_coordinate);

    return gravitycenter;
}

template <class T>
Geom_Node get_gravitycenter(Geom_Element & element, int no_of_nodes, Collection<T> & node_col)
{
    Geom_Node gravitycenter;

    double
    gravitycenter_coordinate = 0;
    for (int i = 1; i <= no_of_nodes; i++)
        gravitycenter_coordinate += node_col[element.get_node(i)].get_coordinate_X();
    gravitycenter_coordinate = gravitycenter_coordinate / no_of_nodes;
    gravitycenter.set_coordinate_X(gravitycenter_coordinate);

    gravitycenter_coordinate = 0;
    for (int i = 1; i <= no_of_nodes; i++)
        gravitycenter_coordinate += node_col[element.get_node(i)].get_coordinate_Y();
    gravitycenter_coordinate = gravitycenter_coordinate / no_of_nodes;
    gravitycenter.set_coordinate_Y(gravitycenter_coordinate);

    gravitycenter_coordinate = 0;
    for (int i = 1; i <= no_of_nodes; i++)
        gravitycenter_coordinate += node_col[element.get_node(i)].get_coordinate_Z();
    gravitycenter_coordinate = gravitycenter_coordinate / no_of_nodes;
    gravitycenter.set_coordinate_Z(gravitycenter_coordinate);

    return gravitycenter;
}


/// GET MIN/MAX DISTANCE POINT 2 POINTSET /// /// ///

template <class T>
double get_max_distance_point_2_pointset(Geom_Node & node, Collection<T> & node_col)
{
    double R = 0;
    for(UINT i = 1; i <= node_col.get_size(); i++)
    {
        if (get_lenght(node, node_col[i]) > R)
            R = get_lenght(node, node_col[i]);
    }
    return R;
}

template <class T>
double get_max_distance_point_2_pointset(Geom_Node & node, UINT & max_distance_node_ID, Collection<T> & node_col)
{
    double R = 0;
    for(UINT i = 1; i <= node_col.get_size(); i++)
    {
        if (get_lenght(node, node_col[i]) > R)
        {
            R = get_lenght(node, node_col[i]);
            max_distance_node_ID = i;
        }
    }
    return R;
}

template <class T>
double get_min_distance_point_2_pointset(Geom_Node & node, Collection<T> & node_col)
{
    double R = get_lenght(node, node_col[1]);
    for(UINT i = 1; i <= node_col.get_size(); i++)
    {
        if (get_lenght(node, node_col[i]) < R)
            R = get_lenght(node, node_col[i]);
    }
    return R;
}

template <class T>
double get_min_distance_point_2_pointset(Geom_Node & node, UINT & min_distance_node_ID, Collection<T> & node_col)
{
    double R = get_lenght(node, node_col[1]);
    for(UINT i = 1; i <= node_col.get_size(); i++)
    {
        if (get_lenght(node, node_col[i]) < R)
        {
            R = get_lenght(node, node_col[i]);
            min_distance_node_ID = i;
        }
    }
    return R;
}

/// SCALE NODES /// /// ///

template <class T>
void scale_nodes(double & scale_factor, Collection <T> & node_col)
{
    Info * info = Info::createInfo();
    info->print_info_message("scaling model");
    info->print_info_message("scaling factor " + dtos(scale_factor));

    double tmp;
    for (UINT i = 1; i <= node_col.get_size(); i++)
    {
        tmp = node_col[i].get_coordinate_X() * scale_factor;
        node_col[i].set_coordinate_X(tmp);

        tmp = node_col[i].get_coordinate_Y() * scale_factor;
        node_col[i].set_coordinate_Y(tmp);

        tmp = node_col[i].get_coordinate_Z() * scale_factor;
        node_col[i].set_coordinate_Z(tmp);
    }
}


template <class T>
void scale_nodes(double & scale_factorX, double & scale_factorY, double & scale_factorZ, Collection <T> & node_col)
{
    Info * info = Info::createInfo();
    info->print_info_message("scaling model");
    info->print_info_message("scaling factor X " + dtos(scale_factorX));
    info->print_info_message("scaling factor Y " + dtos(scale_factorY));
    info->print_info_message("scaling factor Z " + dtos(scale_factorZ));

    double tmp;
    for (UINT i = 1; i <= node_col.get_size(); i++)
    {
        tmp = node_col[i].get_coordinate_X() * scale_factorX;
        node_col[i].set_coordinate_X(tmp);

        tmp = node_col[i].get_coordinate_Y() * scale_factorY;
        node_col[i].set_coordinate_Y(tmp);

        tmp = node_col[i].get_coordinate_Z() * scale_factorZ;
        node_col[i].set_coordinate_Z(tmp);
    }
}

/// CHECK TETRA ELEMENT /// /// ///

template <class T>
double get_tetra_volume(Geom_Element & tetra, Collection <T> & node_col)
{
    double TetraVolume = 0;

    int a = 1, b = 2, c = 3, d = 4;

    Geom_Node first_bracket = get_vector_difference_vecA_minus_vecB(node_col[tetra.get_node(a)], node_col[tetra.get_node(d)]);

    Geom_Node second_bracket_first_part = get_vector_difference_vecA_minus_vecB(node_col[tetra.get_node(b)], node_col[tetra.get_node(d)]);
    Geom_Node second_bracket_second_part = get_vector_difference_vecA_minus_vecB(node_col[tetra.get_node(c)], node_col[tetra.get_node(d)]);

    Geom_Node second_bracket = cross_product(
    second_bracket_first_part,
    second_bracket_second_part);

    double up = fabs(dot_product(first_bracket, second_bracket));

    TetraVolume = up/6;

    return TetraVolume;
}

/// CHECK BRICK ELEMENT /// /// ///

template <class T>
double get_brick_volume(Geom_Element & brick, Collection <T> & node_col)
{
    double BrickVolume = 0;
    {
        double NaturalCoordinatesOfGaussNodes[3] = {.57, .57, .57};
        BrickVolume += Jacobian(NaturalCoordinatesOfGaussNodes, brick, node_col);
    }
    {
        double NaturalCoordinatesOfGaussNodes[3] = {-.57, .57, .57};
        BrickVolume += Jacobian(NaturalCoordinatesOfGaussNodes, brick, node_col);
    }
    {
        double NaturalCoordinatesOfGaussNodes[3] = {-.57, -.57, .57};
        BrickVolume += Jacobian(NaturalCoordinatesOfGaussNodes, brick, node_col);
    }
    {
        double NaturalCoordinatesOfGaussNodes[3] = {.57, -.57, .57};
        BrickVolume += Jacobian(NaturalCoordinatesOfGaussNodes, brick, node_col);
    }
    {
        double NaturalCoordinatesOfGaussNodes[3] = {.57, .57, -.57};
        BrickVolume += Jacobian(NaturalCoordinatesOfGaussNodes, brick, node_col);
    }
    {
        double NaturalCoordinatesOfGaussNodes[3] = {-.57, .57, -.57};
        BrickVolume += Jacobian(NaturalCoordinatesOfGaussNodes, brick, node_col);
    }
    {
        double NaturalCoordinatesOfGaussNodes[3] = {-.57, -.57, -.57};
        BrickVolume += Jacobian(NaturalCoordinatesOfGaussNodes, brick, node_col);
    }
    {
        double NaturalCoordinatesOfGaussNodes[3] = {.57, -.57, -.57};
        BrickVolume += Jacobian(NaturalCoordinatesOfGaussNodes, brick, node_col);
    }
    return BrickVolume;
}

template <class T>
bool this_brick_is_fine(Geom_Element & brick, Collection <T> & node_col)
{
    bool quality = true;
    {
        double NaturalCoordinatesOfGaussNodes[3] = {.57, .57, .57};
        if (Jacobian(NaturalCoordinatesOfGaussNodes, brick, node_col) < 0)
            quality = false;
    }
    {
        double NaturalCoordinatesOfGaussNodes[3] = {-.57, .57, .57};
        if (Jacobian(NaturalCoordinatesOfGaussNodes, brick, node_col) < 0)
            quality = false;
    }
    {
        double NaturalCoordinatesOfGaussNodes[3] = {-.57, -.57, .57};
        if (Jacobian(NaturalCoordinatesOfGaussNodes, brick, node_col) < 0)
            quality = false;
    }
    {
        double NaturalCoordinatesOfGaussNodes[3] = {.57, -.57, .57};
        if (Jacobian(NaturalCoordinatesOfGaussNodes, brick, node_col) < 0)
            quality = false;
    }
    {
        double NaturalCoordinatesOfGaussNodes[3] = {.57, .57, -.57};
        if (Jacobian(NaturalCoordinatesOfGaussNodes, brick, node_col) < 0)
            quality = false;
    }
    {
        double NaturalCoordinatesOfGaussNodes[3] = {-.57, .57, -.57};
        if (Jacobian(NaturalCoordinatesOfGaussNodes, brick, node_col) < 0)
            quality = false;
    }
    {
        double NaturalCoordinatesOfGaussNodes[3] = {-.57, -.57, -.57};
        if (Jacobian(NaturalCoordinatesOfGaussNodes, brick, node_col) < 0)
            quality = false;
    }
    {
        double NaturalCoordinatesOfGaussNodes[3] = {.57, -.57, -.57};
        if (Jacobian(NaturalCoordinatesOfGaussNodes, brick, node_col) < 0)
            quality = false;
    }
    return quality;
}

template <class T>
double Jacobian(double rst[], Geom_Element & brick, Collection <T> & node_col)
{
    double Determinant;
    double HD[8][3];
    double J[3][3];

    InterpolationFunctionRSTDerive(rst, HD);

    for(int i = 0; i < 3; i++)
    for(int j = 1; j <= 3; j++)
    {
        double sum = 0.;

        for (int k = 1; k <= 8; k++)
            sum += HD[k - 1][i] * node_col[brick.get_node(k)].get_coordinate(j);

        J[i][j - 1] = sum;
    }

    Determinant =
    J[0][0] * ((J[1][1] * J[2][2]) - (J[1][2] * J[2][1])) +
    J[0][1] * ((J[1][2] * J[2][0]) - (J[1][0] * J[2][2])) +
    J[0][2] * ((J[1][0] * J[2][1]) - (J[1][1] * J[2][0]));

    return Determinant;
}

template <class T>
double get_volume_of_all_brick_elements
(Collection <Geom_Element> & brick_col, Collection <T> & node_col)
{
    Info * info = Info::createInfo();
    info->print_info_message("calculating volume of the model...");

    double Vol = 0.;

    for (UINT i = 1; i <= brick_col.get_size(); i++)
        Vol += get_brick_volume(brick_col[i], node_col);

    info->print_info_message("volume of the model is " + dtos(Vol));
    return Vol;
}

template <class T>
void check_all_brick_elements
(Collection <Geom_Element> & brick_col, Collection <T> & node_col)
{
    Info * info = Info::createInfo();
    info->print_info_message("checking all brick elements...");

    for (UINT i = 1; i <= brick_col.get_size(); i++)
    if (!this_brick_is_fine(brick_col[i], node_col))
        info->print_info_message("element ID " + utos(i) + " has determinant less than zero");
}


#endif	/* _DGEOM_TFUNCTIONS_H */



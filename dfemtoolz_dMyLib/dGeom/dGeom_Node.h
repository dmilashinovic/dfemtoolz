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

#ifndef _DGEOM_NODE_H
#define	_DGEOM_NODE_H

#include "../dfemtoolz_dMyLib.h"

#include "../dBase/dConstants.h"

class Geom_Node
{
protected:
    double m_dCoordinates[3];

public:
    void set_coordinate(double coordinate_value, int coordinate);
    void set_coordinate_X(double Xcoordinate);
    void set_coordinate_Y(double Ycoordinate);
    void set_coordinate_Z(double Zcoordinate);

    double get_coordinate(int & coordinate) const;
    double get_coordinate_X() const;
    double get_coordinate_Y() const;
    double get_coordinate_Z() const;

    Geom_Node & operator =(const Geom_Node & otherGeom_Node);
    bool operator       ==(const Geom_Node & otherGeom_Node);
    bool operator        <(const Geom_Node & a) const;
    Geom_Node & operator +(const Geom_Node & otherGeom_Node);
    Geom_Node & operator -(const Geom_Node & otherGeom_Node);

    Geom_Node();
    Geom_Node(const Geom_Node & node);
    ~Geom_Node();
};

#endif	/* _DGEOM_NODE_H */

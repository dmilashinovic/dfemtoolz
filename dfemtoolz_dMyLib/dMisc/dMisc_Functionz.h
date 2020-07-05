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
 * File:   dMisc_Functionz.h
 *
 *
 *
 *
 *
 */

#ifndef _DMISC_FUNCTIONZ_H
#define	_DMISC_FUNCTIONZ_H

#include "../dfemtoolz_dMyLib.h"

#include "../dBase/dConstants.h"

#include <sstream>
#include <cstdlib>


void press_any_key_2_continue();
string utos(UINT number_2_string);
string itos(int number_2_string);
string dtos(double number_2_string);

template <class T>
int check_boundary_color(T & node);


template <class T>
int check_boundary_color(T & node)
{
    int color = 0;
    if (node.get_boundary() & constants::IS_ON_OUTLET)
        color += 1;
    if (node.get_boundary() & constants::IS_ON_INLET)
        color += 2;
    if ((node.get_boundary() & constants::IS_BOUNDARY_V) == constants::IS_BOUNDARY_V)
        color += 3;
    if (!((node.get_boundary() & constants::IS_BOUNDARY_V) == constants::IS_BOUNDARY_V))
    if (node.get_boundary() & constants::IS_BOUNDARY_VX)
        color += 4;
    if (!((node.get_boundary() & constants::IS_BOUNDARY_V) == constants::IS_BOUNDARY_V))
    if (node.get_boundary() & constants::IS_BOUNDARY_VY)
        color += 5;
    if (!((node.get_boundary() & constants::IS_BOUNDARY_V) == constants::IS_BOUNDARY_V))
    if (node.get_boundary() & constants::IS_BOUNDARY_VZ)
        color += 6;
    if (node.get_boundary() & constants::IS_BOUNDARY_P)
        color += 7;
    if (node.get_boundary() & constants::IS_BOUNDARY_T)
        color += 8;
    return color;
}


#endif	/* _DMISC_FUNCTIONZ_H */




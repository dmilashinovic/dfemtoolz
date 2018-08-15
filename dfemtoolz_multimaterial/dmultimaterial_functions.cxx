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

#include "dmultimaterial_functions.h"

bool put_contact_edges(
UINT elementID,
Collection <Mesh_Node> & nodez_col,
Geom_Element & one_element,
Collection <Geom_Element> & contact_faces_col,
UINT & current_no_of_contact_surfaces)
{
    UINT niz[10];

    int countR = 0;

    Geom_Element contact_face;
    contact_face.set_flag(true);

    int face_switchR = 4;

    if (one_element.how_many_nodes_per_element() == 4)
        face_switchR = 3;

    for (int x = 1; x <= one_element.how_many_nodes_per_element(); x++)
    {
        niz[x] = one_element.get_node(x);

        if (nodez_col[niz[x]].get_flag())
            countR++;
    }

    if (countR < face_switchR)
        return false;

    if (one_element.how_many_nodes_per_element() == 8)
    {
        if (nodez_col[niz[1]].get_flag())
        if (nodez_col[niz[2]].get_flag())
        if (nodez_col[niz[3]].get_flag())
        if (nodez_col[niz[4]].get_flag())
        {
            contact_face.set_ID(elementID);
            contact_face.set_node(niz[1], 1);
            contact_face.set_node(niz[2], 2);
            contact_face.set_node(niz[3], 3);
            contact_face.set_node(niz[4], 4);
            contact_face.set_node(current_no_of_contact_surfaces, 5);
            contact_faces_col.insert(contact_face);
        }

        if (nodez_col[niz[8]].get_flag())
        if (nodez_col[niz[7]].get_flag())
        if (nodez_col[niz[6]].get_flag())
        if (nodez_col[niz[5]].get_flag())
        {
            contact_face.set_ID(elementID);
            contact_face.set_node(niz[8], 1);
            contact_face.set_node(niz[7], 2);
            contact_face.set_node(niz[6], 3);
            contact_face.set_node(niz[5], 4);
            contact_face.set_node(current_no_of_contact_surfaces, 5);
            contact_faces_col.insert(contact_face);
        }

        if (nodez_col[niz[1]].get_flag())
        if (nodez_col[niz[4]].get_flag())
        if (nodez_col[niz[8]].get_flag())
        if (nodez_col[niz[5]].get_flag())
        {
            contact_face.set_ID(elementID);
            contact_face.set_node(niz[1], 1);
            contact_face.set_node(niz[4], 2);
            contact_face.set_node(niz[8], 3);
            contact_face.set_node(niz[5], 4);
            contact_face.set_node(current_no_of_contact_surfaces, 5);
            contact_faces_col.insert(contact_face);
        }

        if (nodez_col[niz[2]].get_flag())
        if (nodez_col[niz[1]].get_flag())
        if (nodez_col[niz[5]].get_flag())
        if (nodez_col[niz[6]].get_flag())
        {
            contact_face.set_ID(elementID);
            contact_face.set_node(niz[2], 1);
            contact_face.set_node(niz[1], 2);
            contact_face.set_node(niz[5], 3);
            contact_face.set_node(niz[6], 4);
            contact_face.set_node(current_no_of_contact_surfaces, 5);
            contact_faces_col.insert(contact_face);
        }

        if (nodez_col[niz[3]].get_flag())
        if (nodez_col[niz[2]].get_flag())
        if (nodez_col[niz[6]].get_flag())
        if (nodez_col[niz[7]].get_flag())
        {
            contact_face.set_ID(elementID);
            contact_face.set_node(niz[3], 1);
            contact_face.set_node(niz[2], 2);
            contact_face.set_node(niz[6], 3);
            contact_face.set_node(niz[7], 4);
            contact_face.set_node(current_no_of_contact_surfaces, 5);
            contact_faces_col.insert(contact_face);
        }

        if (nodez_col[niz[4]].get_flag())
        if (nodez_col[niz[3]].get_flag())
        if (nodez_col[niz[7]].get_flag())
        if (nodez_col[niz[8]].get_flag())
        {
            contact_face.set_ID(elementID);
            contact_face.set_node(niz[4], 1);
            contact_face.set_node(niz[3], 2);
            contact_face.set_node(niz[7], 3);
            contact_face.set_node(niz[8], 4);
            contact_face.set_node(current_no_of_contact_surfaces, 5);
            contact_faces_col.insert(contact_face);
        }
    }

    if (one_element.how_many_nodes_per_element() == 4)
    {
        if (nodez_col[niz[1]].get_flag())
        if (nodez_col[niz[2]].get_flag())
        if (nodez_col[niz[3]].get_flag())
        {
            contact_face.set_ID(elementID);
            contact_face.set_node(niz[1], 1);
            contact_face.set_node(niz[2], 2);
            contact_face.set_node(niz[3], 3);
            contact_face.set_node(current_no_of_contact_surfaces, 4);
            contact_faces_col.insert(contact_face);
        }

        if (nodez_col[niz[1]].get_flag())
        if (nodez_col[niz[3]].get_flag())
        if (nodez_col[niz[4]].get_flag())
        {
            contact_face.set_ID(elementID);
            contact_face.set_node(niz[1], 1);
            contact_face.set_node(niz[3], 2);
            contact_face.set_node(niz[4], 3);
            contact_face.set_node(current_no_of_contact_surfaces, 4);
            contact_faces_col.insert(contact_face);
        }

        if (nodez_col[niz[1]].get_flag())
        if (nodez_col[niz[4]].get_flag())
        if (nodez_col[niz[2]].get_flag())
        {
            contact_face.set_ID(elementID);
            contact_face.set_node(niz[1], 1);
            contact_face.set_node(niz[4], 2);
            contact_face.set_node(niz[2], 3);
            contact_face.set_node(current_no_of_contact_surfaces, 4);
            contact_faces_col.insert(contact_face);
        }

        if (nodez_col[niz[3]].get_flag())
        if (nodez_col[niz[2]].get_flag())
        if (nodez_col[niz[4]].get_flag())
        {
            contact_face.set_ID(elementID);
            contact_face.set_node(niz[3], 1);
            contact_face.set_node(niz[2], 2);
            contact_face.set_node(niz[4], 3);
            contact_face.set_node(current_no_of_contact_surfaces, 4);
            contact_faces_col.insert(contact_face);
        }
    }

    return true;
}

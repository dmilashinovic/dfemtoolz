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

bool put_contact_edges_first(
UINT elementID,
Collection <Mesh_Node> & nodez_col,
Geom_Element & one_element,
Collection <Geom_Element> & contact_faces_col,
UINT & material2ID,
SuperCollection <UINT> & refs_to_contact_surfaces)
{
    UINT niz[10], contact_surface_ID;

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
            contact_surface_ID = assign_contact_surface_ID(one_element.get_material_ID(), material2ID, refs_to_contact_surfaces);

            if (contact_surface_ID != 0)
            {
                contact_face.set_ID(elementID);
                contact_face.set_node(niz[1], 1);
                contact_face.set_node(niz[2], 2);
                contact_face.set_node(niz[3], 3);
                contact_face.set_node(niz[4], 4);
                contact_face.set_node(contact_surface_ID, 5);
                contact_face.set_node(one_element.get_material_ID(), 6);
                contact_face.set_node(material2ID, 7);
                contact_faces_col.insert(contact_face);

                nodez_col[niz[1]].add_neighbour_node(elementID);
                nodez_col[niz[2]].add_neighbour_node(elementID);
                nodez_col[niz[3]].add_neighbour_node(elementID);
                nodez_col[niz[4]].add_neighbour_node(elementID);
            }
        }

        if (nodez_col[niz[8]].get_flag())
        if (nodez_col[niz[7]].get_flag())
        if (nodez_col[niz[6]].get_flag())
        if (nodez_col[niz[5]].get_flag())
        {
            contact_surface_ID = assign_contact_surface_ID(one_element.get_material_ID(), material2ID, refs_to_contact_surfaces);

            if (contact_surface_ID != 0)
            {
                contact_face.set_ID(elementID);
                contact_face.set_node(niz[8], 1);
                contact_face.set_node(niz[7], 2);
                contact_face.set_node(niz[6], 3);
                contact_face.set_node(niz[5], 4);
                contact_face.set_node(contact_surface_ID, 5);
                contact_face.set_node(one_element.get_material_ID(), 6);
                contact_face.set_node(material2ID, 7);
                contact_faces_col.insert(contact_face);

                nodez_col[niz[8]].add_neighbour_node(elementID);
                nodez_col[niz[7]].add_neighbour_node(elementID);
                nodez_col[niz[6]].add_neighbour_node(elementID);
                nodez_col[niz[5]].add_neighbour_node(elementID);
            }
        }

        if (nodez_col[niz[1]].get_flag())
        if (nodez_col[niz[4]].get_flag())
        if (nodez_col[niz[8]].get_flag())
        if (nodez_col[niz[5]].get_flag())
        {
            contact_surface_ID = assign_contact_surface_ID(one_element.get_material_ID(), material2ID, refs_to_contact_surfaces);

            if (contact_surface_ID != 0)
            {
                contact_face.set_ID(elementID);
                contact_face.set_node(niz[1], 1);
                contact_face.set_node(niz[4], 2);
                contact_face.set_node(niz[8], 3);
                contact_face.set_node(niz[5], 4);
                contact_face.set_node(contact_surface_ID, 5);
                contact_face.set_node(one_element.get_material_ID(), 6);
                contact_face.set_node(material2ID, 7);
                contact_faces_col.insert(contact_face);

                nodez_col[niz[1]].add_neighbour_node(elementID);
                nodez_col[niz[4]].add_neighbour_node(elementID);
                nodez_col[niz[8]].add_neighbour_node(elementID);
                nodez_col[niz[5]].add_neighbour_node(elementID);
            }
        }

        if (nodez_col[niz[2]].get_flag())
        if (nodez_col[niz[1]].get_flag())
        if (nodez_col[niz[5]].get_flag())
        if (nodez_col[niz[6]].get_flag())
        {
            contact_surface_ID = assign_contact_surface_ID(one_element.get_material_ID(), material2ID, refs_to_contact_surfaces);

            if (contact_surface_ID != 0)
            {
                contact_face.set_ID(elementID);
                contact_face.set_node(niz[2], 1);
                contact_face.set_node(niz[1], 2);
                contact_face.set_node(niz[5], 3);
                contact_face.set_node(niz[6], 4);
                contact_face.set_node(contact_surface_ID, 5);
                contact_face.set_node(one_element.get_material_ID(), 6);
                contact_face.set_node(material2ID, 7);
                contact_faces_col.insert(contact_face);

                nodez_col[niz[2]].add_neighbour_node(elementID);
                nodez_col[niz[1]].add_neighbour_node(elementID);
                nodez_col[niz[5]].add_neighbour_node(elementID);
                nodez_col[niz[6]].add_neighbour_node(elementID);
            }
        }

        if (nodez_col[niz[3]].get_flag())
        if (nodez_col[niz[2]].get_flag())
        if (nodez_col[niz[6]].get_flag())
        if (nodez_col[niz[7]].get_flag())
        {
            contact_surface_ID = assign_contact_surface_ID(one_element.get_material_ID(), material2ID, refs_to_contact_surfaces);

            if (contact_surface_ID != 0)
            {
                contact_face.set_ID(elementID);
                contact_face.set_node(niz[3], 1);
                contact_face.set_node(niz[2], 2);
                contact_face.set_node(niz[6], 3);
                contact_face.set_node(niz[7], 4);
                contact_face.set_node(contact_surface_ID, 5);
                contact_face.set_node(one_element.get_material_ID(), 6);
                contact_face.set_node(material2ID, 7);
                contact_faces_col.insert(contact_face);

                nodez_col[niz[3]].add_neighbour_node(elementID);
                nodez_col[niz[2]].add_neighbour_node(elementID);
                nodez_col[niz[6]].add_neighbour_node(elementID);
                nodez_col[niz[7]].add_neighbour_node(elementID);
            }
        }

        if (nodez_col[niz[4]].get_flag())
        if (nodez_col[niz[3]].get_flag())
        if (nodez_col[niz[7]].get_flag())
        if (nodez_col[niz[8]].get_flag())
        {
            contact_surface_ID = assign_contact_surface_ID(one_element.get_material_ID(), material2ID, refs_to_contact_surfaces);

            if (contact_surface_ID != 0)
            {
                contact_face.set_ID(elementID);
                contact_face.set_node(niz[4], 1);
                contact_face.set_node(niz[3], 2);
                contact_face.set_node(niz[7], 3);
                contact_face.set_node(niz[8], 4);
                contact_face.set_node(contact_surface_ID, 5);
                contact_face.set_node(one_element.get_material_ID(), 6);
                contact_face.set_node(material2ID, 7);
                contact_faces_col.insert(contact_face);

                nodez_col[niz[4]].add_neighbour_node(elementID);
                nodez_col[niz[3]].add_neighbour_node(elementID);
                nodez_col[niz[7]].add_neighbour_node(elementID);
                nodez_col[niz[8]].add_neighbour_node(elementID);
            }
        }
    }

    if (one_element.how_many_nodes_per_element() == 4)
    {
        if (nodez_col[niz[1]].get_flag())
        if (nodez_col[niz[2]].get_flag())
        if (nodez_col[niz[3]].get_flag())
        {
            contact_surface_ID = assign_contact_surface_ID
            (one_element.get_material_ID(), material2ID, refs_to_contact_surfaces);

            if (contact_surface_ID != 0)
            {
                contact_face.set_ID(elementID);
                contact_face.set_node(niz[1], 1);
                contact_face.set_node(niz[2], 2);
                contact_face.set_node(niz[3], 3);
                contact_face.set_node(contact_surface_ID, 4);
                contact_face.set_node(one_element.get_material_ID(), 5);
                contact_face.set_node(material2ID, 6);
                contact_faces_col.insert(contact_face);

                nodez_col[niz[1]].add_neighbour_node(elementID);
                nodez_col[niz[2]].add_neighbour_node(elementID);
                nodez_col[niz[3]].add_neighbour_node(elementID);
            }
        }

        if (nodez_col[niz[1]].get_flag())
        if (nodez_col[niz[3]].get_flag())
        if (nodez_col[niz[4]].get_flag())
        {
            contact_surface_ID = assign_contact_surface_ID
            (one_element.get_material_ID(), material2ID, refs_to_contact_surfaces);

            if (contact_surface_ID != 0)
            {
                contact_face.set_ID(elementID);
                contact_face.set_node(niz[1], 1);
                contact_face.set_node(niz[3], 2);
                contact_face.set_node(niz[4], 3);
                contact_face.set_node(contact_surface_ID, 4);
                contact_face.set_node(one_element.get_material_ID(), 5);
                contact_face.set_node(material2ID, 6);
                contact_faces_col.insert(contact_face);

                nodez_col[niz[1]].add_neighbour_node(elementID);
                nodez_col[niz[3]].add_neighbour_node(elementID);
                nodez_col[niz[4]].add_neighbour_node(elementID);
            }
        }

        if (nodez_col[niz[1]].get_flag())
        if (nodez_col[niz[4]].get_flag())
        if (nodez_col[niz[2]].get_flag())
        {
            contact_surface_ID = assign_contact_surface_ID
            (one_element.get_material_ID(), material2ID, refs_to_contact_surfaces);

            if (contact_surface_ID != 0)
            {
                contact_face.set_ID(elementID);
                contact_face.set_node(niz[1], 1);
                contact_face.set_node(niz[4], 2);
                contact_face.set_node(niz[2], 3);
                contact_face.set_node(contact_surface_ID, 4);
                contact_face.set_node(one_element.get_material_ID(), 5);
                contact_face.set_node(material2ID, 6);
                contact_faces_col.insert(contact_face);

                nodez_col[niz[1]].add_neighbour_node(elementID);
                nodez_col[niz[4]].add_neighbour_node(elementID);
                nodez_col[niz[2]].add_neighbour_node(elementID);
            }
        }

        if (nodez_col[niz[3]].get_flag())
        if (nodez_col[niz[2]].get_flag())
        if (nodez_col[niz[4]].get_flag())
        {
            contact_surface_ID = assign_contact_surface_ID
            (one_element.get_material_ID(), material2ID, refs_to_contact_surfaces);

            if (contact_surface_ID != 0)
            {
                contact_face.set_ID(elementID);
                contact_face.set_node(niz[3], 1);
                contact_face.set_node(niz[2], 2);
                contact_face.set_node(niz[4], 3);
                contact_face.set_node(contact_surface_ID, 4);
                contact_face.set_node(one_element.get_material_ID(), 5);
                contact_face.set_node(material2ID, 6);
                contact_faces_col.insert(contact_face);

                nodez_col[niz[3]].add_neighbour_node(elementID);
                nodez_col[niz[2]].add_neighbour_node(elementID);
                nodez_col[niz[4]].add_neighbour_node(elementID);
            }
        }
    }

    return true;
}

bool put_contact_edges_second(
UINT elementID,
Collection <Mesh_Node> & nodez_col,
Geom_Element & one_element,
Collection <Geom_Element> & contact_faces_col,
Collection <Geom_Element> & second_elem_col,
SuperCollection <UINT> & refs_to_contact_surfaces)
{
    UINT niz[10], contact_surface_ID;

    int countR = 0;

    Geom_Element contact_face;
    contact_face.set_flag(true);
    contact_face.set_boundary(true);

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

    UINT second_element_ID = 0;

    if (one_element.how_many_nodes_per_element() == 8)
    {
        if (nodez_col[niz[1]].get_flag())
        if (nodez_col[niz[2]].get_flag())
        if (nodez_col[niz[3]].get_flag())
        if (nodez_col[niz[4]].get_flag())
        {
            second_element_ID = neighbours::get_nodez_neighbour(
            nodez_col[niz[1]],
            nodez_col[niz[2]],
            nodez_col[niz[3]],
            nodez_col[niz[4]]);

            if (second_element_ID != 0)
            {
                contact_surface_ID = assign_contact_surface_ID(one_element.get_material_ID(), second_elem_col[second_element_ID].get_material_ID(), refs_to_contact_surfaces);

                contact_face.set_ID(elementID);
                contact_face.set_node(niz[1], 1);
                contact_face.set_node(niz[2], 2);
                contact_face.set_node(niz[3], 3);
                contact_face.set_node(niz[4], 4);
                contact_face.set_node(contact_surface_ID, 5);
                contact_face.set_node(one_element.get_material_ID(), 6);
                contact_face.set_node(second_elem_col[second_element_ID].get_material_ID(), 7);
                contact_faces_col.insert(contact_face);
            }
        }

        if (nodez_col[niz[8]].get_flag())
        if (nodez_col[niz[7]].get_flag())
        if (nodez_col[niz[6]].get_flag())
        if (nodez_col[niz[5]].get_flag())
        {
            second_element_ID = neighbours::get_nodez_neighbour(
            nodez_col[niz[8]],
            nodez_col[niz[7]],
            nodez_col[niz[6]],
            nodez_col[niz[5]]);

            if (second_element_ID != 0)
            {
                contact_surface_ID = assign_contact_surface_ID(one_element.get_material_ID(), second_elem_col[second_element_ID].get_material_ID(), refs_to_contact_surfaces);

                contact_face.set_ID(elementID);
                contact_face.set_node(niz[8], 1);
                contact_face.set_node(niz[7], 2);
                contact_face.set_node(niz[6], 3);
                contact_face.set_node(niz[5], 4);
                contact_face.set_node(contact_surface_ID, 5);
                contact_face.set_node(one_element.get_material_ID(), 6);
                contact_face.set_node(second_elem_col[second_element_ID].get_material_ID(), 7);
                contact_faces_col.insert(contact_face);
            }
        }

        if (nodez_col[niz[1]].get_flag())
        if (nodez_col[niz[4]].get_flag())
        if (nodez_col[niz[8]].get_flag())
        if (nodez_col[niz[5]].get_flag())
        {
            second_element_ID = neighbours::get_nodez_neighbour(
            nodez_col[niz[1]],
            nodez_col[niz[4]],
            nodez_col[niz[8]],
            nodez_col[niz[5]]);

            if (second_element_ID != 0)
            {
                contact_surface_ID = assign_contact_surface_ID(one_element.get_material_ID(), second_elem_col[second_element_ID].get_material_ID(), refs_to_contact_surfaces);

                contact_face.set_ID(elementID);
                contact_face.set_node(niz[1], 1);
                contact_face.set_node(niz[4], 2);
                contact_face.set_node(niz[8], 3);
                contact_face.set_node(niz[5], 4);
                contact_face.set_node(contact_surface_ID, 5);
                contact_face.set_node(one_element.get_material_ID(), 6);
                contact_face.set_node(second_elem_col[second_element_ID].get_material_ID(), 7);
                contact_faces_col.insert(contact_face);
            }
        }

        if (nodez_col[niz[2]].get_flag())
        if (nodez_col[niz[1]].get_flag())
        if (nodez_col[niz[5]].get_flag())
        if (nodez_col[niz[6]].get_flag())
        {
            second_element_ID = neighbours::get_nodez_neighbour(
            nodez_col[niz[2]],
            nodez_col[niz[1]],
            nodez_col[niz[5]],
            nodez_col[niz[6]]);

            if (second_element_ID != 0)
            {
                contact_surface_ID = assign_contact_surface_ID(one_element.get_material_ID(), second_elem_col[second_element_ID].get_material_ID(), refs_to_contact_surfaces);

                contact_face.set_ID(elementID);
                contact_face.set_node(niz[2], 1);
                contact_face.set_node(niz[1], 2);
                contact_face.set_node(niz[5], 3);
                contact_face.set_node(niz[6], 4);
                contact_face.set_node(contact_surface_ID, 5);
                contact_face.set_node(one_element.get_material_ID(), 6);
                contact_face.set_node(second_elem_col[second_element_ID].get_material_ID(), 7);
                contact_faces_col.insert(contact_face);
            }
        }

        if (nodez_col[niz[3]].get_flag())
        if (nodez_col[niz[2]].get_flag())
        if (nodez_col[niz[6]].get_flag())
        if (nodez_col[niz[7]].get_flag())
        {
            second_element_ID = neighbours::get_nodez_neighbour(
            nodez_col[niz[3]],
            nodez_col[niz[2]],
            nodez_col[niz[6]],
            nodez_col[niz[7]]);

            if (second_element_ID != 0)
            {
                contact_surface_ID = assign_contact_surface_ID(one_element.get_material_ID(), second_elem_col[second_element_ID].get_material_ID(), refs_to_contact_surfaces);

                contact_face.set_ID(elementID);
                contact_face.set_node(niz[3], 1);
                contact_face.set_node(niz[2], 2);
                contact_face.set_node(niz[6], 3);
                contact_face.set_node(niz[7], 4);
                contact_face.set_node(contact_surface_ID, 5);
                contact_face.set_node(one_element.get_material_ID(), 6);
                contact_face.set_node(second_elem_col[second_element_ID].get_material_ID(), 7);
                contact_faces_col.insert(contact_face);
            }
        }

        if (nodez_col[niz[4]].get_flag())
        if (nodez_col[niz[3]].get_flag())
        if (nodez_col[niz[7]].get_flag())
        if (nodez_col[niz[8]].get_flag())
        {
            second_element_ID = neighbours::get_nodez_neighbour(
            nodez_col[niz[4]],
            nodez_col[niz[3]],
            nodez_col[niz[7]],
            nodez_col[niz[8]]);

            if (second_element_ID != 0)
            {
                contact_surface_ID = assign_contact_surface_ID(one_element.get_material_ID(), second_elem_col[second_element_ID].get_material_ID(), refs_to_contact_surfaces);

                contact_face.set_ID(elementID);
                contact_face.set_node(niz[4], 1);
                contact_face.set_node(niz[3], 2);
                contact_face.set_node(niz[7], 3);
                contact_face.set_node(niz[8], 4);
                contact_face.set_node(contact_surface_ID, 5);
                contact_face.set_node(one_element.get_material_ID(), 6);
                contact_face.set_node(second_elem_col[second_element_ID].get_material_ID(), 7);
                contact_faces_col.insert(contact_face);
            }
        }
    }

    if (one_element.how_many_nodes_per_element() == 4)
    {
        if (nodez_col[niz[1]].get_flag())
        if (nodez_col[niz[2]].get_flag())
        if (nodez_col[niz[3]].get_flag())
        {
            second_element_ID = neighbours::get_nodez_neighbour(
            nodez_col[niz[1]],
            nodez_col[niz[2]],
            nodez_col[niz[3]]);

            if (second_element_ID != 0)
            {
                contact_surface_ID = assign_contact_surface_ID
                (one_element.get_material_ID(), second_elem_col[second_element_ID].get_material_ID(), refs_to_contact_surfaces);

                contact_face.set_ID(elementID);
                contact_face.set_node(niz[1], 1);
                contact_face.set_node(niz[2], 2);
                contact_face.set_node(niz[3], 3);
                contact_face.set_node(contact_surface_ID, 4);
                contact_face.set_node(one_element.get_material_ID(), 5);
                contact_face.set_node(second_elem_col[second_element_ID].get_material_ID(), 6);
                contact_faces_col.insert(contact_face);
            }
        }

        if (nodez_col[niz[1]].get_flag())
        if (nodez_col[niz[3]].get_flag())
        if (nodez_col[niz[4]].get_flag())
        {
            second_element_ID = neighbours::get_nodez_neighbour(
            nodez_col[niz[1]],
            nodez_col[niz[3]],
            nodez_col[niz[4]]);

            if (second_element_ID != 0)
            {
                contact_surface_ID = assign_contact_surface_ID
                (one_element.get_material_ID(), second_elem_col[second_element_ID].get_material_ID(), refs_to_contact_surfaces);

                contact_face.set_ID(elementID);
                contact_face.set_node(niz[1], 1);
                contact_face.set_node(niz[3], 2);
                contact_face.set_node(niz[4], 3);
                contact_face.set_node(contact_surface_ID, 4);
                contact_face.set_node(one_element.get_material_ID(), 5);
                contact_face.set_node(second_elem_col[second_element_ID].get_material_ID(), 6);
                contact_faces_col.insert(contact_face);
            }
        }

        if (nodez_col[niz[1]].get_flag())
        if (nodez_col[niz[4]].get_flag())
        if (nodez_col[niz[2]].get_flag())
        {
            second_element_ID = neighbours::get_nodez_neighbour(
            nodez_col[niz[1]],
            nodez_col[niz[4]],
            nodez_col[niz[2]]);

            if (second_element_ID != 0)
            {
                contact_surface_ID = assign_contact_surface_ID
                (one_element.get_material_ID(), second_elem_col[second_element_ID].get_material_ID(), refs_to_contact_surfaces);

                contact_face.set_ID(elementID);
                contact_face.set_node(niz[1], 1);
                contact_face.set_node(niz[4], 2);
                contact_face.set_node(niz[2], 3);
                contact_face.set_node(contact_surface_ID, 4);
                contact_face.set_node(one_element.get_material_ID(), 5);
                contact_face.set_node(second_elem_col[second_element_ID].get_material_ID(), 6);
                contact_faces_col.insert(contact_face);
            }
        }

        if (nodez_col[niz[3]].get_flag())
        if (nodez_col[niz[2]].get_flag())
        if (nodez_col[niz[4]].get_flag())
        {
            second_element_ID = neighbours::get_nodez_neighbour(
            nodez_col[niz[3]],
            nodez_col[niz[2]],
            nodez_col[niz[4]]);

            if (second_element_ID != 0)
            {
                contact_surface_ID = assign_contact_surface_ID
                (one_element.get_material_ID(), second_elem_col[second_element_ID].get_material_ID(), refs_to_contact_surfaces);

                contact_face.set_ID(elementID);
                contact_face.set_node(niz[3], 1);
                contact_face.set_node(niz[2], 2);
                contact_face.set_node(niz[4], 3);
                contact_face.set_node(contact_surface_ID, 4);
                contact_face.set_node(one_element.get_material_ID(), 5);
                contact_face.set_node(second_elem_col[second_element_ID].get_material_ID(), 6);
                contact_faces_col.insert(contact_face);
            }
        }
    }

    return true;
}

UINT assign_contact_surface_ID
(UINT material1_ID, UINT material2_ID, SuperCollection <UINT> &refs_2_contact_surfs)
{
    UINT max_surface_ID = 0;

    for (UINT i = 1; i <= refs_2_contact_surfs.get_size(); i++)
    {
        if ((refs_2_contact_surfs[i][1] == material1_ID) || (refs_2_contact_surfs[i][1] == material2_ID))
        if ((refs_2_contact_surfs[i][2] == material1_ID) || (refs_2_contact_surfs[i][2] == material2_ID))
            return refs_2_contact_surfs[i][3];

        if (max_surface_ID < refs_2_contact_surfs[i][3])
            max_surface_ID = refs_2_contact_surfs[i][3];
    }

    {
        Collection <UINT> ref_2_contact_surface;

        ref_2_contact_surface.insert(material1_ID);
        ref_2_contact_surface.insert(material2_ID);
        ref_2_contact_surface.insert(max_surface_ID + 1);

        refs_2_contact_surfs.insert(ref_2_contact_surface);
    }

    return max_surface_ID + 1;
}


bool put_contact_edges_first(
UINT elementID,
Collection <Mesh_Node> & nodez_col,
Geom_Element & one_element,
Collection <Geom_Element> & contact_faces_col,
UINT & material2ID,
UINT & cur_no_of_contacts)
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

            {
                contact_face.set_ID(elementID);
                contact_face.set_node(niz[1], 1);
                contact_face.set_node(niz[2], 2);
                contact_face.set_node(niz[3], 3);
                contact_face.set_node(niz[4], 4);
                contact_face.set_node(cur_no_of_contacts + 1, 5);
                contact_face.set_node(one_element.get_material_ID(), 6);
                contact_face.set_node(material2ID, 7);
                contact_faces_col.insert(contact_face);

                nodez_col[niz[1]].add_neighbour_node(elementID);
                nodez_col[niz[2]].add_neighbour_node(elementID);
                nodez_col[niz[3]].add_neighbour_node(elementID);
                nodez_col[niz[4]].add_neighbour_node(elementID);
            }
        }

        if (nodez_col[niz[8]].get_flag())
        if (nodez_col[niz[7]].get_flag())
        if (nodez_col[niz[6]].get_flag())
        if (nodez_col[niz[5]].get_flag())
        {

            {
                contact_face.set_ID(elementID);
                contact_face.set_node(niz[8], 1);
                contact_face.set_node(niz[7], 2);
                contact_face.set_node(niz[6], 3);
                contact_face.set_node(niz[5], 4);
                contact_face.set_node(cur_no_of_contacts + 1, 5);
                contact_face.set_node(one_element.get_material_ID(), 6);
                contact_face.set_node(material2ID, 7);
                contact_faces_col.insert(contact_face);

                nodez_col[niz[8]].add_neighbour_node(elementID);
                nodez_col[niz[7]].add_neighbour_node(elementID);
                nodez_col[niz[6]].add_neighbour_node(elementID);
                nodez_col[niz[5]].add_neighbour_node(elementID);
            }
        }

        if (nodez_col[niz[1]].get_flag())
        if (nodez_col[niz[4]].get_flag())
        if (nodez_col[niz[8]].get_flag())
        if (nodez_col[niz[5]].get_flag())
        {

            {
                contact_face.set_ID(elementID);
                contact_face.set_node(niz[1], 1);
                contact_face.set_node(niz[4], 2);
                contact_face.set_node(niz[8], 3);
                contact_face.set_node(niz[5], 4);
                contact_face.set_node(cur_no_of_contacts + 1, 5);
                contact_face.set_node(one_element.get_material_ID(), 6);
                contact_face.set_node(material2ID, 7);
                contact_faces_col.insert(contact_face);

                nodez_col[niz[1]].add_neighbour_node(elementID);
                nodez_col[niz[4]].add_neighbour_node(elementID);
                nodez_col[niz[8]].add_neighbour_node(elementID);
                nodez_col[niz[5]].add_neighbour_node(elementID);
            }
        }

        if (nodez_col[niz[2]].get_flag())
        if (nodez_col[niz[1]].get_flag())
        if (nodez_col[niz[5]].get_flag())
        if (nodez_col[niz[6]].get_flag())
        {

            {
                contact_face.set_ID(elementID);
                contact_face.set_node(niz[2], 1);
                contact_face.set_node(niz[1], 2);
                contact_face.set_node(niz[5], 3);
                contact_face.set_node(niz[6], 4);
                contact_face.set_node(cur_no_of_contacts + 1, 5);
                contact_face.set_node(one_element.get_material_ID(), 6);
                contact_face.set_node(material2ID, 7);
                contact_faces_col.insert(contact_face);

                nodez_col[niz[2]].add_neighbour_node(elementID);
                nodez_col[niz[1]].add_neighbour_node(elementID);
                nodez_col[niz[5]].add_neighbour_node(elementID);
                nodez_col[niz[6]].add_neighbour_node(elementID);
            }
        }

        if (nodez_col[niz[3]].get_flag())
        if (nodez_col[niz[2]].get_flag())
        if (nodez_col[niz[6]].get_flag())
        if (nodez_col[niz[7]].get_flag())
        {

            {
                contact_face.set_ID(elementID);
                contact_face.set_node(niz[3], 1);
                contact_face.set_node(niz[2], 2);
                contact_face.set_node(niz[6], 3);
                contact_face.set_node(niz[7], 4);
                contact_face.set_node(cur_no_of_contacts + 1, 5);
                contact_face.set_node(one_element.get_material_ID(), 6);
                contact_face.set_node(material2ID, 7);
                contact_faces_col.insert(contact_face);

                nodez_col[niz[3]].add_neighbour_node(elementID);
                nodez_col[niz[2]].add_neighbour_node(elementID);
                nodez_col[niz[6]].add_neighbour_node(elementID);
                nodez_col[niz[7]].add_neighbour_node(elementID);
            }
        }

        if (nodez_col[niz[4]].get_flag())
        if (nodez_col[niz[3]].get_flag())
        if (nodez_col[niz[7]].get_flag())
        if (nodez_col[niz[8]].get_flag())
        {

            {
                contact_face.set_ID(elementID);
                contact_face.set_node(niz[4], 1);
                contact_face.set_node(niz[3], 2);
                contact_face.set_node(niz[7], 3);
                contact_face.set_node(niz[8], 4);
                contact_face.set_node(cur_no_of_contacts + 1, 5);
                contact_face.set_node(one_element.get_material_ID(), 6);
                contact_face.set_node(material2ID, 7);
                contact_faces_col.insert(contact_face);

                nodez_col[niz[4]].add_neighbour_node(elementID);
                nodez_col[niz[3]].add_neighbour_node(elementID);
                nodez_col[niz[7]].add_neighbour_node(elementID);
                nodez_col[niz[8]].add_neighbour_node(elementID);
            }
        }
    }

    if (one_element.how_many_nodes_per_element() == 4)
    {
        if (nodez_col[niz[1]].get_flag())
        if (nodez_col[niz[2]].get_flag())
        if (nodez_col[niz[3]].get_flag())
        {

            {
                contact_face.set_ID(elementID);
                contact_face.set_node(niz[1], 1);
                contact_face.set_node(niz[2], 2);
                contact_face.set_node(niz[3], 3);
                contact_face.set_node(cur_no_of_contacts + 1, 4);
                contact_face.set_node(one_element.get_material_ID(), 5);
                contact_face.set_node(material2ID, 6);
                contact_faces_col.insert(contact_face);

                nodez_col[niz[1]].add_neighbour_node(elementID);
                nodez_col[niz[2]].add_neighbour_node(elementID);
                nodez_col[niz[3]].add_neighbour_node(elementID);
            }
        }

        if (nodez_col[niz[1]].get_flag())
        if (nodez_col[niz[3]].get_flag())
        if (nodez_col[niz[4]].get_flag())
        {

            {
                contact_face.set_ID(elementID);
                contact_face.set_node(niz[1], 1);
                contact_face.set_node(niz[3], 2);
                contact_face.set_node(niz[4], 3);
                contact_face.set_node(cur_no_of_contacts + 1, 4);
                contact_face.set_node(one_element.get_material_ID(), 5);
                contact_face.set_node(material2ID, 6);
                contact_faces_col.insert(contact_face);

                nodez_col[niz[1]].add_neighbour_node(elementID);
                nodez_col[niz[3]].add_neighbour_node(elementID);
                nodez_col[niz[4]].add_neighbour_node(elementID);
            }
        }

        if (nodez_col[niz[1]].get_flag())
        if (nodez_col[niz[4]].get_flag())
        if (nodez_col[niz[2]].get_flag())
        {

            {
                contact_face.set_ID(elementID);
                contact_face.set_node(niz[1], 1);
                contact_face.set_node(niz[4], 2);
                contact_face.set_node(niz[2], 3);
                contact_face.set_node(cur_no_of_contacts + 1, 4);
                contact_face.set_node(one_element.get_material_ID(), 5);
                contact_face.set_node(material2ID, 6);
                contact_faces_col.insert(contact_face);

                nodez_col[niz[1]].add_neighbour_node(elementID);
                nodez_col[niz[4]].add_neighbour_node(elementID);
                nodez_col[niz[2]].add_neighbour_node(elementID);
            }
        }

        if (nodez_col[niz[3]].get_flag())
        if (nodez_col[niz[2]].get_flag())
        if (nodez_col[niz[4]].get_flag())
        {

            {
                contact_face.set_ID(elementID);
                contact_face.set_node(niz[3], 1);
                contact_face.set_node(niz[2], 2);
                contact_face.set_node(niz[4], 3);
                contact_face.set_node(cur_no_of_contacts + 1, 4);
                contact_face.set_node(one_element.get_material_ID(), 5);
                contact_face.set_node(material2ID, 6);
                contact_faces_col.insert(contact_face);

                nodez_col[niz[3]].add_neighbour_node(elementID);
                nodez_col[niz[2]].add_neighbour_node(elementID);
                nodez_col[niz[4]].add_neighbour_node(elementID);
            }
        }
    }

    return true;
}

bool put_contact_edges_second(
UINT elementID,
Collection <Mesh_Node> & nodez_col,
Geom_Element & one_element,
Collection <Geom_Element> & contact_faces_col,
Collection <Geom_Element> & second_elem_col,
UINT & cur_no_of_contacts)
{
    UINT niz[10];

    int countR = 0;

    Geom_Element contact_face;
    contact_face.set_flag(true);
    contact_face.set_boundary(true);

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

    UINT second_element_ID = 0;

    if (one_element.how_many_nodes_per_element() == 8)
    {
        if (nodez_col[niz[1]].get_flag())
        if (nodez_col[niz[2]].get_flag())
        if (nodez_col[niz[3]].get_flag())
        if (nodez_col[niz[4]].get_flag())
        {
            second_element_ID = neighbours::get_nodez_neighbour(
            nodez_col[niz[1]],
            nodez_col[niz[2]],
            nodez_col[niz[3]],
            nodez_col[niz[4]]);

            if (second_element_ID != 0)
            {
                contact_face.set_ID(elementID);
                contact_face.set_node(niz[1], 1);
                contact_face.set_node(niz[2], 2);
                contact_face.set_node(niz[3], 3);
                contact_face.set_node(niz[4], 4);
                contact_face.set_node(cur_no_of_contacts + 1, 5);
                contact_face.set_node(one_element.get_material_ID(), 6);
                contact_face.set_node(second_elem_col[second_element_ID].get_material_ID(), 7);
                contact_faces_col.insert(contact_face);
            }
        }

        if (nodez_col[niz[8]].get_flag())
        if (nodez_col[niz[7]].get_flag())
        if (nodez_col[niz[6]].get_flag())
        if (nodez_col[niz[5]].get_flag())
        {
            second_element_ID = neighbours::get_nodez_neighbour(
            nodez_col[niz[8]],
            nodez_col[niz[7]],
            nodez_col[niz[6]],
            nodez_col[niz[5]]);

            if (second_element_ID != 0)
            {
                contact_face.set_ID(elementID);
                contact_face.set_node(niz[8], 1);
                contact_face.set_node(niz[7], 2);
                contact_face.set_node(niz[6], 3);
                contact_face.set_node(niz[5], 4);
                contact_face.set_node(cur_no_of_contacts + 1, 5);
                contact_face.set_node(one_element.get_material_ID(), 6);
                contact_face.set_node(second_elem_col[second_element_ID].get_material_ID(), 7);
                contact_faces_col.insert(contact_face);
            }
        }

        if (nodez_col[niz[1]].get_flag())
        if (nodez_col[niz[4]].get_flag())
        if (nodez_col[niz[8]].get_flag())
        if (nodez_col[niz[5]].get_flag())
        {
            second_element_ID = neighbours::get_nodez_neighbour(
            nodez_col[niz[1]],
            nodez_col[niz[4]],
            nodez_col[niz[8]],
            nodez_col[niz[5]]);

            if (second_element_ID != 0)
            {

                contact_face.set_ID(elementID);
                contact_face.set_node(niz[1], 1);
                contact_face.set_node(niz[4], 2);
                contact_face.set_node(niz[8], 3);
                contact_face.set_node(niz[5], 4);
                contact_face.set_node(cur_no_of_contacts + 1, 5);
                contact_face.set_node(one_element.get_material_ID(), 6);
                contact_face.set_node(second_elem_col[second_element_ID].get_material_ID(), 7);
                contact_faces_col.insert(contact_face);
            }
        }

        if (nodez_col[niz[2]].get_flag())
        if (nodez_col[niz[1]].get_flag())
        if (nodez_col[niz[5]].get_flag())
        if (nodez_col[niz[6]].get_flag())
        {
            second_element_ID = neighbours::get_nodez_neighbour(
            nodez_col[niz[2]],
            nodez_col[niz[1]],
            nodez_col[niz[5]],
            nodez_col[niz[6]]);

            if (second_element_ID != 0)
            {

                contact_face.set_ID(elementID);
                contact_face.set_node(niz[2], 1);
                contact_face.set_node(niz[1], 2);
                contact_face.set_node(niz[5], 3);
                contact_face.set_node(niz[6], 4);
                contact_face.set_node(cur_no_of_contacts + 1, 5);
                contact_face.set_node(one_element.get_material_ID(), 6);
                contact_face.set_node(second_elem_col[second_element_ID].get_material_ID(), 7);
                contact_faces_col.insert(contact_face);
            }
        }

        if (nodez_col[niz[3]].get_flag())
        if (nodez_col[niz[2]].get_flag())
        if (nodez_col[niz[6]].get_flag())
        if (nodez_col[niz[7]].get_flag())
        {
            second_element_ID = neighbours::get_nodez_neighbour(
            nodez_col[niz[3]],
            nodez_col[niz[2]],
            nodez_col[niz[6]],
            nodez_col[niz[7]]);

            if (second_element_ID != 0)
            {

                contact_face.set_ID(elementID);
                contact_face.set_node(niz[3], 1);
                contact_face.set_node(niz[2], 2);
                contact_face.set_node(niz[6], 3);
                contact_face.set_node(niz[7], 4);
                contact_face.set_node(cur_no_of_contacts + 1, 5);
                contact_face.set_node(one_element.get_material_ID(), 6);
                contact_face.set_node(second_elem_col[second_element_ID].get_material_ID(), 7);
                contact_faces_col.insert(contact_face);
            }
        }

        if (nodez_col[niz[4]].get_flag())
        if (nodez_col[niz[3]].get_flag())
        if (nodez_col[niz[7]].get_flag())
        if (nodez_col[niz[8]].get_flag())
        {
            second_element_ID = neighbours::get_nodez_neighbour(
            nodez_col[niz[4]],
            nodez_col[niz[3]],
            nodez_col[niz[7]],
            nodez_col[niz[8]]);

            if (second_element_ID != 0)
            {

                contact_face.set_ID(elementID);
                contact_face.set_node(niz[4], 1);
                contact_face.set_node(niz[3], 2);
                contact_face.set_node(niz[7], 3);
                contact_face.set_node(niz[8], 4);
                contact_face.set_node(cur_no_of_contacts + 1, 5);
                contact_face.set_node(one_element.get_material_ID(), 6);
                contact_face.set_node(second_elem_col[second_element_ID].get_material_ID(), 7);
                contact_faces_col.insert(contact_face);
            }
        }
    }

    if (one_element.how_many_nodes_per_element() == 4)
    {
        if (nodez_col[niz[1]].get_flag())
        if (nodez_col[niz[2]].get_flag())
        if (nodez_col[niz[3]].get_flag())
        {
            second_element_ID = neighbours::get_nodez_neighbour(
            nodez_col[niz[1]],
            nodez_col[niz[2]],
            nodez_col[niz[3]]);

            if (second_element_ID != 0)
            {

                contact_face.set_ID(elementID);
                contact_face.set_node(niz[1], 1);
                contact_face.set_node(niz[2], 2);
                contact_face.set_node(niz[3], 3);
                contact_face.set_node(cur_no_of_contacts + 1, 4);
                contact_face.set_node(one_element.get_material_ID(), 5);
                contact_face.set_node(second_elem_col[second_element_ID].get_material_ID(), 6);
                contact_faces_col.insert(contact_face);
            }
        }

        if (nodez_col[niz[1]].get_flag())
        if (nodez_col[niz[3]].get_flag())
        if (nodez_col[niz[4]].get_flag())
        {
            second_element_ID = neighbours::get_nodez_neighbour(
            nodez_col[niz[1]],
            nodez_col[niz[3]],
            nodez_col[niz[4]]);

            if (second_element_ID != 0)
            {

                contact_face.set_ID(elementID);
                contact_face.set_node(niz[1], 1);
                contact_face.set_node(niz[3], 2);
                contact_face.set_node(niz[4], 3);
                contact_face.set_node(cur_no_of_contacts + 1, 4);
                contact_face.set_node(one_element.get_material_ID(), 5);
                contact_face.set_node(second_elem_col[second_element_ID].get_material_ID(), 6);
                contact_faces_col.insert(contact_face);
            }
        }

        if (nodez_col[niz[1]].get_flag())
        if (nodez_col[niz[4]].get_flag())
        if (nodez_col[niz[2]].get_flag())
        {
            second_element_ID = neighbours::get_nodez_neighbour(
            nodez_col[niz[1]],
            nodez_col[niz[4]],
            nodez_col[niz[2]]);

            if (second_element_ID != 0)
            {

                contact_face.set_ID(elementID);
                contact_face.set_node(niz[1], 1);
                contact_face.set_node(niz[4], 2);
                contact_face.set_node(niz[2], 3);
                contact_face.set_node(cur_no_of_contacts + 1, 4);
                contact_face.set_node(one_element.get_material_ID(), 5);
                contact_face.set_node(second_elem_col[second_element_ID].get_material_ID(), 6);
                contact_faces_col.insert(contact_face);
            }
        }

        if (nodez_col[niz[3]].get_flag())
        if (nodez_col[niz[2]].get_flag())
        if (nodez_col[niz[4]].get_flag())
        {
            second_element_ID = neighbours::get_nodez_neighbour(
            nodez_col[niz[3]],
            nodez_col[niz[2]],
            nodez_col[niz[4]]);

            if (second_element_ID != 0)
            {

                contact_face.set_ID(elementID);
                contact_face.set_node(niz[3], 1);
                contact_face.set_node(niz[2], 2);
                contact_face.set_node(niz[4], 3);
                contact_face.set_node(cur_no_of_contacts + 1, 4);
                contact_face.set_node(one_element.get_material_ID(), 5);
                contact_face.set_node(second_elem_col[second_element_ID].get_material_ID(), 6);
                contact_faces_col.insert(contact_face);
            }
        }
    }

    return true;
}


bool put_contact_edges_first(
UINT elementID,
Collection <Mesh_Node> & nodez_col,
Geom_Element & one_element,
Collection <Geom_Element> & contact_faces_col,
UINT & material2ID)
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

            {
                contact_face.set_ID(elementID);
                contact_face.set_node(niz[1], 1);
                contact_face.set_node(niz[2], 2);
                contact_face.set_node(niz[3], 3);
                contact_face.set_node(niz[4], 4);
                contact_face.set_node(0, 5);
                contact_face.set_node(one_element.get_material_ID(), 6);
                contact_face.set_node(material2ID, 7);
                contact_faces_col.insert(contact_face);

                nodez_col[niz[1]].add_neighbour_node(elementID);
                nodez_col[niz[2]].add_neighbour_node(elementID);
                nodez_col[niz[3]].add_neighbour_node(elementID);
                nodez_col[niz[4]].add_neighbour_node(elementID);
            }
        }

        if (nodez_col[niz[8]].get_flag())
        if (nodez_col[niz[7]].get_flag())
        if (nodez_col[niz[6]].get_flag())
        if (nodez_col[niz[5]].get_flag())
        {

            {
                contact_face.set_ID(elementID);
                contact_face.set_node(niz[8], 1);
                contact_face.set_node(niz[7], 2);
                contact_face.set_node(niz[6], 3);
                contact_face.set_node(niz[5], 4);
                contact_face.set_node(0, 5);
                contact_face.set_node(one_element.get_material_ID(), 6);
                contact_face.set_node(material2ID, 7);
                contact_faces_col.insert(contact_face);

                nodez_col[niz[8]].add_neighbour_node(elementID);
                nodez_col[niz[7]].add_neighbour_node(elementID);
                nodez_col[niz[6]].add_neighbour_node(elementID);
                nodez_col[niz[5]].add_neighbour_node(elementID);
            }
        }

        if (nodez_col[niz[1]].get_flag())
        if (nodez_col[niz[4]].get_flag())
        if (nodez_col[niz[8]].get_flag())
        if (nodez_col[niz[5]].get_flag())
        {

            {
                contact_face.set_ID(elementID);
                contact_face.set_node(niz[1], 1);
                contact_face.set_node(niz[4], 2);
                contact_face.set_node(niz[8], 3);
                contact_face.set_node(niz[5], 4);
                contact_face.set_node(0, 5);
                contact_face.set_node(one_element.get_material_ID(), 6);
                contact_face.set_node(material2ID, 7);
                contact_faces_col.insert(contact_face);

                nodez_col[niz[1]].add_neighbour_node(elementID);
                nodez_col[niz[4]].add_neighbour_node(elementID);
                nodez_col[niz[8]].add_neighbour_node(elementID);
                nodez_col[niz[5]].add_neighbour_node(elementID);
            }
        }

        if (nodez_col[niz[2]].get_flag())
        if (nodez_col[niz[1]].get_flag())
        if (nodez_col[niz[5]].get_flag())
        if (nodez_col[niz[6]].get_flag())
        {

            {
                contact_face.set_ID(elementID);
                contact_face.set_node(niz[2], 1);
                contact_face.set_node(niz[1], 2);
                contact_face.set_node(niz[5], 3);
                contact_face.set_node(niz[6], 4);
                contact_face.set_node(0, 5);
                contact_face.set_node(one_element.get_material_ID(), 6);
                contact_face.set_node(material2ID, 7);
                contact_faces_col.insert(contact_face);

                nodez_col[niz[2]].add_neighbour_node(elementID);
                nodez_col[niz[1]].add_neighbour_node(elementID);
                nodez_col[niz[5]].add_neighbour_node(elementID);
                nodez_col[niz[6]].add_neighbour_node(elementID);
            }
        }

        if (nodez_col[niz[3]].get_flag())
        if (nodez_col[niz[2]].get_flag())
        if (nodez_col[niz[6]].get_flag())
        if (nodez_col[niz[7]].get_flag())
        {

            {
                contact_face.set_ID(elementID);
                contact_face.set_node(niz[3], 1);
                contact_face.set_node(niz[2], 2);
                contact_face.set_node(niz[6], 3);
                contact_face.set_node(niz[7], 4);
                contact_face.set_node(0, 5);
                contact_face.set_node(one_element.get_material_ID(), 6);
                contact_face.set_node(material2ID, 7);
                contact_faces_col.insert(contact_face);

                nodez_col[niz[3]].add_neighbour_node(elementID);
                nodez_col[niz[2]].add_neighbour_node(elementID);
                nodez_col[niz[6]].add_neighbour_node(elementID);
                nodez_col[niz[7]].add_neighbour_node(elementID);
            }
        }

        if (nodez_col[niz[4]].get_flag())
        if (nodez_col[niz[3]].get_flag())
        if (nodez_col[niz[7]].get_flag())
        if (nodez_col[niz[8]].get_flag())
        {

            {
                contact_face.set_ID(elementID);
                contact_face.set_node(niz[4], 1);
                contact_face.set_node(niz[3], 2);
                contact_face.set_node(niz[7], 3);
                contact_face.set_node(niz[8], 4);
                contact_face.set_node(0, 5);
                contact_face.set_node(one_element.get_material_ID(), 6);
                contact_face.set_node(material2ID, 7);
                contact_faces_col.insert(contact_face);

                nodez_col[niz[4]].add_neighbour_node(elementID);
                nodez_col[niz[3]].add_neighbour_node(elementID);
                nodez_col[niz[7]].add_neighbour_node(elementID);
                nodez_col[niz[8]].add_neighbour_node(elementID);
            }
        }
    }

    if (one_element.how_many_nodes_per_element() == 4)
    {
        if (nodez_col[niz[1]].get_flag())
        if (nodez_col[niz[2]].get_flag())
        if (nodez_col[niz[3]].get_flag())
        {

            {
                contact_face.set_ID(elementID);
                contact_face.set_node(niz[1], 1);
                contact_face.set_node(niz[2], 2);
                contact_face.set_node(niz[3], 3);
                contact_face.set_node(0, 4);
                contact_face.set_node(one_element.get_material_ID(), 5);
                contact_face.set_node(material2ID, 6);
                contact_faces_col.insert(contact_face);

                nodez_col[niz[1]].add_neighbour_node(elementID);
                nodez_col[niz[2]].add_neighbour_node(elementID);
                nodez_col[niz[3]].add_neighbour_node(elementID);
            }
        }

        if (nodez_col[niz[1]].get_flag())
        if (nodez_col[niz[3]].get_flag())
        if (nodez_col[niz[4]].get_flag())
        {

            {
                contact_face.set_ID(elementID);
                contact_face.set_node(niz[1], 1);
                contact_face.set_node(niz[3], 2);
                contact_face.set_node(niz[4], 3);
                contact_face.set_node(0, 4);
                contact_face.set_node(one_element.get_material_ID(), 5);
                contact_face.set_node(material2ID, 6);
                contact_faces_col.insert(contact_face);

                nodez_col[niz[1]].add_neighbour_node(elementID);
                nodez_col[niz[3]].add_neighbour_node(elementID);
                nodez_col[niz[4]].add_neighbour_node(elementID);
            }
        }

        if (nodez_col[niz[1]].get_flag())
        if (nodez_col[niz[4]].get_flag())
        if (nodez_col[niz[2]].get_flag())
        {

            {
                contact_face.set_ID(elementID);
                contact_face.set_node(niz[1], 1);
                contact_face.set_node(niz[4], 2);
                contact_face.set_node(niz[2], 3);
                contact_face.set_node(0, 4);
                contact_face.set_node(one_element.get_material_ID(), 5);
                contact_face.set_node(material2ID, 6);
                contact_faces_col.insert(contact_face);

                nodez_col[niz[1]].add_neighbour_node(elementID);
                nodez_col[niz[4]].add_neighbour_node(elementID);
                nodez_col[niz[2]].add_neighbour_node(elementID);
            }
        }

        if (nodez_col[niz[3]].get_flag())
        if (nodez_col[niz[2]].get_flag())
        if (nodez_col[niz[4]].get_flag())
        {

            {
                contact_face.set_ID(elementID);
                contact_face.set_node(niz[3], 1);
                contact_face.set_node(niz[2], 2);
                contact_face.set_node(niz[4], 3);
                contact_face.set_node(0, 4);
                contact_face.set_node(one_element.get_material_ID(), 5);
                contact_face.set_node(material2ID, 6);
                contact_faces_col.insert(contact_face);

                nodez_col[niz[3]].add_neighbour_node(elementID);
                nodez_col[niz[2]].add_neighbour_node(elementID);
                nodez_col[niz[4]].add_neighbour_node(elementID);
            }
        }
    }

    return true;
}

bool put_contact_edges_second(
UINT elementID,
Collection <Mesh_Node> & nodez_col,
Geom_Element & one_element,
Collection <Geom_Element> & contact_faces_col,
Collection <Geom_Element> & second_elem_col)
{
    UINT niz[10];

    int countR = 0;

    Geom_Element contact_face;
    contact_face.set_flag(true);
    contact_face.set_boundary(true);

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

    UINT second_element_ID = 0;

    if (one_element.how_many_nodes_per_element() == 8)
    {
        if (nodez_col[niz[1]].get_flag())
        if (nodez_col[niz[2]].get_flag())
        if (nodez_col[niz[3]].get_flag())
        if (nodez_col[niz[4]].get_flag())
        {
            second_element_ID = neighbours::get_nodez_neighbour(
            nodez_col[niz[1]],
            nodez_col[niz[2]],
            nodez_col[niz[3]],
            nodez_col[niz[4]]);

            if (second_element_ID != 0)
            {
                contact_face.set_ID(elementID);
                contact_face.set_node(niz[1], 1);
                contact_face.set_node(niz[2], 2);
                contact_face.set_node(niz[3], 3);
                contact_face.set_node(niz[4], 4);
                contact_face.set_node(0, 5);
                contact_face.set_node(one_element.get_material_ID(), 6);
                contact_face.set_node(second_elem_col[second_element_ID].get_material_ID(), 7);
                contact_faces_col.insert(contact_face);
            }
        }

        if (nodez_col[niz[8]].get_flag())
        if (nodez_col[niz[7]].get_flag())
        if (nodez_col[niz[6]].get_flag())
        if (nodez_col[niz[5]].get_flag())
        {
            second_element_ID = neighbours::get_nodez_neighbour(
            nodez_col[niz[8]],
            nodez_col[niz[7]],
            nodez_col[niz[6]],
            nodez_col[niz[5]]);

            if (second_element_ID != 0)
            {
                contact_face.set_ID(elementID);
                contact_face.set_node(niz[8], 1);
                contact_face.set_node(niz[7], 2);
                contact_face.set_node(niz[6], 3);
                contact_face.set_node(niz[5], 4);
                contact_face.set_node(0, 5);
                contact_face.set_node(one_element.get_material_ID(), 6);
                contact_face.set_node(second_elem_col[second_element_ID].get_material_ID(), 7);
                contact_faces_col.insert(contact_face);
            }
        }

        if (nodez_col[niz[1]].get_flag())
        if (nodez_col[niz[4]].get_flag())
        if (nodez_col[niz[8]].get_flag())
        if (nodez_col[niz[5]].get_flag())
        {
            second_element_ID = neighbours::get_nodez_neighbour(
            nodez_col[niz[1]],
            nodez_col[niz[4]],
            nodez_col[niz[8]],
            nodez_col[niz[5]]);

            if (second_element_ID != 0)
            {

                contact_face.set_ID(elementID);
                contact_face.set_node(niz[1], 1);
                contact_face.set_node(niz[4], 2);
                contact_face.set_node(niz[8], 3);
                contact_face.set_node(niz[5], 4);
                contact_face.set_node(0, 5);
                contact_face.set_node(one_element.get_material_ID(), 6);
                contact_face.set_node(second_elem_col[second_element_ID].get_material_ID(), 7);
                contact_faces_col.insert(contact_face);
            }
        }

        if (nodez_col[niz[2]].get_flag())
        if (nodez_col[niz[1]].get_flag())
        if (nodez_col[niz[5]].get_flag())
        if (nodez_col[niz[6]].get_flag())
        {
            second_element_ID = neighbours::get_nodez_neighbour(
            nodez_col[niz[2]],
            nodez_col[niz[1]],
            nodez_col[niz[5]],
            nodez_col[niz[6]]);

            if (second_element_ID != 0)
            {

                contact_face.set_ID(elementID);
                contact_face.set_node(niz[2], 1);
                contact_face.set_node(niz[1], 2);
                contact_face.set_node(niz[5], 3);
                contact_face.set_node(niz[6], 4);
                contact_face.set_node(0, 5);
                contact_face.set_node(one_element.get_material_ID(), 6);
                contact_face.set_node(second_elem_col[second_element_ID].get_material_ID(), 7);
                contact_faces_col.insert(contact_face);
            }
        }

        if (nodez_col[niz[3]].get_flag())
        if (nodez_col[niz[2]].get_flag())
        if (nodez_col[niz[6]].get_flag())
        if (nodez_col[niz[7]].get_flag())
        {
            second_element_ID = neighbours::get_nodez_neighbour(
            nodez_col[niz[3]],
            nodez_col[niz[2]],
            nodez_col[niz[6]],
            nodez_col[niz[7]]);

            if (second_element_ID != 0)
            {

                contact_face.set_ID(elementID);
                contact_face.set_node(niz[3], 1);
                contact_face.set_node(niz[2], 2);
                contact_face.set_node(niz[6], 3);
                contact_face.set_node(niz[7], 4);
                contact_face.set_node(0, 5);
                contact_face.set_node(one_element.get_material_ID(), 6);
                contact_face.set_node(second_elem_col[second_element_ID].get_material_ID(), 7);
                contact_faces_col.insert(contact_face);
            }
        }

        if (nodez_col[niz[4]].get_flag())
        if (nodez_col[niz[3]].get_flag())
        if (nodez_col[niz[7]].get_flag())
        if (nodez_col[niz[8]].get_flag())
        {
            second_element_ID = neighbours::get_nodez_neighbour(
            nodez_col[niz[4]],
            nodez_col[niz[3]],
            nodez_col[niz[7]],
            nodez_col[niz[8]]);

            if (second_element_ID != 0)
            {

                contact_face.set_ID(elementID);
                contact_face.set_node(niz[4], 1);
                contact_face.set_node(niz[3], 2);
                contact_face.set_node(niz[7], 3);
                contact_face.set_node(niz[8], 4);
                contact_face.set_node(0, 5);
                contact_face.set_node(one_element.get_material_ID(), 6);
                contact_face.set_node(second_elem_col[second_element_ID].get_material_ID(), 7);
                contact_faces_col.insert(contact_face);
            }
        }
    }

    if (one_element.how_many_nodes_per_element() == 4)
    {
        if (nodez_col[niz[1]].get_flag())
        if (nodez_col[niz[2]].get_flag())
        if (nodez_col[niz[3]].get_flag())
        {
            second_element_ID = neighbours::get_nodez_neighbour(
            nodez_col[niz[1]],
            nodez_col[niz[2]],
            nodez_col[niz[3]]);

            if (second_element_ID != 0)
            {

                contact_face.set_ID(elementID);
                contact_face.set_node(niz[1], 1);
                contact_face.set_node(niz[2], 2);
                contact_face.set_node(niz[3], 3);
                contact_face.set_node(0, 4);
                contact_face.set_node(one_element.get_material_ID(), 5);
                contact_face.set_node(second_elem_col[second_element_ID].get_material_ID(), 6);
                contact_faces_col.insert(contact_face);
            }
        }

        if (nodez_col[niz[1]].get_flag())
        if (nodez_col[niz[3]].get_flag())
        if (nodez_col[niz[4]].get_flag())
        {
            second_element_ID = neighbours::get_nodez_neighbour(
            nodez_col[niz[1]],
            nodez_col[niz[3]],
            nodez_col[niz[4]]);

            if (second_element_ID != 0)
            {

                contact_face.set_ID(elementID);
                contact_face.set_node(niz[1], 1);
                contact_face.set_node(niz[3], 2);
                contact_face.set_node(niz[4], 3);
                contact_face.set_node(0, 4);
                contact_face.set_node(one_element.get_material_ID(), 5);
                contact_face.set_node(second_elem_col[second_element_ID].get_material_ID(), 6);
                contact_faces_col.insert(contact_face);
            }
        }

        if (nodez_col[niz[1]].get_flag())
        if (nodez_col[niz[4]].get_flag())
        if (nodez_col[niz[2]].get_flag())
        {
            second_element_ID = neighbours::get_nodez_neighbour(
            nodez_col[niz[1]],
            nodez_col[niz[4]],
            nodez_col[niz[2]]);

            if (second_element_ID != 0)
            {

                contact_face.set_ID(elementID);
                contact_face.set_node(niz[1], 1);
                contact_face.set_node(niz[4], 2);
                contact_face.set_node(niz[2], 3);
                contact_face.set_node(0, 4);
                contact_face.set_node(one_element.get_material_ID(), 5);
                contact_face.set_node(second_elem_col[second_element_ID].get_material_ID(), 6);
                contact_faces_col.insert(contact_face);
            }
        }

        if (nodez_col[niz[3]].get_flag())
        if (nodez_col[niz[2]].get_flag())
        if (nodez_col[niz[4]].get_flag())
        {
            second_element_ID = neighbours::get_nodez_neighbour(
            nodez_col[niz[3]],
            nodez_col[niz[2]],
            nodez_col[niz[4]]);

            if (second_element_ID != 0)
            {

                contact_face.set_ID(elementID);
                contact_face.set_node(niz[3], 1);
                contact_face.set_node(niz[2], 2);
                contact_face.set_node(niz[4], 3);
                contact_face.set_node(0, 4);
                contact_face.set_node(one_element.get_material_ID(), 5);
                contact_face.set_node(second_elem_col[second_element_ID].get_material_ID(), 6);
                contact_faces_col.insert(contact_face);
            }
        }
    }

    return true;
}


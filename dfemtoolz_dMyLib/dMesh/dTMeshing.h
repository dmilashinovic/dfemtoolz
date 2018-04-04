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
 * File:   dTMeshing.h
 *
 *
 *
 *
 *
 */


#ifndef _DTMESHING_H
#define	_DTMESHING_H


#include "../dfemtoolz_dMyLib.h"

#include "../dBase/dConstants.h"
#include "../dBase/dCollection.h"

#include "../dGeom/dGeom_Element.h"
#include "../dGeom/dGeom_Functions.h"
#include "../dGeom/dGeom_TFunctions.h"

#include "../dMesh/dMesh_Node.h"

#include "../dMisc/dMisc_Functionz.h"
#include "../dMisc/dPercent.h"

#include "../dPrin/dInfo.h"

#include "dMesh_Neighbours.h"

namespace tmeshing
{

    template <class T>
    bool is_surface_facet
    (UINT n1, UINT n2, UINT n3, UINT n4, Collection <T> & node_col)
    {
/*
        if ((node_col[n1].get_boundary() & constants::IS_BOUNDARY_V) == constants::IS_BOUNDARY_V)
        if ((node_col[n2].get_boundary() & constants::IS_BOUNDARY_V) == constants::IS_BOUNDARY_V)
        if ((node_col[n3].get_boundary() & constants::IS_BOUNDARY_V) == constants::IS_BOUNDARY_V)
        if ((node_col[n4].get_boundary() & constants::IS_BOUNDARY_V) == constants::IS_BOUNDARY_V)
*/
        if (node_col[n1].get_boundary() & constants::IS_BOUNDARY_VX ||
            node_col[n1].get_boundary() & constants::IS_BOUNDARY_VY ||
            node_col[n1].get_boundary() & constants::IS_BOUNDARY_VZ)
        if (node_col[n2].get_boundary() & constants::IS_BOUNDARY_VX ||
            node_col[n2].get_boundary() & constants::IS_BOUNDARY_VY ||
            node_col[n2].get_boundary() & constants::IS_BOUNDARY_VZ)
        if (node_col[n3].get_boundary() & constants::IS_BOUNDARY_VX ||
            node_col[n3].get_boundary() & constants::IS_BOUNDARY_VY ||
            node_col[n3].get_boundary() & constants::IS_BOUNDARY_VZ)
        if (node_col[n4].get_boundary() & constants::IS_BOUNDARY_VX ||
            node_col[n4].get_boundary() & constants::IS_BOUNDARY_VY ||
            node_col[n4].get_boundary() & constants::IS_BOUNDARY_VZ)
            return true;
        return false;
    }

    template <class T>
    bool is_surface_facet
    (UINT n1, UINT n2, UINT n3, Collection <T> & node_col)
    {
/*
        if ((node_col[n1].get_boundary() & constants::IS_BOUNDARY_V) == constants::IS_BOUNDARY_V)
        if ((node_col[n2].get_boundary() & constants::IS_BOUNDARY_V) == constants::IS_BOUNDARY_V)
        if ((node_col[n3].get_boundary() & constants::IS_BOUNDARY_V) == constants::IS_BOUNDARY_V)
        if ((node_col[n4].get_boundary() & constants::IS_BOUNDARY_V) == constants::IS_BOUNDARY_V)
*/
        if (node_col[n1].get_boundary() & constants::IS_BOUNDARY_VX ||
            node_col[n1].get_boundary() & constants::IS_BOUNDARY_VY ||
            node_col[n1].get_boundary() & constants::IS_BOUNDARY_VZ)
        if (node_col[n2].get_boundary() & constants::IS_BOUNDARY_VX ||
            node_col[n2].get_boundary() & constants::IS_BOUNDARY_VY ||
            node_col[n2].get_boundary() & constants::IS_BOUNDARY_VZ)
        if (node_col[n3].get_boundary() & constants::IS_BOUNDARY_VX ||
            node_col[n3].get_boundary() & constants::IS_BOUNDARY_VY ||
            node_col[n3].get_boundary() & constants::IS_BOUNDARY_VZ)
            return true;
        return false;
    }

    template <class T>
    bool get_if_surface_facet
    (Geom_Element & quad, UINT n1, UINT n2, UINT n3, UINT n4, Collection <T> & node_col)
    {
        if (is_surface_facet(n1, n2, n3, n4, node_col))
        {
            quad.set_node(n1, 1);
            quad.set_node(n2, 2);
            quad.set_node(n3, 3);
            quad.set_node(n4, 4);
            return true;
        }
        return false;
    }

    template <class T>
    bool get_if_surface_facet
    (Geom_Element & triangle, UINT n1, UINT n2, UINT n3, Collection <T> & node_col)
    {
        if (is_surface_facet(n1, n2, n3, node_col))
        {
            triangle.set_node(n1, 1);
            triangle.set_node(n2, 2);
            triangle.set_node(n3, 3);
            return true;
        }
        return false;
    }

    template <class T>
    void put_surface_facetz
    (Collection <Geom_Element> & face_col, Collection <Geom_Element> & elem_col, Collection <T> & node_col)
    {
        Geom_Element face;

        if (elem_col[1].how_many_nodes_per_element() == constants::BRICK)
            face.set_nodes_per_element(4);

        for (UINT i = 1; i <= elem_col.get_size();i++)
        if (elem_col[i].get_boundary())
        {
            if (get_if_surface_facet
            (face,
            elem_col[i].get_node(1),
            elem_col[i].get_node(2),
            elem_col[i].get_node(3),
            elem_col[i].get_node(4),
            node_col))
            {
                face.set_ID(i);
                face_col.insert(face);
            }

            if (get_if_surface_facet
            (face,
            elem_col[i].get_node(5),
            elem_col[i].get_node(8),
            elem_col[i].get_node(7),
            elem_col[i].get_node(6),
            node_col))
            {
                face.set_ID(i);
                face_col.insert(face);
            }

            if (get_if_surface_facet
            (face,
            elem_col[i].get_node(6),
            elem_col[i].get_node(7),
            elem_col[i].get_node(3),
            elem_col[i].get_node(2),
            node_col))
            {
                face.set_ID(i);
                face_col.insert(face);
            }

            if (get_if_surface_facet
            (face,
            elem_col[i].get_node(7),
            elem_col[i].get_node(8),
            elem_col[i].get_node(4),
            elem_col[i].get_node(3),
            node_col))
            {
                face.set_ID(i);
                face_col.insert(face);
            }

            if (get_if_surface_facet
            (face,
            elem_col[i].get_node(8),
            elem_col[i].get_node(5),
            elem_col[i].get_node(1),
            elem_col[i].get_node(4),
            node_col))
            {
                face.set_ID(i);
                face_col.insert(face);
            }

            if (get_if_surface_facet
            (face,
            elem_col[i].get_node(6),
            elem_col[i].get_node(2),
            elem_col[i].get_node(1),
            elem_col[i].get_node(5),
            node_col))
            {
                face.set_ID(i);
                face_col.insert(face);
            }
        }
    }

    template <class T>
    void put_surface_facetz
    (int material_ID, Collection <Geom_Element> & face_col, Collection <Geom_Element> & elem_col, Collection <T> & node_col)
    {
        Geom_Element face;

        if (elem_col[1].how_many_nodes_per_element() == constants::BRICK)
            face.set_nodes_per_element(4);

        if (elem_col[1].how_many_nodes_per_element() == constants::TETRA)
            face.set_nodes_per_element(3);

        for (UINT i = 1; i <= elem_col.get_size();i++)
        if (elem_col[i].get_boundary())
        if (elem_col[i].get_material_ID() == material_ID)
        {
            if (elem_col[1].how_many_nodes_per_element() == constants::BRICK)
            {
                if (get_if_surface_facet
                (face,
                elem_col[i].get_node(1),
                elem_col[i].get_node(2),
                elem_col[i].get_node(3),
                elem_col[i].get_node(4),
                node_col))
                {
                    face.set_ID(i);
                    face_col.insert(face);
                }

                if (get_if_surface_facet
                (face,
                elem_col[i].get_node(5),
                elem_col[i].get_node(8),
                elem_col[i].get_node(7),
                elem_col[i].get_node(6),
                node_col))
                {
                    face.set_ID(i);
                    face_col.insert(face);
                }

                if (get_if_surface_facet
                (face,
                elem_col[i].get_node(6),
                elem_col[i].get_node(7),
                elem_col[i].get_node(3),
                elem_col[i].get_node(2),
                node_col))
                {
                    face.set_ID(i);
                    face_col.insert(face);
                }

                if (get_if_surface_facet
                (face,
                elem_col[i].get_node(7),
                elem_col[i].get_node(8),
                elem_col[i].get_node(4),
                elem_col[i].get_node(3),
                node_col))
                {
                    face.set_ID(i);
                    face_col.insert(face);
                }

                if (get_if_surface_facet
                (face,
                elem_col[i].get_node(8),
                elem_col[i].get_node(5),
                elem_col[i].get_node(1),
                elem_col[i].get_node(4),
                node_col))
                {
                    face.set_ID(i);
                    face_col.insert(face);
                }

                if (get_if_surface_facet
                (face,
                elem_col[i].get_node(6),
                elem_col[i].get_node(2),
                elem_col[i].get_node(1),
                elem_col[i].get_node(5),
                node_col))
                {
                    face.set_ID(i);
                    face_col.insert(face);
                }
            }
            if (elem_col[1].how_many_nodes_per_element() == constants::TETRA)
            {
                if (get_if_surface_facet
                (face,
                elem_col[i].get_node(1),
                elem_col[i].get_node(2),
                elem_col[i].get_node(3),
                node_col))
                {
                    face.set_ID(i);
                    face_col.insert(face);
                }

                if (get_if_surface_facet
                (face,
                elem_col[i].get_node(1),
                elem_col[i].get_node(3),
                elem_col[i].get_node(4),
                node_col))
                {
                    face.set_ID(i);
                    face_col.insert(face);
                }

                if (get_if_surface_facet
                (face,
                elem_col[i].get_node(1),
                elem_col[i].get_node(4),
                elem_col[i].get_node(2),
                node_col))
                {
                    face.set_ID(i);
                    face_col.insert(face);
                }

                if (get_if_surface_facet
                (face,
                elem_col[i].get_node(2),
                elem_col[i].get_node(4),
                elem_col[i].get_node(3),
                node_col))
                {
                    face.set_ID(i);
                    face_col.insert(face);
                }
            }
        }
    }
}

#endif	/* _DTMESHING_H */


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
 * File:   dSTL_Printer.h
 *
 *
 *
 *
 *
 */

#ifndef _DSTL_PRINTER_H
#define	_DSTL_PRINTER_H

#include "../dfemtoolz_dMyLib.h"

#include "../dBase/dCollection.h"
#include "../dBase/dSuperCollection.h"
#include "../dBase/dConstants.h"

#include "../dGeom/dGeom_Node.h"
#include "../dGeom/dGeom_Element.h"

#include "../dMesh/dMesh_Node.h"
#include "../dMesh/dMeshing.h"

#include "../dMisc/dMisc_Functionz.h"

#include "../dPost/dPost_Node.h"

#include "../dInit/dInit_Node.h"

#include <fstream>

#include "dInfo.h"


class STL_Printer
{
private:
    static STL_Printer * m_pSTL_PrinterSingleton;

    int  m_iElementType;

    void print_node_into_stl(Geom_Node & node, UINT value, ofstream & stl_file);

    template <class T>
    void print_elem_into_stl(Geom_Element & elem, string POS_elem_type, Collection <T> & node_c, ofstream & stl_file);
    void print_triangle_into_stl(Geom_Node & node1, Geom_Node & node2, Geom_Node & node3, fstream & stl_file);

protected:
    STL_Printer();

public:

    void print_quad_into_stl(Geom_Node & node1, Geom_Node & node2, Geom_Node & node3, Geom_Node & node4, ofstream & stl_file);

    void set_elem_type(int elem_type);

    template <class T>
    void print_elems_to_stl_file
    (Collection <Geom_Element> & elem_col, string POS_elem_type, Collection <T> & node_col, string path_and_fileName);

    template <class T>
    void print_quads_from_quadrilateral_elements_as_lines_into_stl
    (bool only_quads_with_flag, Collection <Geom_Element> & face_col, Collection <T> & node_col, string path_and_fileName);


    void print_stl_file
    (UINT face_type, Collection <Geom_Element> & faces, Collection <Mesh_Node> & node_col, string sPath_and_FileName);


    template <class T>
    void print_quads_from_quadrilateral_elements_as_lines_into_stl
    (UINT startID, UINT endID, bool only_quads_with_flag, Collection <Geom_Element> & face_col, Collection <T> & node_col, string path_and_fileName);

    template <class T>
    void print_surface_quads_from_brick_elements_as_lines_into_stl
    (Collection <Geom_Element> & bric_col, Collection <T> & node_col, string path_and_fileName);

    template <class T>
    void print_triangles_from_triangle_elements_as_lines_into_stl
    (UINT startID, UINT endID,
    bool only_triangles_with_flag, Collection <Geom_Element> & face_col, Collection <T> & node_col, string path_and_fileName);

    template <class T>
    void print_triangles_from_triangle_elements_as_lines_into_stl
    (bool only_triangles_with_flag, Collection <Geom_Element> & face_col, Collection <T> & node_col, string path_and_fileName);

    static STL_Printer * create_STL_Printer();
    ~STL_Printer();
};


template <class T>
void STL_Printer::print_elem_into_stl
(Geom_Element & elem, string POS_elem_type, Collection <T> & node_c, ofstream & stl_file)
{
    stl_file << POS_elem_type << "(";
    for (int i = 1;; i++)
    {
        print_node_coordinates_into_stl(node_c[elem.get_node(i)], stl_file);
        if (m_iElementType == 0)
        if (i == elem.how_many_nodes_per_element())
            break;
        if (m_iElementType != 0)
        if (i == m_iElementType)
            break;
        stl_file << ", ";
    }
    stl_file << "){";
    for (int i = 1 ;; i++)
    {
        stl_file << check_boundary_color(node_c[elem.get_node(i)]);
        if (m_iElementType == 0)
        if (i == elem.how_many_nodes_per_element())
            break;
        if (m_iElementType != 0)
        if (i == m_iElementType)
            break;
        stl_file << ", ";
    }
    stl_file << "};" << endl;
}

template <class T>
void STL_Printer::print_elems_to_stl_file
(Collection <Geom_Element> & elem_col, string POS_elem_type, Collection <T> & node_col, string path_and_fileName)
{
    Info * info = Info::createInfo();
    info->print_info_message("printing file " + path_and_fileName);

    ofstream output_file;
    output_file.open(path_and_fileName.c_str());
    output_file << "View \"elements\" {" << endl;

    for (UINT i = 1; i <= elem_col.get_size(); i++)
        this->print_elem_into_stl(elem_col[i], POS_elem_type, node_col, output_file);

    output_file << endl << "};";
    output_file.close();
}

template <class T>
void STL_Printer::print_quads_from_quadrilateral_elements_as_lines_into_stl
(bool only_quads_with_flag, Collection <Geom_Element> & face_col, Collection <T> & node_col, string path_and_fileName)
{
    Info * info = Info::createInfo();
    info->print_info_message("printing file " + path_and_fileName);

    ofstream output_file;
    output_file.open(path_and_fileName.c_str());
    output_file << "View \"quads\" {" << endl;

    if (!only_quads_with_flag)
    for (UINT i = 1; i <= face_col.get_size(); i++)
        this->print_quad_into_stl(
        node_col[face_col[i].get_node(1)],
        node_col[face_col[i].get_node(2)],
        node_col[face_col[i].get_node(3)],
        node_col[face_col[i].get_node(4)],
        output_file);

    if (only_quads_with_flag)
    for (UINT i = 1; i <= face_col.get_size(); i++)
    if (face_col[i].get_flag())
        this->print_quad_into_stl(
        node_col[face_col[i].get_node(1)],
        node_col[face_col[i].get_node(2)],
        node_col[face_col[i].get_node(3)],
        node_col[face_col[i].get_node(4)],
        output_file);

    output_file << endl << "};";
    output_file.close();
}

template <class T>
void STL_Printer::print_quads_from_quadrilateral_elements_as_lines_into_stl
(UINT startID, UINT endID,
bool only_quads_with_flag, Collection <Geom_Element> & face_col, Collection <T> & node_col, string path_and_fileName)
{
    Info * info = Info::createInfo();
    info->print_info_message("printing file " + path_and_fileName);

    ofstream output_file;
    output_file.open(path_and_fileName.c_str());
    output_file << "View \"quads\" {" << endl;

    if (!only_quads_with_flag)
    for (UINT i = startID; i <= endID; i++)
        this->print_quad_into_stl(
        node_col[face_col[i].get_node(1)],
        node_col[face_col[i].get_node(2)],
        node_col[face_col[i].get_node(3)],
        node_col[face_col[i].get_node(4)],
        output_file);

    if (only_quads_with_flag)
    for (UINT i = startID; i <= endID; i++)
    if (face_col[i].get_flag())
        this->print_quad_into_stl(
        node_col[face_col[i].get_node(1)],
        node_col[face_col[i].get_node(2)],
        node_col[face_col[i].get_node(3)],
        node_col[face_col[i].get_node(4)],
        output_file);

    output_file << endl << "};";
    output_file.close();
}

template <class T>
void STL_Printer::print_surface_quads_from_brick_elements_as_lines_into_stl
(Collection <Geom_Element> & bric_col, Collection <T> & node_col, string path_and_fileName)
{
    Info * info = Info::createInfo();
    info->print_info_message("printing file " + path_and_fileName);

    ofstream output_file;
    output_file.open(path_and_fileName.c_str());
    output_file << "View \"surface_faces\" {" << endl;

    for (UINT i = 1; i <= bric_col.get_size(); i++)
    {
        if (
        ((node_col[bric_col[i].get_node(1)].get_boundary() & constants::IS_BOUNDARY_V) == constants::IS_BOUNDARY_V) &&
        ((node_col[bric_col[i].get_node(2)].get_boundary() & constants::IS_BOUNDARY_V) == constants::IS_BOUNDARY_V) &&
        ((node_col[bric_col[i].get_node(3)].get_boundary() & constants::IS_BOUNDARY_V) == constants::IS_BOUNDARY_V) &&
        ((node_col[bric_col[i].get_node(4)].get_boundary() & constants::IS_BOUNDARY_V) == constants::IS_BOUNDARY_V))
            this->print_quad_into_stl(
            node_col[bric_col[i].get_node(1)],
            node_col[bric_col[i].get_node(2)],
            node_col[bric_col[i].get_node(3)],
            node_col[bric_col[i].get_node(4)],
            output_file);

        if (
        ((node_col[bric_col[i].get_node(5)].get_boundary() & constants::IS_BOUNDARY_V) == constants::IS_BOUNDARY_V) &&
        ((node_col[bric_col[i].get_node(8)].get_boundary() & constants::IS_BOUNDARY_V) == constants::IS_BOUNDARY_V) &&
        ((node_col[bric_col[i].get_node(7)].get_boundary() & constants::IS_BOUNDARY_V) == constants::IS_BOUNDARY_V) &&
        ((node_col[bric_col[i].get_node(6)].get_boundary() & constants::IS_BOUNDARY_V) == constants::IS_BOUNDARY_V))
            this->print_quad_into_stl(
            node_col[bric_col[i].get_node(5)],
            node_col[bric_col[i].get_node(8)],
            node_col[bric_col[i].get_node(7)],
            node_col[bric_col[i].get_node(6)],
            output_file);

        if (
        ((node_col[bric_col[i].get_node(1)].get_boundary() & constants::IS_BOUNDARY_V) == constants::IS_BOUNDARY_V) &&
        ((node_col[bric_col[i].get_node(5)].get_boundary() & constants::IS_BOUNDARY_V) == constants::IS_BOUNDARY_V) &&
        ((node_col[bric_col[i].get_node(6)].get_boundary() & constants::IS_BOUNDARY_V) == constants::IS_BOUNDARY_V) &&
        ((node_col[bric_col[i].get_node(2)].get_boundary() & constants::IS_BOUNDARY_V) == constants::IS_BOUNDARY_V))
            this->print_quad_into_stl(
            node_col[bric_col[i].get_node(1)],
            node_col[bric_col[i].get_node(5)],
            node_col[bric_col[i].get_node(6)],
            node_col[bric_col[i].get_node(2)],
            output_file);

        if (
        ((node_col[bric_col[i].get_node(2)].get_boundary() & constants::IS_BOUNDARY_V) == constants::IS_BOUNDARY_V) &&
        ((node_col[bric_col[i].get_node(6)].get_boundary() & constants::IS_BOUNDARY_V) == constants::IS_BOUNDARY_V) &&
        ((node_col[bric_col[i].get_node(7)].get_boundary() & constants::IS_BOUNDARY_V) == constants::IS_BOUNDARY_V) &&
        ((node_col[bric_col[i].get_node(3)].get_boundary() & constants::IS_BOUNDARY_V) == constants::IS_BOUNDARY_V))
            this->print_quad_into_stl(
            node_col[bric_col[i].get_node(2)],
            node_col[bric_col[i].get_node(6)],
            node_col[bric_col[i].get_node(7)],
            node_col[bric_col[i].get_node(3)],
            output_file);

        if (
        ((node_col[bric_col[i].get_node(3)].get_boundary() & constants::IS_BOUNDARY_V) == constants::IS_BOUNDARY_V) &&
        ((node_col[bric_col[i].get_node(7)].get_boundary() & constants::IS_BOUNDARY_V) == constants::IS_BOUNDARY_V) &&
        ((node_col[bric_col[i].get_node(8)].get_boundary() & constants::IS_BOUNDARY_V) == constants::IS_BOUNDARY_V) &&
        ((node_col[bric_col[i].get_node(4)].get_boundary() & constants::IS_BOUNDARY_V) == constants::IS_BOUNDARY_V))
            this->print_quad_into_stl(
            node_col[bric_col[i].get_node(3)],
            node_col[bric_col[i].get_node(7)],
            node_col[bric_col[i].get_node(8)],
            node_col[bric_col[i].get_node(4)],
            output_file);

        if (
        ((node_col[bric_col[i].get_node(4)].get_boundary() & constants::IS_BOUNDARY_V) == constants::IS_BOUNDARY_V) &&
        ((node_col[bric_col[i].get_node(8)].get_boundary() & constants::IS_BOUNDARY_V) == constants::IS_BOUNDARY_V) &&
        ((node_col[bric_col[i].get_node(5)].get_boundary() & constants::IS_BOUNDARY_V) == constants::IS_BOUNDARY_V) &&
        ((node_col[bric_col[i].get_node(1)].get_boundary() & constants::IS_BOUNDARY_V) == constants::IS_BOUNDARY_V))
            this->print_quad_into_stl(
            node_col[bric_col[i].get_node(4)],
            node_col[bric_col[i].get_node(8)],
            node_col[bric_col[i].get_node(5)],
            node_col[bric_col[i].get_node(1)],
            output_file);
    }

    output_file << endl << "};";
    output_file.close();
}

template <class T>
void STL_Printer::print_triangles_from_triangle_elements_as_lines_into_stl
(bool only_triangles_with_flag, Collection <Geom_Element> & face_col, Collection <T> & node_col, string path_and_fileName)
{
    Info * info = Info::createInfo();
    info->print_info_message("printing file " + path_and_fileName);

    ofstream output_file;
    output_file.open(path_and_fileName.c_str());
    output_file << "View \"triangles\" {" << endl;

    if (!only_triangles_with_flag)
    for (UINT i = 1; i <= face_col.get_size(); i++)
        this->print_triangle_into_stl(
        node_col[face_col[i].get_node(1)],
        node_col[face_col[i].get_node(2)],
        node_col[face_col[i].get_node(3)],
        output_file);

    if (only_triangles_with_flag)
    for (UINT i = 1; i <= face_col.get_size(); i++)
    if (face_col[i].get_flag())
        this->print_triangle_into_stl(
        node_col[face_col[i].get_node(1)],
        node_col[face_col[i].get_node(2)],
        node_col[face_col[i].get_node(3)],
        output_file);

    output_file << endl << "};";
    output_file.close();
}

template <class T>
void STL_Printer::print_triangles_from_triangle_elements_as_lines_into_stl
(UINT startID, UINT endID,
bool only_triangles_with_flag, Collection <Geom_Element> & face_col, Collection <T> & node_col, string path_and_fileName)
{
    Info * info = Info::createInfo();
    info->print_info_message("printing file " + path_and_fileName);

    ofstream output_file;
    output_file.open(path_and_fileName.c_str());
    output_file << "View \"triangles\" {" << endl;

    if (!only_triangles_with_flag)
    for (UINT i = startID; i <= endID; i++)
        this->print_triangle_into_stl(
        node_col[face_col[i].get_node(1)],
        node_col[face_col[i].get_node(2)],
        node_col[face_col[i].get_node(3)],
        output_file);

    if (only_triangles_with_flag)
    for (UINT i = startID; i <= endID; i++)
    if (face_col[i].get_flag())
        this->print_triangle_into_stl(
        node_col[face_col[i].get_node(1)],
        node_col[face_col[i].get_node(2)],
        node_col[face_col[i].get_node(3)],
        output_file);

    output_file << endl << "};";
    output_file.close();
}

#endif	/* _DSTL_PRINTER_H */

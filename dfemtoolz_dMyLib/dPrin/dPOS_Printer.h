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
 * File:   dPOS_Printer.h
 *
 *
 *
 *
 *
 */

#ifndef _DPOS_PRINTER_H
#define	_DPOS_PRINTER_H

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


class POS_Printer
{
private:
    static POS_Printer * m_pPOS_PrinterSingleton;

    UINT m_uHowManyNodes2Print;
    int  m_iElementType;
    UINT m_uNodesWithoutBoundary;

    void print_node_coordinates_into_pos(Geom_Node & node, ofstream & pos_file);
    void print_node_into_pos(Geom_Node & node, UINT value, ofstream & pos_file);

    template <class T>
    int check_boundary_color(T & node);

    template <class T>
    void print_elem_into_pos(Geom_Element & elem, string POS_elem_type, Collection <T> & node_c, ofstream & pos_file);
    template <class T>
    void print_elem_with_material_into_pos(Geom_Element & elem, string POS_elem_type, Collection <T> & node_c, ofstream & pos_file);
    void print_elem_vector_physical_quantity_into_pos
    (Geom_Element & elem, string POS_elem_type, Collection <Post_Node> & node_c, ofstream & pos_file);
    void print_elem_scalar_physical_quantity_into_pos
    (Geom_Element & elem, string POS_elem_type, Collection <Post_Node> & node_c, ofstream & pos_file);

    void print_vector_into_pos(Geom_Node & node, Geom_Node & value, ofstream & pos_file);
    void print_line_into_pos(Geom_Node & node1, Geom_Node & node2, double value1, double value2, ofstream & pos_file);
    void print_triangle_into_pos(Geom_Node & node1, Geom_Node & node2, Geom_Node & node3, ofstream & pos_file);
    void print_quad_into_pos(Geom_Node & node1, Geom_Node & node2, Geom_Node & node3, Geom_Node & node4, ofstream & pos_file);

protected:
    POS_Printer();

public:

    void set_how_many_nodes_2_print(UINT no_of_nodes2print);
    void set_elem_type(int elem_type);
    UINT get_how_many_nodes_2_print();

    template <class T>
    void print_nodes_using_nodeID_to_pos_file(Collection <T> & node_col, string path_and_fileName);
    template <class T>
    void print_specific_nodes_to_pos_file
    (Collection <T> & node_col, Collection <UINT> & specific_nodes_IDs, string path_and_fileName);
    template <class T>
    void print_nodes_using_node_position_in_collection_as_ID_to_pos_file
    (Collection <T> & node_col, string path_and_fileName);
    template <class T>
    void print_nodes_using_node_position_in_collection_as_ID_to_pos_file
    (SuperCollection <T> & node_supercol, string path_and_fileName);
    template <class T>
    void print_nodes_boundary_to_pos_file(Collection <T> & node_col, string path_and_fileName);
    UINT how_many_nodes_have_no_boundary_defined();

    template <class T>
    void print_elems_to_pos_file
    (Collection <Geom_Element> & elem_col, string POS_elem_type, Collection <T> & node_col, string path_and_fileName);
    template <class T>
    void print_elems_with_material_to_pos_file
    (Collection <Geom_Element> & elem_col, string POS_elem_type, Collection <T> & node_col, string path_and_fileName);
    template <class T>
    void print_bricks_from_15node_tetrahedrons_and_14node_prisms_to_pos_file
    (Collection <Geom_Element> & elem_col, Collection <T> & node_col, string path_and_fileName);
    template <class T>
    void print_bricks_from_27node_bricks_to_pos_file
    (Collection <Geom_Element> & elem_col, Collection <T> & node_col, string path_and_fileName);

    void print_initial_nodes_velocity_vectors_to_pos_file
    (Collection <Init_Node> & node_col, string path_and_fileName);
    void print_nodes_vector_physical_quantity_to_pos_file
    (Collection <Post_Node> & node_col, string path_and_fileName, string text_physical_quantity = "physical_quantity");
    void print_elems_vector_physical_quantity_to_pos_file
    (Collection <Geom_Element> & elem_col, string POS_elem_type, Collection <Post_Node> & node_col, string path_and_fileName, string text_physical_quantity = "physical_quantity");
    void print_elems_scalar_physical_quantity_to_pos_file
    (bool only_elements_near_surface, Collection <Geom_Element> & elem_col, string POS_elem_type, Collection <Post_Node> & node_col, string path_and_fileName, string text_physical_quantity = "physical_quantity");

    template <class T>
    void print_lines_with_nodesID_to_pos_file(Collection <T> & one_streamline, string path_and_fileName);
    template <class T>
    void print_lines_with_length_absolute_to_pos_file(Collection <T> & one_streamline, string path_and_fileName);
    template <class T>
    void print_lines_with_nodesID_to_pos_file(SuperCollection <T> & streamline_supercol, string path_and_fileName);
    template <class T>
    void print_lines_with_length_absolute_to_pos_file(SuperCollection <T> & streamline_supercol, string path_and_fileName);

    template <class T>
    void print_quads_from_quadrilateral_elements_as_lines_into_pos
    (bool only_quads_with_flag, Collection <Geom_Element> & face_col, Collection <T> & node_col, string path_and_fileName);
    template <class T>
    void print_surface_quads_from_brick_elements_as_lines_into_pos
    (Collection <Geom_Element> & bric_col, Collection <T> & node_col, string path_and_fileName);
    template <class T>
    void print_triangles_from_triangle_elements_as_lines_into_pos
    (bool only_triangles_with_flag, Collection <Geom_Element> & face_col, Collection <T> & node_col, string path_and_fileName);

    static POS_Printer * create_POS_Printer();
    ~POS_Printer();
};

template <class T>
int POS_Printer::check_boundary_color(T & node)
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

template <class T>
void POS_Printer::print_elem_into_pos
(Geom_Element & elem, string POS_elem_type, Collection <T> & node_c, ofstream & pos_file)
{
    pos_file << POS_elem_type << "(";
    for (int i = 1;; i++)
    {
        print_node_coordinates_into_pos(node_c[elem.get_node(i)], pos_file);
        if (m_iElementType == 0)
        if (i == elem.how_many_nodes_per_element())
            break;
        if (m_iElementType != 0)
        if (i == m_iElementType)
            break;
        pos_file << ", ";
    }
    pos_file << "){";
    for (int i = 1 ;; i++)
    {
        pos_file << check_boundary_color(node_c[elem.get_node(i)]);
        if (m_iElementType == 0)
        if (i == elem.how_many_nodes_per_element())
            break;
        if (m_iElementType != 0)
        if (i == m_iElementType)
            break;
        pos_file << ", ";
    }
    pos_file << "};" << endl;
}

template <class T>
void POS_Printer::print_elem_with_material_into_pos
(Geom_Element & elem, string POS_elem_type, Collection <T> & node_c, ofstream & pos_file)
{
    pos_file << POS_elem_type << "(";
    for (int i = 1;; i++)
    {
        print_node_coordinates_into_pos(node_c[elem.get_node(i)], pos_file);
        if (i == elem.how_many_nodes_per_element()) break;
        pos_file << ", ";
    }
    pos_file << "){";
    for (int i = 1 ;; i++)
    {
        pos_file << elem.get_material_ID();
        if (i == elem.how_many_nodes_per_element()) break;
        pos_file << ", ";
    }
    pos_file << "};" << endl;
}

template <class T>
void POS_Printer::print_nodes_using_nodeID_to_pos_file
(Collection <T> & node_col, string path_and_fileName)
{
    Info * info = Info::createInfo();
    info->print_info_message("printing file " + path_and_fileName);

    ofstream output_file;
    output_file.open(path_and_fileName.c_str());
    output_file << "View \"nodesID\" {" << endl;

    UINT up;
    if (m_uHowManyNodes2Print == 0)
        up = node_col.get_size();
    if (m_uHowManyNodes2Print != 0)
        up = m_uHowManyNodes2Print;

    for (UINT i = 1; i <= up; i++)
        this->print_node_into_pos(node_col[i], node_col[i].get_ID(), output_file);

    output_file << endl << "};";
    output_file.close();
}

template <class T>
void POS_Printer::print_specific_nodes_to_pos_file
(Collection <T> & node_col, Collection <UINT> & specific_nodes_IDs, string path_and_fileName)
{
    Info * info = Info::createInfo();
    info->print_info_message("printing file " + path_and_fileName);

    ofstream output_file;
    output_file.open(path_and_fileName.c_str());
    output_file << "View \"nodesID\" {" << endl;

    for (UINT i = 1; i <= specific_nodes_IDs.get_size(); i++)
        this->print_node_into_pos(node_col[specific_nodes_IDs[i]], specific_nodes_IDs[i], output_file);

    output_file << endl << "};";
    output_file.close();
}

template <class T>
void POS_Printer::print_nodes_using_node_position_in_collection_as_ID_to_pos_file
(Collection <T> & node_col, string path_and_fileName)
{
    Info * info = Info::createInfo();
    info->print_info_message("printing file " + path_and_fileName);

    ofstream output_file;
    output_file.open(path_and_fileName.c_str());
    output_file << "View \"nodesID\" {" << endl;

    UINT up;
    if (m_uHowManyNodes2Print == 0)
        up = node_col.get_size();
    if (m_uHowManyNodes2Print != 0)
        up = m_uHowManyNodes2Print;

    for (UINT i = 1; i <= up; i++)
        this->print_node_into_pos(node_col[i], i, output_file);

    output_file << endl << "};";
    output_file.close();
}

template <class T>
void POS_Printer::print_nodes_using_node_position_in_collection_as_ID_to_pos_file
(SuperCollection <T> & node_supercol, string path_and_fileName)
{
    Info * info = Info::createInfo();
    info->print_info_message("printing file " + path_and_fileName);

    ofstream output_file;
    output_file.open(path_and_fileName.c_str());
    output_file << "View \"nodesID\" {" << endl;

    for (UINT i = 1; i <= node_supercol.get_size();   i++)
    for (UINT j = 1; j < node_supercol[i].get_size(); j++)
        this->print_node_into_pos(node_supercol[i][j], j, output_file);

    output_file << endl << "};";
    output_file.close();
}

template <class T>
void POS_Printer::print_nodes_boundary_to_pos_file(Collection <T> & node_col, string path_and_fileName)
{
    Info * info = Info::createInfo();
    info->print_info_message("printing file " + path_and_fileName);

    ofstream output_file;
    output_file.open(path_and_fileName.c_str());
    output_file << "View \"nodesBoundary\" {" << endl;

    int bmarker;
    m_uNodesWithoutBoundary = 0;

    UINT up;
    if (m_uHowManyNodes2Print == 0)
        up = node_col.get_size();
    if (m_uHowManyNodes2Print != 0)
        up = m_uHowManyNodes2Print;

    for (UINT i = 1; i <= up; i++)
    {
        bmarker = check_boundary_color(node_col[i]);
        this->print_node_into_pos(node_col[i], bmarker, output_file);
        if (bmarker == 0)
            m_uNodesWithoutBoundary++;
    }

    output_file << endl << "};";
    output_file.close();
}

template <class T>
void POS_Printer::print_elems_to_pos_file
(Collection <Geom_Element> & elem_col, string POS_elem_type, Collection <T> & node_col, string path_and_fileName)
{
    Info * info = Info::createInfo();
    info->print_info_message("printing file " + path_and_fileName);

    ofstream output_file;
    output_file.open(path_and_fileName.c_str());
    output_file << "View \"elements\" {" << endl;

    for (UINT i = 1; i <= elem_col.get_size(); i++)
        this->print_elem_into_pos(elem_col[i], POS_elem_type, node_col, output_file);

    output_file << endl << "};";
    output_file.close();
}

template <class T>
void POS_Printer::print_elems_with_material_to_pos_file
(Collection <Geom_Element> & elem_col, string POS_elem_type, Collection <T> & node_col, string path_and_fileName)
{
    Info * info = Info::createInfo();
    info->print_info_message("printing file " + path_and_fileName);

    ofstream output_file;
    output_file.open(path_and_fileName.c_str());
    output_file << "View \"elements\" {" << endl;

    for (UINT i = 1; i <= elem_col.get_size(); i++)
        this->print_elem_with_material_into_pos(elem_col[i], POS_elem_type, node_col, output_file);

    output_file << endl << "};";
    output_file.close();
}

template <class T>
void POS_Printer::print_bricks_from_27node_bricks_to_pos_file
(Collection <Geom_Element> & elem_col, Collection <T> & node_col, string path_and_fileName)
{
    Info * info = Info::createInfo();
    info->print_info_message("printing file " + path_and_fileName);

    ofstream output_file;
    output_file.open(path_and_fileName.c_str());
    output_file << "View \"elements\" {" << endl;

    vector <Geom_Element> bricks(8, Geom_Element(8));

    for (UINT i = 1; i <= elem_col.get_size(); i++)
    {
        meshing::get_8_bricks_from_27_brick(bricks, elem_col[i]);

        for (int j = 0; j < 8; j++)
            print_elem_into_pos(bricks[j], "SH", node_col, output_file);
    }

    output_file << endl << "};";
    output_file.close();
}

template <class T>
void POS_Printer::print_bricks_from_15node_tetrahedrons_and_14node_prisms_to_pos_file
(Collection <Geom_Element> & elem_col, Collection <T> & node_col, string path_and_fileName)
{
    Info * info = Info::createInfo();
    info->print_info_message("printing file " + path_and_fileName);

    ofstream output_file;
    output_file.open(path_and_fileName.c_str());
    output_file << "View \"elements\" {" << endl;

    vector <Geom_Element> bricks(4, Geom_Element(8));

    for (UINT i = 1; i <= elem_col.get_size(); i++)
    {
        if (elem_col[i].how_many_nodes_per_element() == 15)
        {
            meshing::get_4_bricks_from_15_tetrahedron(bricks, elem_col[i]);

            for (int j = 0; j < 4; j++)
                print_elem_into_pos(bricks[j], "SH", node_col, output_file);
        }
        if (elem_col[i].how_many_nodes_per_element() == 14)
        {
            meshing::get_3_bricks_from_14_prism(bricks, elem_col[i]);

            for (int j = 0; j < 3; j++)
                print_elem_into_pos(bricks[j], "SH", node_col, output_file);
        }
    }

    output_file << endl << "};";
    output_file.close();
}

template <class T>
void POS_Printer::print_lines_with_nodesID_to_pos_file(Collection <T> & one_streamline, string path_and_fileName)
{
    Info * info = Info::createInfo();
    info->print_info_message("printing file " + path_and_fileName);

    ofstream output_file;
    output_file.open(path_and_fileName.c_str());
    output_file << "View \"lines\" {" << endl;

    UINT k;
    for (UINT i = 1; i < one_streamline.get_size(); i++)
    {
        k = i + 1;
        this->print_line_into_pos(one_streamline[i], one_streamline[k], i, k, output_file);
    }

    output_file << endl << "};";
    output_file.close();
}

template <class T>
void POS_Printer::print_lines_with_length_absolute_to_pos_file(Collection <T> & one_streamline, string path_and_fileName)
{
    Info * info = Info::createInfo();
    info->print_info_message("printing file " + path_and_fileName);

    ofstream output_file;
    output_file.open(path_and_fileName.c_str());
    output_file << "View \"lines\" {" << endl;

    UINT k;
    double length = 0.0, last_length = 0.0;
    for (UINT i = 1; i < one_streamline.get_size(); i++)
    {
        k = i + 1;
        length += get_lenght(one_streamline[i], one_streamline[k]);
        this->print_line_into_pos(one_streamline[i], one_streamline[k], last_length, length, output_file);
        last_length = length;
    }

    output_file << endl << "};";
    output_file.close();
}

template <class T>
void POS_Printer::print_lines_with_nodesID_to_pos_file(SuperCollection <T> & streamline_supercol, string path_and_fileName)
{
    Info * info = Info::createInfo();
    info->print_info_message("printing file " + path_and_fileName);

    ofstream output_file;
    output_file.open(path_and_fileName.c_str());
    output_file << "View \"lines\" {" << endl;

    UINT k;
    for (UINT i = 1; i <= streamline_supercol.get_size();   i++)
    for (UINT j = 1; j < streamline_supercol[i].get_size(); j++)
    {
        k = j + 1;
        this->print_line_into_pos(streamline_supercol[i][j], streamline_supercol[i][k], j, k, output_file);
    }

    output_file << endl << "};";
    output_file.close();
}

template <class T>
void POS_Printer::print_lines_with_length_absolute_to_pos_file(SuperCollection <T> & streamline_supercol, string path_and_fileName)
{
    Info * info = Info::createInfo();
    info->print_info_message("printing file " + path_and_fileName);

    ofstream output_file;
    output_file.open(path_and_fileName.c_str());
    output_file << "View \"lines\" {" << endl;

    UINT k;
    for (UINT i = 1; i <= streamline_supercol.get_size();   i++)
    {
        double last_length = 0.0;
        double length = 0.0;
        for (UINT j = 1; j < streamline_supercol[i].get_size(); j++)
        {
            k = j + 1;
            length += get_lenght(streamline_supercol[i][j], streamline_supercol[i][k]);
            this->print_line_into_pos(streamline_supercol[i][j], streamline_supercol[i][k], last_length, length, output_file);
            last_length = length;
        }
    }

    output_file << endl << "};";
    output_file.close();
}

template <class T>
void POS_Printer::print_quads_from_quadrilateral_elements_as_lines_into_pos
(bool only_quads_with_flag, Collection <Geom_Element> & face_col, Collection <T> & node_col, string path_and_fileName)
{
    Info * info = Info::createInfo();
    info->print_info_message("printing file " + path_and_fileName);

    ofstream output_file;
    output_file.open(path_and_fileName.c_str());
    output_file << "View \"quads\" {" << endl;

    if (!only_quads_with_flag)
    for (UINT i = 1; i <= face_col.get_size(); i++)
        this->print_quad_into_pos(
        node_col[face_col[i].get_node(1)],
        node_col[face_col[i].get_node(2)],
        node_col[face_col[i].get_node(3)],
        node_col[face_col[i].get_node(4)],
        output_file);

    if (only_quads_with_flag)
    for (UINT i = 1; i <= face_col.get_size(); i++)
    if (face_col[i].get_flag())
        this->print_quad_into_pos(
        node_col[face_col[i].get_node(1)],
        node_col[face_col[i].get_node(2)],
        node_col[face_col[i].get_node(3)],
        node_col[face_col[i].get_node(4)],
        output_file);

    output_file << endl << "};";
    output_file.close();
}

template <class T>
void POS_Printer::print_surface_quads_from_brick_elements_as_lines_into_pos
(Collection <Geom_Element> & bric_col, Collection <T> & node_col, string path_and_fileName)
{
    Info * info = Info::createInfo();
    info->print_info_message("printing file " + path_and_fileName);

    ofstream output_file;
    output_file.open(path_and_fileName.c_str());
    output_file << "View \"surface_quads\" {" << endl;

    for (UINT i = 1; i <= bric_col.get_size(); i++)
    {
        if (
        ((node_col[bric_col[i].get_node(1)].get_boundary() & constants::IS_BOUNDARY_V) == constants::IS_BOUNDARY_V) &&
        ((node_col[bric_col[i].get_node(2)].get_boundary() & constants::IS_BOUNDARY_V) == constants::IS_BOUNDARY_V) &&
        ((node_col[bric_col[i].get_node(3)].get_boundary() & constants::IS_BOUNDARY_V) == constants::IS_BOUNDARY_V) &&
        ((node_col[bric_col[i].get_node(4)].get_boundary() & constants::IS_BOUNDARY_V) == constants::IS_BOUNDARY_V))
            this->print_quad_into_pos(
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
            this->print_quad_into_pos(
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
            this->print_quad_into_pos(
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
            this->print_quad_into_pos(
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
            this->print_quad_into_pos(
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
            this->print_quad_into_pos(
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
void POS_Printer::print_triangles_from_triangle_elements_as_lines_into_pos
(bool only_triangles_with_flag, Collection <Geom_Element> & face_col, Collection <T> & node_col, string path_and_fileName)
{
    Info * info = Info::createInfo();
    info->print_info_message("printing file " + path_and_fileName);

    ofstream output_file;
    output_file.open(path_and_fileName.c_str());
    output_file << "View \"quads\" {" << endl;

    if (!only_triangles_with_flag)
    for (UINT i = 1; i <= face_col.get_size(); i++)
        this->print_triangle_into_pos(
        node_col[face_col[i].get_node(1)],
        node_col[face_col[i].get_node(2)],
        node_col[face_col[i].get_node(3)],
        output_file);

    if (only_triangles_with_flag)
    for (UINT i = 1; i <= face_col.get_size(); i++)
    if (face_col[i].get_flag())
        this->print_triangle_into_pos(
        node_col[face_col[i].get_node(1)],
        node_col[face_col[i].get_node(2)],
        node_col[face_col[i].get_node(3)],
        output_file);

    output_file << endl << "};";
    output_file.close();
}

#endif	/* _DPOS_PRINTER_H */

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

#include "dPOS_Printer.h"


POS_Printer::POS_Printer()
{
    m_uHowManyNodes2Print = 0;
    m_iElementType = 0;
}

POS_Printer * POS_Printer::m_pPOS_PrinterSingleton = 0;
POS_Printer * POS_Printer::create_POS_Printer()
{
    if (m_pPOS_PrinterSingleton == 0)
        m_pPOS_PrinterSingleton = new POS_Printer();
    return m_pPOS_PrinterSingleton;
}

POS_Printer::~POS_Printer()
{
    delete m_pPOS_PrinterSingleton;
    m_pPOS_PrinterSingleton = 0;
}

void POS_Printer::print_node_coordinates_into_pos
(Geom_Node & node, ofstream & pos_file)
{
    pos_file <<
    node.get_coordinate_X() << ", " <<
    node.get_coordinate_Y() << ", " <<
    node.get_coordinate_Z();
}

void POS_Printer::print_node_into_pos
(Geom_Node & node, UINT value, ofstream & pos_file)
{
    pos_file << "SP(";
    print_node_coordinates_into_pos(node, pos_file);
    pos_file << "){" <<
    value << "};" << endl;
}

void POS_Printer::print_vector_into_pos
(Geom_Node & node, Geom_Node & value, ofstream & pos_file)
{
    pos_file << "VP(" <<
    node.get_coordinate_X() << "," <<
    node.get_coordinate_Y() << "," <<
    node.get_coordinate_Z() << "){" <<
    value.get_coordinate_X() << ", " <<
    value.get_coordinate_Y() << ", " <<
    value.get_coordinate_Z() << "};" << endl;
}

void POS_Printer::print_line_into_pos
(Geom_Node & node1, Geom_Node & node2, double value1, double value2, ofstream & pos_file)
{
    pos_file << "SL(" <<
    node1.get_coordinate_X() << "," <<
    node1.get_coordinate_Y() << "," <<
    node1.get_coordinate_Z() << "," <<
    node2.get_coordinate_X() << ", " <<
    node2.get_coordinate_Y() << ", " <<
    node2.get_coordinate_Z() << "){" <<
    value1 << ", " <<
    value2 << "};" << endl;
}

void POS_Printer::print_triangle_into_pos
(Geom_Node & node1, Geom_Node & node2, Geom_Node & node3, ofstream & pos_file)
{
    print_line_into_pos(node1, node2, 1, 1, pos_file);
    print_line_into_pos(node2, node3, 1, 1, pos_file);
    print_line_into_pos(node3, node1, 1, 1, pos_file);
}

void POS_Printer::print_quad_into_pos
(Geom_Node & node1, Geom_Node & node2, Geom_Node & node3, Geom_Node & node4, ofstream & pos_file)
{
    print_line_into_pos(node1, node2, 1, 1, pos_file);
    print_line_into_pos(node2, node3, 1, 1, pos_file);
    print_line_into_pos(node3, node4, 1, 1, pos_file);
    print_line_into_pos(node4, node1, 1, 1, pos_file);
}

void POS_Printer::set_how_many_nodes_2_print(UINT no_of_nodes2print)
{
    m_uHowManyNodes2Print = no_of_nodes2print;
}

void POS_Printer::set_elem_type(int elem_type)
{
    m_iElementType = elem_type;
}

UINT POS_Printer::get_how_many_nodes_2_print()
{
    return m_uHowManyNodes2Print;
}

UINT POS_Printer::how_many_nodes_have_no_boundary_defined()
{
    return m_uNodesWithoutBoundary;
}

void POS_Printer::print_nodes_vector_physical_quantity_to_pos_file
(Collection <Post_Node> & node_col, string path_and_fileName, string text_physical_quantity)
{
    Info * info = Info::createInfo();
    info->print_info_message("printing file " + path_and_fileName);

    ofstream output_file;
    output_file.open(path_and_fileName.c_str());
    output_file << "View \"" + text_physical_quantity + "\" {" << endl;

    UINT up = 0;
    if (m_uHowManyNodes2Print == 0)
        up = node_col.get_size();
    if (m_uHowManyNodes2Print != 0)
        up = m_uHowManyNodes2Print;

    for (UINT i = 1; i <= up; i++)
        this->print_vector_into_pos(node_col[i], node_col[i].vector_physical_quantity, output_file);

    output_file << endl << "};";
    output_file.close();
}

void POS_Printer::print_initial_nodes_velocity_vectors_to_pos_file
(Collection <Init_Node> & node_col, string path_and_fileName)
{
    Info * info = Info::createInfo();
    info->print_info_message("printing file " + path_and_fileName);

    ofstream output_file;
    output_file.open(path_and_fileName.c_str());
    output_file << "View \"initial_velocity\" {" << endl;

    for (UINT i = 1; i <= node_col.get_size(); i++)
        this->print_vector_into_pos(node_col[i], node_col[i].initial_velocity, output_file);

    output_file << endl << "};";
    output_file.close();
}

void POS_Printer::print_elems_vector_physical_quantity_to_pos_file
(Collection <Geom_Element> & elem_col, string POS_elem_type, Collection <Post_Node> & node_col, string path_and_fileName, string text_physical_quantity)
{
    Info * info = Info::createInfo();
    info->print_info_message("printing file " + path_and_fileName);

    ofstream output_file;
    output_file.open(path_and_fileName.c_str());
    output_file << "View \"" + text_physical_quantity + "\" {" << endl;

    for (UINT i = 1; i <= elem_col.get_size(); i++)
        this->print_elem_vector_physical_quantity_into_pos(elem_col[i], POS_elem_type, node_col, output_file);

    output_file << endl << "};";
    output_file.close();
}

void POS_Printer::print_elems_scalar_physical_quantity_to_pos_file
(bool only_elements_near_surface, Collection <Geom_Element> & elem_col, string POS_elem_type, Collection <Post_Node> & node_col, string path_and_fileName, string text_physical_quantity)
{
    Info * info = Info::createInfo();
    info->print_info_message("printing file " + path_and_fileName);

    ofstream output_file;
    output_file.open(path_and_fileName.c_str());
    output_file << "View \"" + text_physical_quantity + "\" {" << endl;

    if (!only_elements_near_surface)
    for (UINT i = 1; i <= elem_col.get_size(); i++)
        this->print_elem_scalar_physical_quantity_into_pos(elem_col[i], POS_elem_type, node_col, output_file);

    if (only_elements_near_surface)
    for (UINT i = 1; i <= elem_col.get_size(); i++)
    if (elem_col[i].get_boundary())
        this->print_elem_scalar_physical_quantity_into_pos(elem_col[i], POS_elem_type, node_col, output_file);

    output_file << endl << "};";
    output_file.close();
}

void POS_Printer::print_elem_vector_physical_quantity_into_pos
(Geom_Element & elem, string POS_elem_type, Collection <Post_Node> & node_c, ofstream & pos_file)
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
        pos_file << get_the_vector_intensity(node_c[elem.get_node(i)].vector_physical_quantity);
        if (i == elem.how_many_nodes_per_element()) break;
        pos_file << ", ";
    }
    pos_file << "};" << endl;
}

void POS_Printer::print_elem_scalar_physical_quantity_into_pos
(Geom_Element & elem, string POS_elem_type, Collection <Post_Node> & node_c, ofstream & pos_file)
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
        pos_file << node_c[elem.get_node(i)].get_scalar_physical_quantity();
        if (i == elem.how_many_nodes_per_element()) break;
        pos_file << ", ";
    }
    pos_file << "};" << endl;
}

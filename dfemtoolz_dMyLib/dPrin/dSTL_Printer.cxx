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

#include "dSTL_Printer.h"


STL_Printer::STL_Printer()
{
    m_iElementType = 0;
}

STL_Printer * STL_Printer::m_pSTL_PrinterSingleton = 0;
STL_Printer * STL_Printer::create_STL_Printer()
{
    if (m_pSTL_PrinterSingleton == 0)
        m_pSTL_PrinterSingleton = new STL_Printer();
    return m_pSTL_PrinterSingleton;
}

STL_Printer::~STL_Printer()
{
    delete m_pSTL_PrinterSingleton;
    m_pSTL_PrinterSingleton = 0;
}


void STL_Printer::print_stl_file
(UINT face_type, Collection <Geom_Element> & faces, Collection <Mesh_Node> & node_col, string sPath_and_FileName)
{
    if (sPath_and_FileName.length() > constants::minimum_characters_in_fileName)
    {

        Info * info = Info::createInfo();
        info->print_info_message("printing file " + sPath_and_FileName);

        ofstream stl;
        stl.open(sPath_and_FileName.c_str());
        stl.close();

        fstream file(sPath_and_FileName.c_str(), ios::ate | ios::out | ios::in);
        file.seekp(file.tellp());

        file << "solid WRAP" << endl;

        if (face_type == constants::TRIANGLE)
        for (UINT i = 1; i <= faces.get_size(); i++)
        {
            print_triangle_into_stl(
            node_col[faces[i].get_node(1)],
            node_col[faces[i].get_node(2)],
            node_col[faces[i].get_node(3)], file);
        }

        if (face_type == constants::QUAD)
        for (UINT i = 1; i <= faces.get_size(); i++)
        {
            print_triangle_into_stl(
            node_col[faces[i].get_node(1)],
            node_col[faces[i].get_node(2)],
            node_col[faces[i].get_node(3)], file);

            print_triangle_into_stl(
            node_col[faces[i].get_node(1)],
            node_col[faces[i].get_node(3)],
            node_col[faces[i].get_node(4)], file);
        }



        file << "endsolid WRAP" << endl;
        file.close();
    }
}

void STL_Printer::print_triangle_into_stl
(Geom_Node & node1, Geom_Node & node2, Geom_Node & node3, fstream & stl_file)
{
    Geom_Node a = get_vector_difference_vecA_minus_vecB(node1, node2);
    Geom_Node b = get_vector_difference_vecA_minus_vecB(node1, node3);

    Geom_Node crs_product_a_x_b = cross_product(a, b);

    transform_2_1value_vector(crs_product_a_x_b);

    stl_file << "facet normal " <<
    crs_product_a_x_b.get_coordinate_X() << " " <<
    crs_product_a_x_b.get_coordinate_Y() << " " <<
    crs_product_a_x_b.get_coordinate_Z() << endl;

    stl_file << "outer loop" << endl;

    stl_file << "vertex " <<
    node1.get_coordinate_X() << " " <<
    node1.get_coordinate_Y() << " " <<
    node1.get_coordinate_Z() << endl;

    stl_file << "vertex " <<
    node2.get_coordinate_X() << " " <<
    node2.get_coordinate_Y() << " " <<
    node2.get_coordinate_Z() << endl;

    stl_file << "vertex " <<
    node3.get_coordinate_X() << " " <<
    node3.get_coordinate_Y() << " " <<
    node3.get_coordinate_Z() << endl;

    stl_file << "endloop" << endl;
    stl_file << "endfacet" << endl;

}

void STL_Printer::print_quad_into_stl
(Geom_Node & node1, Geom_Node & node2, Geom_Node & node3, Geom_Node & node4, ofstream & stl_file)
{
}

void STL_Printer::set_elem_type(int elem_type)
{
    m_iElementType = elem_type;
}

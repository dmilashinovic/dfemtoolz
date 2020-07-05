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

#include "dVTK_Printer.h"


VTK_Printer::VTK_Printer()
{
    m_uHowManyNodes2Print = 0;
    m_iElementType = 0;
}

VTK_Printer * VTK_Printer::m_pVTK_PrinterSingleton = 0;
VTK_Printer * VTK_Printer::create_VTK_Printer()
{
    if (m_pVTK_PrinterSingleton == 0)
        m_pVTK_PrinterSingleton = new VTK_Printer();
    return m_pVTK_PrinterSingleton;
}

VTK_Printer::~VTK_Printer()
{
    delete m_pVTK_PrinterSingleton;
    m_pVTK_PrinterSingleton = 0;
}

void VTK_Printer::print_brick_elems_scalar_physical_quantity_to_vtk_file
(Collection <Geom_Element> & elem_col, Collection <Post_Node> & node_col, string path_and_fileName, string text_scalar_physical_quantity)
{
    Info * info = Info::createInfo();
    info->print_info_message("printing file " + path_and_fileName);

    ofstream output_file;
    output_file.open(path_and_fileName.c_str());
    output_file << "# vtk DataFile Version 3.0" << endl;
    output_file << "solid_mesh" << endl;
    output_file << "ASCII" << endl;
    output_file << "DATASET UNSTRUCTURED_GRID" << endl;

    output_file << "POINTS " << node_col.get_size() << " float" << endl;

    for (UINT i = 1; i <= node_col.get_size(); i++)
    {
        for (int j = 1; j <= 3; j++)
            output_file << node_col[i].get_coordinate(j) << " ";
        output_file << endl;
    }

    output_file << "CELLS " << elem_col.get_size() << " " <<  elem_col.get_size() * 9 <<  endl;

    for (UINT i = 1; i <= elem_col.get_size(); i++)
    {
        output_file << "8 ";

        for (int j = 5; j <= 8; j++)
            output_file << elem_col[i].get_node(j) - 1 << " ";
        for (int j = 1; j <= 4; j++)
            output_file << elem_col[i].get_node(j) - 1 << " ";
        output_file << endl;
    }

    output_file << "CELL_TYPES " << elem_col.get_size() << endl;

    for (UINT i = 1; i <= elem_col.get_size(); i++)
    {
        output_file << "12" << endl;
    }

    output_file << "POINT_DATA " << node_col.get_size() << endl;
    output_file << "SCALARS " << text_scalar_physical_quantity << " float 1 " << endl;
    output_file << "LOOKUP_TABLE default " << endl;

    for (UINT i = 1; i <= node_col.get_size(); i++)
    {
        output_file << node_col[i].get_scalar_physical_quantity() << endl;
    }

    output_file.close();
}

void VTK_Printer::print_bricks_from_15node_tetrahedrons_and_14node_prisms_to_vtk_file
(Collection <Geom_Element> & elem_col, Collection <Mesh_Node> & node_col, string path_and_fileName)
{
    Info * info = Info::createInfo();
    info->print_info_message("printing file " + path_and_fileName);

    ofstream output_file;
    output_file.open(path_and_fileName.c_str());
    output_file << "# vtk DataFile Version 3.0" << endl;
    output_file << "solid_mesh" << endl;
    output_file << "ASCII" << endl;
    output_file << "DATASET UNSTRUCTURED_GRID" << endl;

    output_file << "POINTS " << node_col.get_size() << " float" << endl;

    for (UINT i = 1; i <= node_col.get_size(); i++)
    {
        for (int j = 1; j <= 3; j++)
            output_file << node_col[i].get_coordinate(j) << " ";
        output_file << endl;
    }

    if (elem_col[1].how_many_nodes_per_element() == 15)
        output_file << "CELLS " << elem_col.get_size() * 4 << " " <<
        elem_col.get_size() * 9 * 4 <<  endl;

    if (elem_col[1].how_many_nodes_per_element() == 14)
        output_file << "CELLS " << elem_col.get_size() * 3 << " " <<
        elem_col.get_size() * 9 * 3 <<  endl;

    vector <Geom_Element> bricks(4, Geom_Element(8));

    for (UINT i = 1; i <= elem_col.get_size(); i++)
    {
        if (elem_col[i].how_many_nodes_per_element() == 15)
        {
            meshing::get_4_bricks_from_15_tetrahedron(bricks, elem_col[i]);

            for (int j = 0; j < 4; j++)
            {
                output_file << "8 ";

                for (int n = 5; n <= 8; n++)
                    output_file << bricks[j].get_node(n) - 1 << " ";
                for (int n = 1; n <= 4; n++)
                    output_file << bricks[j].get_node(n) - 1 << " ";
                output_file << endl;
            }
        }

        if (elem_col[i].how_many_nodes_per_element() == 14)
        {
            meshing::get_3_bricks_from_14_prism(bricks, elem_col[i]);

            for (int j = 0; j < 3; j++)
            {
                output_file << "8 ";

                for (int n = 5; n <= 8; n++)
                    output_file << bricks[j].get_node(n) - 1 << " ";
                for (int n = 1; n <= 4; n++)
                    output_file << bricks[j].get_node(n) - 1 << " ";
                output_file << endl;
            }
        }

    }

    if (elem_col[1].how_many_nodes_per_element() == 14)
        output_file << "CELL_TYPES " << elem_col.get_size() * 3 << endl;

    if (elem_col[1].how_many_nodes_per_element() == 15)
        output_file << "CELL_TYPES " << elem_col.get_size() * 4 << endl;

    if (elem_col[1].how_many_nodes_per_element() == 14)
    for (UINT i = 1; i <= elem_col.get_size() * 3; i++)
        output_file << "12" << endl;

    if (elem_col[1].how_many_nodes_per_element() == 15)
    for (UINT i = 1; i <= elem_col.get_size() * 4; i++)
        output_file << "12" << endl;

    if (elem_col[1].how_many_nodes_per_element() == 14)
        output_file << "CELL_DATA " << elem_col.get_size() * 3 << endl;

    if (elem_col[1].how_many_nodes_per_element() == 15)
        output_file << "CELL_DATA " << elem_col.get_size() * 4 << endl;

    output_file << "SCALARS material" << " float 1 " << endl;
    output_file << "LOOKUP_TABLE default " << endl;

    if (elem_col[1].how_many_nodes_per_element() == 14)
    for (UINT i = 1; i <= elem_col.get_size(); i++)
    for (UINT j = 1; j <= 3; j++)
        output_file << elem_col[i].get_material_ID() << endl;

    if (elem_col[1].how_many_nodes_per_element() == 15)
    for (UINT i = 1; i <= elem_col.get_size(); i++)
    for (UINT j = 1; j <= 4; j++)
        output_file << elem_col[i].get_material_ID() << endl;

    output_file.close();
}

void VTK_Printer::print_brick_elems_material_2_vtk_file
(Collection <Geom_Element> & elem_col, Collection <Mesh_Node> & node_col, string path_and_fileName)
{
    Info * info = Info::createInfo();
    info->print_info_message("printing file " + path_and_fileName);

    ofstream output_file;
    output_file.open(path_and_fileName.c_str());
    output_file << "# vtk DataFile Version 3.0" << endl;
    output_file << "solid_mesh" << endl;
    output_file << "ASCII" << endl;
    output_file << "DATASET UNSTRUCTURED_GRID" << endl;

    output_file << "POINTS " << node_col.get_size() << " float" << endl;

    for (UINT i = 1; i <= node_col.get_size(); i++)
    {
        for (int j = 1; j <= 3; j++)
            output_file << node_col[i].get_coordinate(j) << " ";
        output_file << endl;
    }

    output_file << "CELLS " << elem_col.get_size() << " " <<  elem_col.get_size() * 9 <<  endl;

    for (UINT i = 1; i <= elem_col.get_size(); i++)
    {
        output_file << "8 ";

        for (int j = 5; j <= 8; j++)
            output_file << elem_col[i].get_node(j) - 1 << " ";
        for (int j = 1; j <= 4; j++)
            output_file << elem_col[i].get_node(j) - 1 << " ";
        output_file << endl;
    }

    output_file << "CELL_TYPES " << elem_col.get_size() << endl;

    for (UINT i = 1; i <= elem_col.get_size(); i++)
    {
        output_file << "12" << endl;
    }

    output_file << "CELL_DATA " << elem_col.get_size() << endl;
    output_file << "SCALARS material" << " float 1 " << endl;
    output_file << "LOOKUP_TABLE default " << endl;

    for (UINT i = 1; i <= elem_col.get_size(); i++)
    {
        output_file << elem_col[i].get_material_ID() << endl;
    }

    output_file.close();
}

void VTK_Printer::print_tetrahedron_elems_material_2_vtk_file
(Collection <Geom_Element> & elem_col, Collection <Mesh_Node> & node_col, string path_and_fileName)
{
    Info * info = Info::createInfo();
    info->print_info_message("printing file " + path_and_fileName);

    ofstream output_file;
    output_file.open(path_and_fileName.c_str());
    output_file << "# vtk DataFile Version 3.0" << endl;
    output_file << "solid_mesh" << endl;
    output_file << "ASCII" << endl;
    output_file << "DATASET UNSTRUCTURED_GRID" << endl;

    output_file << "POINTS " << node_col.get_size() << " float" << endl;

    for (UINT i = 1; i <= node_col.get_size(); i++)
    {
        for (int j = 1; j <= 3; j++)
            output_file << node_col[i].get_coordinate(j) << " ";
        output_file << endl;
    }

    output_file << "CELLS " << elem_col.get_size() << " " <<  elem_col.get_size() * 5 <<  endl;

    for (UINT i = 1; i <= elem_col.get_size(); i++)
    {
        output_file << "4 ";

        for (int j = 1; j <= 4; j++)
            output_file << elem_col[i].get_node(j) - 1 << " ";

        output_file << endl;
    }

    output_file << "CELL_TYPES " << elem_col.get_size() << endl;

    for (UINT i = 1; i <= elem_col.get_size(); i++)
    {
        output_file << "10" << endl;
    }

    output_file << "CELL_DATA " << elem_col.get_size() << endl;
    output_file << "SCALARS material" << " float 1 " << endl;
    output_file << "LOOKUP_TABLE default " << endl;

    for (UINT i = 1; i <= elem_col.get_size(); i++)
    {
        output_file << elem_col[i].get_material_ID() << endl;
    }

    output_file.close();
}

void VTK_Printer::print_brick_elems_nodes_boundary_2_vtk_file
(Collection <Geom_Element> & elem_col, Collection <Mesh_Node> & node_col, string path_and_fileName)
{
    Info * info = Info::createInfo();
    info->print_info_message("printing file " + path_and_fileName);

    ofstream output_file;
    output_file.open(path_and_fileName.c_str());
    output_file << "# vtk DataFile Version 3.0" << endl;
    output_file << "solid_mesh" << endl;
    output_file << "ASCII" << endl;
    output_file << "DATASET UNSTRUCTURED_GRID" << endl;

    output_file << "POINTS " << node_col.get_size() << " float" << endl;

    for (UINT i = 1; i <= node_col.get_size(); i++)
    {
        for (int j = 1; j <= 3; j++)
            output_file << node_col[i].get_coordinate(j) << " ";
        output_file << endl;
    }

    output_file << "CELLS " << elem_col.get_size() << " " <<  elem_col.get_size() * 9 <<  endl;

    for (UINT i = 1; i <= elem_col.get_size(); i++)
    {
        output_file << "8 ";

        for (int j = 5; j <= 8; j++)
            output_file << elem_col[i].get_node(j) - 1 << " ";
        for (int j = 1; j <= 4; j++)
            output_file << elem_col[i].get_node(j) - 1 << " ";
        output_file << endl;
    }

    output_file << "CELL_TYPES " << elem_col.get_size() << endl;

    for (UINT i = 1; i <= elem_col.get_size(); i++)
    {
        output_file << "12" << endl;
    }

    output_file << "POINT_DATA " << node_col.get_size() << endl;
    output_file << "SCALARS boundary_condition" << " float 1 " << endl;
    output_file << "LOOKUP_TABLE default " << endl;

    for (UINT i = 1; i <= node_col.get_size(); i++)
    {
        output_file << check_boundary_color(node_col[i]) << endl;
    }

    output_file.close();
}

void VTK_Printer::print_brick_elems_vector_physical_quantity_to_vtk_file
(Collection <Geom_Element> & elem_col, Collection <Post_Node> & node_col, string path_and_fileName, string text_scalar_physical_quantity, string text_vector_physical_quantity)
{
    Info * info = Info::createInfo();
    info->print_info_message("printing file " + path_and_fileName);

    ofstream output_file;
    output_file.open(path_and_fileName.c_str());
    output_file << "# vtk DataFile Version 3.0" << endl;
    output_file << "file_printed_using_dfemtoolz" << endl;
    output_file << "ASCII" << endl;
    output_file << "DATASET UNSTRUCTURED_GRID" << endl;

    output_file << "POINTS " << node_col.get_size() << " float" << endl;

    for (UINT i = 1; i <= node_col.get_size(); i++)
    {
        for (int j = 1; j <= 3; j++)
            output_file << node_col[i].get_coordinate(j) << " ";
        output_file << endl;
    }

    output_file << "CELLS " << elem_col.get_size() << " " <<  elem_col.get_size() * 9 <<  endl;

    for (UINT i = 1; i <= elem_col.get_size(); i++)
    {
        output_file << "8 ";

        for (int j = 1; j <= 8; j++)
            output_file << elem_col[i].get_node(j) - 1 << " ";
        output_file << endl;
    }

    output_file << "CELL_TYPES " << elem_col.get_size() << endl;

    for (UINT i = 1; i <= elem_col.get_size(); i++)
    {
        output_file << "12" << endl;
    }

    output_file << "POINT_DATA " << node_col.get_size() << endl;
    output_file << "SCALARS " << text_scalar_physical_quantity << " float 1 " << endl;
    output_file << "LOOKUP_TABLE default " << endl;

    for (UINT i = 1; i <= node_col.get_size(); i++)
    {
        output_file << get_the_vector_intensity(node_col[i].vector_physical_quantity) << endl;
    }

    output_file << "VECTORS " << text_vector_physical_quantity << " float " << endl;

    for (UINT i = 1; i <= node_col.get_size(); i++)
    {
        for (int j = 1; j <= 3; j++)
            output_file << node_col[i].vector_physical_quantity.get_coordinate(j) << " ";

        output_file << endl;
    }

    output_file.close();
}

void VTK_Printer::print_triangles_to_vtk_file
(Collection <Geom_Element> & triangles, Collection <Mesh_Node> & node_col, string path_and_fileName)
{
    Info * info = Info::createInfo();
    info->print_info_message("printing file " + path_and_fileName);

    ofstream output_file;
    output_file.open(path_and_fileName.c_str());
    output_file << "# vtk DataFile Version 3.0" << endl;
    output_file << "file_printed_using_dfemtoolz" << endl;
    output_file << "ASCII" << endl;
    output_file << "DATASET UNSTRUCTURED_GRID" << endl;

    output_file << "POINTS " << node_col.get_size() << " float" << endl;

    for (UINT i = 1; i <= node_col.get_size(); i++)
    {
        for (int j = 1; j <= 3; j++)
            output_file << node_col[i].get_coordinate(j) << " ";
        output_file << endl;
    }

    output_file << "CELLS " << triangles.get_size() << " " <<  triangles.get_size() * 4 <<  endl;

    for (UINT i = 1; i <= triangles.get_size(); i++)
    {
        output_file << "3 ";

        for (int j = 1; j <= 3; j++)
            output_file << triangles[i].get_node(j) - 1 << " ";
        output_file << endl;
    }

    output_file << "CELL_TYPES " << triangles.get_size() << endl;

    for (UINT i = 1; i <= triangles.get_size(); i++)
    {
        output_file << "5" << endl;
    }

    output_file << "CELL_DATA " << triangles.get_size() << endl;
    output_file << "SCALARS material" << " float 1 " << endl;
    output_file << "LOOKUP_TABLE default " << endl;

    for (UINT i = 1; i <= triangles.get_size(); i++)
    {
        output_file << "1 " << endl;
    }

    output_file.close();
}

void VTK_Printer::print_triangles_to_vtk_file
(bool only_with_flag, Collection <Geom_Element> & triangles, Collection <Mesh_Node> & node_col, string path_and_fileName)
{
    Info * info = Info::createInfo();
    info->print_info_message("printing file " + path_and_fileName);

    ofstream output_file;
    output_file.open(path_and_fileName.c_str());
    output_file << "# vtk DataFile Version 3.0" << endl;
    output_file << "file_printed_using_dfemtoolz" << endl;
    output_file << "ASCII" << endl;
    output_file << "DATASET UNSTRUCTURED_GRID" << endl;

    output_file << "POINTS " << node_col.get_size() << " float" << endl;

    for (UINT i = 1; i <= node_col.get_size(); i++)
    {
        for (int j = 1; j <= 3; j++)
            output_file << node_col[i].get_coordinate(j) << " ";
        output_file << endl;
    }

    UINT no_of_triangles = 0;

    if (!only_with_flag)
        no_of_triangles = triangles.get_size();


    if (only_with_flag)
    for (UINT i = 1; i <= triangles.get_size(); i++)
    if (triangles[i].get_flag())
        no_of_triangles++;

    output_file << "CELLS " << no_of_triangles << " " <<  no_of_triangles * 4 <<  endl;

    if (!only_with_flag)
    for (UINT i = 1; i <= triangles.get_size(); i++)
    {
        output_file << "3 ";

        for (int j = 1; j <= 3; j++)
            output_file << triangles[i].get_node(j) - 1 << " ";
        output_file << endl;
    }

    if (only_with_flag)
    for (UINT i = 1; i <= triangles.get_size(); i++)
    if (triangles[i].get_flag())
    {
        output_file << "3 ";

        for (int j = 1; j <= 3; j++)
            output_file << triangles[i].get_node(j) - 1 << " ";
        output_file << endl;
    }

    output_file << "CELL_TYPES " << no_of_triangles << endl;

    for (UINT i = 1; i <= no_of_triangles; i++)
    {
        output_file << "5" << endl;
    }

    output_file << "CELL_DATA " << no_of_triangles  << endl;
    output_file << "SCALARS material" << " float 1 " << endl;
    output_file << "LOOKUP_TABLE default " << endl;

    for (UINT i = 1; i <= no_of_triangles; i++)
    {
        output_file << "1 " << endl;
    }

    output_file.close();
}

void VTK_Printer::print_triangles_to_vtk_file
(UINT startID, UINT endID, bool only_with_flag, Collection <Geom_Element> & triangles, Collection <Mesh_Node> & node_col, string path_and_fileName)
{
    Info * info = Info::createInfo();
    info->print_info_message("printing file " + path_and_fileName);

    ofstream output_file;
    output_file.open(path_and_fileName.c_str());
    output_file << "# vtk DataFile Version 3.0" << endl;
    output_file << "file_printed_using_dfemtoolz" << endl;
    output_file << "ASCII" << endl;
    output_file << "DATASET UNSTRUCTURED_GRID" << endl;

    output_file << "POINTS " << node_col.get_size() << " float" << endl;

    for (UINT i = 1; i <= node_col.get_size(); i++)
    {
        for (int j = 1; j <= 3; j++)
            output_file << node_col[i].get_coordinate(j) << " ";
        output_file << endl;
    }

    UINT no_of_triangles = 0;

    if (only_with_flag)
    for (UINT i = startID; i <= endID; i++)
    if (triangles[i].get_flag())
        no_of_triangles++;

    if (!only_with_flag)
        no_of_triangles = endID - startID + 1;

    output_file << "CELLS " << no_of_triangles << " " <<  no_of_triangles * 4 <<  endl;

    if (!only_with_flag)
    for (UINT i = startID; i <= endID; i++)
    {
        output_file << "3 ";

        for (int j = 1; j <= 3; j++)
            output_file << triangles[i].get_node(j) - 1 << " ";
        output_file << endl;
    }

    if (only_with_flag)
    for (UINT i = startID; i <= endID; i++)
    if (triangles[i].get_flag())
    {
        output_file << "3 ";

        for (int j = 1; j <= 3; j++)
            output_file << triangles[i].get_node(j) - 1 << " ";
        output_file << endl;
    }

    output_file << "CELL_TYPES " << no_of_triangles << endl;

    for (UINT i = 1; i <= no_of_triangles; i++)
    {
        output_file << "5" << endl;
    }

    output_file << "CELL_DATA " << no_of_triangles  << endl;
    output_file << "SCALARS material" << " float 1 " << endl;
    output_file << "LOOKUP_TABLE default " << endl;

    for (UINT i = 1; i <= no_of_triangles; i++)
    {
        output_file << "1 " << endl;
    }

    output_file.close();
}

void VTK_Printer::print_triangles_to_vtk_file
(UINT color_ID, Collection <Geom_Element> & triangles, Collection <Mesh_Node> & node_col, string path_and_fileName)
{
    Info * info = Info::createInfo();
    info->print_info_message("printing file " + path_and_fileName);

    ofstream output_file;
    output_file.open(path_and_fileName.c_str());
    output_file << "# vtk DataFile Version 3.0" << endl;
    output_file << "file_printed_using_dfemtoolz" << endl;
    output_file << "ASCII" << endl;
    output_file << "DATASET UNSTRUCTURED_GRID" << endl;

    output_file << "POINTS " << node_col.get_size() << " float" << endl;

    for (UINT i = 1; i <= node_col.get_size(); i++)
    {
        for (int j = 1; j <= 3; j++)
            output_file << node_col[i].get_coordinate(j) << " ";
        output_file << endl;
    }

    output_file << "CELLS " << triangles.get_size() << " " <<  triangles.get_size() * 4 <<  endl;

    for (UINT i = 1; i <= triangles.get_size(); i++)
    {
        output_file << "3 ";

        for (int j = 1; j <= 3; j++)
            output_file << triangles[i].get_node(j) - 1 << " ";
        output_file << endl;
    }

    output_file << "CELL_TYPES " << triangles.get_size() << endl;

    for (UINT i = 1; i <= triangles.get_size(); i++)
    {
        output_file << "5" << endl;
    }

    output_file << "CELL_DATA " << triangles.get_size() << endl;
    output_file << "SCALARS material" << " float 1 " << endl;
    output_file << "LOOKUP_TABLE default " << endl;

    for (UINT i = 1; i <= triangles.get_size(); i++)
    {
        output_file << color_ID << endl;
    }

    output_file.close();
}

void VTK_Printer::print_quads_to_vtk_file
(Collection <Geom_Element> & quads, Collection <Mesh_Node> & node_col, string path_and_fileName)
{
    Info * info = Info::createInfo();
    info->print_info_message("printing file " + path_and_fileName);

    ofstream output_file;
    output_file.open(path_and_fileName.c_str());
    output_file << "# vtk DataFile Version 3.0" << endl;
    output_file << "file_printed_using_dfemtoolz" << endl;
    output_file << "ASCII" << endl;
    output_file << "DATASET UNSTRUCTURED_GRID" << endl;

    output_file << "POINTS " << node_col.get_size() << " float" << endl;

    for (UINT i = 1; i <= node_col.get_size(); i++)
    {
        for (int j = 1; j <= 3; j++)
            output_file << node_col[i].get_coordinate(j) << " ";
        output_file << endl;
    }

    output_file << "CELLS " << quads.get_size() << " " <<  quads.get_size() * 5 <<  endl;

    for (UINT i = 1; i <= quads.get_size(); i++)
    {
        output_file << "4 ";

        for (int j = 1; j <= 4; j++)
            output_file << quads[i].get_node(j) - 1 << " ";
        output_file << endl;
    }

    output_file << "CELL_TYPES " << quads.get_size() << endl;

    for (UINT i = 1; i <= quads.get_size(); i++)
    {
        output_file << "9" << endl;
    }

    output_file << "CELL_DATA " << quads.get_size() << endl;
    output_file << "SCALARS material" << " float 1 " << endl;
    output_file << "LOOKUP_TABLE default " << endl;

    for (UINT i = 1; i <= quads.get_size(); i++)
    {
        output_file << "1 " << endl;
    }

    output_file.close();
}

void VTK_Printer::print_quads_to_vtk_file
(bool only_with_flag, Collection <Geom_Element> & quads, Collection <Mesh_Node> & node_col, string path_and_fileName)
{
    Info * info = Info::createInfo();
    info->print_info_message("printing file " + path_and_fileName);

    ofstream output_file;
    output_file.open(path_and_fileName.c_str());
    output_file << "# vtk DataFile Version 3.0" << endl;
    output_file << "file_printed_using_dfemtoolz" << endl;
    output_file << "ASCII" << endl;
    output_file << "DATASET UNSTRUCTURED_GRID" << endl;

    output_file << "POINTS " << node_col.get_size() << " float" << endl;

    for (UINT i = 1; i <= node_col.get_size(); i++)
    {
        for (int j = 1; j <= 3; j++)
            output_file << node_col[i].get_coordinate(j) << " ";
        output_file << endl;
    }

    UINT no_of_quads = 0;

    if (!only_with_flag)
        no_of_quads = quads.get_size();

    if (only_with_flag)
    for (UINT i = 1; i <= quads.get_size(); i++)
    if (quads[i].get_flag())
        no_of_quads++;

    output_file << "CELLS " << no_of_quads << " " <<  no_of_quads * 5 <<  endl;

    if (!only_with_flag)
    for (UINT i = 1; i <= quads.get_size(); i++)
    {
        output_file << "4 ";

        for (int j = 1; j <= 4; j++)
            output_file << quads[i].get_node(j) - 1 << " ";
        output_file << endl;
    }

    if (only_with_flag)
    for (UINT i = 1; i <= quads.get_size(); i++)
    if (quads[i].get_flag())
    {
        output_file << "4 ";

        for (int j = 1; j <= 4; j++)
            output_file << quads[i].get_node(j) - 1 << " ";
        output_file << endl;
    }

    output_file << "CELL_TYPES " << no_of_quads << endl;

    for (UINT i = 1; i <= no_of_quads; i++)
    {
        output_file << "9" << endl;
    }

    output_file << "CELL_DATA " << no_of_quads << endl;
    output_file << "SCALARS material" << " float 1 " << endl;
    output_file << "LOOKUP_TABLE default " << endl;

    for (UINT i = 1; i <= no_of_quads; i++)
    {
        output_file << "1 " << endl;
    }

    output_file.close();
}

void VTK_Printer::print_quads_to_vtk_file
(UINT startID, UINT endID, bool only_with_flag, Collection <Geom_Element> & quads, Collection <Mesh_Node> & node_col, string path_and_fileName)
{
    Info * info = Info::createInfo();
    info->print_info_message("printing file " + path_and_fileName);

    ofstream output_file;
    output_file.open(path_and_fileName.c_str());
    output_file << "# vtk DataFile Version 3.0" << endl;
    output_file << "file_printed_using_dfemtoolz" << endl;
    output_file << "ASCII" << endl;
    output_file << "DATASET UNSTRUCTURED_GRID" << endl;

    output_file << "POINTS " << node_col.get_size() << " float" << endl;

    for (UINT i = 1; i <= node_col.get_size(); i++)
    {
        for (int j = 1; j <= 3; j++)
            output_file << node_col[i].get_coordinate(j) << " ";
        output_file << endl;
    }

    UINT no_of_quads = 0;

    if (only_with_flag)
    for (UINT i = startID; i <= endID; i++)
    if (quads[i].get_flag())
        no_of_quads++;

    if (!only_with_flag)
        no_of_quads = endID - startID + 1;

    output_file << "CELLS " << no_of_quads << " " <<  no_of_quads * 5 <<  endl;

    if (!only_with_flag)
    for (UINT i = startID; i <= endID; i++)
    {
        output_file << "4 ";

        for (int j = 1; j <= 4; j++)
            output_file << quads[i].get_node(j) - 1 << " ";
        output_file << endl;
    }

    if (only_with_flag)
    for (UINT i = startID; i <= endID; i++)
    if (quads[i].get_flag())
    {
        output_file << "4 ";

        for (int j = 1; j <= 4; j++)
            output_file << quads[i].get_node(j) - 1 << " ";
        output_file << endl;
    }

    output_file << "CELL_TYPES " << no_of_quads << endl;

    for (UINT i = 1; i <= no_of_quads; i++)
    {
        output_file << "9" << endl;
    }

    output_file << "CELL_DATA " << no_of_quads << endl;
    output_file << "SCALARS material" << " float 1 " << endl;
    output_file << "LOOKUP_TABLE default " << endl;

    for (UINT i = 1; i <= no_of_quads; i++)
    {
        output_file << "1 " << endl;
    }

    output_file.close();
}

void VTK_Printer::print_quads_to_vtk_file
(UINT color_ID, Collection <Geom_Element> & quads, Collection <Mesh_Node> & node_col, string path_and_fileName)
{
    Info * info = Info::createInfo();
    info->print_info_message("printing file " + path_and_fileName);

    ofstream output_file;
    output_file.open(path_and_fileName.c_str());
    output_file << "# vtk DataFile Version 3.0" << endl;
    output_file << "file_printed_using_dfemtoolz" << endl;
    output_file << "ASCII" << endl;
    output_file << "DATASET UNSTRUCTURED_GRID" << endl;

    output_file << "POINTS " << node_col.get_size() << " float" << endl;

    for (UINT i = 1; i <= node_col.get_size(); i++)
    {
        for (int j = 1; j <= 3; j++)
            output_file << node_col[i].get_coordinate(j) << " ";
        output_file << endl;
    }

    output_file << "CELLS " << quads.get_size() << " " <<  quads.get_size() * 5 <<  endl;

    for (UINT i = 1; i <= quads.get_size(); i++)
    {
        output_file << "4 ";

        for (int j = 1; j <= 4; j++)
            output_file << quads[i].get_node(j) - 1 << " ";
        output_file << endl;
    }

    output_file << "CELL_TYPES " << quads.get_size() << endl;

    for (UINT i = 1; i <= quads.get_size(); i++)
    {
        output_file << "9" << endl;
    }

    output_file << "CELL_DATA " << quads.get_size() << endl;
    output_file << "SCALARS material" << " float 1 " << endl;
    output_file << "LOOKUP_TABLE default " << endl;

    for (UINT i = 1; i <= quads.get_size(); i++)
    {
        output_file << color_ID << endl;
    }

    output_file.close();
}

void VTK_Printer::print_quads_as_lines_to_vtk_file
(Collection <Geom_Element> & quads, Collection <Mesh_Node> & node_col, string path_and_fileName)
{
    Info * info = Info::createInfo();
    info->print_info_message("printing file " + path_and_fileName);

    ofstream output_file;
    output_file.open(path_and_fileName.c_str());
    output_file << "# vtk DataFile Version 3.0" << endl;
    output_file << "file_printed_using_dfemtoolz" << endl;
    output_file << "ASCII" << endl;
    output_file << "DATASET POLYDATA" << endl;

    output_file << "POINTS " << node_col.get_size() << " float" << endl;

    for (UINT i = 1; i <= node_col.get_size(); i++)
    {
        for (int j = 1; j <= 3; j++)
            output_file << node_col[i].get_coordinate(j) << " ";
        output_file << endl;
    }

    output_file << "LINES " << quads.get_size() * 4 << " " <<  quads.get_size() * 4 * 3 <<  endl;

    for (UINT i = 1; i <= quads.get_size(); i++)
    {
        output_file << "2 " <<
        quads[i].get_node(1) - 1 << "  " <<
        quads[i].get_node(2) - 1 << "\n2 " <<
        quads[i].get_node(2) - 1 << "  " <<
        quads[i].get_node(3) - 1 << "\n2 " <<
        quads[i].get_node(3) - 1 << "  " <<
        quads[i].get_node(4) - 1 << "\n2 " <<
        quads[i].get_node(4) - 1 << "  " <<
        quads[i].get_node(1) - 1 << "\n";
    }


    output_file << "CELL_DATA " << 4 * quads.get_size() << endl;
    output_file << "SCALARS pointvar float" << endl;
    output_file << "LOOKUP_TABLE default " << endl;

    for (UINT i = 1; i <= quads.get_size(); i++)
        output_file << "1 ";


    output_file.close();
}

void VTK_Printer::print_quads_as_lines_to_vtk_file
(UINT color_ID, Collection <Geom_Element> & quads, Collection <Mesh_Node> & node_col, string path_and_fileName)
{
    Info * info = Info::createInfo();
    info->print_info_message("printing file " + path_and_fileName);

    ofstream output_file;
    output_file.open(path_and_fileName.c_str());
    output_file << "# vtk DataFile Version 3.0" << endl;
    output_file << "file_printed_using_dfemtoolz" << endl;
    output_file << "ASCII" << endl;
    output_file << "DATASET POLYDATA" << endl;

    output_file << "POINTS " << node_col.get_size() << " float" << endl;

    for (UINT i = 1; i <= node_col.get_size(); i++)
    {
        for (int j = 1; j <= 3; j++)
            output_file << node_col[i].get_coordinate(j) << " ";
        output_file << endl;
    }

    output_file << "LINES " << quads.get_size() * 4 << " " <<  quads.get_size() * 4 * 3 <<  endl;

    for (UINT i = 1; i <= quads.get_size(); i++)
    {
        output_file << "2 " <<
        quads[i].get_node(1) - 1 << "  " <<
        quads[i].get_node(2) - 1 << "\n2 " <<
        quads[i].get_node(2) - 1 << "  " <<
        quads[i].get_node(3) - 1 << "\n2 " <<
        quads[i].get_node(3) - 1 << "  " <<
        quads[i].get_node(4) - 1 << "\n2 " <<
        quads[i].get_node(4) - 1 << "  " <<
        quads[i].get_node(1) - 1 << "\n";
    }

    output_file << "CELL_DATA " << 4 * quads.get_size() << endl;
    output_file << "SCALARS pointvar float" << endl;
    output_file << "LOOKUP_TABLE default " << endl;

    for (UINT i = 1; i <= 4 * quads.get_size(); i++)
        output_file << color_ID << endl;

    output_file.close();
}


void VTK_Printer::print_triangles_as_lines_to_vtk_file
(Collection <Geom_Element> & triangles, Collection <Mesh_Node> & node_col, string path_and_fileName)
{
    Info * info = Info::createInfo();
    info->print_info_message("printing file " + path_and_fileName);

    ofstream output_file;
    output_file.open(path_and_fileName.c_str());
    output_file << "# vtk DataFile Version 3.0" << endl;
    output_file << "file_printed_using_dfemtoolz" << endl;
    output_file << "ASCII" << endl;
    output_file << "DATASET POLYDATA" << endl;

    output_file << "POINTS " << node_col.get_size() << " float" << endl;

    for (UINT i = 1; i <= node_col.get_size(); i++)
    {
        for (int j = 1; j <= 3; j++)
            output_file << node_col[i].get_coordinate(j) << " ";
        output_file << endl;
    }

    output_file << "LINES " << triangles.get_size() * 3 << " " <<  triangles.get_size() * 3 * 3 <<  endl;

    for (UINT i = 1; i <= triangles.get_size(); i++)
    {
        output_file << "2 " <<
        triangles[i].get_node(1) - 1 << "  " <<
        triangles[i].get_node(2) - 1 << "\n2 " <<
        triangles[i].get_node(2) - 1 << "  " <<
        triangles[i].get_node(3) - 1 << "\n2 " <<
        triangles[i].get_node(3) - 1 << "  " <<
        triangles[i].get_node(1) - 1 << "\n";
    }

    output_file << "CELL_DATA " << 3 * triangles.get_size() << endl;
    output_file << "SCALARS pointvar float" << endl;
    output_file << "LOOKUP_TABLE default " << endl;

    for (UINT i = 1; i <= 3*triangles.get_size(); i++)
    {
        output_file << "1 ";
    }


    output_file.close();
}

void VTK_Printer::print_triangles_as_lines_to_vtk_file
(UINT color_ID, Collection <Geom_Element> & triangles, Collection <Mesh_Node> & node_col, string path_and_fileName)
{
    Info * info = Info::createInfo();
    info->print_info_message("printing file " + path_and_fileName);

    ofstream output_file;
    output_file.open(path_and_fileName.c_str());
    output_file << "# vtk DataFile Version 3.0" << endl;
    output_file << "file_printed_using_dfemtoolz" << endl;
    output_file << "ASCII" << endl;
    output_file << "DATASET POLYDATA" << endl;

    output_file << "POINTS " << node_col.get_size() << " float" << endl;

    for (UINT i = 1; i <= node_col.get_size(); i++)
    {
        for (int j = 1; j <= 3; j++)
            output_file << node_col[i].get_coordinate(j) << " ";
        output_file << endl;
    }

    output_file << "LINES " << triangles.get_size() * 3 << " " <<  triangles.get_size() * 3 * 3 <<  endl;

    for (UINT i = 1; i <= triangles.get_size(); i++)
    {
        output_file << "2 " <<
        triangles[i].get_node(1) - 1 << "  " <<
        triangles[i].get_node(2) - 1 << "\n2 " <<
        triangles[i].get_node(2) - 1 << "  " <<
        triangles[i].get_node(3) - 1 << "\n2 " <<
        triangles[i].get_node(3) - 1 << "  " <<
        triangles[i].get_node(1) - 1 << "\n";
    }

    output_file << "CELL_DATA " << 3 * triangles.get_size() << endl;
    output_file << "SCALARS pointvar float" << endl;
    output_file << "LOOKUP_TABLE default " << endl;

    for (UINT i = 1; i <= 3 * triangles.get_size(); i++)
        output_file << color_ID << endl;

    output_file.close();
}

void VTK_Printer::print_lines_to_vtk_file
(SuperCollection <Geom_Node> & lines, string path_and_fileName)
{
    Info * info = Info::createInfo();
    info->print_info_message("printing file " + path_and_fileName);

    ofstream output_file;
    output_file.open(path_and_fileName.c_str());
    output_file << "# vtk DataFile Version 3.0" << endl;
    output_file << "file_printed_using_dfemtoolz" << endl;
    output_file << "ASCII" << endl;
    output_file << "DATASET POLYDATA" << endl;

    UINT no_of_nodez = 0;

    for (UINT i = 1; i <= lines.get_size(); i++)
        no_of_nodez += lines[i].get_size();

    output_file << "POINTS " << no_of_nodez << " float" << endl;

    UINT no_of_lines = 0;

    SuperCollection <UINT> nodeIDs_supercol;

    for (UINT i = 1; i <= lines.get_size(); i++)
    {
        Collection <UINT> nodeIDs_col;

        for (UINT j = 1; j <= lines[i].get_size(); j++)
        {
            no_of_lines++;
            nodeIDs_col.insert(no_of_lines);

            for (int k = 1; k <= 3; k++)
                output_file << lines[i][j].get_coordinate(k) << " ";
            output_file << endl;
        }

        nodeIDs_supercol.insert(nodeIDs_col);
    }

    no_of_lines = no_of_lines - lines.get_size();

    output_file << "LINES " << no_of_lines << " " <<  no_of_lines * 3 <<  endl;

    for (UINT i = 1; i <= lines.get_size(); i++)
    for (UINT j = 1; j < lines[i].get_size(); j++)
    {
        output_file << "2 " <<
        nodeIDs_supercol[i][j] - 1 << "  " <<
        nodeIDs_supercol[i][j+1] - 1 << "\n";
    }


    output_file << "CELL_DATA " << no_of_lines << endl;
    output_file << "SCALARS pointvar float" << endl;
    output_file << "LOOKUP_TABLE default " << endl;

    for (UINT i = 1; i <= no_of_lines; i++)
        output_file << "1 ";


    output_file.close();
}



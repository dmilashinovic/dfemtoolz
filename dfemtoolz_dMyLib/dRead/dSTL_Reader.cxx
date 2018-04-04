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

#include "dSTL_Reader.h"


STL_Reader::STL_Reader()
{
    m_sPath_and_FileName = constants::input_directory + "pakf.dat";
}

STL_Reader * STL_Reader::m_pSTL_ReaderSingleton = 0;
STL_Reader * STL_Reader::create_STL_Reader()
{
    if (m_pSTL_ReaderSingleton == 0)
        m_pSTL_ReaderSingleton = new STL_Reader();
    return m_pSTL_ReaderSingleton;
}

STL_Reader::~STL_Reader()
{
    delete m_pSTL_ReaderSingleton;
    m_pSTL_ReaderSingleton = 0;
}

void STL_Reader::del_reader()
{
    delete m_pSTL_ReaderSingleton;
    m_pSTL_ReaderSingleton = 0;
}

bool STL_Reader::negative_reading_condition(char * buffer)
{
    if (
            buffer[0] == 'e' &&
            buffer[1] == 'n' &&
            buffer[2] == 'd' &&
            buffer[3] == 's' &&
            buffer[4] == 'o' &&
            buffer[5] == 'l' &&
            buffer[6] == 'i' &&
            buffer[7] == 'd')
        return true;
    return false;
}

bool STL_Reader::read_STL_edges
(Collection<Geom_Node> & node_col, Collection<Geom_Element> & edge_col, string path_and_fileName)
{
    ifstream stl_file;
    m_uTriangles_read = 0;

    if (path_and_fileName.length() > constants::minimum_characters_in_fileName)
        m_sPath_and_FileName = path_and_fileName;

    stl_file.open(m_sPath_and_FileName.c_str());

    if (reading::check_if_file_is_not_open(stl_file, m_sPath_and_FileName))
        return false;

    char line[constants::no_of_line_characters];

    Geom_Node node;
    stl_file.getline(line, constants::no_of_line_characters);
    {
        double dX, dY, dZ;
        bool edge_switch, end_loop = false;

        for(;!end_loop;)
        {
            edge_switch = 0;

            for (int i = 0; i < 7; i++)
            {
                stl_file.getline(line, constants::no_of_line_characters);

                if (this->negative_reading_condition(line))
                {
                    end_loop = true;
                    break;
                }

                if (i > 1 && i < 5)
                {
                    sscanf(line, "%*s%lf%lf%lf", &dX, &dY, &dZ);

                    node.set_coordinate_X(dX);
                    node.set_coordinate_Y(dY);
                    node.set_coordinate_Z(dZ);

                    node_col.insert(node);

                    if (i == 4)
                        edge_switch = 1;
                }

                if (edge_switch)
                {
                    m_uTriangles_read++;
                    this->put_triangle_edges_to_collection(node_col, edge_col);
                    edge_switch = 0;
                }
            }
        }
    }
    stl_file.close();

    this->calcul8_boundary_edges(node_col, edge_col);

    return true;
}

bool STL_Reader::read_STL_triangles
(Collection<STL_Triangle> & triangle_col, string path_and_fileName)
{
    ifstream stl_file;
    m_uTriangles_read = 0;

    if (path_and_fileName.length() > constants::minimum_characters_in_fileName)
        m_sPath_and_FileName = path_and_fileName;

    stl_file.open(m_sPath_and_FileName.c_str());

    if (reading::check_if_file_is_not_open(stl_file, m_sPath_and_FileName))
        return false;

    char line[constants::no_of_line_characters];

    stl_file.getline(line, constants::no_of_line_characters);

    double dX, dY, dZ;
    STL_Triangle triangle;

    for(;;)
    {
        stl_file.getline(line, constants::no_of_line_characters);

        if (this->negative_reading_condition(line))
            break;

        stl_file.getline(line, constants::no_of_line_characters);
        stl_file.getline(line, constants::no_of_line_characters);

        sscanf(line, "%*s%lf%lf%lf", &dX, &dY, &dZ);
        triangle.node1.set_coordinate_X(dX);
        triangle.node1.set_coordinate_Y(dY);
        triangle.node1.set_coordinate_Z(dZ);

        stl_file.getline(line, constants::no_of_line_characters);
        sscanf(line, "%*s%lf%lf%lf", &dX, &dY, &dZ);
        triangle.node2.set_coordinate_X(dX);
        triangle.node2.set_coordinate_Y(dY);
        triangle.node2.set_coordinate_Z(dZ);

        stl_file.getline(line, constants::no_of_line_characters);
        sscanf(line, "%*s%lf%lf%lf", &dX, &dY, &dZ);
        triangle.node3.set_coordinate_X(dX);
        triangle.node3.set_coordinate_Y(dY);
        triangle.node3.set_coordinate_Z(dZ);

        m_uTriangles_read++;
        triangle.set_ID(m_uTriangles_read);

        triangle_col.insert(triangle);

        stl_file.getline(line, constants::no_of_line_characters);
        stl_file.getline(line, constants::no_of_line_characters);
    }

    triangle_col.get_size();
    stl_file.close();

    return true;
}

UINT STL_Reader::how_many_triangles_read()
{
    return m_uTriangles_read;
}

void STL_Reader::put_triangle_edges_to_collection
(Collection<Geom_Node> & node_c, Collection<Geom_Element> & edge_c)
{
    Geom_Element edge(2);
    edge.set_boundary(true);

    edge.set_ID((m_uTriangles_read * 3) - 2);
    edge.set_node(node_c.get_size() - 2, 1);
    edge.set_node(node_c.get_size() - 1, 2);
    edge_c.insert(edge);

    edge.set_ID((m_uTriangles_read * 3) - 1);
    edge.set_node(node_c.get_size() - 1, 1);
    edge.set_node(node_c.get_size() - 0, 2);
    edge_c.insert(edge);

    edge.set_ID((m_uTriangles_read * 3) - 0);
    edge.set_node(node_c.get_size() - 2, 1);
    edge.set_node(node_c.get_size() - 0, 2);
    edge_c.insert(edge);
}

void STL_Reader::calcul8_boundary_edges
(Collection<Geom_Node> & node_c, Collection<Geom_Element> & edge_c)
{
    UINT count = 0;
    for (UINT i = 1; i <= edge_c.get_size(); i ++)
    {
        if (edge_c[i].get_boundary())
        for (UINT j = 1; j <= edge_c.get_size(); j ++)
        if (i != j)
        if (edge_c[j].get_boundary())
        if (these_edges_are_same(edge_c[i], edge_c[j], node_c))
        {
            edge_c[i].set_boundary(false);
            edge_c[j].set_boundary(false);
            count++;
            break;
        }
    }
}

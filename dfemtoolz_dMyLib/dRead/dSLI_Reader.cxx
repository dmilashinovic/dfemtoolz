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

#include "dSLI_Reader.h"


SLI_Reader::SLI_Reader()
{
    m_sPath_and_FileName = constants::input_directory + "simple_list.sli";
}

SLI_Reader * SLI_Reader::m_pSLI_ReaderSingleton = 0;
SLI_Reader * SLI_Reader::create_SLI_Reader()
{
    if (m_pSLI_ReaderSingleton == 0)
        m_pSLI_ReaderSingleton = new SLI_Reader();
    return m_pSLI_ReaderSingleton;
}

SLI_Reader::~SLI_Reader()
{
    delete m_pSLI_ReaderSingleton;
    m_pSLI_ReaderSingleton = 0;
}

bool SLI_Reader::negative_reading_condition(char * buffer)
{
    if (buffer[0] == 'C')
        return true;
    if (buffer[0] == 'c')
        return true;
    return false;
}

UINT SLI_Reader::read_file
(Collection <Mesh_Node> & node_col,
Collection<Geom_Element> & elem_col,
Collection <Geom_Element> & init_face_col,
Collection <Geom_Element> & contact_face_col,
string path_and_fileName)
{
    ifstream input_sli;

    if (path_and_fileName.length() > constants::minimum_characters_in_fileName)
        m_sPath_and_FileName = path_and_fileName;

    input_sli.open(m_sPath_and_FileName.c_str());

    if (reading::check_if_file_is_not_open(input_sli, m_sPath_and_FileName))
        return 0;

    char line[constants::no_of_line_characters];

    int N = 0;
    for (;;)
    {
        input_sli.getline(line, constants::no_of_line_characters);

        if (!this->negative_reading_condition(line))
            N++;
        if (N > constants::no_of_SLI_usable_lines_before_nodes_block) break;
    }

    UINT no_of_node_lets = this->read_nodes(line, node_col, input_sli);

    Info * info = Info::createInfo();
    info->print_info_message(utos(node_col.get_size()) + " nodes read!");

    int nodes_per_element_read_from_SLI;

    N = 0;
    for (;;)
    {
        input_sli.getline(line, constants::no_of_line_characters);

        if (!this->negative_reading_condition(line))
            N++;

        if (N > constants::no_of_SLI_usable_lines_before_nodes_per_element_after_nodes_block)
        {
            sscanf(line, "%d", &nodes_per_element_read_from_SLI);
            break;
        }
    }

    for (;;)
    {
        input_sli.getline(line, constants::no_of_line_characters);
        if (this->negative_reading_condition(line)) continue;
        break;
    }

    this->read_elements(line, nodes_per_element_read_from_SLI, elem_col, input_sli);

    info->print_info_message(utos(nodes_per_element_read_from_SLI) + " nodes per element");
    info->print_info_message(utos(elem_col.get_size()) + " elements read!");

   int NoOfInletFaces = 0;
    input_sli.getline(line, constants::no_of_line_characters);
    sscanf(line, "%d", &NoOfInletFaces);

    if (NoOfInletFaces > 0)
        this->read_numsta_faces
        (init_face_col, nodes_per_element_read_from_SLI, input_sli);

    int NoOfContactFaces = 0;
    input_sli.getline(line, constants::no_of_line_characters);
    input_sli.getline(line, constants::no_of_line_characters);
    sscanf(line, "%d", &NoOfContactFaces);

    if (NoOfContactFaces > 0)
        this->read_numstb_faces
        (contact_face_col, nodes_per_element_read_from_SLI, input_sli);

    input_sli.close();
    return no_of_node_lets;
}

UINT SLI_Reader::read_file
(Collection <Mesh_Node> & node_col, Collection<Geom_Element> & elem_col, string path_and_fileName)
{
    ifstream input_sli;

    if (path_and_fileName.length() > constants::minimum_characters_in_fileName)
        m_sPath_and_FileName = path_and_fileName;

    input_sli.open(m_sPath_and_FileName.c_str());

    if (reading::check_if_file_is_not_open(input_sli, m_sPath_and_FileName))
        return 0;

    char line[constants::no_of_line_characters];

    int N = 0;
    for (;;)
    {
        input_sli.getline(line, constants::no_of_line_characters);

        if (!this->negative_reading_condition(line))
            N++;
        if (N > constants::no_of_SLI_usable_lines_before_nodes_block) break;
    }

    UINT no_of_node_lets = this->read_nodes(line, node_col, input_sli);

    Info * info = Info::createInfo();
    info->print_info_message(utos(node_col.get_size()) + " nodes read!");

    int nodes_per_element_read_from_SLI;

    N = 0;
    for (;;)
    {
        input_sli.getline(line, constants::no_of_line_characters);

        if (!this->negative_reading_condition(line))
            N++;

        if (N > constants::no_of_SLI_usable_lines_before_nodes_per_element_after_nodes_block)
        {
            sscanf(line, "%d", &nodes_per_element_read_from_SLI);
            break;
        }
    }

    for (;;)
    {
        input_sli.getline(line, constants::no_of_line_characters);
        if (this->negative_reading_condition(line)) continue;
        break;
    }

    this->read_elements(line, nodes_per_element_read_from_SLI, elem_col, input_sli);

    info->print_info_message(utos(nodes_per_element_read_from_SLI) + " nodes per element");
    info->print_info_message(utos(elem_col.get_size()) + " elements read!");

    input_sli.close();
    return no_of_node_lets;
}

void SLI_Reader::read_elements
(char * the_line, int & nodes_per_elem, Collection<Geom_Element> & elem_col, ifstream & SLI_file)
{
    bool firstlineout = false;

    Geom_Element element(nodes_per_elem);

    Info * info = Info::createInfo();
    info->print_info_message("reading elements... ");

    UINT node_ID[11];

    for(;;)
    {
        if (!firstlineout)
            firstlineout = reading::check_if_block_reading_is_ok(the_line);

        if (this->negative_reading_condition(the_line)) break;

        sscanf(the_line, "%*d%d%d%d%d%d%d%d%d%d%d",
            &node_ID[1], &node_ID[2], &node_ID[3], &node_ID[4],
            &node_ID[5], &node_ID[6], &node_ID[7], &node_ID[8], &node_ID[9], &node_ID[10]);

        for (int i = 1; i <= nodes_per_elem; i++)
            element.set_node(node_ID[i], i);

        element.set_boundary((bool) node_ID[nodes_per_elem + 1]);
        element.set_material_ID((int) node_ID[nodes_per_elem + 2]);

        elem_col.insert(element);
        SLI_file.getline(the_line, constants::no_of_line_characters);
    };
}

UINT SLI_Reader::read_nodes
(char * the_line, Collection<Mesh_Node> & node_col, ifstream & SLI_file)
{
    bool firstlineout = false;

    UINT no_of_nodelets = 0;

    Mesh_Node node;
    int temp[9];
    UINT let_ID;
    double d_X, d_Y, d_Z;

    Info * info = Info::createInfo();
    info->print_info_message("reading nodes... ");

    for(;;)
    {
        if (!firstlineout)
            firstlineout = reading::check_if_block_reading_is_ok(the_line);

        if (this->negative_reading_condition(the_line)) break;

        sscanf(the_line, "%*d%d%d%d%d%d%d%d%d%lf%lf%lf%d",
            &temp[1], &temp[2], &temp[3], &temp[4],
            &temp[5], &temp[6], &temp[7], &temp[8],
            &d_X, &d_Y, &d_Z, &let_ID);

        node.clear_boundary();

        if((bool)temp[1])
            node.set_boundary(constants::IS_BOUNDARY_VX);
        if((bool)temp[2])
            node.set_boundary(constants::IS_BOUNDARY_VY);
        if((bool)temp[3])
            node.set_boundary(constants::IS_BOUNDARY_VZ);
        if((bool)temp[4])
            node.set_boundary(constants::IS_ON_INLET);
        if((bool)temp[5])
            node.set_boundary(constants::IS_ON_OUTLET);
        if((bool)temp[6])
            node.set_boundary(constants::IS_BOUNDARY_P);
        if((bool)temp[7])
            node.set_boundary(constants::IS_BOUNDARY_T);
        if((bool)temp[8])
            node.set_boundary(constants::IS_ON_EDGE);

        node.set_coordinate_X(d_X);
        node.set_coordinate_Y(d_Y);
        node.set_coordinate_Z(d_Z);
        node.set_ID(let_ID);
        node_col.insert(node);

        if (let_ID > no_of_nodelets)
            no_of_nodelets = let_ID;

        SLI_file.getline(the_line, constants::no_of_line_characters);
    };
    return no_of_nodelets;
}

void SLI_Reader::read_numsta_faces
(Collection <Geom_Element> & init_face_col, int node_per_elem, ifstream & SLI_file)
{
    char line[constants::no_of_line_characters];

    UINT elemID, nodes[6];

    Geom_Element init_face(5);

    for (;;)
    {
        SLI_file.getline(line, constants::no_of_line_characters);
        if (line[0] == 'C')
        if (line[7] == 'B') break;

        if (node_per_elem == 8)
        {
            sscanf(line, "%d %d %d %d %d %d",
            &elemID, &nodes[1], &nodes[2], &nodes[3], &nodes[4], &nodes[5]);

            for (int j = 1; j <= 5; j++)
                init_face.set_node(nodes[j], j);
        }

        if (node_per_elem == 4)
        {
            sscanf(line, "%d %d %d %d %d",
            &elemID, &nodes[1], &nodes[2], &nodes[3], &nodes[4]);

            for (int j = 1; j <= 5; j++)
                init_face.set_node(nodes[j], j);
        }

        init_face.set_ID(elemID);

        init_face_col.insert(init_face);
    }
}

void SLI_Reader::read_numstb_faces
(Collection <Geom_Element> & contact_face_col, int node_per_elem, ifstream & SLI_file)
{
    char line[constants::no_of_line_characters];

    UINT elemID, nodes[10], side, ID;

    Geom_Element contact_face;

    for (;;)
    {
        SLI_file.getline(line, constants::no_of_line_characters);
        if (line[0] == 'S') break;

        if (node_per_elem == 8)
        {
            sscanf(line, "%d %d %d %d %d %d %d %d %d %d",
            &ID, &elemID, &nodes[1], &nodes[2], &nodes[3], &nodes[4], &nodes[5], &nodes[6], &nodes[7], &side);

            for (int j = 1; j <= 7; j++)
                contact_face.set_node(nodes[j], j);
        }

        if (node_per_elem == 4)
        {
            sscanf(line, "%d %d %d %d %d %d %d %d",
            &elemID, &nodes[1], &nodes[2], &nodes[3], &nodes[4], &nodes[5], &nodes[6], &side);

            for (int j = 1; j <= 6; j++)
                contact_face.set_node(nodes[j], j);
        }

        contact_face.set_ID(elemID);
        contact_face.set_boundary((bool)side);
        contact_face_col.insert(contact_face);
    }
}


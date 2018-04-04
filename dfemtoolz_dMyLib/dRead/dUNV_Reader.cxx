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

#include "dUNV_Reader.h"


UNV_Reader::UNV_Reader()
{
    m_sPath_and_FileName = constants::input_directory + "pakf.unv";
}

UNV_Reader * UNV_Reader::m_pUNV_ReaderSingleton = 0;
UNV_Reader * UNV_Reader::create_UNV_Reader()
{
    if (m_pUNV_ReaderSingleton == 0)
        m_pUNV_ReaderSingleton = new UNV_Reader();
    return m_pUNV_ReaderSingleton;
}

UNV_Reader::~UNV_Reader()
{}

bool UNV_Reader::negative_reading_condition(char * buffer)
{
    if ((buffer[3] == ' ') && (buffer[4] == '-') && (buffer[5] == '1'))
        return true;
    return false;
}

bool UNV_Reader::read_geometry
(int nodes_per_element, Collection <Post_Node> & node_col, Collection<Geom_Element> & elem_col, string path_and_fileName)
{
    ifstream input_unv;

    if (path_and_fileName.length() > constants::minimum_characters_in_fileName)
        m_sPath_and_FileName = path_and_fileName;

    input_unv.open(m_sPath_and_FileName.c_str());

    if (reading::check_if_file_is_not_open(input_unv, m_sPath_and_FileName))
        return false;

    char line[constants::no_of_line_characters];

    for (;;)
    {
        input_unv.getline(line, constants::no_of_line_characters);

        if (this->negative_reading_condition(line))
        {
            input_unv.getline(line, constants::no_of_line_characters);
            break;
        }
    }

    this->read_nodes(node_col, input_unv);

    for (;;)
    {
        input_unv.getline(line, constants::no_of_line_characters);
        if ((line[2] == 'D') && (line[3] == 'O') && (line[4] == 'F'))
            break;
    }

    this->read_boundary_conditions(node_col, input_unv);

    input_unv.getline(line, constants::no_of_line_characters);
    input_unv.getline(line, constants::no_of_line_characters);

    this->read_elements(nodes_per_element, elem_col, input_unv);

    for (UINT i = 1; i <= 10; i++)
        input_unv.getline(line, constants::no_of_line_characters);

    input_unv.close();
    return true;
}

void UNV_Reader::read_elements
(int & nodes_per_elem, Collection<Geom_Element> & elem_col, ifstream & UNV_file)
{
    bool firstlineout = false;

    Geom_Element element(nodes_per_elem);

    Info * info = Info::createInfo();
    info->print_info_message("reading elements... ");

    UINT node_ID[10];

    char line[constants::no_of_line_characters];

    for(;;)
    {
        UNV_file.getline(line, constants::no_of_line_characters);
        if (!firstlineout)
            firstlineout = reading::check_if_block_reading_is_ok(line);

        if (this->negative_reading_condition(line)) break;

        sscanf(line, "%d",
            &node_ID[0]);

        UNV_file.getline(line, constants::no_of_line_characters);
        sscanf(line, "%d%d%d%d%d%d%d%d",
            &node_ID[1], &node_ID[2], &node_ID[3], &node_ID[4],
            &node_ID[5], &node_ID[6], &node_ID[7], &node_ID[8]);

        for (int i = 1; i <= nodes_per_elem; i++)
            element.set_node(node_ID[i], i);

        elem_col.insert(element);
    };
}

void UNV_Reader::read_nodes
(Collection<Post_Node> & node_col, ifstream & UNV_file)
{
    bool firstlineout = false;

    Post_Node node;
    double d_X, d_Y, d_Z;
    UINT ID;

    char line[constants::no_of_line_characters];

    Info * info = Info::createInfo();
    info->print_info_message("reading nodes... ");

    for(;;)
    {
        UNV_file.getline(line, constants::no_of_line_characters);

        if (!firstlineout)
            firstlineout = reading::check_if_block_reading_is_ok(line);

        if (this->negative_reading_condition(line)) break;

        sscanf(line, "%d%*d%*d%*d %lf %lf %lf",
            &ID, &d_X, &d_Y, &d_Z);

        node.set_ID(ID);
        node.set_coordinate_X(d_X);
        node.set_coordinate_Y(d_Y);
        node.set_coordinate_Z(d_Z);
        node_col.insert(node);
    };
}

void UNV_Reader::read_boundary_conditions
(Collection<Post_Node> & node_col, ifstream & UNV_file)
{
    bool firstlineout = false;

    int Vx, Vy, Vz, P, T;
    char boundary = 0;
    UINT ID;

    char line[constants::no_of_line_characters];

    Info * info = Info::createInfo();
    info->print_info_message("reading boundary... ");

    for(;;)
    {
        UNV_file.getline(line, constants::no_of_line_characters);

        if (!firstlineout)
            firstlineout = reading::check_if_block_reading_is_ok(line);

        if (this->negative_reading_condition(line)) break;

        sscanf(line, "%d %*d %d %d %d %d %d",
            &ID, &Vx, &Vy, &Vz, &P, &T);

        if (Vx == 1) boundary = boundary | constants::IS_BOUNDARY_VX;
        if (Vy == 1) boundary = boundary | constants::IS_BOUNDARY_VY;
        if (Vz == 1) boundary = boundary | constants::IS_BOUNDARY_VZ;
        if (P == 1)  boundary = boundary | constants::IS_BOUNDARY_P;
        if (T == 1)  boundary = boundary | constants::IS_BOUNDARY_T;

        node_col[ID].set_boundary(boundary);
        boundary = 0;
    };
}

bool UNV_Reader::read_vector_physical_quantity
(Collection<Post_Node> & node_col, string quantity, string path_and_fileName)
{
    ifstream input_unv;

    if (path_and_fileName.length() > constants::minimum_characters_in_fileName)
        m_sPath_and_FileName = path_and_fileName;

    input_unv.open(m_sPath_and_FileName.c_str());

    if (reading::check_if_file_is_not_open(input_unv, m_sPath_and_FileName))
        return false;

    bool firstlineout = false;

    double Vx, Vy, Vz;
    UINT ID;

    char line[constants::no_of_line_characters];

    reading::go_to_line_that_contains_this_string(quantity, input_unv);

    for (UINT i = 1; i <= 6; i++)
        input_unv.getline(line, constants::no_of_line_characters);

    Info * info = Info::createInfo();
    info->print_info_message("reading " + quantity + "... ");

    for(;;)
    {
        input_unv.getline(line, constants::no_of_line_characters);

        if (!firstlineout)
            firstlineout = reading::check_if_block_reading_is_ok(line);

        if (this->negative_reading_condition(line)) break;

        sscanf(line, "%d", &ID);

        input_unv.getline(line, constants::no_of_line_characters);
        sscanf(line, "%lf %lf %lf",
            &Vx, &Vy, &Vz);

        node_col[ID].vector_physical_quantity.set_coordinate_X(Vx);
        node_col[ID].vector_physical_quantity.set_coordinate_Y(Vy);
        node_col[ID].vector_physical_quantity.set_coordinate_Z(Vz);
    };

    return true;
}

bool UNV_Reader::read_translations
(Collection<Post_Node> & node_col, string path_and_fileName)
{
    ifstream input_unv;

    if (path_and_fileName.length() > constants::minimum_characters_in_fileName)
        m_sPath_and_FileName = path_and_fileName;

    input_unv.open(m_sPath_and_FileName.c_str());

    if (reading::check_if_file_is_not_open(input_unv, m_sPath_and_FileName))
        return false;

    bool firstlineout = false;

    double T[4];
    UINT ID;

    char line[constants::no_of_line_characters];

    reading::go_to_line_that_contains_this_string("NODAL TRANSLATIONS", input_unv);

    for (UINT i = 1; i <= 6; i++)
        input_unv.getline(line, constants::no_of_line_characters);

    Info * info = Info::createInfo();
    info->print_info_message("reading translations of nodes... ");

    for(;;)
    {
        input_unv.getline(line, constants::no_of_line_characters);

        if (!firstlineout)
            firstlineout = reading::check_if_block_reading_is_ok(line);

        if (this->negative_reading_condition(line)) break;

        sscanf(line, "%d", &ID);

        input_unv.getline(line, constants::no_of_line_characters);
        sscanf(line, "%lf %lf %lf",
            &T[1], &T[2], &T[3]);

        for (int i = 1; i <= 3; i++)
        {
            T[i] = node_col[ID].get_coordinate(i) + T[i];
            node_col[ID].set_coordinate(T[i], i);
        }
    };

    return true;
}

bool UNV_Reader::read_scalar_physical_quantity
(Collection<Post_Node> & node_col, string quantity, string path_and_fileName)
{
    ifstream input_unv;

    if (path_and_fileName.length() > constants::minimum_characters_in_fileName)
        m_sPath_and_FileName = path_and_fileName;

    input_unv.open(m_sPath_and_FileName.c_str());

    if (reading::check_if_file_is_not_open(input_unv, m_sPath_and_FileName))
        return false;

    bool firstlineout = false;

    double P;
    UINT ID;

    char line[constants::no_of_line_characters];

    reading::go_to_line_that_contains_this_string(quantity, input_unv);

    for (UINT i = 1; i <= 6; i++)
        input_unv.getline(line, constants::no_of_line_characters);

    Info * info = Info::createInfo();
    info->print_info_message("reading " + quantity + "... ");

    for(;;)
    {
        input_unv.getline(line, constants::no_of_line_characters);

        if (!firstlineout)
            firstlineout = reading::check_if_block_reading_is_ok(line);

        if (this->negative_reading_condition(line)) break;

        sscanf(line, "%d", &ID);

        input_unv.getline(line, constants::no_of_line_characters);
        sscanf(line, "%lf",
            &P);

        node_col[ID].set_scalar_physical_quantity(P);
    };

    return true;
}


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

#include "dFemap_Reader.h"


Femap_Reader::Femap_Reader()
{
    m_sPath_and_FileName = constants::input_directory + "femap.dat";
}

Femap_Reader * Femap_Reader::m_pFemap_ReaderSingleton = 0;
Femap_Reader * Femap_Reader::create_Femap_Reader()
{
    if (m_pFemap_ReaderSingleton == 0)
        m_pFemap_ReaderSingleton = new Femap_Reader();
    return m_pFemap_ReaderSingleton;
}

Femap_Reader::~Femap_Reader()
{
    delete m_pFemap_ReaderSingleton;
    m_pFemap_ReaderSingleton = 0;
}

bool Femap_Reader::negative_reading_condition(char * buffer)
{
    if (buffer[0] == 'C')
        return true;
    if (buffer[0] == 'c')
        return true;
    return false;
}

bool Femap_Reader::read_file
(int nodes_per_element, Collection<Mesh_Node> & node_col, Collection<Geom_Element> & elem_col, string path_and_fileName)
{
    ifstream input_Femap;

    if (path_and_fileName.length() > constants::minimum_characters_in_fileName)
        m_sPath_and_FileName = path_and_fileName;

    input_Femap.open(m_sPath_and_FileName.c_str());

    if (reading::check_if_file_is_not_open(input_Femap, m_sPath_and_FileName))
        return false;

    char line[constants::no_of_line_characters];

    do input_Femap.getline(line, 200);
    while(line[0] !='G');
    this->read_nodes(line, node_col, input_Femap);

    Info * info = Info::createInfo();
    info->print_info_message(utos(node_col.get_size()) + " nodes read!");

    this->read_elements(line, elem_col, input_Femap);

    input_Femap.close();

    return true;
}

bool Femap_Reader::read_file_inherit_loads
(int nodes_per_element, Collection<Mesh_Node> & node_col, Collection<Geom_Element> & elem_col, string path_and_fileName)
{
    ifstream input_Femap;

    if (path_and_fileName.length() > constants::minimum_characters_in_fileName)
        m_sPath_and_FileName = path_and_fileName;

    input_Femap.open(m_sPath_and_FileName.c_str());

    if (reading::check_if_file_is_not_open(input_Femap, m_sPath_and_FileName))
        return false;

    char line[constants::no_of_line_characters];

    do input_Femap.getline(line, 200);
    while(line[0] !='G');
    this->read_nodes(line, node_col, input_Femap);

    Info * info = Info::createInfo();
    info->print_info_message(utos(node_col.get_size()) + " nodes read!");

    this->read_elements(line, elem_col, input_Femap);

    input_Femap.close();

    input_Femap.open(m_sPath_and_FileName.c_str());

    do input_Femap.getline(line, 200);
    while(!((line[0] =='S') && (line[1] =='P')));
    this->read_loads(line, node_col, input_Femap);

    input_Femap.close();

    return true;
}

void Femap_Reader::read_elements
(char * the_line, Collection<Geom_Element> & elem_col, ifstream & Femap_file)
{
    Info * info = Info::createInfo();
    info->print_info_message("reading elements... ");

    UINT node_ID[7], no_of_tetrahedrons = 0, no_of_prisms = 0;

    do
    {
        if (the_line[0] == 'C' && the_line[1] == 'T')
        {
            Geom_Element element(15);
            sscanf(the_line, "%*8s%*d%*1d%8d%8d%8d%8d",
                        &node_ID[1], &node_ID[2], &node_ID[3], &node_ID[4]);

            for (int i = 1; i <= 4; i++)
                element.set_node(node_ID[i], i);

            elem_col.insert(element);
            no_of_tetrahedrons++;
            Femap_file.getline(the_line, 200);
        }
        if (the_line[0] == 'C' && the_line[1] == 'P')
        {
            Geom_Element element(14);
            sscanf(the_line, "%*s%*d%*d%8d%8d%8d%8d%8d%8d",
                        &node_ID[4], &node_ID[5], &node_ID[6], &node_ID[1], &node_ID[2], &node_ID[3]);

            for (int i = 1; i <= 6; i++)
                element.set_node(node_ID[i], i);
            elem_col.insert(element);
            no_of_prisms++;
            Femap_file.getline(the_line, 200);
        }
    }while(the_line[0] !='E');

    info->print_info_message(utos(no_of_tetrahedrons) + " tetrahedrons read!");
    info->print_info_message(utos(no_of_prisms) + " prisms read!");
}

void Femap_Reader::read_nodes
(char * the_line, Collection<Mesh_Node> & node_col, ifstream & Femap_file)
{
    Mesh_Node node;
    double d_X, d_Y, d_Z;
    UINT ID;

    Info * info = Info::createInfo();
    info->print_info_message("reading nodes... ");

    {
        do
        {
// old femap format reading nodes....
// sscanf(the_line, "%*4s%d%*d%lf%lf%lf",
//      &ID, &d_X, &d_Y, &d_Z);


// nisam siguran da li ovde femap ima zatup da pishe E-4 kao -4
// ako ima treba i to uvrstiti u ovaj presqljivach

            char coordX[9], coordY[9], coordZ[9];

            coordX[8] = ' ';
            coordY[8] = ' ';
            coordZ[8] = ' ';

            for (UINT i = 0; i < (8); i++)
            {
                coordX[i] = the_line[24 + i];
                coordY[i] = the_line[32 + i];
                coordZ[i] = the_line[40 + i];
            }

            sscanf(the_line, "%*4s%d",&ID);

            d_X = this->coordin8_2_double(coordX);
            d_Y = this->coordin8_2_double(coordY);
            d_Z = this->coordin8_2_double(coordZ);

            node.set_coordinate_X(d_X);
            node.set_coordinate_Y(d_Y);
            node.set_coordinate_Z(d_Z);
            node.set_ID(ID);

            node_col.insert(node);
            Femap_file.getline(the_line, 200);
        }while(the_line[0] !='C');
    }
}

double Femap_Reader::coordin8_2_double
(char coord[])
{
    UINT num = 0;
    double coordin8;

    for (UINT i = 1; i < (7); i++)
    if (coord[i] == '+' || coord[i] == '-')
        num = i;

    if ((num != 0) && (coord[num-1] != ' '))
    {
        for (UINT i = 8; i > num; i--)
            coord[i] = coord[i-1];
        coord[num] = 'e';
    }

    sscanf(coord, "%lf", &coordin8);

    return coordin8;
}

void Femap_Reader::read_loads
(char * the_line, Collection<Mesh_Node> & node_col, ifstream & Femap_file)
{
    Info * info = Info::createInfo();
    info->print_info_message("reading loads... ");

    UINT ID;
    int load;
    bool skip = false;

    for(;;)
    {
        if (!((the_line[0] =='S') && (the_line[1] =='P'))) break;

        sscanf(the_line, "%*s%*d%d%d", &load, &ID);

        if (!((load == 1) || (load == 2) || (load == 4) || (load == 5) || (load == 6))) skip = true;
        if (load == 1) load = 2;
        if (load == 2) load = 2;
        if (load == 4) load = 4;
        if (load == 5) load = 32;
        if (load == 6) load = 64;

        if (!skip)
        {

            node_col[ID].set_boundary((char) load);
            node_col[ID].set_boundary(constants::IS_ON_INLET);
        }
        skip = false;
        Femap_file.getline(the_line, 200);
    }
}

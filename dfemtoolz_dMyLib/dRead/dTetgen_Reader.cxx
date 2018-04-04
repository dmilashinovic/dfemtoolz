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

#include "dTetgen_Reader.h"


Tetgen_Reader::Tetgen_Reader()
{
    m_sPath_and_FileName = constants::input_directory + "Tetgen.dat";
}

Tetgen_Reader * Tetgen_Reader::m_pTetgen_ReaderSingleton = 0;
Tetgen_Reader * Tetgen_Reader::create_Tetgen_Reader()
{
    if (m_pTetgen_ReaderSingleton == 0)
        m_pTetgen_ReaderSingleton = new Tetgen_Reader();
    return m_pTetgen_ReaderSingleton;
}

Tetgen_Reader::~Tetgen_Reader()
{
    delete m_pTetgen_ReaderSingleton;
    m_pTetgen_ReaderSingleton = 0;
}

bool Tetgen_Reader::negative_reading_condition(char * buffer)
{
    if (buffer[0] == '#')
        return true;
    if (!((buffer[0] > 30) && (buffer[0] < 80)))
        return true;
    return false;
}

bool Tetgen_Reader::read_node_file
(Collection<Mesh_Node> & node_col, string path_and_fileName)
{
    ifstream input_node_file;

    if (path_and_fileName.length() > constants::minimum_characters_in_fileName)
        m_sPath_and_FileName = path_and_fileName;

    input_node_file.open(m_sPath_and_FileName.c_str());

    if (reading::check_if_file_is_not_open(input_node_file, m_sPath_and_FileName))
        return false;

    Info * info = Info::createInfo();
    info->print_info_message_no_newline("reading nodes... ");

    Percent * PercentTrackR = Percent::createPercent();
    char line[constants::no_of_line_characters];

    Mesh_Node node;
    double d_X, d_Y, d_Z;
    UINT ID, nodenumbR;

    input_node_file.getline(line, 200);
    sscanf(line, "%d", &nodenumbR);
    PercentTrackR->set_percent_max_value(nodenumbR);

    for (; !input_node_file.eof();)
    {
        input_node_file.getline(line, 200);

        if (negative_reading_condition(line))
            continue;

        sscanf(line, "%d %lf %lf %lf",
                &ID, &d_X, &d_Y, &d_Z);
        node.set_coordinate_X(d_X);
        node.set_coordinate_Y(d_Y);
        node.set_coordinate_Z(d_Z);

        node_col.insert(node);

        PercentTrackR->info_percentage(ID);
    }
    input_node_file.close();
    info->newline();
    info->print_info_message(utos(node_col.get_size()) + " nodes read!");

    return true;
}

bool Tetgen_Reader::read_elem_file
(Collection<Geom_Element> & elem_col, string path_and_fileName)
{
    ifstream input_elem_file;

    if (path_and_fileName.length() > constants::minimum_characters_in_fileName)
        m_sPath_and_FileName = path_and_fileName;

    input_elem_file.open(m_sPath_and_FileName.c_str());

    if (reading::check_if_file_is_not_open(input_elem_file, m_sPath_and_FileName))
        return false;

    Info * info = Info::createInfo();
    info->print_info_message_no_newline("reading elements... ");

    Percent * PercentTrackR = Percent::createPercent();
    char line[constants::no_of_line_characters];

    Geom_Element tetrahedron(15);

    UINT ID, elem_numbR, node_ID[5];
    input_elem_file.getline(line, 200);
    sscanf(line, "%d", &elem_numbR);
    PercentTrackR->set_percent_max_value(elem_numbR);

    for (;!input_elem_file.eof();)
    {
        input_elem_file.getline(line, 200);

        if (negative_reading_condition(line))
            continue;

        sscanf(line, "%d%d%d%d%d",
                &ID, &node_ID[1], &node_ID[2], &node_ID[3], &node_ID[4]);
        for (int i = 1; i <= 4; i++)
            tetrahedron.set_node(node_ID[i], i);

        elem_col.insert(tetrahedron);
        PercentTrackR->info_percentage(ID);
    }
    input_elem_file.close();
    info->newline();
    info->print_info_message(utos(elem_col.get_size()) + " elements read!");

    return true;
}

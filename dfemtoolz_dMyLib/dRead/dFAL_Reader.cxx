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

#include "dFAL_Reader.h"


FAL_Reader::FAL_Reader()
{
    m_sPath_and_FileName = constants::input_directory + "faces.fal";
}

FAL_Reader * FAL_Reader::m_pFAL_ReaderSingleton = 0;
FAL_Reader * FAL_Reader::create_FAL_Reader()
{
    if (m_pFAL_ReaderSingleton == 0)
        m_pFAL_ReaderSingleton = new FAL_Reader();
    return m_pFAL_ReaderSingleton;
}

FAL_Reader::~FAL_Reader()
{
    delete m_pFAL_ReaderSingleton;
    m_pFAL_ReaderSingleton = 0;
}

void FAL_Reader::read_faces
(int nodes_per_face, Collection <Geom_Element> & face_col, ifstream & FAL_file)
{
    char line[constants::no_of_line_characters];

    UINT elemID, nodes[6];
    Geom_Element init_face(nodes_per_face);

    for (;;)
    {
        FAL_file.getline(line, constants::no_of_line_characters);
        if (line[0] == 'S') break;

        sscanf(line, "%d %d %d %d %d", &elemID, &nodes[1], &nodes[2], &nodes[3], &nodes[4]);

        init_face.set_ID(elemID);
        for (int j = 1; j <= nodes_per_face; j++)
            init_face.set_node(nodes[j], j);

        face_col.insert(init_face);
    }
}

bool FAL_Reader::read_file
(Collection <Geom_Element> & init_face_col, string path_and_fileName)
{
    ifstream input_fal;

    if (path_and_fileName.length() > constants::minimum_characters_in_fileName)
        m_sPath_and_FileName = path_and_fileName;

    input_fal.open(m_sPath_and_FileName.c_str());

    if (reading::check_if_file_is_not_open(input_fal, m_sPath_and_FileName))
        return false;

    char line[constants::no_of_line_characters];

    int nodes_per_face_read_from_FAL;

    input_fal.getline(line, constants::no_of_line_characters);
    input_fal.getline(line, constants::no_of_line_characters);
    sscanf(line, "%d", &nodes_per_face_read_from_FAL);

    this->read_faces(nodes_per_face_read_from_FAL, init_face_col, input_fal);

    input_fal.close();
    return true;
}


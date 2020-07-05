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

#include "dSLI_Printer.h"


SLI_Printer::SLI_Printer()
{
    m_uNoOfPrintedElements = 0;
    m_uHowManyNodes2Print = 0;
    m_uNodesWithoutBoundary = 0;
}

SLI_Printer * SLI_Printer::m_pSLI_PrinterSingleton = 0;
SLI_Printer * SLI_Printer::create_SLI_Printer()
{
    if (m_pSLI_PrinterSingleton == 0)
        m_pSLI_PrinterSingleton = new SLI_Printer();
    return m_pSLI_PrinterSingleton;
}

SLI_Printer::~SLI_Printer()
{
    delete m_pSLI_PrinterSingleton;
    m_pSLI_PrinterSingleton = 0;
}

void SLI_Printer::create_sli_file(string path_and_fileName)
{
    Info * info = Info::createInfo();
    info->print_info_message("printing file " + path_and_fileName);

    m_sPath_and_FileName = path_and_fileName;
    ofstream sli;
    sli.open(m_sPath_and_FileName.c_str());
    sli << "C this sli file is printed by dfemtoolz by dmilashinovic@gmail.com" << endl;
    sli.close();
}

void SLI_Printer::set_how_many_nodes_2_print(UINT no_of_nodes2print)
{
    m_uHowManyNodes2Print = no_of_nodes2print;
}

UINT SLI_Printer::get_how_many_nodes_2_print()
{
    return m_uHowManyNodes2Print;
}

UINT SLI_Printer::how_many_nodes_that_have_no_boundary_condition_were_printed()
{
    return m_uNodesWithoutBoundary;
}

void SLI_Printer::reset_nodes_without_boundary()
{
    m_uNodesWithoutBoundary = 0;
}

void SLI_Printer::first_block
(UINT no_of_nodes)
{
    if (m_sPath_and_FileName.length() > constants::minimum_characters_in_fileName)
    {
        char buffR[11];
        fstream file(m_sPath_and_FileName.c_str(), ios::ate | ios::out | ios::in);
        file.seekp(file.tellp());

        file << "C nodeID IS_BOUNDARY_VX IS_BOUNDARY_VY IS_BOUNDARY_VZ IS_ON_INLET IS_ON_OUTLET IS_BOUNDARY_P IS_BOUNDARY_T IS_ON_EDGE X Y X INLET_OR_OUTLET_ID";

        sprintf(buffR, "%10d", no_of_nodes);
        file << endl << buffR << " is number of nodes" << endl;

        file.close();
    }
}

void SLI_Printer::second_block
(UINT no_of_elems, UINT elem_type)
{
    if (m_sPath_and_FileName.length() > constants::minimum_characters_in_fileName)
    {
        char buffR[11];
        fstream file(m_sPath_and_FileName.c_str(), ios::ate | ios::out | ios::in);
        file.seekp(file.tellp());

        file << "C elementID node1 node2.. is_near_surface material_ID";
        sprintf(buffR, "%10d", no_of_elems);
        file  << endl << buffR << " is number of elements" << endl;

        file << " C nodes per element: ";
        file  << endl << elem_type << endl;

        file.close();
    }
}

void SLI_Printer::third_block_part1(fstream & sli_file)
{
    sli_file <<
    "C NUMSTA elementID nodesID.. inlet_outletID" << endl;
}

void SLI_Printer::third_block_part1c(fstream & sli_file)
{
    sli_file <<
    "C NUMSTB ID elementID nodesID.. contact_surfaceID material1_ID material2_ID contact_side(0_or_1) " << endl;
}

void SLI_Printer::third_block_end(fstream & sli_file)
{
    sli_file <<
    "STOP" << endl;
}

void SLI_Printer::third_block()
{
    if (m_sPath_and_FileName.length() > constants::minimum_characters_in_fileName)
    {
        fstream file(m_sPath_and_FileName.c_str(), ios::ate | ios::out | ios::in);
        file.seekp(file.tellp());

        this->third_block_part1(file);
        file << "0 is number of input/output faces" << endl;

        this->third_block_part1c(file);
        file << "0 is number of contact faces" << endl;

        this->third_block_end(file);

        file.close();
    }
}

void SLI_Printer::third_block
(int face_type,
Collection <Geom_Element> & init_face_col,
Collection <Geom_Element> & contact_face_col,
Collection <Geom_Element> & face_col)
{
    if (m_sPath_and_FileName.length() > constants::minimum_characters_in_fileName)
    {
        fstream file(m_sPath_and_FileName.c_str(), ios::ate | ios::out | ios::in);
        file.seekp(file.tellp());

        this->third_block_part1(file);

        char buffR[200];

        UINT no_of_inlet_outlet_faces = 0;

        for (UINT i = 1; i <= face_col.get_size(); i++)
        if (face_col[i].get_flag())
            no_of_inlet_outlet_faces++;

        file << init_face_col.get_size() + no_of_inlet_outlet_faces <<
        " is number of input/output faces" << endl;

        for (UINT i = 1; i <= init_face_col.get_size(); i++)
        {
            if (face_type == constants::TRIANGLE)
                sprintf(buffR, "%10d%10d%10d%10d%10d",
                init_face_col[i].get_ID(),
                init_face_col[i].get_node(1),
                init_face_col[i].get_node(2),
                init_face_col[i].get_node(3),
                init_face_col[i].get_node(4));

            if (face_type == constants::QUAD)
                sprintf(buffR, "%10d%10d%10d%10d%10d%5d",
                init_face_col[i].get_ID(),
                init_face_col[i].get_node(1),
                init_face_col[i].get_node(2),
                init_face_col[i].get_node(3),
                init_face_col[i].get_node(4),
                init_face_col[i].get_node(5));

            file << buffR << endl;
        }

        for (UINT i = 1; i <= face_col.get_size(); i++)
        if (face_col[i].get_flag())
        {
            if (face_type == constants::TRIANGLE)
                sprintf(buffR, "%10d%10d%10d%10d%10d",
                face_col[i].get_ID(),
                face_col[i].get_node(1),
                face_col[i].get_node(2),
                face_col[i].get_node(3),
                face_col[i].get_node(4));

            if (face_type == constants::QUAD)
                sprintf(buffR, "%10d%10d%10d%10d%10d%5d",
                face_col[i].get_ID(),
                face_col[i].get_node(1),
                face_col[i].get_node(2),
                face_col[i].get_node(3),
                face_col[i].get_node(4),
                face_col[i].get_node(5));

            file << buffR << endl;
        }

        this->third_block_part1c(file);

        file << contact_face_col.get_size() <<
        " is number of contact faces" << endl;

        for (UINT i = 1; i <= contact_face_col.get_size(); i++)
        {
            if (face_type == constants::TRIANGLE)
                sprintf(buffR, "%10d%10d%10d%10d%10d%5d%5d%5d",
                contact_face_col[i].get_ID(),
                contact_face_col[i].get_node(1),
                contact_face_col[i].get_node(2),
                contact_face_col[i].get_node(3),
                contact_face_col[i].get_node(4),
                contact_face_col[i].get_node(5),
                contact_face_col[i].get_node(6),
                (int) contact_face_col[i].get_boundary());

            if (face_type == constants::QUAD)
                sprintf(buffR, "%10d%10d%10d%10d%10d%5d%5d%5d%5d",
                contact_face_col[i].get_ID(),
                contact_face_col[i].get_node(1),
                contact_face_col[i].get_node(2),
                contact_face_col[i].get_node(3),
                contact_face_col[i].get_node(4),
                contact_face_col[i].get_node(5),
                contact_face_col[i].get_node(6),
                contact_face_col[i].get_node(7),
                (int) contact_face_col[i].get_boundary());

            file << buffR << endl;
        }

        this->third_block_end(file);

        file.close();
    }
}

void SLI_Printer::third_block
(int face_type,
Collection <Geom_Element> & init_face_col,
Collection <Geom_Element> & contact_face_col)
{
    if (m_sPath_and_FileName.length() > constants::minimum_characters_in_fileName)
    {
        fstream file(m_sPath_and_FileName.c_str(), ios::ate | ios::out | ios::in);
        file.seekp(file.tellp());

        this->third_block_part1(file);

        char buffR[200];

        file << init_face_col.get_size() <<
        " is number of input/output faces" << endl;

        for (UINT i = 1; i <= init_face_col.get_size(); i++)
        {
            if (face_type == constants::TRIANGLE)
                sprintf(buffR, "%10d%10d%10d%10d%10d",
                init_face_col[i].get_ID(),
                init_face_col[i].get_node(1),
                init_face_col[i].get_node(2),
                init_face_col[i].get_node(3),
                init_face_col[i].get_node(4));

            if (face_type == constants::QUAD)
                sprintf(buffR, "%10d%10d%10d%10d%10d%5d",
                init_face_col[i].get_ID(),
                init_face_col[i].get_node(1),
                init_face_col[i].get_node(2),
                init_face_col[i].get_node(3),
                init_face_col[i].get_node(4),
                init_face_col[i].get_node(5));

            file << buffR << endl;
        }

        this->third_block_part1c(file);

        file << contact_face_col.get_size() <<
        " is number of contact faces" << endl;

        for (UINT i = 1; i <= contact_face_col.get_size(); i++)
        {
            if (face_type == constants::TRIANGLE)
                sprintf(buffR, "%10d%10d%10d%10d%10d%10d%5d%5d%5d",
                i,
                contact_face_col[i].get_ID(),
                contact_face_col[i].get_node(1),
                contact_face_col[i].get_node(2),
                contact_face_col[i].get_node(3),
                contact_face_col[i].get_node(4),
                contact_face_col[i].get_node(5),
                contact_face_col[i].get_node(6),
                (int) contact_face_col[i].get_boundary());

            if (face_type == constants::QUAD)
                sprintf(buffR, "%10d%10d%10d%10d%10d%10d%5d%5d%5d%5d",
                i,
                contact_face_col[i].get_ID(),
                contact_face_col[i].get_node(1),
                contact_face_col[i].get_node(2),
                contact_face_col[i].get_node(3),
                contact_face_col[i].get_node(4),
                contact_face_col[i].get_node(5),
                contact_face_col[i].get_node(6),
                contact_face_col[i].get_node(7),
                (int) contact_face_col[i].get_boundary());

            file << buffR << endl;
        }

        this->third_block_end(file);

        file.close();
    }
}

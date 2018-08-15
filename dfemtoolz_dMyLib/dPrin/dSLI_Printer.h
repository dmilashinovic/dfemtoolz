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

/*
 * File:   dSLI_Printer.h
 *
 *
 *
 * Note:   This file was made by Author as simplification of
 *         original dSLI_Printer. SLI is for simple-list.
 *
 *
 */


#ifndef _DSLI_PRINTER_H
#define	_DSLI_PRINTER_H

#include "../dfemtoolz_dMyLib.h"

#include "../dBase/dCollection.h"
#include "../dBase/dConstants.h"

#include "../dGeom/dGeom_Node.h"
#include "../dGeom/dGeom_Element.h"

#include "../dInit/dInit_Node.h"

#include "../dMesh/dMeshing.h"
#include "../dMesh/dMesh_Node.h"

#include "dInfo.h"

#include <fstream>


class SLI_Printer
{
private:
    static SLI_Printer * m_pSLI_PrinterSingleton;

    string m_sPath_and_FileName;
    long m_lCurrentPositionInFile;

    UINT m_uNoOfPrintedElements;
    UINT m_uHowManyNodes2Print;
    UINT m_uNodesWithoutBoundary;

    template <class T>
    void print_node_into_sli(T & node, UINT & nodeID, fstream & sli_file);
    template <class T>
    void print_element
    (Geom_Element & elem, UINT elemID, Collection <T> & node_col, fstream & sli_file);
    template <class T>
    void print_tetra
    (Geom_Element & elem, UINT elemID, Collection <T> & node_col, fstream & sli_file);

    void third_block_part1(fstream & sli_file);
    void third_block_part1c(fstream & sli_file);
    void third_block_end(fstream & sli_file);

protected:
    SLI_Printer();

public:
    void create_sli_file(string path_and_fileName);

    void set_how_many_nodes_2_print(UINT no_of_nodes2print);
    UINT get_how_many_nodes_2_print();

    UINT how_many_nodes_that_have_no_boundary_condition_were_printed();
    void reset_nodes_without_boundary();

    void first_block(UINT no_of_nodes);

    void second_block(UINT no_of_elems, UINT elem_type);

    void third_block();
    void third_block
    (int face_type,
    Collection <Geom_Element> & init_face_col,
    Collection <Geom_Element> & contact_face_col,
    Collection <Geom_Element> & face_col);
    void third_block
    (int face_type,
    Collection <Geom_Element> & init_face_col,
    Collection <Geom_Element> & contact_face_col);

    template <class T>
    void print_nodes_using_node_position_in_collection_as_ID_into_sli(Collection <T> & node_col);
    template <class T>
    void print_nodes_using_nodeIDs_into_sli(Collection <T> & node_col);

    template <class T>
    void print_elems_using_elem_position_in_collection_as_ID_into_sli
    (Collection <Geom_Element> & elem_col, Collection <T> & node_col);
    template <class T>
    void print_elems_using_elemIDs_into_sli
    (Collection <Geom_Element> & elem_col, Collection <T> & node_col);

    template <class T>
    void print_bricks_from_15node_tetrahedrons_and_14node_prisms
    (Collection <Geom_Element> & elem_col, Collection <T> & node_col);
    template <class T>
    void print_4tetras_from_15node_tetrahedrons
    (Collection <Geom_Element> & elem_col, Collection <T> & node_col);
    template <class T>
    void print_bricks_from_27node_bricks_to_pos_file
    (Collection <Geom_Element> & elem_col, Collection <T> & node_col);

    static SLI_Printer * create_SLI_Printer();
    ~SLI_Printer();
};

template <class T>
void SLI_Printer::print_node_into_sli
(T & node, UINT & nodeID, fstream & sli_file)
{
    if (nodeID > 0)
    {
        char buffR[200];

            sprintf(buffR, "%10d%5d%5d%5d%5d%5d%5d%5d%5d  %8.5E %8.5E %8.5E %5d",
            nodeID,
            (node.get_boundary() >> 0) & 1,
            (node.get_boundary() >> 1) & 1,
            (node.get_boundary() >> 2) & 1,
            (node.get_boundary() >> 3) & 1,
            (node.get_boundary() >> 4) & 1,
            (node.get_boundary() >> 5) & 1,
            (node.get_boundary() >> 6) & 1,
            (node.get_boundary() >> 7) & 1,
            node.get_coordinate_X(),
            node.get_coordinate_Y(),
            node.get_coordinate_Z(),
            node.get_ID());

        if (node.get_boundary() == 0)
            m_uNodesWithoutBoundary++;

        sli_file << buffR << endl;
    }
}

template <class T>
void SLI_Printer::print_nodes_using_node_position_in_collection_as_ID_into_sli
(Collection <T> & node_col)
{
    if (m_sPath_and_FileName.length() > constants::minimum_characters_in_fileName)
    {
        Info * info = Info::createInfo();
        info->print_info_message("printing nodes into sli file");

        fstream file(m_sPath_and_FileName.c_str(), ios::ate | ios::out | ios::in);
        file.seekp(file.tellp());

        if (m_uHowManyNodes2Print == 0)
        for (UINT i = 1; i <= node_col.get_size(); i++)
            print_node_into_sli(node_col[i], i, file);

        if (m_uHowManyNodes2Print != 0)
        for (UINT i = 1; i <= m_uHowManyNodes2Print; i++)
            print_node_into_sli(node_col[i], i, file);
    }
}

template <class T>
void SLI_Printer::print_nodes_using_nodeIDs_into_sli
(Collection <T> & node_col)
{
    if (m_sPath_and_FileName.length() > constants::minimum_characters_in_fileName)
    {
        Info * info = Info::createInfo();
        info->print_info_message("printing nodes into sli file");

        fstream file(m_sPath_and_FileName.c_str(), ios::ate | ios::out | ios::in);
        file.seekp(file.tellp());

        UINT ID;
        if (m_uHowManyNodes2Print == 0)
        for (UINT i = 1; i <= node_col.get_size(); i++)
        {
            ID = node_col[i].get_ID();
            print_node_into_sli(node_col[i], ID, file);
        }

        if (m_uHowManyNodes2Print != 0)
        for (UINT i = 1; i <= m_uHowManyNodes2Print; i++)
        {
            ID = node_col[i].get_ID();
            print_node_into_sli(node_col[i], ID, file);
        }
    }
}

template <class T>
void SLI_Printer::print_element
(Geom_Element & elem, UINT elemID, Collection <T> & node_col, fstream & sli_file)
{
    UINT ID;
    if (elemID != 0)
        ID = elemID;
    else
        ID = ++m_uNoOfPrintedElements;

    char buffR[11];
    sprintf(buffR, "%10d", ID);
    sli_file << buffR;

    int surface_element = 0;

    for (int i = 1; i <= elem.how_many_nodes_per_element(); i++)
    {
        sprintf(buffR, "%10d", elem.get_node(i));

        if ((node_col[elem.get_node(i)].get_boundary() & constants::IS_BOUNDARY_V) == constants::IS_BOUNDARY_V)
            surface_element = 1;

        sli_file << buffR;
    }

    sprintf(buffR, "%10d", surface_element);
    sli_file << buffR;

    sprintf(buffR, "%10d", elem.get_material_ID());
    sli_file << buffR << endl;
}

template <class T>
void SLI_Printer::print_tetra
(Geom_Element & elem, UINT elemID, Collection <T> & node_col, fstream & sli_file)
{
    UINT ID;
    if (elemID != 0)
        ID = elemID;
    else
        ID = ++m_uNoOfPrintedElements;

    char buffR[11];
    sprintf(buffR, "%10d", ID);
    sli_file << buffR;

    int surface_element = 0;

    for (int i = 1; i <= 4; i++)
    {
        sprintf(buffR, "%10d", elem.get_node(i));

        if ((node_col[elem.get_node(i)].get_boundary() & constants::IS_BOUNDARY_V) == constants::IS_BOUNDARY_V)
            surface_element = 1;

        sli_file << buffR;
    }

    sprintf(buffR, "%10d", surface_element);
    sli_file << buffR;

    sprintf(buffR, "%10d", elem.get_material_ID());
    sli_file << buffR << endl;
}

template <class T>
void SLI_Printer::print_elems_using_elem_position_in_collection_as_ID_into_sli
(Collection <Geom_Element> & elem_col, Collection <T> & node_col)
{
    if (m_sPath_and_FileName.length() > constants::minimum_characters_in_fileName)
    {
        Info * info = Info::createInfo();
        info->print_info_message("printing elements into sli file");

        fstream file(m_sPath_and_FileName.c_str(), ios::ate | ios::out | ios::in);
        file.seekp(file.tellp());

        for (UINT i = 1; i <= elem_col.get_size(); i++)
            print_element(elem_col[i], i, node_col, file);
    }
}

template <class T>
void SLI_Printer::print_elems_using_elemIDs_into_sli
(Collection <Geom_Element> & elem_col, Collection <T> & node_col)
{
    if (m_sPath_and_FileName.length() > constants::minimum_characters_in_fileName)
    {
        Info * info = Info::createInfo();
        info->print_info_message("printing elements into sli file");

        fstream file(m_sPath_and_FileName.c_str(), ios::ate | ios::out | ios::in);
        file.seekp(file.tellp());

        UINT ID;
        for (UINT i = 1; i <= elem_col.get_size(); i++)
        {
            ID = elem_col[i].get_ID();
            print_element(elem_col[i], ID, node_col, file);
        }
    }
}

template <class T>
void SLI_Printer::print_bricks_from_15node_tetrahedrons_and_14node_prisms
(Collection <Geom_Element> & elem_col, Collection <T> & node_col)
{
    if (m_sPath_and_FileName.length() > constants::minimum_characters_in_fileName)
    {
        Info * info = Info::createInfo();
        info->print_info_message("printing elements into sli file");

        fstream file(m_sPath_and_FileName.c_str(), ios::ate | ios::out | ios::in);
        file.seekp(file.tellp());

        vector <Geom_Element> bricks(4, Geom_Element(8));

        for (UINT i = 1; i <= elem_col.get_size(); i++)
        {
            for (int m = 0; m < 4; m++)
                bricks[m].set_material_ID(elem_col[i].get_material_ID());

            if (elem_col[i].how_many_nodes_per_element() == 15)
            {
                meshing::get_4_bricks_from_15_tetrahedron(bricks, elem_col[i]);

                for (int j = 0; j < 4; j++)
                    print_element(bricks[j], constants::default_value, node_col, file);
            }
            if (elem_col[i].how_many_nodes_per_element() == 14)
            {
                meshing::get_3_bricks_from_14_prism(bricks, elem_col[i]);

                for (int j = 0; j < 3; j++)
                    print_element(bricks[j], constants::default_value, node_col, file);
            }
        }
    }
}

template <class T>
void SLI_Printer::print_4tetras_from_15node_tetrahedrons
(Collection <Geom_Element> & elem_col, Collection <T> & node_col)
{
    if (m_sPath_and_FileName.length() > constants::minimum_characters_in_fileName)
    {
        Info * info = Info::createInfo();
        info->print_info_message("printing elements into sli file");

        fstream file(m_sPath_and_FileName.c_str(), ios::ate | ios::out | ios::in);
        file.seekp(file.tellp());

//        vector <Geom_Element> bricks(4, Geom_Element(8));

        for (UINT i = 1; i <= elem_col.get_size(); i++)
        {
            print_tetra(elem_col[i], constants::default_value, node_col, file);
        }
    }
}

template <class T>
void SLI_Printer::print_bricks_from_27node_bricks_to_pos_file
(Collection <Geom_Element> & elem_col, Collection <T> & node_col)
{
    if (m_sPath_and_FileName.length() > constants::minimum_characters_in_fileName)
    {
        Info * info = Info::createInfo();
        info->print_info_message("printing elements into sli file");

        fstream file(m_sPath_and_FileName.c_str(), ios::ate | ios::out | ios::in);
        file.seekp(file.tellp());

        vector <Geom_Element> bricks(8, Geom_Element(8));

        for (UINT i = 1; i <= elem_col.get_size(); i++)
        {
            meshing::get_8_bricks_from_27_brick(bricks, elem_col[i]);

            for (int j = 0; j < 8; j++)
                print_element(bricks[j], constants::default_value, node_col, file);
        }
    }
}


#endif	/* _DSLI_PRINTER_H */

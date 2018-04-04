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
 * File:   dSLI_Reader.h
 *
 *
 *
 *
 *
 */

#ifndef _DSLI_READER_H
#define	_DSLI_READER_H

#include "../dfemtoolz_dMyLib.h"

#include "../dBase/dCollection.h"
#include "../dBase/dConstants.h"

#include "../dGeom/dGeom_Element.h"

#include "../dMesh/dMesh_Node.h"

#include "../dInit/dInit_Node.h"

#include "../dMisc/dMisc_Functionz.h"

#include "../dPrin/dInfo.h"

#include "dReading.h"


class SLI_Reader
{
private:
    static SLI_Reader * m_pSLI_ReaderSingleton;
    string m_sPath_and_FileName;

    bool negative_reading_condition(char * buffer);

protected:
    SLI_Reader();

    void read_elements
    (char * the_line, int & nodes_per_elem, Collection<Geom_Element> & elem_col, ifstream & SLI_file);

    UINT read_nodes
    (char * the_line, Collection<Mesh_Node> & node_col, ifstream & SLI_file);

    void read_numsta_faces
    (Collection <Geom_Element> & init_face_col, int node_per_elem, ifstream & SLI_file);

    void read_numstb_faces
    (Collection <Geom_Element> & contact_face_col, int node_per_elem, ifstream & SLI_file);

public:

    UINT read_file
    (Collection <Mesh_Node> & node_col,
    Collection<Geom_Element> & elem_col,
    Collection <Geom_Element> & init_face_col,
    Collection <Geom_Element> & contact_face_col,
    string path_and_fileName);

    UINT read_file
    (Collection <Mesh_Node> & node_col, Collection<Geom_Element> & elem_col,
    string path_and_fileName);

    static SLI_Reader * create_SLI_Reader();
    ~SLI_Reader();
};

#endif	/* _DSLI_READER_H */


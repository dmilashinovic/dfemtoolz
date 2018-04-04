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
 * File:   dFemap_Reader.h
 *
 *
 *
 *
 *
 */

#ifndef _DFEMAP_READER_H
#define	_DFEMAP_READER_H

#include "../dfemtoolz_dMyLib.h"

#include "../dBase/dCollection.h"
#include "../dBase/dConstants.h"

#include "../dGeom/dGeom_Element.h"

#include "../dMesh/dMesh_Node.h"

#include "../dMisc/dMisc_Functionz.h"

#include "../dPrin/dInfo.h"

#include "dReading.h"

class Femap_Reader
{
private:
    static Femap_Reader * m_pFemap_ReaderSingleton;
    string m_sPath_and_FileName;

    bool negative_reading_condition(char * buffer);

    double coordin8_2_double(char coord[]);

protected:
    Femap_Reader();

    void read_nodes
    (char * the_line, Collection<Mesh_Node> & node_col, ifstream & Femap_file);

    void read_elements
    (char * the_line, Collection<Geom_Element> & elem_col, ifstream & Femap_file);

    void read_loads
    (char * the_line, Collection<Mesh_Node> & node_col, ifstream & Femap_file);

public:

    bool read_file
    (int nodes_per_element, Collection<Mesh_Node> & node_col, Collection<Geom_Element> & elem_col, string path_and_fileName);

    bool read_file_inherit_loads
    (int nodes_per_element, Collection<Mesh_Node> & node_col, Collection<Geom_Element> & elem_col, string path_and_fileName);

    static Femap_Reader * create_Femap_Reader();
    ~Femap_Reader();
};

#endif	/* _DFEMAP_READER_H */

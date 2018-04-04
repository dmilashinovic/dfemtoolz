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
 * File:   dUNV_Reader.h
 *
 *
 *
 *
 *
 */

#ifndef _DUNV_READER_H
#define	_DUNV_READER_H

#include "../dfemtoolz_dMyLib.h"

#include "../dBase/dError.h"
#include "../dBase/dCollection.h"
#include "../dBase/dConstants.h"

#include "../dGeom/dGeom_Element.h"

#include "../dMesh/dMesh_Node.h"

#include "../dPost/dPost_Node.h"

#include "../dMisc/dMisc_Functionz.h"

#include "../dPrin/dInfo.h"

#include "dReading.h"


class UNV_Reader
{
private:
    static UNV_Reader * m_pUNV_ReaderSingleton;
    string m_sPath_and_FileName;
    bool negative_reading_condition(char * buffer);

protected:
    UNV_Reader();

    void read_nodes
    (Collection<Post_Node> & node_col, ifstream & UNV_file);

    void read_boundary_conditions
    (Collection<Post_Node> & node_col, ifstream & UNV_file);

    void read_elements
    (int & nodes_per_elem, Collection<Geom_Element> & elem_col, ifstream & UNV_file);

public:

    bool read_geometry
    (int nodes_per_element, Collection <Post_Node> & node_col, Collection<Geom_Element> & elem_col, string path_and_fileName);

    bool read_vector_physical_quantity
    (Collection<Post_Node> & node_col, string quantity, string path_and_fileName);

    bool read_translations
    (Collection<Post_Node> & node_col, string path_and_fileName);

    bool read_scalar_physical_quantity
    (Collection<Post_Node> & node_col, string quantity, string path_and_fileName);

    static UNV_Reader * create_UNV_Reader();
    ~UNV_Reader();
};


#endif	/* _DUNV_READER_H */

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
 * File:   dSTL_Reader.h
 *
 *
 *
 *
 *
 */

#ifndef _DSTL_READER_H
#define	_DSTL_READER_H

#include "../dfemtoolz_dMyLib.h"

#include "../dBase/dError.h"
#include "../dBase/dCollection.h"
#include "../dBase/dConstants.h"

#include "../dGeom/dGeom_Node.h"
#include "../dGeom/dGeom_Element.h"
#include "../dGeom/dGeom_Functions.h"

#include "../dMisc/dSTL_Triangle.h"

#include "dReading.h"

class STL_Reader
{
private:
    static STL_Reader * m_pSTL_ReaderSingleton;
    string m_sPath_and_FileName;
    UINT m_uTriangles_read;

    bool negative_reading_condition(char * buffer);
    void put_triangle_edges_to_collection
    (Collection<Geom_Node> & node_c, Collection<Geom_Element> & edge_c);
    void calcul8_boundary_edges
    (Collection<Geom_Node> & node_c, Collection<Geom_Element> & edge_c);

protected:
    STL_Reader();

public:

    bool read_STL_edges
    (Collection<Geom_Node> & node_col, Collection<Geom_Element> & edge_col, string path_and_fileName);

    bool read_STL_triangles
    (Collection<STL_Triangle> & triangle_col, string path_and_fileName);

    UINT how_many_triangles_read();

    static STL_Reader * create_STL_Reader();
    ~STL_Reader();

    static void del_reader();
};

#endif	/* _DSTL_READER_H */

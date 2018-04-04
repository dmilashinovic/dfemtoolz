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
 * File:   dTetgen_Reader.h
 *
 *
 *
 *
 *
 */


#ifndef _DTETGEN_READER_H
#define	_DTETGEN_READER_H

#include "../dfemtoolz_dMyLib.h"

#include "../dBase/dError.h"
#include "../dBase/dCollection.h"
#include "../dBase/dConstants.h"

#include "../dGeom/dGeom_Element.h"

#include "../dMesh/dMesh_Node.h"

#include "../dMisc/dMisc_Functionz.h"
#include "../dMisc/dPercent.h"

#include "../dPrin/dInfo.h"

#include "dReading.h"


class Tetgen_Reader
{
private:
    static Tetgen_Reader * m_pTetgen_ReaderSingleton;
    string m_sPath_and_FileName;

    bool negative_reading_condition(char * buffer);

protected:
    Tetgen_Reader();

public:

    bool read_node_file
    (Collection<Mesh_Node> & node_col, string path_and_fileName);

    bool read_elem_file
    (Collection<Geom_Element> & elem_col, string path_and_fileName);

    static Tetgen_Reader * create_Tetgen_Reader();
    ~Tetgen_Reader();
};


#endif	/* _DTETGEN_READER_H */

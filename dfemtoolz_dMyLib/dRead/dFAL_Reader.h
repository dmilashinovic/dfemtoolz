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
 * File:   dFAL_Reader.h
 *
 *
 *
 *
 *
 */

#ifndef _DFAL_READER_H
#define	_DFAL_READER_H

#include "../dfemtoolz_dMyLib.h"

#include "../dBase/dCollection.h"
#include "../dBase/dConstants.h"

#include "../dGeom/dGeom_Element.h"

#include "../dMisc/dMisc_Functionz.h"

#include "../dPrin/dInfo.h"

#include "dReading.h"


class FAL_Reader
{
private:
    static FAL_Reader * m_pFAL_ReaderSingleton;
    string m_sPath_and_FileName;

    UINT m_uNoOfInletFaces;

    bool negative_reading_condition(char * buffer);

protected:
    FAL_Reader();

    void read_faces
    (int nodes_per_face, Collection <Geom_Element> & face_col, ifstream & FAL_file);

public:

    bool read_file
    (Collection <Geom_Element> & init_face_col, string path_and_fileName);

    static FAL_Reader * create_FAL_Reader();
    ~FAL_Reader();
};

#endif	/* _DFAL_READER_H */

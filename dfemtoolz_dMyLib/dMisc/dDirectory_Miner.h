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
 * File:   dDirectory_Miner.h
 *
 *
 *
 *
 *
 */


#ifndef _DDIRECTORY_MINER_H
#define	_DDIRECTORY_MINER_H

#include <sys/types.h>
#include <dirent.h>
#include <vector>

#include "../dfemtoolz_dMyLib.h"

#include "../dBase/dCollection.h"
#include "../dBase/dConstants.h"


class  Directory_Miner
{
private:
    static Directory_Miner * m_pDirectory_MinerSingleton;
    Collection <string> m_collFileNames;
    string m_sLocation;
    void mine_directory();

protected:
    Directory_Miner(string & Location);

public:
    UINT how_many_fileZ();
    void sort_the_namez();

    string give_me_the_file_name(UINT i);
    void set_the_new_location(string Location);
    void forget_the_nameZ();

    static Directory_Miner * create_Directory_Miner(string Location);
    ~Directory_Miner();
};

#endif	/* _DDIRECTORY_MINER_H */


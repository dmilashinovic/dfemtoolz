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

#include "dDirectory_Miner.h"

Directory_Miner::Directory_Miner(string & Location)
{
    m_sLocation = Location;
    mine_directory();
}

Directory_Miner * Directory_Miner::m_pDirectory_MinerSingleton = 0;
Directory_Miner * Directory_Miner::create_Directory_Miner(string Location)
{
    if (m_pDirectory_MinerSingleton == 0)
	m_pDirectory_MinerSingleton = new Directory_Miner(Location);
    return m_pDirectory_MinerSingleton;
}

UINT Directory_Miner::how_many_fileZ()
{
    return m_collFileNames.get_size();
}

string Directory_Miner::give_me_the_file_name(UINT i)
{
    return m_collFileNames[i];
}

void Directory_Miner::forget_the_nameZ()
{
    m_collFileNames.clear_collection();
}

void Directory_Miner::set_the_new_location(string Location)
{
    m_sLocation = Location;
    mine_directory();
}

void Directory_Miner::sort_the_namez()
{
    m_collFileNames.sort_collection();
}

void Directory_Miner::mine_directory()
{
    DIR * pdir = opendir(m_sLocation.c_str());
    struct dirent* pent;
    string FileName;
    if(pdir)
    {
        while((pent = readdir(pdir)))
        {
            FileName = pent->d_name;
            if (FileName.size() > constants::minimum_characters_in_fileName)
                m_collFileNames.insert(pent->d_name);
        }
        closedir(pdir);
    }
}

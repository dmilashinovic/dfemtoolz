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

#include "dInfo.h"

bool Info::m_bInfoHeader = false;
Info::Info()
{}

Info * Info::m_pInfoSingleton = 0;
Info * Info::createInfo()
{
    if (m_pInfoSingleton == 0)
        m_pInfoSingleton = new Info;
    return m_pInfoSingleton;
}

Info::~Info()
{
    delete m_pInfoSingleton;
    m_pInfoSingleton = 0;
}

void Info::print_info_message(string message)
{
    cout << "     " << message << endl;
}

void Info::print_info_message_no_newline(string message)
{
    cout << "     " << message;
}

void Info::newline()
{
    cout << endl;
}

void Info::print_software_header(string header, UINT year, UINT build)
{
    if (!Info::m_bInfoHeader)
    {
        cout << endl << endl << endl <<
        "       ..:: " << header << " ::.." << endl << "            ";

        if (header.length() >  9)
        for (UINT i = 0; i <= header.length() - 10; i++)
            cout << ' ';

        cout << "                 v" << build << endl << endl
        << "    by danko milasinovic (c) " << year << endl
        << "    * dmilashinovic@gmail.com "
        << endl << endl
        << "  this software is under GNU GPLv3 licence" << endl << endl;

        m_bInfoHeader = true;
    }
}

void Info::print_software_footer()
{
    cout << endl <<
    "   operation completed, farewell" << endl <<
    endl;
}

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

#include "dPercent.h"

#include "dPercent.h"

bool Percent::m_bPercent = false;
Percent::Percent()
:m_uPercentMaxValue(0)
{}

Percent * Percent::m_pPercentSingleton = 0;
Percent * Percent::createPercent()
{
    if (m_pPercentSingleton == 0)
        m_pPercentSingleton = new Percent;
    return m_pPercentSingleton;
}

Percent::~Percent()
{
    delete m_pPercentSingleton;
    m_pPercentSingleton = 0;
}

void Percent::info_percentage(UINT & counter)
{
	UINT OnePercent = (UINT) m_uPercentMaxValue / 100, percent;
    if (OnePercent == 0) percent = 100;
    else percent = (UINT) (counter/OnePercent);

    if ((percent > 100) || (percent < 0)) percent = 100;
    cout << "\r" <<  percent << '%';
}

void Percent::set_percent_max_value(UINT percent_max_value)
{
    m_uPercentMaxValue = percent_max_value;
}

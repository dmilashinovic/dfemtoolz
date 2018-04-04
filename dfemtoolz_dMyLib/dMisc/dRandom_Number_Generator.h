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
 * File:   dRandom_Number_Generator.h
 *
 *
 *
 *
 *
 */

#ifndef _DRANDOM_NUMBER_GENERATOR_H
#define	_DRANDOM_NUMBER_GENERATOR_H

#include "../dfemtoolz_dMyLib.h"

#include "../dBase/dConstants.h"

#include <time.h>

#include <sstream>
#include <cstdlib>


class Random_Number_Generator
{
private:
    static Random_Number_Generator * m_pRandom_Number_GeneratorSingleton;

protected:
    Random_Number_Generator();

public:

    double random_double_number(double & minimum, double & maximum);

    static Random_Number_Generator * create_Random_Number_Generator();
    ~Random_Number_Generator();
};





#endif	/* _DRANDOM_NUMBER_GENERATOR_H */




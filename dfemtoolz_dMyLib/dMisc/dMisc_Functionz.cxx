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

#include "dMisc_Functionz.h"

void press_any_key_2_continue()
{
    cout << endl <<
    " press any key 2 continue" << endl;
    char input;
    cin.get(input);
}

string utos(UINT number_2_string)
{
    stringstream sstmp;
    sstmp << number_2_string;
    return sstmp.str();
}

string itos(int number_2_string)
{
    stringstream sstmp;
    sstmp << number_2_string;
    return sstmp.str();
}

string dtos(double number_2_string)
{
    stringstream sstmp;
    sstmp << number_2_string;
    return sstmp.str();
}



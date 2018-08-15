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
 * File:   dConstants.h
 *
 *
 *
 *
 *
 */

#ifndef _DCONSTANTS_H
#define	_DCONSTANTS_H

#include "../dfemtoolz_dMyLib.h"

namespace constants
{
    const string input_directory = "input/";
    const string output_directory = "output/";

    const double PI = 3.14159265;
    const double benchmar_function_cut_tol = 0.0001;

    const double same_node_tol = 0.001;
    const double zero_tol = 0.0000000000000000001;

    enum placeHolders{default_value = 0};
    enum type_of_STL_problems
    {one_hole_problem, multi_holeZ_problem, auto_multi_holeZ_problem, stl_noise_remove};
    enum elemtypes
    {PRISM    =  16,
     BRICK    =  8,
     TETRA    =  4,
     QUAD          =  2,
     TRIANGLE      =  1};
    enum dat_or_sli_filetype{dat = 1, sli = 2, stl = 3, fal = 4};

    /// boundary_conditions
    const char
    IS_BOUNDARY_VX =   1, // 1 bit
    IS_BOUNDARY_VY =   2, // 2 bit
    IS_BOUNDARY_VZ =   4, // 3 bit
    IS_BOUNDARY_V  =   7,
    IS_ON_INLET    =   8, // 4 bit
    IS_ON_OUTLET   =  16, // 5 bit
    IS_BOUNDARY_P  =  32, // 6 bit
    IS_BOUNDARY_T  =  64, // 7 bit
    IS_ON_EDGE     = 128; // 8 bit


    /// POS elemtypes
    const string POS_BRICK   =  "SH";
    const string POS_QUAD    =  "SQ";
    const string POS_TETRA   =  "SS";

    const string UNV_velocity_string =       "NODAL VELOCITIES";
    const string UNV_shear_stress_string =   "SHEAR STRESSES";
    const string UNV_temperature_string =    "NODAL TEMPERATURE";
    const string UNV_pressure_string =       "PRESSURES AT NODES";
    const string UNV_translation_string =    "NODAL TRANSLATIONS";
    const string UNV_forces_string =         "WALL FORCES AT NODES";
    const string UNV_osi =                   "OSCILLATORY SHEAR INDES";
    const string UNV_res_time =              "RESIDENCE TIME";

    const int stl_footer_size = 26;
    const double stl_multiHole_tol = 14.0;

    const int no_of_DAT_usable_lines_before_nodes_block = 6;
    const int no_of_SLI_usable_lines_before_nodes_block = 1;
    const int no_of_DAT_usable_lines_before_nodes_per_element_after_nodes_block = 1;
    const int no_of_SLI_usable_lines_before_nodes_per_element_after_nodes_block = 2;
    const int no_of_DAT_usable_lines_before_NUMZAD_nodes = 2;
    const int no_of_SLI_usable_lines_before_NUMZAD_nodes = 0;
    const int no_of_SLI_usable_lines_before_STOP_CARD = 0;
    const int no_of_DAT_usable_lines_before_STOP_CARD = 3;

    const int no_of_line_characters = 200;

    const UINT minimum_characters_in_fileName = 3;
}

#endif	/* _DCONSTANTS_H */



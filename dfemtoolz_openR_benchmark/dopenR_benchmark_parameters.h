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
 * File:   dopenR_benchmark_parameters.h
 *
 *
 *
 *
 *
 */

#ifndef _OPENR_PARAMETERS_H
#define	_OPENR_PARAMETERS_H

#include "../dfemtoolz_dMyLib/dfemtoolz_dMyLib.h"

#include "../dfemtoolz_dMyLib/dBase/dConstants.h"

#include "../dfemtoolz_dMyLib/dPrin/dInfo.h"

#include "../dfemtoolz_dMyLib/dRead/dReading.h"


class openR_benchmark_Parameters
{
private:
    static openR_benchmark_Parameters * m_popenR_benchmark_ParametersSingleton;
    string m_sPath_and_FileName;

protected:
    openR_benchmark_Parameters();

public:

    bool   print_pos_nodes;
    bool   print_pos_elements;
    bool   print_pos_init_velocity;
    bool   print_pos_inlet_or_outlet;
    bool   print_pos_surface;
    bool   plane_defined_with_nodes;
    UINT   plane_nodeA;
    UINT   plane_nodeB;
    UINT   plane_nodeC;
    bool   Xplane_of_sym_for_outlet_or_inlet;
    double Xsym_defined_at;
    bool   Yplane_of_sym_for_outlet_or_inlet;
    double Ysym_defined_at;
    bool   Zplane_of_sym_for_outlet_or_inlet;
    double Zsym_defined_at;
    bool   defined_plane;
    double plane_defined_at;
    int    plane_coord_ID;
    int    numzad_time_function;
    int    numst_time_function;
    bool   velocity_invert0R;
    bool   parabolic_input;
    bool   use_all_inlet_or_outlet_faces;
    bool   use_all_inlet_or_outlet_nodes;
    bool   print_numzad_nodes_and_inlet_or_outlet_facets;
    bool   print_prescribed_pressure;
    char   clear_and_set_this_boundary_to_nodes;
    char   add_this_boundary_to_all_nodes_outlet_or_inlet_faces;
    double near_node_tol;
    double same_node_tol;
    double scale_facX;
    double scale_facY;
    double scale_facZ;
    bool   check_distance;
    double TOLdistance;
    UINT   refNode;
    int    dat_or_sli_input;
    int    stl_or_fal_input;
    int    materialID_of_outlet_or_inlet;


    bool read_file();


    static openR_benchmark_Parameters * create_openR_benchmark_Parameters();
    ~openR_benchmark_Parameters();
};



#endif	/* _OPENR_PARAMETERS_H */



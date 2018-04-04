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

#include "dPrinting.h"

namespace printing
{

    /// STL

    void print_triangle_into_stl
    (Geom_Node & node1, Geom_Node & node2, Geom_Node & node3, fstream & stl_file)
    {
        Geom_Node normal_vector = get_normal_vector_coordinates(node1, node2, node3);

        char buffR[constants::no_of_line_characters];
        sprintf(buffR, "facet normal %12.7E %12.7E %12.7E",
        normal_vector.get_coordinate_X(),
        normal_vector.get_coordinate_Y(),
        normal_vector.get_coordinate_Z());
        stl_file << buffR << endl;

        stl_file << "  outer loop" << endl;

        sprintf(buffR, "    vertex   %12.7E %12.7E %12.7E",
        node1.get_coordinate_X(),
        node1.get_coordinate_Y(),
        node1.get_coordinate_Z());
        stl_file << buffR << endl;

        sprintf(buffR, "    vertex   %12.7E %12.7E %12.7E",
        node2.get_coordinate_X(),
        node2.get_coordinate_Y(),
        node2.get_coordinate_Z());
        stl_file << buffR << endl;

        sprintf(buffR, "    vertex   %12.7E %12.7E %12.7E",
        node3.get_coordinate_X(),
        node3.get_coordinate_Y(),
        node3.get_coordinate_Z());
        stl_file << buffR << endl;

        stl_file << "  endloop" << endl << "endfacet" << endl;
    }

    void print_triangle_into_stl
    (Geom_Node & node1, Geom_Node & node2, Geom_Node & node3, ofstream & stl_file)
    {
        Geom_Node normal_vector = get_normal_vector_coordinates(node1, node2, node3);

        char buffR[constants::no_of_line_characters];
        sprintf(buffR, "facet normal %12.7E %12.7E %12.7E",
        normal_vector.get_coordinate_X(),
        normal_vector.get_coordinate_Y(),
        normal_vector.get_coordinate_Z());
        stl_file << buffR << endl;

        stl_file << "  outer loop" << endl;

        sprintf(buffR, "    vertex   %12.7E %12.7E %12.7E",
        node1.get_coordinate_X(),
        node1.get_coordinate_Y(),
        node1.get_coordinate_Z());
        stl_file << buffR << endl;

        sprintf(buffR, "    vertex   %12.7E %12.7E %12.7E",
        node2.get_coordinate_X(),
        node2.get_coordinate_Y(),
        node2.get_coordinate_Z());
        stl_file << buffR << endl;

        sprintf(buffR, "    vertex   %12.7E %12.7E %12.7E",
        node3.get_coordinate_X(),
        node3.get_coordinate_Y(),
        node3.get_coordinate_Z());
        stl_file << buffR << endl;

        stl_file << "  endloop" << endl << "endfacet" << endl;
    }

}

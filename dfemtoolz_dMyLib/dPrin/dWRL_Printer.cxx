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


#include "dWRL_Printer.h"


WRL_Printer::WRL_Printer()
{
}

WRL_Printer * WRL_Printer::m_pWRL_PrinterSingleton = 0;
WRL_Printer * WRL_Printer::create_WRL_Printer()
{
    if (m_pWRL_PrinterSingleton == 0)
        m_pWRL_PrinterSingleton = new WRL_Printer();
    return m_pWRL_PrinterSingleton;
}

WRL_Printer::~WRL_Printer()
{}

void WRL_Printer::print_stl_triangle_nodes_to_wrl_file
(STL_Triangle & triangle, ofstream & wrl_file)
{
    wrl_file <<
    triangle.node1.get_coordinate_X() << "  " <<
    triangle.node1.get_coordinate_Y() << "  " <<
    triangle.node1.get_coordinate_Z() << ", " << endl <<
    triangle.node2.get_coordinate_X() << "  " <<
    triangle.node2.get_coordinate_Y() << "  " <<
    triangle.node2.get_coordinate_Z() << ", " << endl <<
    triangle.node3.get_coordinate_X() << "  " <<
    triangle.node3.get_coordinate_Y() << "  " <<
    triangle.node3.get_coordinate_Z() << ", " << endl;
}

void WRL_Printer::print_stl_triangles_to_wrl_file
(Collection <STL_Triangle> & triangle_col, string path_and_fileName)
{
    Info * info = Info::createInfo();
    info->print_info_message("printing file " + path_and_fileName);

    ofstream output_file;
    output_file.open(path_and_fileName.c_str());
    output_file << "#VRML V1.0 ascii\n#created by dfemtoolz\n#dmilashinovic@kg.ac.rs\n#dmilashinovic@gmail.com" << endl;

    output_file << "Coordinate3 {\npoint [\n" << endl;

    for (UINT i = 1; i <= triangle_col.get_size(); i++)
        this->print_stl_triangle_nodes_to_wrl_file(triangle_col[i], output_file);

    output_file << "  ] \n}" << endl;

    output_file << "DEF Surface1 IndexedFaceSet {\ncoordIndex [" << endl;

    for (UINT i = 1; i <= triangle_col.get_size(); i++)
        output_file << 3*i - 3 << ", " << 3*i - 2 << ", " << 3*i - 1 << ",-1," << endl;

    output_file << "  ] \n}" << endl;

    output_file.close();
}

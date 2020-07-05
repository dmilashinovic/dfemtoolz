
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

#include "dremeshF.h"

int dremesh_get_elems(Collection <Mesh_Node> & nodes_collection, Collection <Geom_Element>  & elements_collection, string Tetgen_node_fileName, string Tetgen_elem_fileName, string Femap_dat_fileName)
{
    dremesh_Parameters * params = dremesh_Parameters::create_dremesh_Parameters();
    params->read_file();

    dremesh_get_elemsF(
    params->submodule,
    nodes_collection,
    elements_collection,
    Tetgen_node_fileName,
    Tetgen_elem_fileName,
    Femap_dat_fileName);

    return 0;
}

int dremesh_get_elemsF
(int mesh_element_type,
Collection <Mesh_Node> & nodes_collection,
Collection <Geom_Element>  & elements_collection,
string Tetgen_node_fileName,
string Tetgen_elem_fileName,
string Femap_dat_fileName)
{
    Info * info = Info::createInfo();
    info->print_software_header("remesh", 2017, 180313);
    info->print_info_message("");

//    dremesh_Parameters * params = dremesh_Parameters::create_dremesh_Parameters();
//    params->read_file();


/// napomena vazna:
/// dremesh4TetgenF_get_bricks funkcija ne stavlja surface element marker
/// (element blizu povrshine) ako se ne ukljuchi da proverava konveksnost
/// treba da se pogleda malo, nije big-deal - ali sada nemam kad'

    int submodule;

    if (mesh_element_type == constants::TETRA)
        submodule = 1;
    if (mesh_element_type == constants::BRICK)
        submodule = 8;

    switch (submodule)
    {
        case 1:
        {
            dremesh4Tetgen_tetraF_get_tetras(nodes_collection, elements_collection, 1, Tetgen_node_fileName, Tetgen_elem_fileName);
            break;
        }
        /// FemapF is currently unused - but it works :)
        case 4:
        {
            dremesh4FemapF_get_bricks(nodes_collection, elements_collection, 0, 1 /*check_bricks*/, 0, 1, Femap_dat_fileName);
            break;
        }
        default:
        {
            dremesh4TetgenF_get_bricks(nodes_collection, elements_collection, 1 /* check_bricks */ , 0, 1, Tetgen_node_fileName, Tetgen_elem_fileName);
        }
    }

    return 0;
}


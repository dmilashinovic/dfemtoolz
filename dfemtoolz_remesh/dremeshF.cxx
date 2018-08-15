
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
    Info * info = Info::createInfo();
    info->print_software_header("remesh", 2017, 180313);
    info->print_info_message("");

    dremesh_Parameters * params = dremesh_Parameters::create_dremesh_Parameters();
    params->read_file();

    switch (params->submodule)
    {
        case 1:
        {
            dremesh4Tetgen_tetraF_get_tetras(nodes_collection, elements_collection, params->material_ID, Tetgen_node_fileName, Tetgen_elem_fileName);
            break;
        }
        case 4:
        {
            dremesh4FemapF_get_bricks(nodes_collection, elements_collection, params->inheritBoundary, params->chekAllBrickElements, params->calculateVolumeOfTheModel, params->material_ID, Femap_dat_fileName);
            break;
        }
        default:
        {
            dremesh4TetgenF_get_bricks(nodes_collection, elements_collection, params->chekAllBrickElements, params->calculateVolumeOfTheModel, params->material_ID, Tetgen_node_fileName, Tetgen_elem_fileName);
        }
    }

    return 0;
}


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

#include "dremesh.h"

int main()
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
            dremesh4Tetgen_tetra(params->print_pos_nodes, params->print_pos_elements, params->material_ID);
            break;
        }
        case 4:
        {
            dremesh4Femap(params->inheritBoundary, params->print_pos_nodes, params->print_pos_elements, params->chekAllBrickElements, params->calculateVolumeOfTheModel, params->material_ID);
            break;
        }
        default:
        {
            dremesh4Tetgen(params->print_pos_nodes, params->print_pos_elements, params->chekAllBrickElements, params->calculateVolumeOfTheModel, params->material_ID);
        }
    }

    info->print_software_footer();
    press_any_key_2_continue();
    return 0;
}


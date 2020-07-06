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
 * File:   dVTK_Printer.h
 *
 *
 *
 *
 *
 */

#ifndef _DVTK_PRINTER_H
#define	_DVTK_PRINTER_H

#include "../dfemtoolz_dMyLib.h"

#include "../dBase/dCollection.h"
#include "../dBase/dSuperCollection.h"
#include "../dBase/dConstants.h"

#include "../dGeom/dGeom_Node.h"
#include "../dGeom/dGeom_Element.h"

#include "../dMesh/dMesh_Node.h"
#include "../dMesh/dMeshing.h"

#include "../dMisc/dMisc_Functionz.h"

#include "../dPost/dPost_Node.h"

#include "../dInit/dInit_Node.h"

#include <fstream>
#include <vector>

#include "dInfo.h"


class VTK_Printer
{
private:
    static VTK_Printer * m_pVTK_PrinterSingleton;

    UINT m_uHowManyNodes2Print;
    int  m_iElementType;
    UINT m_uNodesWithoutBoundary;

protected:
    VTK_Printer();

public:

    void print_brick_elems_scalar_physical_quantity_to_vtk_file
    (Collection <Geom_Element> & elem_col, Collection <Post_Node> & node_col, string path_and_fileName, string text_scalar_physical_quantity);

    void print_bricks_from_15node_tetrahedrons_and_14node_prisms_to_vtk_file
    (Collection <Geom_Element> & elem_col, Collection <Mesh_Node> & node_col, string path_and_fileName);

    void print_brick_elems_material_2_vtk_file
    (Collection <Geom_Element> & elem_col, Collection <Mesh_Node> & node_col, string path_and_fileName);

    void print_tetrahedron_elems_material_2_vtk_file
    (Collection <Geom_Element> & elem_col, Collection <Mesh_Node> & node_col, string path_and_fileName);

    void print_brick_elems_nodes_boundary_2_vtk_file
    (Collection <Geom_Element> & elem_col, Collection <Mesh_Node> & node_col, string path_and_fileName);

    void print_brick_elems_vector_physical_quantity_to_vtk_file
    (Collection <Geom_Element> & elem_col, Collection <Post_Node> & node_col, string path_and_fileName, string text_scalar_physical_quantity, string text_vector_physical_quantity);

    void print_triangles_to_vtk_file
    (Collection <Geom_Element> & triangles, Collection <Mesh_Node> & node_col, string path_and_fileName);

    void print_triangles_to_vtk_file
    (bool only_with_flag, Collection <Geom_Element> & triangles, Collection <Mesh_Node> & node_col, string path_and_fileName);

    void print_triangles_to_vtk_file
    (UINT color_ID, Collection <Geom_Element> & triangles, Collection <Mesh_Node> & node_col, string path_and_fileName);

    void print_quads_to_vtk_file
    (Collection <Geom_Element> & quads, Collection <Mesh_Node> & node_col, string path_and_fileName);

    void print_quads_to_vtk_file
    (bool only_with_flag, Collection <Geom_Element> & quads, Collection <Mesh_Node> & node_col, string path_and_fileName);

    void print_quads_to_vtk_file
    (UINT startID, UINT endID, bool only_with_flag, Collection <Geom_Element> & quads, Collection <Mesh_Node> & node_col, string path_and_fileName);

    void print_quads_to_vtk_file
    (UINT color_ID, Collection <Geom_Element> & quads, Collection <Mesh_Node> & node_col, string path_and_fileName);

    void print_quads_as_lines_to_vtk_file
    (Collection <Geom_Element> & quads, Collection <Mesh_Node> & node_col, string path_and_fileName);

    void print_quads_as_lines_to_vtk_file
    (UINT color_ID, Collection <Geom_Element> & quads, Collection <Mesh_Node> & node_col, string path_and_fileName);

    void print_triangles_as_lines_to_vtk_file
    (Collection <Geom_Element> & triangles, Collection <Mesh_Node> & node_col, string path_and_fileName);

    void print_triangles_to_vtk_file
    (UINT startID, UINT endID, bool only_with_flag, Collection <Geom_Element> & triangles, Collection <Mesh_Node> & node_col, string path_and_fileName);

    void print_triangles_as_lines_to_vtk_file
    (UINT color_ID, Collection <Geom_Element> & triangles, Collection <Mesh_Node> & node_col, string path_and_fileName);

    void print_lines_to_vtk_file
    (SuperCollection <Geom_Node> & lines, string path_and_fileName);


    static VTK_Printer * create_VTK_Printer();
    ~VTK_Printer();
};

#endif	/* _DVTK_PRINTER_H */

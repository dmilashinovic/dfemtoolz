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

#include "dMesh_Neighbours.h"


namespace neighbours
{
    UINT get_nodez_neighbour(Mesh_Node & node1, Mesh_Node & node2)
    {
        for (UINT i = 1; i <= node1.how_many_neighbours(); i++)
        for (UINT j = 1; j <= node2.how_many_neighbours(); j++)
        if (node1.get_neighbour_node(i) == node2.get_neighbour_node(j))
            return node1.get_neighbour_node(i);
        return 0;
    }

    UINT get_nodez_neighbour(Mesh_Node & node1, Mesh_Node & node2, Mesh_Node & node3)
    {
        for (UINT i = 1; i <= node1.how_many_neighbours(); i++)
        for (UINT j = 1; j <= node2.how_many_neighbours(); j++)
        for (UINT k = 1; k <= node3.how_many_neighbours(); k++)
        if (node1.get_neighbour_node(i) == node2.get_neighbour_node(j))
        if (node1.get_neighbour_node(i) == node3.get_neighbour_node(k))
            return node1.get_neighbour_node(i);

        return 0;
    }

    UINT get_nodez_neighbour(Mesh_Node & node1, Mesh_Node & node2, Mesh_Node & node3, Mesh_Node & node4)
    {
        for (UINT i = 1; i <= node1.how_many_neighbours(); i++)
        for (UINT j = 1; j <= node2.how_many_neighbours(); j++)
        for (UINT k = 1; k <= node3.how_many_neighbours(); k++)
        for (UINT l = 1; l <= node4.how_many_neighbours(); l++)
        if (node1.get_neighbour_node(i) == node2.get_neighbour_node(j))
        if (node1.get_neighbour_node(i) == node3.get_neighbour_node(k))
        if (node1.get_neighbour_node(i) == node4.get_neighbour_node(l))
            return node1.get_neighbour_node(i);

        return 0;
    }

    void create_facetz_add_facet_cogz_2_tetra
    (Geom_Element & tetra, Collection<Geom_Element> & facetz, Collection<Mesh_Node> & node_col)
    {
        Geom_Element facet(7);

        facet.set_node(tetra.get_node(1), 1);
        facet.set_node(tetra.get_node(2), 2);
        facet.set_node(tetra.get_node(4), 3);
        facet.set_node(tetra.get_node(5), 5);
        facet.set_node(tetra.get_node(9), 6);
        facet.set_node(tetra.get_node(8), 7);
        facet.set_node
        (calculate_face_cog_and_add_neighbourz(facet, node_col), 4); // CoG for Triangle
        tetra.set_node(facet.get_node(4), 11);
        facetz.insert(facet);

        facet.set_node(tetra.get_node(2), 1);
        facet.set_node(tetra.get_node(3), 2);
        facet.set_node(tetra.get_node(4), 3);
        facet.set_node(tetra.get_node(6), 5);
        facet.set_node(tetra.get_node(10), 6);
        facet.set_node(tetra.get_node(9), 7);
        facet.set_node
        (calculate_face_cog_and_add_neighbourz(facet, node_col), 4); // CoG for Triangle
        tetra.set_node(facet.get_node(4), 12);
        facetz.insert(facet);

        facet.set_node(tetra.get_node(3), 1);
        facet.set_node(tetra.get_node(1), 2);
        facet.set_node(tetra.get_node(4), 3);
        facet.set_node(tetra.get_node(7), 5);
        facet.set_node(tetra.get_node(8), 6);
        facet.set_node(tetra.get_node(10), 7);
        facet.set_node
        (calculate_face_cog_and_add_neighbourz(facet, node_col), 4); // CoG for Triangle
        tetra.set_node(facet.get_node(4), 13);
        facetz.insert(facet);

        facet.set_node(tetra.get_node(2), 1);
        facet.set_node(tetra.get_node(1), 2);
        facet.set_node(tetra.get_node(3), 3);
        facet.set_node(tetra.get_node(5), 5);
        facet.set_node(tetra.get_node(7), 6);
        facet.set_node(tetra.get_node(6), 7);
        facet.set_node
        (calculate_face_cog_and_add_neighbourz(facet, node_col), 4); // CoG for Triangle
        tetra.set_node(facet.get_node(4), 14);
        facetz.insert(facet);
    }

    void create_facetz_add_facet_cogz_2_brick
    (Geom_Element & brick, Collection<Geom_Element> & facetz, Collection<Mesh_Node> & node_col)
    {
        Geom_Element facet(5);

        facet.set_node(brick.get_node(1), 1);
        facet.set_node(brick.get_node(2), 2);
        facet.set_node(brick.get_node(3), 3);
        facet.set_node(brick.get_node(4), 4);
        facet.set_node
        (calculate_quadrilateral_cog_and_add_neighbourz(facet, node_col), 5); // CoG for Quad
        // this line is empty because here Face-CoG is used only for boundary condition...
        facetz.insert(facet);

        facet.set_node(brick.get_node(1), 1);
        facet.set_node(brick.get_node(4), 2);
        facet.set_node(brick.get_node(8), 3);
        facet.set_node(brick.get_node(5), 4);
        facet.set_node
        (calculate_quadrilateral_cog_and_add_neighbourz(facet, node_col), 5); // CoG for Quad
        // this line is empty because here Face-CoG is used only for boundary condition...
        facetz.insert(facet);

        facet.set_node(brick.get_node(4), 1);
        facet.set_node(brick.get_node(3), 2);
        facet.set_node(brick.get_node(7), 3);
        facet.set_node(brick.get_node(8), 4);
        facet.set_node
        (calculate_quadrilateral_cog_and_add_neighbourz(facet, node_col), 5); // CoG for Quad
        // this line is empty because here Face-CoG is used only for boundary condition...
        facetz.insert(facet);

        facet.set_node(brick.get_node(3), 1);
        facet.set_node(brick.get_node(2), 2);
        facet.set_node(brick.get_node(6), 3);
        facet.set_node(brick.get_node(7), 4);
        facet.set_node
        (calculate_quadrilateral_cog_and_add_neighbourz(facet, node_col), 5); // CoG for Quad
        // this line is empty because here Face-CoG is used only for boundary condition...
        facetz.insert(facet);

        facet.set_node(brick.get_node(2), 1);
        facet.set_node(brick.get_node(1), 2);
        facet.set_node(brick.get_node(5), 3);
        facet.set_node(brick.get_node(6), 4);
        facet.set_node
        (calculate_quadrilateral_cog_and_add_neighbourz(facet, node_col), 5); // CoG for Quad
        // this line is empty because here Face-CoG is used only for boundary condition...
        facetz.insert(facet);

        facet.set_node(brick.get_node(5), 1);
        facet.set_node(brick.get_node(8), 2);
        facet.set_node(brick.get_node(7), 3);
        facet.set_node(brick.get_node(6), 4);
        facet.set_node
        (calculate_quadrilateral_cog_and_add_neighbourz(facet, node_col), 5); // CoG for Quad
        // this line is empty because here Face-CoG is used only for boundary condition...
        facetz.insert(facet);
    }

    void create_facetz_add_facet_cogz_2_prism
    (Geom_Element & prism, Collection<Geom_Element> & facetz, Collection<Mesh_Node> & node_col)
    {
        Geom_Element facet(7);

    /// triangle
        facet.set_node(prism.get_node(1), 1);
        facet.set_node(prism.get_node(2), 2);
        facet.set_node(prism.get_node(3), 3);
        facet.set_node(prism.get_node(7), 5);
        facet.set_node(prism.get_node(8), 6);
        facet.set_node(prism.get_node(9), 7);
        facet.set_node
        (calculate_face_cog_and_add_neighbourz(facet, node_col), 4); // CoG for Triangle
        prism.set_node(facet.get_node(4), 13);
        facetz.insert(facet);

    /// triangle
        facet.set_node(prism.get_node(4),  1);
        facet.set_node(prism.get_node(5),  2);
        facet.set_node(prism.get_node(6),  3);
        facet.set_node(prism.get_node(10), 5);
        facet.set_node(prism.get_node(11), 6);
        facet.set_node(prism.get_node(12), 7);
        facet.set_node
        (calculate_face_cog_and_add_neighbourz(facet, node_col), 4); // CoG for Triangle
        prism.set_node(facet.get_node(4), 14);
        facetz.insert(facet);
    }

    UINT calculate_face_cog_and_add_neighbourz
    (Geom_Element & triangle, Collection<Mesh_Node> & node_c)
    {
        UINT all3neighbour_ID =
        neighbours::get_nodez_neighbour
        (node_c[triangle.get_node(5)], node_c[triangle.get_node(6)], node_c[triangle.get_node(7)]);

        if (all3neighbour_ID != 0)
        {
            node_c[all3neighbour_ID].set_flag();
            return all3neighbour_ID;
        }

        Mesh_Node CoG;
        CoG = get_gravitycenter(node_c[triangle.get_node(1)], node_c[triangle.get_node(2)], node_c[triangle.get_node(3)]);
        CoG.set_flag();

        node_c.insert(CoG);

        UINT CoG_ID = node_c.get_size();
        node_c[triangle.get_node(5)].add_neighbour_node(CoG_ID);
        node_c[triangle.get_node(6)].add_neighbour_node(CoG_ID);
        node_c[triangle.get_node(7)].add_neighbour_node(CoG_ID);

        return CoG_ID;
    }

    UINT calculate_edge_cog_and_add_neighbourz
    (Geom_Element & edge, Collection<Mesh_Node> & node_c)
    {
        UINT all2neighbour_ID =
        neighbours::get_nodez_neighbour
        (node_c[edge.get_node(1)], node_c[edge.get_node(2)]);

        if (all2neighbour_ID != 0)
        {
            node_c[all2neighbour_ID].set_flag(false);
            return all2neighbour_ID;
        }

        Mesh_Node CoG;
        CoG = get_gravitycenter(node_c[edge.get_node(1)], node_c[edge.get_node(2)]);
        CoG.set_flag(true);
        node_c.insert(CoG);

        UINT CoG_ID = node_c.get_size();
        node_c[edge.get_node(1)].add_neighbour_node(CoG_ID);
        node_c[edge.get_node(2)].add_neighbour_node(CoG_ID);

        return CoG_ID;
    }

    UINT calculate_edge_cog_and_add_neighbourz
    (UINT & nodeA, UINT & nodeB, Collection<Mesh_Node> & node_col)
    {
        UINT all2neighbour_ID =
        neighbours::get_nodez_neighbour
        (node_col[nodeA], node_col[nodeB]);

        if (all2neighbour_ID != 0)
        {
            node_col[all2neighbour_ID].set_flag(false);
            return all2neighbour_ID;
        }

        Mesh_Node CoG(get_gravitycenter(node_col[nodeA], node_col[nodeB]));
        CoG.set_flag(true);
        node_col.insert(CoG);

        UINT CoG_ID = node_col.get_size();
        node_col[nodeA].add_neighbour_node(CoG_ID);
        node_col[nodeB].add_neighbour_node(CoG_ID);

        return CoG_ID;
    }

    UINT calculate_quadrilateral_cog_and_add_neighbourz
    (Geom_Element & quad, Collection<Mesh_Node> & node_c)
    {
        UINT all4neighbour_ID =
        neighbours::get_nodez_neighbour
        (node_c[quad.get_node(1)], node_c[quad.get_node(2)], node_c[quad.get_node(3)], node_c[quad.get_node(4)]);

        if (all4neighbour_ID != 0)
        {
            node_c[all4neighbour_ID].set_flag();
            return all4neighbour_ID;
        }

        Mesh_Node CoG;
        CoG = get_gravitycenter(node_c[quad.get_node(1)], node_c[quad.get_node(2)], node_c[quad.get_node(3)], node_c[quad.get_node(4)]);
        CoG.set_flag();
        node_c.insert(CoG);
        UINT CoG_ID = node_c.get_size();
        node_c[quad.get_node(1)].add_neighbour_node(CoG_ID);
        node_c[quad.get_node(2)].add_neighbour_node(CoG_ID);
        node_c[quad.get_node(3)].add_neighbour_node(CoG_ID);
        node_c[quad.get_node(4)].add_neighbour_node(CoG_ID);

        return CoG_ID;
    }

}

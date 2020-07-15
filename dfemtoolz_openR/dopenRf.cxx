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

#include "dopenR.h"

UINT dopenR(
Collection <Mesh_Node> & nodez,
Collection <Geom_Element> & elements, Collection <Geom_Element> & initial_faces, Collection <Geom_Element> & contact_faces, Collection <Geom_Element> & surface_facets, Collection <Geom_Element> & input_faces_from_fal, string parameters_path_and_filename, string input_file_path_and_name)
{
    Info * info = Info::createInfo();

//    Timer * timer = Timer::createTimer();
//    timer->set_start_time();

    openR_Parameters * params =
    openR_Parameters::create_openR_Parameters();

    params->set_params_filename(parameters_path_and_filename);

    params->read_file();

    Collection <Geom_Node> stl_input_nodes;
    Collection <Geom_Element>  inlet_or_outlet_edges, inlet_or_outlet_edges_reduced, stl_input_edges;
    Collection <Init_Node> initial_nodes, initial_nodes_from_input_file;

    /// reading stl input
    if (params->stl_or_fal_input == constants::stl)
    {
        STL_Reader * stl_reader = STL_Reader::create_STL_Reader();
        if (!stl_reader->read_STL_edges(stl_input_nodes, stl_input_edges, input_file_path_and_name))
            return 1;
    }

    /// reading fal input
    if (params->stl_or_fal_input == constants::fal)
    {
        FAL_Reader * fal_reader = FAL_Reader::create_FAL_Reader();
        if (!fal_reader->read_file(input_faces_from_fal, input_file_path_and_name + ".fal"))
            return 1;
    }

    for (UINT j = 1; j <= nodez.get_size(); j++)
        nodez[j].set_flag(false);

    UINT no_of_nodez = 0,
    no_of_nodez_lets = 0, no_of_faces_lets = 0;

    /// in this version only .sli is supported
    {
        no_of_nodez = nodez.get_size();

        for (UINT x = 1; x <= initial_faces.get_size(); x++)
        {
            if (elements[1].how_many_nodes_per_element() == constants::BRICK)
            if (no_of_faces_lets < initial_faces[x].get_node(5))
                no_of_faces_lets = initial_faces[x].get_node(5);

            if (elements[1].how_many_nodes_per_element() == constants::TETRA)
            if (no_of_faces_lets < initial_faces[x].get_node(4))
                no_of_faces_lets = initial_faces[x].get_node(4);
        }
    }

    Collection <UINT> input_nodez_IDs;
    Collection <UINT> input_elementz_IDs;

    Collection <Mesh_Node> surface_nodez;

    for (UINT j = 1; j <= nodez.get_size(); j++)
    if (nodez[j].is_velocity_boundary())
    {
        surface_nodez.insert(nodez[j]);
        surface_nodez[surface_nodez.get_size()].set_ID(j);
    }

    surface_nodez.sort_collection();

    if (params->stl_or_fal_input == constants::stl)
    {
        stl_input_nodes.sort_collection();
        stl_input_nodes.no_overlapping();
    }

    UINT surface_to_mesh_Xmin_node = 1;

    if (params->stl_or_fal_input == constants::stl)
    {
        UINT one = 1;

        for (UINT j = 1; j <= surface_nodez.get_size(); j++)
        if (these_nodes_are_the_same(stl_input_nodes[one], surface_nodez[j], params->same_node_tol))
        {
            surface_to_mesh_Xmin_node = j - 1;
            if (surface_to_mesh_Xmin_node == 0)
                surface_to_mesh_Xmin_node = 1;
            break;
        }
    }

    if (params->stl_or_fal_input == constants::stl)
    for (UINT i = 1; i <= stl_input_nodes.get_size(); i++)
    for (UINT j = surface_to_mesh_Xmin_node; j <= surface_nodez.get_size(); j++)
    if (!surface_nodez[j].get_flag())
    if(these_nodes_are_the_same(stl_input_nodes[i], surface_nodez[j], params->same_node_tol))
    {
        surface_nodez[j].set_flag(true);
        input_nodez_IDs.insert(surface_nodez[j].get_ID());

        break;
    }

    input_nodez_IDs.sort_collection();
    input_nodez_IDs.no_overlapping();

    if (params->stl_or_fal_input == constants::stl)
        tmeshing::put_surface_facetz(params->materialID_of_outlet_or_inlet, surface_facets, elements, nodez);

    double area_of_inlet_or_outlet_surfece = 0;

    if (params->stl_or_fal_input == constants::stl)
    {
        Geom_Element edge[4];

        for (UINT i = 1; i <= surface_facets.get_size(); i++)
        {
            if (elements[1].how_many_nodes_per_element() == constants::BRICK)
            for (UINT j = 1; j <= input_nodez_IDs.get_size(); j++)
            {
                if (
                (surface_facets[i].get_node(1) != input_nodez_IDs[j]) &&
                (surface_facets[i].get_node(2) != input_nodez_IDs[j]) &&
                (surface_facets[i].get_node(3) != input_nodez_IDs[j]) &&
                (surface_facets[i].get_node(4) != input_nodez_IDs[j]))
                    continue;

                edge[1].set_ID(i);
                edge[1].set_node(surface_facets[i].get_node(1), 1);
                edge[1].set_node(surface_facets[i].get_node(2), 2);

                edge[2].set_ID(i);
                edge[2].set_node(surface_facets[i].get_node(2), 1);
                edge[2].set_node(surface_facets[i].get_node(3), 2);

                edge[3].set_ID(i);
                edge[3].set_node(surface_facets[i].get_node(3), 1);
                edge[3].set_node(surface_facets[i].get_node(4), 2);

                edge[0].set_ID(i);
                edge[0].set_node(surface_facets[i].get_node(4), 1);
                edge[0].set_node(surface_facets[i].get_node(1), 2);

                inlet_or_outlet_edges.insert(edge[1]);
                inlet_or_outlet_edges.insert(edge[2]);
                inlet_or_outlet_edges.insert(edge[3]);
                inlet_or_outlet_edges.insert(edge[0]);

                surface_facets[i].set_flag(true);
            }

            if (elements[1].how_many_nodes_per_element() == constants::TETRA)
            {
                int triple_check = 0;

                for (UINT j = 1; j <= input_nodez_IDs.get_size(); j++)
                {
                    if (surface_facets[i].get_node(1) == input_nodez_IDs[j])
                        triple_check++;
                    if (surface_facets[i].get_node(2) == input_nodez_IDs[j])
                        triple_check++;
                    if (surface_facets[i].get_node(3) == input_nodez_IDs[j])
                        triple_check++;
                }

                if (triple_check == 3)
                {
                    edge[1].set_ID(i);
                    edge[1].set_node(surface_facets[i].get_node(1), 1);
                    edge[1].set_node(surface_facets[i].get_node(2), 2);

                    edge[2].set_ID(i);
                    edge[2].set_node(surface_facets[i].get_node(2), 1);
                    edge[2].set_node(surface_facets[i].get_node(3), 2);

                    edge[3].set_ID(i);
                    edge[3].set_node(surface_facets[i].get_node(3), 1);
                    edge[3].set_node(surface_facets[i].get_node(1), 2);

                    inlet_or_outlet_edges.insert(edge[1]);
                    inlet_or_outlet_edges.insert(edge[2]);
                    inlet_or_outlet_edges.insert(edge[3]);

                    surface_facets[i].set_flag(true);
                }

                triple_check = 0;
            }
        }
    }

    if (params->stl_or_fal_input == constants::stl)
    {
        int no_of_inlet_or_outlet_edges_on_a_face_should_be_twice_no_of_faces = 0;
        Geom_Element edge[4];

        for (UINT i = 1; i <= surface_facets.get_size(); i++)
        if (surface_facets[i].get_flag())
        {

            if (elements[1].how_many_nodes_per_element() == constants::BRICK)
            {
                for  (int k = 1; k <= 4; k++)
                {
                    int m = k + 1;
                    if (m == 5) m = 1;

                    edge[k - 1].set_ID(i);
                    edge[k - 1].set_node(surface_facets[i].get_node(k), 1);
                    edge[k - 1].set_node(surface_facets[i].get_node(m), 2);
                }

                for (UINT j = 1; j <= inlet_or_outlet_edges.get_size(); j++)
                for  (int k = 0; k < 4; k++)
                if (these_edges_are_same(edge[k], inlet_or_outlet_edges[j]))
                    no_of_inlet_or_outlet_edges_on_a_face_should_be_twice_no_of_faces++;

                if (no_of_inlet_or_outlet_edges_on_a_face_should_be_twice_no_of_faces < 8)
                    surface_facets[i].set_flag(false);
            }

/// was under comment to *** for github version of the software
/// ovo odkomentarisati - da se koristi samo kada se skida edge sloj input-a
/*
            if (elements[1].how_many_nodes_per_element() == constants::TETRA)
            {
                for  (int k = 1; k <= 3; k++)
                {
                    int m = k + 1;
                    if (m == 4) m = 1;

                    edge[k - 1].set_ID(i);
                    edge[k - 1].set_node(surface_facets[i].get_node(k), 1);
                    edge[k - 1].set_node(surface_facets[i].get_node(m), 2);
                }

                for (UINT j = 1; j <= inlet_or_outlet_edges.get_size(); j++)
                for  (int k = 0; k < 3; k++)
                if (these_edges_are_same(edge[k], inlet_or_outlet_edges[j]))
                    no_of_inlet_or_outlet_edges_on_a_face_should_be_twice_no_of_faces++;

                if (no_of_inlet_or_outlet_edges_on_a_face_should_be_twice_no_of_faces < 6)
                    surface_facets[i].set_flag(false);
            }
/// comment to this point ***
*/
            no_of_inlet_or_outlet_edges_on_a_face_should_be_twice_no_of_faces = 0;
        }
    }

    if (params->stl_or_fal_input == constants::stl)
    if (!params->use_all_inlet_or_outlet_faces)
    {
        UINT nodeID;
        Geom_Element edge(3);

        for (UINT i = 1; i <= surface_facets.get_size(); i++)
        if (surface_facets[i].get_flag())
        {
            if (elements[1].how_many_nodes_per_element() == constants::BRICK)
            for  (int k = 1; k <= 4; k++)
            {
                int m = k + 1;
                if (m == 5) m = 1;

                edge.set_ID(i);
                edge.set_node(surface_facets[i].get_node(k), 1);
                edge.set_node(surface_facets[i].get_node(m), 2);

                nodeID = neighbours::calculate_edge_cog_and_add_neighbourz(edge, nodez);
                edge.set_node(nodeID, 3);

                inlet_or_outlet_edges_reduced.insert(edge);
            }

            if (elements[1].how_many_nodes_per_element() == constants::TETRA)
            for  (int k = 1; k <= 3; k++)
            {
                int m = k + 1;
                if (m == 4) m = 1;

                edge.set_ID(i);
                edge.set_node(surface_facets[i].get_node(k), 1);
                edge.set_node(surface_facets[i].get_node(m), 2);

                nodeID = neighbours::calculate_edge_cog_and_add_neighbourz(edge, nodez);
                edge.set_node(nodeID, 3);

                inlet_or_outlet_edges_reduced.insert(edge);
            }
        }

        Collection <UINT> edgenodesIDs;

        /// kod tetri ni jedan ne ulazi u donju petlju, jer ni jedan
        /// edge nema flag

        for (UINT i = 1; i <= inlet_or_outlet_edges_reduced.get_size(); i++)
        if (nodez[inlet_or_outlet_edges_reduced[i].get_node(3)].get_flag())
        {
            edgenodesIDs.insert(inlet_or_outlet_edges_reduced[i].get_node(1));
            edgenodesIDs.insert(inlet_or_outlet_edges_reduced[i].get_node(2));
        }

        for (UINT i = 1; i <= surface_facets.get_size(); i++)
        if (surface_facets[i].get_flag())
        for (UINT j = 1; j <= edgenodesIDs.get_size(); j++)
        {

            if (elements[1].how_many_nodes_per_element() == constants::BRICK)
            for (int  k = 1; k <= 4; k++)
            if (surface_facets[i].get_node(k) == edgenodesIDs[j])
                surface_facets[i].set_flag(false);

            if (elements[1].how_many_nodes_per_element() == constants::TETRA)
            for (int  k = 1; k <= 3; k++)
            if (surface_facets[i].get_node(k) == edgenodesIDs[j])
                surface_facets[i].set_flag(false);
        }
    }

    if (surface_facets.get_size() > 0)
    {
        no_of_nodez_lets++;
        no_of_faces_lets++;
    }

    /// for now works only for brick mesh
    if (params->stl_or_fal_input == constants::fal)
    for (UINT i = 1; i <= input_faces_from_fal.get_size(); i++)
    {
        for (int  k = 1; k <= 4; k++)
        {
            nodez[input_faces_from_fal[i].get_node(k)].clear_boundary();
            nodez[input_faces_from_fal[i].get_node(k)].set_boundary(params->clear_and_set_this_boundary_to_nodes);
            nodez[input_faces_from_fal[i].get_node(k)].set_ID(no_of_nodez_lets);
        }

        area_of_inlet_or_outlet_surfece += get_area(
        nodez[input_faces_from_fal[i].get_node(1)],
        nodez[input_faces_from_fal[i].get_node(2)],
        nodez[input_faces_from_fal[i].get_node(3)],
        nodez[input_faces_from_fal[i].get_node(4)]);

        input_faces_from_fal[i].set_node(no_of_faces_lets, 5);
        initial_faces.insert(input_faces_from_fal[i]);
    }

    if (params->stl_or_fal_input != constants::fal)
    for (UINT i = 1; i <= surface_facets.get_size(); i++)
    if (surface_facets[i].get_flag())
    {
        if (elements[1].how_many_nodes_per_element() == constants::BRICK)
        {
            for (int  k = 1; k <= 4; k++)
            {
                nodez[surface_facets[i].get_node(k)].clear_boundary();
                nodez[surface_facets[i].get_node(k)].set_boundary(params->clear_and_set_this_boundary_to_nodes);
                nodez[surface_facets[i].get_node(k)].set_ID(no_of_nodez_lets);
            }

            area_of_inlet_or_outlet_surfece += get_area(
            nodez[surface_facets[i].get_node(1)],
            nodez[surface_facets[i].get_node(2)],
            nodez[surface_facets[i].get_node(3)],
            nodez[surface_facets[i].get_node(4)]);

            surface_facets[i].set_node(no_of_faces_lets, 5);
        }
        if (elements[1].how_many_nodes_per_element() == constants::TETRA)
        {
            for (int  k = 1; k <= 3; k++)
            {
                nodez[surface_facets[i].get_node(k)].clear_boundary();
                nodez[surface_facets[i].get_node(k)].set_boundary(params->clear_and_set_this_boundary_to_nodes);
                nodez[surface_facets[i].get_node(k)].set_ID(no_of_nodez_lets);
            }

            area_of_inlet_or_outlet_surfece += get_area(
            nodez[surface_facets[i].get_node(1)],
            nodez[surface_facets[i].get_node(2)],
            nodez[surface_facets[i].get_node(3)]);

            surface_facets[i].set_node(no_of_faces_lets, 4);
        }
    }

    info->print_info_message("Area of inlet or outlet surfece is "   + dtos(area_of_inlet_or_outlet_surfece));

//    timer->print_time_interval_in_seconds_from_start_to_now();

    return no_of_nodez;
}


UINT dopenR(
Collection <Mesh_Node> & nodez,
Collection <Geom_Element> & elements,
Collection <Geom_Element> & initial_faces,
Collection <Geom_Element> & contact_faces,
Collection <Geom_Element> & surface_facets,
Collection <Geom_Element> & input_faces_from_fal,
string input_file_path_and_name,
UINT material_ID)
{
    Info * info = Info::createInfo();

//    Timer * timer = Timer::createTimer();
//    timer->set_start_time();

//    openR_Parameters * params =
//    openR_Parameters::create_openR_Parameters();

//    params->set_params_filename(parameters_path_and_filename);

//    params->read_file();

    Collection <Geom_Node> stl_input_nodes;
    Collection <Geom_Element>  inlet_or_outlet_edges, inlet_or_outlet_edges_reduced, stl_input_edges;
    Collection <Init_Node> initial_nodes, initial_nodes_from_input_file;

    /// reading stl input
    {
        STL_Reader * stl_reader = STL_Reader::create_STL_Reader();
        if (!stl_reader->read_STL_edges(stl_input_nodes, stl_input_edges, input_file_path_and_name))
            return 1;
    }

    for (UINT j = 1; j <= nodez.get_size(); j++)
        nodez[j].set_flag(false);

    UINT no_of_nodez = 0,
    no_of_nodez_lets = 0, no_of_faces_lets = 0;

    /// in this version only .sli is supported
    {
        no_of_nodez = nodez.get_size();

        for (UINT x = 1; x <= initial_faces.get_size(); x++)
        {
            if (elements[1].how_many_nodes_per_element() == constants::BRICK)
            if (no_of_faces_lets < initial_faces[x].get_node(5))
                no_of_faces_lets = initial_faces[x].get_node(5);

            if (elements[1].how_many_nodes_per_element() == constants::TETRA)
            if (no_of_faces_lets < initial_faces[x].get_node(4))
                no_of_faces_lets = initial_faces[x].get_node(4);
        }
    }

    Collection <UINT> input_nodez_IDs;
    Collection <UINT> input_elementz_IDs;

    Collection <Mesh_Node> surface_nodez;

    for (UINT j = 1; j <= nodez.get_size(); j++)
    if (nodez[j].is_velocity_boundary())
    {
        surface_nodez.insert(nodez[j]);
        surface_nodez[surface_nodez.get_size()].set_ID(j);
    }

    surface_nodez.sort_collection();

    /// stl operations
    {
        stl_input_nodes.sort_collection();
        stl_input_nodes.no_overlapping();
    }

    UINT surface_to_mesh_Xmin_node = 1;

    /// stl procedure 1
    {
        UINT one = 1;

        for (UINT j = 1; j <= surface_nodez.get_size(); j++)
        if (these_nodes_are_the_same(stl_input_nodes[one], surface_nodez[j], constants::same_node_tol))
        {
            surface_to_mesh_Xmin_node = j - 1;
            if (surface_to_mesh_Xmin_node == 0)
                surface_to_mesh_Xmin_node = 1;
            break;
        }
    }

    /// stl procedure 2
    for (UINT i = 1; i <= stl_input_nodes.get_size(); i++)
    for (UINT j = surface_to_mesh_Xmin_node; j <= surface_nodez.get_size(); j++)
    if (!surface_nodez[j].get_flag())
    if(these_nodes_are_the_same(stl_input_nodes[i], surface_nodez[j], constants::same_node_tol))
    {
        surface_nodez[j].set_flag(true);
        input_nodez_IDs.insert(surface_nodez[j].get_ID());

        break;
    }

    input_nodez_IDs.sort_collection();
    input_nodez_IDs.no_overlapping();

    /// stl matching
    tmeshing::put_surface_facetz(material_ID, surface_facets, elements, nodez);

    double area_of_inlet_or_outlet_surfece = 0;

    /// stl edge procedure 1
    {
        Geom_Element edge[4];

        for (UINT i = 1; i <= surface_facets.get_size(); i++)
        {
            if (elements[1].how_many_nodes_per_element() == constants::BRICK)
            for (UINT j = 1; j <= input_nodez_IDs.get_size(); j++)
            {
                if (
                (surface_facets[i].get_node(1) != input_nodez_IDs[j]) &&
                (surface_facets[i].get_node(2) != input_nodez_IDs[j]) &&
                (surface_facets[i].get_node(3) != input_nodez_IDs[j]) &&
                (surface_facets[i].get_node(4) != input_nodez_IDs[j]))
                    continue;

                edge[1].set_ID(i);
                edge[1].set_node(surface_facets[i].get_node(1), 1);
                edge[1].set_node(surface_facets[i].get_node(2), 2);

                edge[2].set_ID(i);
                edge[2].set_node(surface_facets[i].get_node(2), 1);
                edge[2].set_node(surface_facets[i].get_node(3), 2);

                edge[3].set_ID(i);
                edge[3].set_node(surface_facets[i].get_node(3), 1);
                edge[3].set_node(surface_facets[i].get_node(4), 2);

                edge[0].set_ID(i);
                edge[0].set_node(surface_facets[i].get_node(4), 1);
                edge[0].set_node(surface_facets[i].get_node(1), 2);

                inlet_or_outlet_edges.insert(edge[1]);
                inlet_or_outlet_edges.insert(edge[2]);
                inlet_or_outlet_edges.insert(edge[3]);
                inlet_or_outlet_edges.insert(edge[0]);

                surface_facets[i].set_flag(true);
            }

            if (elements[1].how_many_nodes_per_element() == constants::TETRA)
            {
                int triple_check = 0;

                for (UINT j = 1; j <= input_nodez_IDs.get_size(); j++)
                {
                    if (surface_facets[i].get_node(1) == input_nodez_IDs[j])
                        triple_check++;
                    if (surface_facets[i].get_node(2) == input_nodez_IDs[j])
                        triple_check++;
                    if (surface_facets[i].get_node(3) == input_nodez_IDs[j])
                        triple_check++;
                }

                if (triple_check == 3)
                {
                    edge[1].set_ID(i);
                    edge[1].set_node(surface_facets[i].get_node(1), 1);
                    edge[1].set_node(surface_facets[i].get_node(2), 2);

                    edge[2].set_ID(i);
                    edge[2].set_node(surface_facets[i].get_node(2), 1);
                    edge[2].set_node(surface_facets[i].get_node(3), 2);

                    edge[3].set_ID(i);
                    edge[3].set_node(surface_facets[i].get_node(3), 1);
                    edge[3].set_node(surface_facets[i].get_node(1), 2);

                    inlet_or_outlet_edges.insert(edge[1]);
                    inlet_or_outlet_edges.insert(edge[2]);
                    inlet_or_outlet_edges.insert(edge[3]);

                    surface_facets[i].set_flag(true);
                }

                triple_check = 0;
            }
        }
    }

    /// stl edge procedure 2
    {
        int no_of_inlet_or_outlet_edges_on_a_face_should_be_twice_no_of_faces = 0;
        Geom_Element edge[4];

        for (UINT i = 1; i <= surface_facets.get_size(); i++)
        if (surface_facets[i].get_flag())
        {

            if (elements[1].how_many_nodes_per_element() == constants::BRICK)
            {
                for  (int k = 1; k <= 4; k++)
                {
                    int m = k + 1;
                    if (m == 5) m = 1;

                    edge[k - 1].set_ID(i);
                    edge[k - 1].set_node(surface_facets[i].get_node(k), 1);
                    edge[k - 1].set_node(surface_facets[i].get_node(m), 2);
                }

                for (UINT j = 1; j <= inlet_or_outlet_edges.get_size(); j++)
                for  (int k = 0; k < 4; k++)
                if (these_edges_are_same(edge[k], inlet_or_outlet_edges[j]))
                    no_of_inlet_or_outlet_edges_on_a_face_should_be_twice_no_of_faces++;

                if (no_of_inlet_or_outlet_edges_on_a_face_should_be_twice_no_of_faces < 8)
                    surface_facets[i].set_flag(false);
            }

/// was under comment to *** for github version of the software
/// ovo odkomentarisati - da se koristi samo kada se skida edge sloj input-a
/*
            if (elements[1].how_many_nodes_per_element() == constants::TETRA)
            {
                for  (int k = 1; k <= 3; k++)
                {
                    int m = k + 1;
                    if (m == 4) m = 1;

                    edge[k - 1].set_ID(i);
                    edge[k - 1].set_node(surface_facets[i].get_node(k), 1);
                    edge[k - 1].set_node(surface_facets[i].get_node(m), 2);
                }

                for (UINT j = 1; j <= inlet_or_outlet_edges.get_size(); j++)
                for  (int k = 0; k < 3; k++)
                if (these_edges_are_same(edge[k], inlet_or_outlet_edges[j]))
                    no_of_inlet_or_outlet_edges_on_a_face_should_be_twice_no_of_faces++;

                if (no_of_inlet_or_outlet_edges_on_a_face_should_be_twice_no_of_faces < 6)
                    surface_facets[i].set_flag(false);
            }
/// comment to this point ***
*/
            no_of_inlet_or_outlet_edges_on_a_face_should_be_twice_no_of_faces = 0;
        }
    }

    if (surface_facets.get_size() > 0)
    {
        no_of_nodez_lets++;
        no_of_faces_lets++;
    }

    /// stl procedure 3
    for (UINT i = 1; i <= surface_facets.get_size(); i++)
    if (surface_facets[i].get_flag())
    {
        if (elements[1].how_many_nodes_per_element() == constants::BRICK)
        {
            for (int  k = 1; k <= 4; k++)
            {
                nodez[surface_facets[i].get_node(k)].clear_boundary();
                nodez[surface_facets[i].get_node(k)].set_boundary(15);
                nodez[surface_facets[i].get_node(k)].set_ID(no_of_nodez_lets);
            }

            area_of_inlet_or_outlet_surfece += get_area(
            nodez[surface_facets[i].get_node(1)],
            nodez[surface_facets[i].get_node(2)],
            nodez[surface_facets[i].get_node(3)],
            nodez[surface_facets[i].get_node(4)]);

            surface_facets[i].set_node(no_of_faces_lets, 5);
        }
        if (elements[1].how_many_nodes_per_element() == constants::TETRA)
        {
            for (int  k = 1; k <= 3; k++)
            {
                nodez[surface_facets[i].get_node(k)].clear_boundary();
                nodez[surface_facets[i].get_node(k)].set_boundary(15);
                nodez[surface_facets[i].get_node(k)].set_ID(no_of_nodez_lets);
            }

            area_of_inlet_or_outlet_surfece += get_area(
            nodez[surface_facets[i].get_node(1)],
            nodez[surface_facets[i].get_node(2)],
            nodez[surface_facets[i].get_node(3)]);

            surface_facets[i].set_node(no_of_faces_lets, 4);
        }
    }

    info->print_info_message("Area of inlet or outlet surfece is "   + dtos(area_of_inlet_or_outlet_surfece));

    return no_of_nodez;
}

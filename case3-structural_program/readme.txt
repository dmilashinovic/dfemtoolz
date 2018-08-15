Structural analysis of multi-material FEM model – Tooth mastication

The purpose of this example is to demonstrate usage of the dfemtoolz for modelling of an assembly, which is composed of multiple parts and materials. Here, the tooth was composed of the following materials-parts: enamel, dentin, pulp and periodontal ligament (PDL). Geometries of the composing parts are provided as triangular surface meshes, and we assume that one needs to generate hexahedral or tetrahedral elements in order to run the FEA. Assuming that the PDL is fixed inside a mandible, the BCs include: 1) displacements of nodes on PDL’s outer surface are restricted; and 2) mastication forces are distributed over user-selected top surface of the enamel.

Algorithm

Input:
.stl files defining the four tooth materials.

Input:
.stl file defining the load (pressure) surface.

Output:
.sli (simple list) file, which contains the generated model (list of nodes, elements and interface-contact surfaces between materials) and BCs (for each node and the list of faces where pressure is prescribed); and .pos files of user’s preference for visualisation (surface with applied pressure, elements, nodes…).

1
for i=1 to number of materials (defined with 4 separate .stl files)  do

	2
	Call the Tetgen to generate unstructured tetrahedral mesh for i-th material (input: .stl files; output: .node .ele files).
	(this was done, and .node and .ele files are in input/ directory)

3
end for

4
for i=1 to number of materals (4) do

	5
	Call the dfemtoolz_remesh module to recognize model/material surface and (depending on user preference to element type tetrahedral/hexahedral) generate hexahedral or tetrahedral mesh of the i-th material (inputs: .node and .ele files)

6
end for

7
Call the dfemtoolz_multimaterial module to merge independently generated meshes-materials into a single multi-material model.

8
for i=1 to number of .stl files that contains surfaces on which loads should be applied do

	9
	Set BCs and referring material for the i-th load-surface.
	(this was done, and .cfg files are configured in input/ directory) 

	10
	Call the dfemtoolz_openR module to prescribe the given BCs to the model.

11
end for

In output/ directory user can find the results. Output files can be different if user modify settings in .cfg files.

Final results are in multimaterial-output.zip and final-output.zip package as well.
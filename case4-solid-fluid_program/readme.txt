Fluid-solid interaction (coupled problem) using tetrahedral mesh – Plaque progression in arteries

The fluid-solid interaction represents extension of the fluid-flow case and typical example of coupled problems. The vessel lumen represents fluid domain, its boundary conditions are already described in case1/example. The solid domain is represented by the vessel wall given as a triangular surface mesh so that it needs to be discretized into linear tetrahedral or hexahedral elements. The BCs that one needs to prescribe include: 1) nodes belonging to the end-sections need to be fixed; and 2) The key point for coupling solid and fluid is detection of interface-contact between the two domains – the list of contact faces and their corresponding elements. Note that although this feature was demonstrated in the fluid-solid example, it could be used for coupling arbitrary physical phenomena.

Algorithm

Input:
.stl files defining the two domains-materials (solid and fluid).

Input:
.stl file defining the inlet surface.

Input:
.stl file defining the outlet surface.

Input:
.stl file defining the fixated nodes.

Output:
.sli (simple list) file, which contains the generated model (list of nodes, elements and interface-contact surfaces between materials) and BCs (for each node and the list of faces where pressure is prescribed); and .pos files of user’s preference for visualisation (surfaces with applied inlet, outlet, fixations, elements, nodes…).

1
for i=1 to number of materials (defined with 2 separate .stl files)  do

	2
	Call the Tetgen to generate unstructured tetrahedral mesh 
	for i-th material (input: .stl files; output: .node .ele files).
	(this was done, and .node and .ele files are in input/ directory)

3
end for

4
for i=1 to number of materals (2) do

	5
	Call the dfemtoolz_remesh module to recognize model/material 
	surface and (depending on user preference to element type 
	tetrahedral/hexahedral) export tetrahedral2 mesh of the i-th material.

6
end for

7
Call the dfemtoolz_multimaterial module to merge independently generated meshes-materials into a single multi-material model.

8
for i=1 to number of .stl files that define surfaces for fixations(1)/outlet(1)/inlet(1) of this model do

	9
	Set BCs and referring material for the i-th load-surface 
	(fixations/ outlet/ inlet).
	(this was done, and .cfg files are configured in input/ directory) 

	10
	Call the dfemtoolz_openR module to prescribe the given BCs to the model.

11
end for

In output/ directory user can find the results. Output files can be different if user modify settings in .cfg files.

Final results are zipped in output/

Thank you for your interest 
dmilashinovic ..::at::.. gmail.com

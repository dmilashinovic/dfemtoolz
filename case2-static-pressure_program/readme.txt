Static structural analysis using an existing hexahedral mesh – Stent expansion

Assuming that the hexahedral mesh of the stent is generated using an alternative meshing tool, the purpose of this example1 is to demonstrate usage of the dfemtoolz for applying BCs to an existing hexahedral mesh. Briefly, we assume that one needs to simulate expansion-deployment of the stent by applying the uniform pressure to the stents’ inner surfaces.

Algorithm

Input:
List of nodes and hexahedral elements that define the stent mesh (in the .sli format).

Input:
List of the stent mesh faces (quadrilaterals) where pressure should be applied (in the facet list - .fal plain text format).

Output:
.sli (simple list) file, which contains the generated model (list of nodes and elements) and BCs (for each node and the list of faces where pressure is prescribed); and posfiles of user preference for visualisation (surface with applied pressure, elements, nodes…).

1
Call the dfemtoolz_nolimit module to recognize outer surface of the given model.

2
for i=1 to to number of .fal files (1) that contains surfaces on which loads should be applied do

	3
	Set a type of load (force, pressure) for the i-th load surface.
	(this was done, and .cfg files are configured in input/ directory) 

	4
	Call the dfemtoolz_openR module to prescribe the given BCs to the model.

5
end for

In output/ directory user can find the results. Output files can be different if user modify settings in .cfg files.

Final results are in final-output.zip package as well.

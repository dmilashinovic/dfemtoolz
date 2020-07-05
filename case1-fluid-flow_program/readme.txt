Fluid flow using hexahedral elements - Blood flow through a coronary artery

In this example, we consider modelling of the blood flow through a human coronary artery reconstructed from its medical scans (x-ray angiography). The fluid domain was defined with a single input .stl file (the triangle mesh defines the surface of the fluid domain). In this particular example, there is one inlet and six outlets, and each of them is defined with a user-selected triangular patch provided in the .stl file format. In order to perform the FE simulation, one needs to discretize the defined domain into the linear hexahedral or tetrahedral elements and apply the following BCs: 1) prescribe an inlet (velocity or flow) [5]; 2) set the outflow boundary condition for six outlets; and 3) velocities on the vessel wall should be set to 0 (** thus BCs for velocity in x, y and z directions are set to 1) (excluding inlet and outlets). The simplified pseudo-code-sniped is given bellow (Algorithm 1),

Algorithm

Input:
.stl file defining the fluid domain.
Input:
.stl file defining the inlet surface.
Input:
Six .stl files defining the outlet surfaces.

Output:
.sli (simple list) file, which contains generated model (list of nodes and elements) and BCs (for each node and the list of faces where outlet/inlet are prescribed); and .pos files of user preference for visualisation (inlets, outlets, surface, elements, nodes…).

1
Call the Tetgen to generate unstructured tetrahedral mesh of the fluid domain (input: .stl files; output: .node .ele files).
(this was done, and .node and .ele files are in input/ directory)

2
Call the dfemtoolz_remesh module to split the tetrahedral elements to hexahedral and identify the model outer surface.

3
for i = 1 to number of *.stl files that define inlets(1)/outlets(6) of the model do

	4
	Set type of boundary conditions for i-th outlet/inlet.
	(this was done, and .cfg files are configured in input/ directory) 

	5
	Call the dfemtoolz_openR to apply the given outlets/inlet to the model.

6
end for

In output/ directory user can find the results. Output files can be different if user modify settings in .cfg files.

Final results are zipped in output/

Thank you for your interest
dmilashinovic ..::at::.. gmail.com

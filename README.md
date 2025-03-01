# dfemtoolz


Hello and thank you for your interest in dfemtoolz

In this package users can find the C++ source code, benchmark tests and set of examples of dfemtoolz software written by Danko Milasinovic.

This package includes (in short words):

* dfemtoolz_dMyLib - core library

* dfemtoolz_remesh - tool that creates [re]mesh using existing mesh (usually import from Tetgen, or other similar software)

* dfemtoolz_nolimit - tool that identifies surface boundary of an existing mesh (material)

* dfemtoolz_openR - tool that is able to set various boundary conditions and loads to the finite element model (this software is able to print various data concerning the mesh, and to make different outputs / formats)

* dfemtoolz_multimaterial - tool that is used to generate multi-material models from multiple models (this software is also able to export interface surfaces between materials)

* caseX-... - set of examples / use-cases scenarios

* dfemtoolz_..._benchmark - benchmark tests

* dmilashinovic_dok_low_res.pdf - phd thesis

In order to have better insight in usage of dfemtoolz, a series of use-case scenarios (examples) is given to the user in this package. Phenomena that are commonly analyzed numerically is shown in these examples: fluid flow, fluid-solid interaction and structural analysis. Due to its structure, dfemtoolz is not limited to these types of FEM simulations. Users can set meaning of boundary conditions so this software can be used for preparation of models for any kind of FEM simulations. In order to use these examples fully it is recommended that user have Tetgen software made by H.Si (wias-berlin.de/software/tetgen/) and Gmsh software made by C.Geuzaine and J.F.Remacle (gmsh.info) and ParaView software (www.paraview.org) installed on his/her computer (with Linux or Windows os). Tetgen is used to generate initial mesh, and Gmsh and ParaView are used purely for visualization in these examples.

Due to its design (well written plain C++ code and standard library) these tools could be efficiently incorporated in other software. Because there are no specific libraries that are needed for this software - it is portable to virtually any platform (although in the given package user can find binaries and makefiles only for Linux and Windows). All function names, variables, classes... have long and self-descriptive names, so I do presume that anybody can manage to use the code with ease.

There are modules of dfemtoolz that are excluded from this [public] package (additional sub-modules of openR for prescribing specific loads to the model, exports and imports for PAKF, modules for skeletalization, tools for STL reparation, noise reduction modules, modules for streamlines, module for generation of particle clouds...). In future some of these modules may become part of the public package as well.

This software is available for the public under GNU GPLv3 license.

dmilashinovic ..::at::.. gmail.com

Citation: D.Z. Milasinovic, A.M. Vukicevic, N.D. Filipovic, dfemtoolz: An open-source C++ framework for efficient imposition of material and boundary conditions in finite element biomedical simulations, Computer Physics Communications, 249 (2020) 106996, doi: 10.1016/j.cpc.2019.106996.

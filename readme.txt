
Hello and thank you for your interest in dfemtoolz


In this package user can find the C++ source code and set of examples of dfemtoolz (aka danko's finite element toolz) software written by Danko Milasinovic. 

This package includes (in short words):

* dfemtoolz_dMyLib - library that is made for this software

* dfemtoolz_remesh - tool that creates [re]mesh using existing mesh (usually import from tetgen, or other similar software).

* dfemtoolz_nolimit - tool that sets adequate boundary to all surface nodes in existing mesh, as well as for all interrior nodes (various exports are possible)

* dfemtoolz_openR - tool that is able to set various boundary conditions and loads to the finite element model (this software is able to print various data concerning the mesh, and to make different outputs / formats)

* dfemtoolz_multimaterial - tool that is used to generate multimaterial models from multiple models (this software is able to export contact surfaces and various data as well)

* dfemtoolz_example-XX.tar.gz - set of examples

In the given examples all the software tools are compiled as standalone - so user is able to execute them as command-line programs. In order to use these examples fully it is recommended that user have Tetgen software made by H.Si (wias-berlin.de/software/tetgen/) and Gmsh software made by C.Geuzaine and J.F.Remacle (gmsh.info) installed on his/hers computer (with Linux or Windows os). Tetgen is used to generate initial mesh, and Gmsh is used purely for visualization in these examples.

Due to its design (well written plain C++ code and standard library) these tools could be efficiently incorporated in other software. Because there are no specific libraries that are needed for this software - it is portable to virtually any platform (although in the given package user can find binaries and makefiles only for Linux and Windows). All function names, variables, classes... have long and self-descriptive names, so i do presume that anybody can manage to use the code with ease. Beside these software tools, dMyLib library can be useful itself due to ease of use, and could be employed by other software as well.

There are modules of dfemtoolz that are excluded from this [public] package (additional sub-modules of openR for prescribing specific loads to the model, exports and imports for PAKF, modules for skeletalization, tools for STL reparation, noise reduction modules, modules for streamlines, module for generation of particle clouds...). In future some of these modules maybe become part of public package as well.

This software is available for public under GNU GPLv3 license. Please use it according to the license.


Thank you for your interest
dmilashinovic ..::at::.. gmail.com
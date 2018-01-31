# FRSML 3.0

A small linear math library using SSE4.

## What is FRSML
 
  - FRSML (FranceSnack Math Library) is a project which targets Vulkan developers
  - The library does some linear math, and contains basic class for linear math like vec3,mat4,quat with fast optimizations.
  - Works cross-platform


## Build project:

  + Windows: Using solutions provied
  + Unix:    Clone and build the project using CMake and your favorite compiler.
   
## Using the library
 
  - Now you can compile the library dynamiclly or static. 
		+ Compiler will produce two libraries: Once implements specific optimization, once is wrapper
		+ For example: if you choose FRSML_SSE and dynamiclly build, compiler will produce *frsml_sse.dll* and *frsml.dll*
		+ But you only have to link frsml.dll to use in your project (frsml_sse is depency)

   - Please include the headers in the include/frsml folder
                     

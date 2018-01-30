# FRSML 3.0

A small linear math library using SSE4.

## What is FRSML
 
  + FRSML (FranceSnack Math Library) is a project which targets Vulkan developers (so do I). The library does some linear math, and contains basic class for linear math like Vector3, Matrix4, Quaternion, and so on. All the math are done in SSE4.2, which I can confirm that my library would support Linux and Windows platform. In the feauture, the project may implement a easy way for devs to buffering indices, vertices, ... The library gets to the point where it stable now, but not so good, since many feautures i dream for haven't still been implemented.

 **************************

## Build project:

  + Windows: Using solutions provied
  + Unix:    Clone and build the project using CMake and your favorite compiler.
   
 **************************

## Using the library
 
  + Link the library with the project you like, and take all the headers in the include folder to work with.
  + Detail:
      - Compile the project and link the library with the porject you want.
      - You can compile the library as static or dynamic.
                     

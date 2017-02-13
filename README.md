# FRSML

A small linear math library using SSE4 technology and upper.

###STATUS

| Complier      | Architecture       
| ------------- |:-------------:   
| MSVC2015      | x86_x64
| MinGW         | -
| GCC           | -
| Clang         | -

 
 

##- What is FRSML
 
![alt tag](https://raw.githubusercontent.com/bentokun/FRSML/master/pupa.png)
>I'm sorry
 
  + FRSML (FranceSnack Math Library) is a projekt which targets Vulkan developers (so do I). The library does some linear math, and contains basic class for linear math like Vector3, Matrix4, Quaternion, and so on. All the math are done in SSE4.2, which I can confirm that my library would support Linux and Windows platform. In the feauture, the project may implement a easy way for devs to buffering indices, vertices, ... The library gets to the point where it stable now, but not so good, since many feautures i dream for haven't still been implemented.

**************************

##- Build project:

  + Windows: Current solution
    
      * Using cmake to generate solution for the newest VS2017-RC or VS2015
             + Include CPUID: include header file that check support of hardware for WIN32 (NOT AUTO DISABLED ON LINUX)
             + Debug: using in-dev version of some headers and enable assert 
                    
      * Build the project as DLL
              
              
  + Unix:    
    
      * Open terminal and get to the directory of the git (downloaded, using cd)
      
                - If you haven't download yet,
                     : git clone --recursive https://github.com/bentokun/FRSML
                     : cd FRSML
                      
      * Make a folder to put the build result 
      * Using "cmake ." to generate the gcc project
      * Using "make" to complie gcc project
             
      >I don't know if CMake have a gui version on linuxz, but probally it does.
             
   
  ###WISH SOMEONE CAN CONTRIBUTE WITH ME. IF GIVE ME SOME ISSUE BENTOKUN NEED ERRORS AND BUGS TO SMASH.
     + I mean if you want to contribute, hit me up with something (pull request, maybe?). And bentokun sorry, bentokun don't speak English.
              
      
                     

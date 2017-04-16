# FRSML

A small linear math library using SSE4 technology and upper.

## What is FRSML
 
![alt tag](https://raw.githubusercontent.com/bentokun/FRSML/master/pupa.png)
>I'm sorry
 
  + FRSML (FranceSnack Math Library) is a projekt which targets Vulkan developers (so do I). The library does some linear math, and contains basic class for linear math like Vector3, Matrix4, Quaternion, and so on. All the math are done in SSE4.2, which I can confirm that my library would support Linux and Windows platform. In the feauture, the project may implement a easy way for devs to buffering indices, vertices, ... The library gets to the point where it stable now, but not so good, since many feautures i dream for haven't still been implemented.
  
## UPDATE:
  
### 16/4/2017 :) -------------------
  + Good news:
  	* I have studied a little bit and now the vector is compatible with Vulkan mapping! Now you can do a struct like this
		
		```C++
		struct Vertex{
			FRSML::vec2 pos;
			FRSML::vec3 color;
			FRSML::vec3 normal;
		}
		```
		
	* The noticeable thing is the size per struct is very huge. The reason is its contains a "m128", which is 32 bit total, adds up is the property thing that x,y which also cost 24 bit, so it is bigger than normal. So cant compete with another math library, but at least some function still fast!
	
	* ~~Compatible matrix will going up asap when i studied about matrix data struct in GLSL. I have only found the vector,i think i didnt dig deep enough. Good news anyways~~ Compatible Matrix is up! It's just simple 4 cols of vec4. It will get the cols but not rows, however i handle all of it before by return the Matrix value, and the constructor generated the cols so it doesnt so big.
	
	* Diving in glm's massive hardcore code, i find out that glsl take an array of vec4 or float[16] or float[4][4]. the responsible line:
		```c++
			col_type value[4];
		```
		
	* However, col_type is just the same as row_type. There are confusion draws here:
		- Will it take the rows or cols value: I dont even know? It's poorly documented
		- Therefore, i put the cols value public. When i test the uniform (which i lost my precious time because of the math library throw exception that took 5 hours to figure out the error that make fstream fck failed), i will dive into it and can edit the struct.
		
		
	* Also, MSVS 2017 has a really nice logo! ^_^
  
### 15/4/2017 ................
  
  +  Bad news:
      * Sorry, because of my design, the library won't work well with vertex input, since i don't intent it to be a GLSL mirror.
  The design affects pretty much on that vertex input on Vulkan, but on OpenGl, you can just go with another option like float. For me, working like this is pretty much doom,  ~~i will try create a wrapper function, convert into array then return binding and attribute description to reattack this disavantage~~, but just use float[]. Pretty much with i expected, ~~uniform still work well lol~~ it's doom.
 
      * The Pascal version is abondoned. When i have inspration, i might do it, cause i am despreted of making the graphic engine done in C++. Pascal make object developing very hard, **must manually call constructor on every object created is fucked**.
  
  - For now, with Vulkan, bind per vertex via float. I still think float is suitable, since it size is small and we pretty much don't do
  anything with it. Vertex born as static.
  
  - If anyone curious about what i am doing, i am doing Vulkan stuff, of course. Have written a allocator and memory management, now just image and mipmap, so do depth buffering. Hope will finish its core soon.

**************************

## Example code in C++

```C++
	
     #include <FRSML>
	
     std::cout << "FRSML Vulkan Math Library ~_^" << std::endl;

     FRSML::vec2 gltest{5.0f, 7.0f};

     //Can be used with OpenGl
     glUniform2fv(pos, 1, FRSML::value_ptr(gltest));

	FRSML::Matrix4 mat{
		{5,3,4,6},
		{12,13,15,17},
		{12,13,16,14},
		{1,26,15,1}
	};

	FRSML::Matrix4 mat2{
		{ 8,7,1,2 },
		{ 2,9,1,7 },
		{ 2,6,5,4 },
		{ 4,7,5,3 }
	};

	FRSML::vec3 vec{
		3,4,5
	};

	FRSML::vec4 vec2{ vec, 1.0f };

	FRSML::Quaternion quat = FRSML::Quaternion::Rotate(FRSML::vec3(1, 1, 1), 90);

	std::cout << "Determinant: " << mat.Determinant()<<"\n" << std::endl;
	std::cout << "Quaternion" << "\n"<<quat << std::endl;
	std::cout << "Perspective Matrix with Para: fov (zoom) = 45, aspect = 800/600, nad zNear and zFar betwwen 0 and 100" << std::endl;
	std::cout << CreatePerspectiveMatrix(45, FRSML::vec2(800, 600), 0,100) <<std::endl;
	std::cout << "Mul of mat1 and mat2" << std::endl;
	std::cout << mat*mat2 << std::endl;
	std::cout << "Inverse of mat1" << std::endl;
	std::cout << mat.Inverse() << std::endl;
	std::cout << "Transpose Matrix1: " << std::endl;
	std::cout << mat.Transpose() << std::endl;
	std::cout << vec2.X << " " << vec2.Y << " " << vec2.Z << " " << vec2.W << std::endl;
	std::cout << "Vector Magnitude: " << vec.Length() << std::endl;
	std::cout << "Log(10) is: " << FRSML::Log(10) << std::endl;

        std::cout << "Log(10) in cmath: "<< log(10) << std::endl;

	vec = FRSML::Reflect(vec, FRSML::vec3(0, 90, 0));

	std::cout << "Reflect of vec is: " << vec.X <<" "<< vec.Y<<" " << vec.Z << std::endl;
	std::cout << "(The y value is reflect by 90 degrees, which means the length"
		<< "of y mag in two surface are the same, bentokun said ^-^)" << std::endl;
```

 **************************
 
## Example code in Pascal (not finished)

```pascal
	uses Vector, Standard;
	
	var ex: TVec3;
	
	begin
		ex:= vec3(5,5);
		ex:= Cross(ex,ex);
		writeln(ex.X,' ',ex.Y,' ',ex.Z);
	end.
```

 **************************

# NEWS:

A branch contains Pascal implementation of FRSML is available at the objfpc-FRSML branch. 

 **************************

## Build project (C++):

  + Windows: Current solution
    
      * Using cmake to generate solution for the newest VS2017-RC or VS2015
             + Include CPUID: include header file that check support of hardware for WIN32 (NOT AUTO DISABLED ON LINUX)
             + Debug: using in-dev version of some headers and enable assert 
                    
      * Build the project as DLL
      
      * Or you could use MinGW. 
              
              
  + Unix:    
    
      * Sponsor: Cmake Terminal and GCC
      
      * Open terminal and get to the directory of the git (downloaded, using cd)
      
                - If you haven't download yet, download git
                     : git clone --recursive https://github.com/bentokun/FRSML
                     : cd FRSML
                - Or just download on github. 
                     
      * Make a folder to put the build result 
      * Using "cmake ." to generate the gcc project
      * Using "make" to complie gcc project
             
      ~~>I don't know if CMake have a gui version on linuxz, but probally it does.~~      
   
 **************************
 
## Building the library (Pascal)

- You don't have to build it in Pascal, just use it right away like you should in C#. Making a library in Pascal will only makes thing messier.
 
## Using the library
 
  + Link the library with the project you like, and take all the headers in the include folder to work with.
  + Detail:
      - Compile the project and link the library with the porject you want.
      - Use the header "FRSML" in the include folder to interface with dll function
      - Put the FRSML.dll in your executable folder or in System32 (if you are in Windows)
   
****************
## HELP ME :>
  + I mean if you want to contribute, hit me up with something (pull request, maybe?). But i think this lib is stable now. Thanks for reading!
              
      
                     

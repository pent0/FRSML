# FRSML 3.1 Milestone: **3.33% / 100**
   - Add noise functions:  **11.1% - Map = 3.33/30%**
		+ Simplex Noise: **0% (Resources?)**
		+ Perlin (1d,2d,3d): **60% - Map = 11.1%/33.3%**
			* Gradient functions: **10/10%**
				. SSE: **5/5%**
				. Norm: **5/5%**
			* Perlin 3D Functions: **50/50%**
				. SSE: **25/25%**
				. Norm: **25/25%**
			* Perlin 1D, 2D Wrapper: **0/10%**
				. SSE: **0%**
				. Norm: **0%**
			* Interfaces: **0/5%**
			* Seed to permutations: **0%/25%** (PNG incomplete)
		+ Octawaves: **0%** (Perlin incompleted)
   - Add mat2 and mat3 - **0% - Map = 0%/5%**
   - Fast pseudo number generator - **0% - Map = /10%**
   - Smooth damp implementation - **0% - Map = / 5%**
   - Implement NEON optimizations - **0% - Map = / 50%**

# FRSML 3.0.4 Milestone: **28%/100%**
   - Implement non-optimization methods:
		+ Matrix: **70%/100% - Map = 28%/40%**
		+ Quaternion: **0/100% - Map = 0/50%**

	- CMake for users: 0/10%
		+ Add FindFRSML.cmake module: 0/5%
		+ Add SSE flag: 0/5%

# FRSML 3.0.3.1 -8/2/2018 11:08PM
   - Correct non-optimization functions (some compiler gives error about **x**f not presented)

# FRSML 3.0.3 - 31/1/2018 10:51PM
   - Correct the lerp, sin functions
   - Add fade function
   - Now you can use some functions of the library without optimizations
	 * To do that, build the project without ticking any optimization option.
   - Now you can compile the library dynamiclly or static. 
	 * Compiler will produce two libraries: Once implements specific optimization, once is wrapper
	 * For example: if you choose FRSML_SSE and dynamiclly build, compiler will produce *frsml_sse.dll* and *frsml.dll*
	 * But you only have to link frsml.dll to use in your project (frsml_sse is depency)
	
# FRSML 3.0.2 - 30/1/2018 6:00PM
   - Last time origanized the header

# THE NEW FRSML 3.0
   - Still compatible with Vulkan and OpenGL, but some new class is in	
		+ Add a Rectangle and Point struct
		+ Fix issues with Matrix4 about the multiplying
	- Clean the project, rename namespace to lowercase
	- Merge the struct to single file
	- Remove the PASCAL version 

# WHAT IS NEW IN FRSML 2.0
   - Totally compatible with Vulkan mapping and OpenGl. How?
	- Directly use x, y, z, w keyword, remove SSE struct from class, to make OPENGL or Vulkan able to
		get the value from the static offset 
   - Reduce shift-typing keyword, making typing more easier 
   - Matrix4 now only has columns value
   - Fix LookAt function
   - Replace the old Sin function with the new one (The reason is because the old function give unpercision result)
   - Normal math won't use any SSE because of unnecessaries.
   
   Working now : ->-
   
  ![alt tag](https://raw.githubusercontent.com/bentokun/FRSML/master/RESULT.png)

## UPDATE:
 
### 27/4/2017 ----------------------
	
  + FRSML ver 2 is out. However the quaternion is the thing that i haven't touched for months, and its my next milestone.
  
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
		- Therefore, i put the cols value public. ~~When i test the uniform (which i lost my precious time because of the math library throw exception that took 5 hours to figure out the error that make fstream fck failed), i will dive into it and can edit the struct.~~ Confirm that it take the public value first.
		
  
### 15/4/2017 ................
  
  +  Bad news:
      * Sorry, because of my design, the library won't work well with vertex input, since i don't intent it to be a GLSL mirror.
  The design affects pretty much on that vertex input on Vulkan, but on OpenGl, you can just go with another option like float. For me, working like this is pretty much doom,  ~~i will try create a wrapper function, convert into array then return binding and attribute description to reattack this disavantage~~, but just use float[]. Pretty much with i expected, ~~uniform still work well lol~~ it's doom.
 
      * The Pascal version is abondoned. When i have inspration, i might do it, cause i am despreted of making the graphic engine done in C++. Pascal make object developing very hard, **must manually call constructor on every object created is fucked**.
  
  - For now, with Vulkan, bind per vertex via float. I still think float is suitable, since it size is small and we pretty much don't do
  anything with it. Vertex born as static.
  
  - If anyone curious about what i am doing, i am doing Vulkan stuff, of course. Have written a allocator and memory management, now just image and mipmap, so do depth buffering. Hope will finish its core soon.

**********************************************

# CHANGELOG
  
  - __*16/4/2017*__
    + Change the property style of vector from getset func X(), Y(), Z(), W() to member property X, Y, Z, W
    + Compatible with Vulkan and GLSL data struct added for Vector and Matrix
    + Add auto-convert-to-array for glUniform2fv, glUniform3fv, glUniform4fv, gluniformMatrix4fv. You can still use the value_ptr.
    
    + __Markdown feauture for future__
      * Support NEON (for my precious phone :)) ) (start on 15th June)
      * Support Matrix4x3, Matrix2x2, Matrix3x4, Matrix3x3. Will not use template, since data decleration is seperated.
      (unknown time)

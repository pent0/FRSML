#ifndef ASSERTSSE_H
#define ASSERTSSE_H

#include <iostream>
#include <string>

#ifdef _FRSML_SSE4_DEBUG
#define FRSML_S_ASSERT(x) \
             if ((x)) \
               { \
                 std::cout << "[Line: "<<__LINE__<<" ; File: "<<__FILE__<<"]: ERROR: "<< #x <<std::endl; \
               }

#define FRSML_ASSERT(x,message)\
	 if ((x)) \
	 { \
		 std::cout << "[Line: " << __LINE__ << " ; File: " << __FILE__ << "]: ERROR: " << #message << std::endl; \
	 }

#define FRSML_ASSERT_WV(x,message,v1,v2)\
	 if ((x)) \
	 { \
		 std::cout << "[Line: " << __LINE__ << " ; File: " << __FILE__ << "]: ERROR: " << #message <<". Value: "<<v1<<","<<v2 << std::endl; \
	 }
#else
#define FRSML_ASSERT(x,message)
#define FRSML_ASSERT_WV(x,message,v1,v2)
#define FRSML_S_ASSERT(x)
#endif

#endif

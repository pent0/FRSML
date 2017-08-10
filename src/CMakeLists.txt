set (HEADER
	math_internal.h
	sse_extensions.h
	Standard.h)

set (SOURCES 
	math_internal.cpp
	Matrix.cpp
	point.cpp
	Quaternion.cpp
	rectangle.cpp
	sse_extensions.cpp
	Standard.cpp
	vector.cpp)

add_library(FRSML MODULE ${SRCS} ${HEADERS})
	
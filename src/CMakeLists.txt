set (HEADER
	math_internal.h)

set (SOURCES 
	math_internal.cpp
	matrix.cpp
	point.cpp
	quat.cpp
	rect.cpp
	standard.cpp
	vector.cpp
	noise.cpp)

add_subdirectory(norm)
add_subdirectory(sse)

if (DEFINED DYNAMIC_FRSML)
	add_library(frsml MODULE ${SOURCES} ${HEADERS})
else()
	add_library(frsml ${SOURCES} ${HEADERS})
endif()

if (DEFINED SSE_FRSML)
	target_link_libraries(frsml frsml_sse)
else()
	target_link_libraries(frsml frsml_normal)
endif()
	
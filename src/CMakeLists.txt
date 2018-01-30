set (HEADER_DIR ${CMAKE_SOURCE_DIR}/include/frsml)

set (EXTERNAL_HEADER
	${HEADER_DIR}/config.h
	${HEADER_DIR}/internal.h
	${HEADER_DIR}/matrix.h
	${HEADER_DIR}/vector.h
	${HEADER_DIR}/quat.h
	${HEADER_DIR}/rect.h
	${HEADER_DIR}/noise.h
	${HEADER_DIR}/standard.h)

set (HEADER
	math_internal.h
	sse/sse_extensions.h
	sse/sse_standard.h)

set (SOURCES 
	sse/sse_extensions.cpp
	sse/sse_standard.cpp
	math_internal.cpp
	matrix.cpp
	point.cpp
	quat.cpp
	rect.cpp
	standard.cpp
	vector.cpp
	noise.cpp)

add_library(FRSML MODULE ${SOURCES} ${HEADERS} ${EXTERNAL_HEADER})
	
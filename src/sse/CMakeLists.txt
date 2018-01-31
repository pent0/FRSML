set (HEADERS
	sse_noise.h
	sse_standard.h
	sse_extensions.h)

set (SRCS
	sse_noise.cpp
	sse_standard.cpp
	sse_extensions.cpp)

add_library(frsml_sse ${HEADERS} ${SRCS})


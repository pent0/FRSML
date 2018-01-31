set (HEADERS
	norm_noise.h
	norm_standard.h)

set (SRCS
	norm_noise.cpp
	norm_standard.cpp)

add_library(frsml_normal ${HEADERS} ${SRCS})


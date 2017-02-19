include_directories("${PROJECT_SOURCE_DIR}/src")

set(HEADERS
	AssertSSE.h
	CPUId.h
	FRSVar.h
	Matrix4x4.h
	Standard.h
	Vector.h)

set(SRCS
	FRSVar.cpp
	Matrix4x4.cpp
	Standard.cpp
	Vector4f.cpp
	Vector4i.cpp
	Vector3.cpp
	Vector2.cpp)

if (INCLUDE_CPUID)
	set (SRCS ${SRCS}
		CPUId.cpp)
endif()

#Quaternion havent suitable yet
#I still need to revise the euler things
if (DEBUG_FEAUTURE)
	set (HEADERS ${HEADERS} Quaternion.h)
	set (SRCS ${SRCS} Quaternion.cpp)
endif()

add_library(FRSML MODULE ${SRCS} ${HEADERS})


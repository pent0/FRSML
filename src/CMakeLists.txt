include_directories("${PROJECT_SOURCE_DIR}/src")

set(HEADERS
	AssertSSE.h
	Config.h
	CPUId.h
	FRSML
	FRSVar.h
	Matrix4x4.h
	Quaternion.h
	QuickMathSSE4.h
	StandardMathSSE4.h
	Vector4f.h
	Vector4i.h
	VectorAnt.h)

set(SRCS
	FRSVar.cpp
	Matrix4x4.cpp
	Quaternion.cpp
	QuickMathSSE4.cpp
	StandardMathSSE4.cpp
	Vector4f.cpp
	Vector4i.cpp
	VectorAnt.cpp)

if (INCLUDE_CPUID)
	set (SRCS ${SRCS}
		CPUId.cpp)
endif()

add_library(FRSML MODULE ${SRCS} ${HEADERS})


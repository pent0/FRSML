cmake_minimum_required (VERSION 3.6 FATAL_ERROR)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
project (frsml)

set(CMAKE_CXX_STANDARD 14)

include (ComplierTarget)

set (FRSML_VERSION_MAJOR_PUBLIC 3)
set (FRSML_VERSION_MINOR_PUBLIC 0)

if (MSVC)
    detect_architecture("_M_AMD64" x86_64)
    detect_architecture("_M_IX86" x86)
    detect_architecture("_M_ARM" ARM)
else()
    detect_architecture("__x86_64__" x86_64)
    detect_architecture("__i386__" x86)
    detect_architecture("__arm__" ARM)
endif()

if (NOT DEFINED ARCHITECTURE)
	set(ARCHITECTURE "GENERIC")
	set(ARCHITURE_GENERIC 1)
	add_definitions(-DARCHITECTURE_GENERIC = 1)
endif()

option(DYNAMIC_FRSML ON)
option(SSE_FRSML ON)
option(AVX_FRSML OFF)
option(NEON_FRSML OFF)

if (DYNAMIC_FRSML)
	set(FRSML_DYNAMIC 1)
	set(FRSML_DYNAMIC_EXPORTS 1)
endif()

add_definitions(-DFRSML_NORMAL)

if (SSE_FRSML)
	add_definitions(-DFRSML_SSE)
elseif (NEON_FRSML)
	add_definitions(-DFRSML_NEON)
else ()
	add_definitions(-DFRSML_NORMAL)
endif()

message(STATUS "The target architure going to is: ${ARCHITECTURE}")

configure_file(
	"${PROJECT_SOURCE_DIR}/include/frsml/config.h.in"
	"${PROJECT_SOURCE_DIR}/include/frsml/config.h")

include_directories(include)
add_subdirectory (src)

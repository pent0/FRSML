cmake_minimum_required (VERSION 3.2 FATAL_ERROR)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

message(STATUS "Authors IDE is VS2017-RC")

project (FRSML)

set(CMAKE_CXX_STANDARD 14)

message(STATUS "Loading include file!!")

include (ComplierTarget)

set (FRSML_VERSION_MAJOR_PUBLIC 2)
set (FRSML_VERSION_MINOR_PUBLIC 0)
set (FRSML_WORKINGCODE 2017042786L_V20_0)

message(STATUS "Starting generated projekt")

configure_file(
	"${PROJECT_SOURCE_DIR}/include/Config.h.in"
	"${PROJECT_BINARY_DIR}/include/Config.h")

option(INCLUDE_CPUID "Include CPUID file" ON)
option(DEBUG_FEAUTURE "Include debug feautures, if you like wink wink" ON)

option(USE_DECREPATED "Use decrepated feautures" OFF)

if (DEBUG_FEAUTURE)
	add_definitions(-D_FRSML_SSE4_DEBUG)
endif()

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

if (DEFINED ARCHITURE_x86)
	message(WARNING "x86 version hadn't been revised yet!")
endif()

message(STATUS "The target architure going to is: ${ARCHITECTURE}")

add_subdirectory (src)

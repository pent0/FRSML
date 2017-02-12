cmake_minimum_required (VERSION 3.2)

include(CheckSymbolExists)

function(detect_architecture symbol arch)
	if (NOT DEFINED ARCHITECTURE)
		set(CMAKE_REQUIRED_QUIET 1)
		check_symbol_exists("${symbol}" "" ARCHITECTURE_${arch})
		unset(CMAKE_REQUIRED_QUIET)
	

		if (ARCHITECTURE_${arch})
			set(ARCHITECTURE "${arch}" PARENT_SCOPE)
			set(ARCHITECTURE_${arch} 1 PARENT_SCOPE)
			add_definitions(-DARCHITECTURE_${arch}=1)

		endif()

	endif()

endfunction()

project (FRSML)

set (FRSML_VERSION_MAJOR_PUBLIC 1)
set (FRSML_VERSION_MINOR_PUBLIC 0)
set (FRSML_WORKINGCODE 2017212104_V5_36)

message(STATUS "Starting generated projekt")

configure_file(
	"${PROJECT_SOURCE_DIR}/src/Config.getcmake"
	"${PROJECT_BINARY_DIR}/src/Config.h")

option(INCLUDE_CPUID "Include CPUID file" ON)
option(INCLUDE_ASSERTCHECK "Include Assert check, if you like wink wink" ON)

if (INCLUDE_ASSERTCHECK)
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

message(STATUS "The target architure going to is: ${ARCHITECTURE}")

set(CMAKE_CXX_STANDARD 14)

add_subdirectory (src)

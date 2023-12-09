cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_EXTENSIONS false)
set(CMAKE_CXX_SCAN_FOR_MODULES true)

project(TEMathLib VERSION 1.0 LANGUAGES CXX)

add_subdirectory(lib)
add_subdirectory(test)
add_subdirectory(benchmarks)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	#if (${CMAKE_CXX_COMPILER_VERSION} VER_LESS VERSION 17.0.0)
		#message(FATAL_ERROR "Project requires Clang 17.0 version")
	#endif()
else()
	message(FATAL_ERROR "Project has been wrote against only Clang compiler.")
endif()
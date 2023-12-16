cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_EXTENSIONS false)
set(CMAKE_CXX_SCAN_FOR_MODULES false)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(SHOW_ASM_CODE false)

project(TEMathLib VERSION 1.0 LANGUAGES CXX)

if (NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	#message(FATAL_ERROR "Project should be built with GNU compiler.")
endif()

if ("${CMAKE_HOST_SYSTEM_NAME}" STREQUAL "Windows")
	set(CMAKE_STATIC_LIBRARY_PREFIX "")
	set(CMAKE_STATIC_LIBRARY_SUFFIX ".lib")
endif()

add_compile_options(-funsafe-math-optimizations)
add_compile_options(-ffast-math)
add_compile_options(-Wno-undefined-inline)
add_compile_options(-w)

#add_compile_options(-S)
#add_compile_options(-masm=intel)
#add_compile_options(-fverbose-asm)

set(CMAKE_DEBUG_POSTFIX _d)

add_subdirectory(lib)
add_subdirectory(test)
add_subdirectory(benchmarks)

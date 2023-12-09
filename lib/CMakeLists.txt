cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_EXTENSIONS false)
set(CMAKE_CXX_SCAN_FOR_MODULES true)

file(GLOB_RECURSE HeaderSources "headers/*.cppm")
file(GLOB_RECURSE ImplementationSources "source/*.cpp")
set(CMAKE_DEBUG_POSTFIX _d)

add_compile_options(-funsafe-math-optimizations)

# COMPATIBLE MODE COMPILATION
project(TEMath VERSION 1.0 LANGUAGES CXX)

add_compile_options(-Wno-undefined-inline)
add_compile_options(-mavx)

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME} PRIVATE ${ImplementationSources})
target_sources(${PROJECT_NAME} PUBLIC FILE_SET CXX_MODULES FILES ${HeaderSources})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

set_target_properties(${PROJECT_NAME} PROPERTIES
	CXX_STANDARD 20
)

# PERFORMANCE MODE COMPILATION (AVAILABLE ONLY WITH RELEASE BUILD)
if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
	project(TEMathP VERSION 1.0 LANGUAGES CXX)

	add_compile_options(-Wno-undefined-inline)
	add_compile_options(-mavx2)
	add_compile_options(-mfma)

	add_library(${PROJECT_NAME} STATIC)

	target_sources(${PROJECT_NAME} PRIVATE ${ImplementationSources})
	target_sources(${PROJECT_NAME} PUBLIC FILE_SET CXX_MODULES FILES ${HeaderSources})

	target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

	set_target_properties(${PROJECT_NAME} PROPERTIES
		CXX_STANDARD 20
	)
endif()
cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_EXTENSIONS false)
set(CMAKE_CXX_SCAN_FOR_MODULES true)

add_compile_options(-funsafe-math-optimizations)
add_compile_options(-Wno-undefined-inline)

project(TEMathTest VERSION 1.0 LANGUAGES CXX)

file(GLOB_RECURSE ImplementationSources "source/*.cpp")
set(CMAKE_DEBUG_POSTFIX _d)

add_compile_options(-mavx)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE ${ImplementationSources})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

add_dependencies(${PROJECT_NAME} TEMath)
target_link_libraries(${PROJECT_NAME} TEMath)

set_target_properties(${PROJECT_NAME} PROPERTIES
	OUTPUT_NAME_DEBUG ${PROJECT_NAME}_d
	OUTPUT_NAME_RELEASE ${PROJECT_NAME}
	CXX_STANDARD 20
)
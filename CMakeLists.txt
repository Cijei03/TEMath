cmake_minimum_required(VERSION 3.28)

project(TEMath VERSION 1.0 LANGUAGES CXX)

add_compile_options(-funsafe-math-optimizations)
add_compile_options(-ffast-math)
add_compile_options(-Wno-undefined-inline)

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME} PRIVATE
	"source/tem.angle_units.cpp"
	"source/tem.basic_math.cpp"
	"source/tem.vec2.cpp"
	"source/tem.vec3.cpp"
	"source/tem.vec4.cpp"
	"source/tem.mat2.cpp"
	"source/tem.mat3.cpp"
	"source/tem.mat4.cpp"
)

set_target_properties(${PROJECT_NAME} PROPERTIES
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED true
	DEBUG_POSTFIX "_d"
)


if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
	set(TEST_PROJECT_NAME "TEMathTest")

	add_executable(${TEST_PROJECT_NAME})

	target_sources(${TEST_PROJECT_NAME} PRIVATE
		"source/test/main.cpp"
		"source/test/OutputColor.cpp"
		"source/test/TestDef.cpp"
		"source/test/Tests-vec2.cpp"
		"source/test/Tests-vec3.cpp"
		"source/test/Tests-vec4.cpp"
		"source/test/Tests-mat2.cpp"
		"source/test/Tests-mat3.cpp"
		"source/test/Tests-mat4.cpp"
	)

	set_target_properties(${TEST_PROJECT_NAME} PROPERTIES
		CXX_STANDARD 20
		CXX_STANDARD_REQUIRED true
		DEBUG_POSTFIX "_d"
	)

	add_dependencies(${TEST_PROJECT_NAME} ${PROJECT_NAME})
	target_link_libraries(${TEST_PROJECT_NAME} ${PROJECT_NAME})
endif()
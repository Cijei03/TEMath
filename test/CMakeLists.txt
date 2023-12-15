project(TEMathTest VERSION 1.0 LANGUAGES CXX)

file(GLOB_RECURSE ImplementationSources "source/*.cpp")
set(CMAKE_DEBUG_POSTFIX _d)

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
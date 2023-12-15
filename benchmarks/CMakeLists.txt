if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
	file(GLOB_RECURSE ImplementationSources "*.cpp")

	project(TEMathBenchmark VERSION 1.0 LANGUAGES CXX)

	add_executable(${PROJECT_NAME})
	target_sources(${PROJECT_NAME} PRIVATE ${ImplementationSources})
	target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
	add_dependencies(${PROJECT_NAME} TEMath)
	target_link_libraries(${PROJECT_NAME} TEMath)
	#set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 20)
endif()
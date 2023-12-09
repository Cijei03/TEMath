if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
	set(CMAKE_CXX_STANDARD 20)
	set(CMAKE_CXX_STANDARD_REQUIRED true)
	set(CMAKE_CXX_EXTENSIONS false)
	set(CMAKE_CXX_SCAN_FOR_MODULES true)

	file(GLOB_RECURSE ImplementationSources "*.cpp")

	add_compile_options(-funsafe-math-optimizations)
	add_compile_options(-Wno-undefined-inline)

	# BUILD AVX BENCHMARK
	project(TEMathBenchmark VERSION 1.0 LANGUAGES CXX)

	add_compile_options(-mavx)
	add_executable(${PROJECT_NAME})
	target_sources(${PROJECT_NAME} PRIVATE ${ImplementationSources})
	target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
	add_dependencies(${PROJECT_NAME} TEMath)
	target_link_libraries(${PROJECT_NAME} TEMath)
	set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 20)


	# BUILD AVX2+FMA BENCHMARK
	project(TEMathBenchmarkP VERSION 1.0 LANGUAGES CXX)

	add_compile_options(-mavx2 -mfma)
	add_executable(${PROJECT_NAME})
	target_sources(${PROJECT_NAME} PRIVATE ${ImplementationSources})
	target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
	add_dependencies(${PROJECT_NAME} TEMathP)
	target_link_libraries(${PROJECT_NAME} TEMathP)
	set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 20)


endif()
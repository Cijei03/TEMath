file(GLOB_RECURSE ImplementationSources 
	"source/*.cpp"
)
project(TEMath VERSION 1.0 LANGUAGES CXX)

add_library(${PROJECT_NAME} STATIC)
target_sources(${PROJECT_NAME} PRIVATE ${ImplementationSources})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

#set_target_properties(${PROJECT_NAME} PROPERTIES
#		CXX_STANDARD 20
#	)
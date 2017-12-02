if( NOT TARGET ciCubeMap )
	get_filename_component( CINDER_PATH "${CMAKE_CURRENT_LIST_DIR}/../../../.." ABSOLUTE )

	get_filename_component( ciCubeMap_SOURCE_PATH "${CMAKE_CURRENT_LIST_DIR}/../../src" ABSOLUTE )
	get_filename_component( ciCubeMap_INCLUDE_PATH "${CMAKE_CURRENT_LIST_DIR}/../../include" ABSOLUTE )

	FILE(GLOB ciCubeMap_SOURCES ${ciCubeMap_SOURCE_PATH}/ciCubeMap/*.cpp)
	add_library( ciCubeMap ${ciCubeMap_SOURCES} )

	target_include_directories( ciCubeMap PUBLIC "${ciCubeMap_INCLUDE_PATH}" )
	target_include_directories( ciCubeMap SYSTEM BEFORE PUBLIC "${CINDER_PATH}/include" )

	if( NOT TARGET cinder )
		    include( "${CINDER_PATH}/proj/cmake/configure.cmake" )
		    find_package( cinder REQUIRED PATHS
		        "${CINDER_PATH}/${CINDER_LIB_DIRECTORY}"
		        "$ENV{CINDER_PATH}/${CINDER_LIB_DIRECTORY}" )
	endif()
	target_link_libraries( ciCubeMap PRIVATE cinder )
endif()

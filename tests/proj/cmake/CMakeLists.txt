cmake_minimum_required( VERSION 3.0 FATAL_ERROR )
set( CMAKE_VERBOSE_MAKEFILE ON )

project( ciCubeMapTests )

get_filename_component( CINDER_PATH "${CMAKE_CURRENT_LIST_DIR}/../../../../.." ABSOLUTE )
get_filename_component( APP_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../" ABSOLUTE )

include( "${CINDER_PATH}/proj/cmake/modules/cinderMakeApp.cmake" )

FILE(GLOB APP_SOURCES ${APP_PATH}/src/*.cpp)

ci_make_app(
	SOURCES     ${APP_SOURCES}
	CINDER_PATH ${CINDER_PATH}
	BLOCKS		ciCubeMap
)

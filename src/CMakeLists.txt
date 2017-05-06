project( Polygon_mesh_processing )

cmake_minimum_required(VERSION 2.6.2)

# CGAL and its components
find_package(CGAL QUIET COMPONENTS)

if ( NOT CGAL_FOUND )
	message(STATUS "This project requires the CGAL library, and will not be compiled.")
	return()  
endif()

# Boost and its components
find_package(Boost REQUIRED)

if(NOT Boost_FOUND)
	message(STATUS "This project requires the Boost library, and will not be compiled.")
	return()  
endif()

find_package(OpenMesh QUIET)

if(OpenMesh_FOUND)
	include(UseOpenMesh)
else()
	message(STATUS "Examples that use OpenMesh will not be compiled.")
endif()

#(requires 3.1.0 or greater)
find_package(Eigen3 3.1.0) 

if (EIGEN3_FOUND)
	# Executables that require Eigen 3.1
	include( ${EIGEN3_USE_FILE} )
else(EIGEN3_FOUND)
	message(STATUS "NOTICE: Some examples require Eigen 3.1 (or greater) and will not be compiled.")  
endif(EIGEN3_FOUND)

find_package(VTK REQUIRED)
include(${CGAL_USE_FILE})

include(${VTK_USE_FILE})
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

# include for local package
include_directories( BEFORE ../../include )

ADD_DEFINITIONS(-DCGAL_TO_VTK_DLL -DCGAL_EIGEN3_ENABLED)


FILE(GLOB SRC_FILES "./*.cpp") 
FILE(GLOB HEAD_FILES "${CMAKE_CURRENT_SOURCE_DIR}/../include/*.h" "./*.h") 

add_library(Polygon_processing SHARED ${HEAD_FILES} ${SRC_FILES})

target_link_libraries(Polygon_processing ${CGAL_LIBRARIES} ${CGAL_3RD_PARTY_LIBRARIES})
target_link_libraries(Polygon_processing ${VTK_LIBRARIES})

#SET_TARGET_PROPERTIES(Polygon_processing PROPERTIES OUTPUT_NAME "Polygon_processing")
SET_TARGET_PROPERTIES(Polygon_processing PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../bin)

add_subdirectory(Testing)
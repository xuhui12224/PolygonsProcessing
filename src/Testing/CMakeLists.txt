FILE(GLOB SRC_FILES "./*.cpp") 
FILE(GLOB HEAD_FILES "./*.h") 

include(${VTK_USE_FILE})
include(${CGAL_USE_FILE})

add_executable(TestvtkIO ${SRC_FILES} ${HEAD_FILES})

target_link_libraries(TestvtkIO ${CGAL_LIBRARIES} ${CGAL_3RD_PARTY_LIBRARIES})

target_link_libraries(TestvtkIO ${VTK_LIBRARIES} Polygon_processing)

SET_TARGET_PROPERTIES(TestvtkIO PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../../bin)
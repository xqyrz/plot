
file(GLOB IOAPP_SRC_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)
MESSAGE(STATUS "IOAPP_SRC_FILES: ${IOAPP_SRC_FILES}")
add_subdirectory(selfapp)
add_subdirectory(vofa)


MESSAGE(STATUS "IOAPP_SRC_FILES: ${IOAPP_SRC_FILES}")
set(CMAKE_FOLDER "${CMAKE_FOLDER}/ioapp")
add_subdirectory(selfapp)
add_subdirectory(vofa)
cmake_minimum_required(VERSION 3.16)
project(${JLINKARM})

file(GLOB_RECURSE SRC_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)
file(GLOB_RECURSE HEAD_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)
add_library(${JLINKARM} SHARED
        ${PlugBase_SRC_FILES}
        ${IO_SRC_FILES}
        ${SRC_FILES}
        ${HEAD_FILES}
        ${BUS_PATH}/bus.h
        ${BUS_PATH}/bus.cpp
)

target_include_directories(${JLINKARM}
        PUBLIC
        ${IO_PATH}
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${JLINKARM}
        Qt${QT_VERSION_MAJOR}::Core
        mdb::mdb
        ${IO_LIB}
)

install(TARGETS ${JLINKARM}
        ARCHIVE DESTINATION lib     # 静态库 (.a / .lib)
        LIBRARY DESTINATION lib     # 共享库 (.so / .dll)
        RUNTIME DESTINATION plugins
)

install(FILES ${HEAD_FILES}
        DESTINATION include/${JLINKARM}
)
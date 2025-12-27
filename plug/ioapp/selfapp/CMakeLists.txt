cmake_minimum_required(VERSION 3.16)


add_definitions(-DQCUSTOMPLOT_USE_OPENGL)

file(GLOB_RECURSE SRC_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.c"

)
add_library(${SELFIOAPP_LIB} SHARED
        ${SRC_FILES}
)

target_include_directories(${SELFIOAPP_LIB}
        PUBLIC
        ${IOAPP_PATH}
        ${IO_PATH}
)

target_link_libraries(${SELFIOAPP_LIB}
        Qt${QT_VERSION_MAJOR}::Core
)

install(TARGETS ${SELFIOAPP_LIB}
        ARCHIVE DESTINATION plugins     # 静态库 (.a / .lib)
        LIBRARY DESTINATION plugins     # 共享库 (.so / .dll)
        RUNTIME DESTINATION plugins
)
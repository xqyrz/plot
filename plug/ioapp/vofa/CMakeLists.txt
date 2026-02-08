cmake_minimum_required(VERSION 3.16)

file(GLOB_RECURSE SRC_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.c"

)
add_library(${VOFA_APP} SHARED
        ${SRC_FILES}
)

target_include_directories(${VOFA_APP}
        PUBLIC
        ${IOAPP_PATH}
        ${IO_PATH}
)

target_link_libraries(${VOFA_APP}
        Qt${QT_VERSION_MAJOR}::Core
)

install(TARGETS ${VOFA_APP}
        ARCHIVE DESTINATION lib     # 静态库 (.a / .lib)
        LIBRARY DESTINATION lib     # 共享库 (.so / .dll)
        RUNTIME DESTINATION plugins
)
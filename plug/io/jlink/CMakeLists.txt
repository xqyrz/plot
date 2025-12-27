cmake_minimum_required(VERSION 3.16)


file(GLOB_RECURSE SRC_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.h"

)
add_library(${JLINKARM} SHARED
        ${SRC_FILES}
)
MESSAGE("JLINKARM ${JLINKARM}")

target_include_directories(${JLINKARM}
        PUBLIC
        ${IO_PATH}
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${JLINKARM}
        Qt${QT_VERSION_MAJOR}::Core
)
#if(WIN32)
#    target_link_libraries(${JLINKARM} ws2_32 mswsock)
#endif()
install(TARGETS ${JLINKARM}
        ARCHIVE DESTINATION plugins     # 静态库 (.a / .lib)
        LIBRARY DESTINATION plugins     # 共享库 (.so / .dll)
        RUNTIME DESTINATION plugins
)
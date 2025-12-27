cmake_minimum_required(VERSION 3.16)


add_definitions(-DQCUSTOMPLOT_USE_OPENGL)

file(GLOB_RECURSE SRC_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.h"

)
add_library(${ATCLIENT_LIB} SHARED
        ${SRC_FILES}
)
MESSAGE("ATCLIENT_LIB ${ATCLIENT_LIB}")
target_include_directories(${ATCLIENT_LIB}
        PUBLIC
        ${IO_PATH}
        ${IO_PATH}/asio/asio/asio/include
)

target_link_libraries(${ATCLIENT_LIB}
        Qt${QT_VERSION_MAJOR}::Core
)
if(WIN32)
    target_link_libraries(${ATCLIENT_LIB} ws2_32 mswsock)
endif()
install(TARGETS ${ATCLIENT_LIB}
        ARCHIVE DESTINATION lib     # 静态库 (.a / .lib)
        LIBRARY DESTINATION lib     # 共享库 (.so / .dll)
        RUNTIME DESTINATION plugins
)
cmake_minimum_required(VERSION 3.16)


file(GLOB_RECURSE SRC_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.h"

)
add_library(${AUDP_LIB} SHARED
        ${SRC_FILES}
)
MESSAGE("AUDP_LIB ${AUDP_LIB}")
target_include_directories(${AUDP_LIB}
        PUBLIC
        ${IO_PATH}
        ${IO_PATH}/asio/asio/asio/include
)

target_link_libraries(${AUDP_LIB}
        Qt${QT_VERSION_MAJOR}::Core
)
if(WIN32)
    target_link_libraries(${AUDP_LIB} ws2_32 mswsock)
endif()
install(TARGETS ${AUDP_LIB}
        ARCHIVE DESTINATION plug     # 静态库 (.a / .lib)
        LIBRARY DESTINATION plug     # 共享库 (.so / .dll)
        RUNTIME DESTINATION plug
)
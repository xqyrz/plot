cmake_minimum_required(VERSION 3.16)
set(APP_NAME testplug)
file(GLOB_RECURSE SRC_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)

add_executable(${APP_NAME} ${SRC_FILES})

target_link_libraries(${APP_NAME}
        Qt${QT_VERSION_MAJOR}::Core

)

target_compile_definitions(${APP_NAME}
        PRIVATE
        PROJECT_NAME="${APP_NAME}"
)
message("ATCPSERVER_LIB ${ATCPSERVER_LIB}")
add_dependencies(${APP_NAME} ${ATCPSERVER_LIB})
cmake_minimum_required(VERSION 3.16)
project(testhex VERSION 0.1 LANGUAGES CXX)
file(GLOB_RECURSE SRC_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.ui"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.qrc"
)
find_package(binfile REQUIRED)
add_executable(${PROJECT_NAME} ${SRC_FILES})
target_link_libraries(${PROJECT_NAME}
        PRIVATE
        binfile::binfile
)
target_compile_definitions(${PROJECT_NAME}
        PRIVATE
        PROJECT_NAME="${APP_NAME}"
)
target_include_directories(${PROJECT_NAME}
        PUBLIC
        {CMAKE_INSTALL_PREFIX}/include
)
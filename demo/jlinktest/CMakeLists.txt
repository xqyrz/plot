cmake_minimum_required(VERSION 3.16)
project(jlinkTest VERSION 0.1 LANGUAGES CXX)

file(GLOB_RECURSE SRC_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.ui"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.qrc"
)

add_executable(${PROJECT_NAME} ${SRC_FILES})
#find_library(AJLINKARM_LIB
#        NAMES ajlinkarmd
#        PATHS ${CMAKE_INSTALL_PREFIX}/lib
#        NO_DEFAULT_PATH
#)
target_link_libraries(${PROJECT_NAME}
        PRIVATE
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Widgets

)
target_compile_definitions(${PROJECT_NAME}
        PRIVATE
        PROJECT_NAME="${APP_NAME}"
)
target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${CMAKE_SOURCE_DIR}/install/include
)
target_compile_definitions(${PROJECT_NAME}
        PRIVATE PLUG_PATH="${CMAKE_INSTALL_PREFIX}/plugins/ajlinkarmd.dll"
)
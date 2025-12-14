cmake_minimum_required(VERSION 3.16)
set(APP_NAME testelf)

 
#file(GLOB_RECURSE SRC_FILES
#        "${CMAKE_CURRENT_SOURCE_DIR}/elfio/*.cpp"
#        "${CMAKE_CURRENT_SOURCE_DIR}/elfio/*.h"
#        "${CMAKE_CURRENT_SOURCE_DIR}/elfio/*.hpp"
#        "${CMAKE_CURRENT_SOURCE_DIR}/elfio/*.ui"
#        "${CMAKE_CURRENT_SOURCE_DIR}/elfio/*.qrc"
#)

add_executable(${APP_NAME} main.cpp)
target_include_directories(${APP_NAME}
        PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/elfio
)
target_link_libraries(${APP_NAME}
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::PrintSupport
        ${PLOT_LIB}
)

target_compile_definitions(${APP_NAME}
        PRIVATE
        PROJECT_NAME="${APP_NAME}"
)

add_subdirectory(elfio)
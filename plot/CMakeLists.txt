cmake_minimum_required(VERSION 4.0)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(PLOT_LIB plotd)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(PLOT_LIB plot)
endif()


file(GLOB_RECURSE SRC_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.ui"
)

add_library(${PLOT_LIB} ${SRC_FILES}
        plotdata.cpp
        plotdata.h
        plotmodel.cpp
        plotmodel.h
        plottree.cpp
        plottree.h
        ../testplot/main.cpp)

target_include_directories(${PLOT_LIB}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}   # 头文件所在目录
)

target_link_libraries(${PLOT_LIB}
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::PrintSupport
)

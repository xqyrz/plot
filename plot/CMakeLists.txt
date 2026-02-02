cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O1")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O1")
add_definitions(-DQCUSTOMPLOT_USE_OPENGL)

file(GLOB_RECURSE SRC_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.ui"
)

add_library(${PLOT_LIB} ${SRC_FILES}
        ../plug/io/iointerface.h
        ../plug/io/iocommon.h
        ../plug/testplug/main.cpp)

target_include_directories(${PLOT_LIB}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}   # 头文件所在目录
)
if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    set(OPENGL_LIB OpenGL::GL OpenGL::GLU)

endif()

target_link_libraries(${PLOT_LIB}
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::PrintSupport
        Qt${QT_VERSION_MAJOR}::OpenGL
        ${OPENGL_LIB}
)


if(WIN32)
    target_link_libraries(${PLOT_LIB} opengl32 glu32)
endif()
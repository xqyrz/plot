cmake_minimum_required(VERSION 3.16)
cmake_policy(SET CMP0072 NEW) # new in 3.11. The NEW behavior for this policy is to set OpenGL_GL_PREFERENCE to GLVND.
cmake_policy(SET CMP0068 NEW) # new in 3.9. The NEW behavior of this policy is to ignore the RPATH settings for install_name on macOS.
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES  ON)
set(OpenGL_GL_PREFERENCE LEGACY)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


get_directory_property(_has_parent PARENT_DIRECTORY)
if(_has_parent)
    set(is_root_project OFF)
else()
    set(is_root_project ON)
endif()

set(QT_NODES_DEVELOPER_DEFAULTS "${is_root_project}" CACHE BOOL "Turns on default settings for development of QtNodes")

option(BUILD_TESTING "Build tests" "${QT_NODES_DEVELOPER_DEFAULTS}")
option(BUILD_EXAMPLES "Build Examples" "${QT_NODES_DEVELOPER_DEFAULTS}")
option(BUILD_DOCS "Build Documentation" "${QT_NODES_DEVELOPER_DEFAULTS}")
option(BUILD_SHARED_LIBS "Build as shared library" ON)
option(BUILD_DEBUG_POSTFIX_D "Append d suffix to debug libraries" OFF)
option(QT_NODES_FORCE_TEST_COLOR "Force colorized unit test output" OFF)
option(USE_QT6 "Build with Qt6 (Enabled by default)" ON)

if(QT_NODES_DEVELOPER_DEFAULTS)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
endif()

if(BUILD_DEBUG_POSTFIX_D)
    set(CMAKE_DEBUG_POSTFIX "d")
    set(CMAKE_RELEASE_POSTFIX "")
    set(CMAKE_RELWITHDEBINFO_POSTFIX "rd")
    set(CMAKE_MINSIZEREL_POSTFIX "s")
endif()

project(plot VERSION 0.1 LANGUAGES CXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /utf-8")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build as static library" FORCE)

if(BUILD_STATIC_LIBS AND BUILD_SHARED_LIBS)
    message(FATAL_ERROR "Cannot build both static and shared libraries simultaneously")
endif()

# 3. 定义静态库宏
if(NOT BUILD_SHARED_LIBS)
    add_definitions(-DQT_NODES_STATIC)
    add_definitions(-DQT_STATICPLUGIN)

    # Qt 静态构建需要定义
    if (Qt6_FOUND)
        add_definitions(-DQT_STATIC)
    endif()
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_DEBUG_POSTFIX "d")
endif()
message("CMAKE_SYSTEM_NAME ${CMAKE_SYSTEM_NAME}")
message("CMAKE_SYSTEM_PROCESSOR ${CMAKE_SYSTEM_PROCESSOR}")
message("CMAKE_CXX_COMPILER_ID ${CMAKE_CXX_COMPILER_ID}")
message("CMAKE_SIZEOF_VOID_P ${CMAKE_SIZEOF_VOID_P}")

if (CMAKE_SYSTEM_NAME MATCHES "Emscripten")
elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        if(CMAKE_SIZEOF_VOID_P MATCHES "8")
            set(CMAKE_PREFIX_PATH C:/Qt/5.15.2/mingw81_64)
        endif()
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        if(CMAKE_SIZEOF_VOID_P MATCHES "8")
            set(CMAKE_PREFIX_PATH C:/Qt/5.15.2/msvc2019_64)
        endif()
    endif ()
elseif (CMAKE_SYSTEM_NAME MATCHES "Linux")
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        if(CMAKE_SIZEOF_VOID_P MATCHES "8")
            set(CMAKE_PREFIX_PATH /home/hw/Qt/5.15.2/gcc_64)
            find_package(OpenGL REQUIRED)
        endif()
    endif()
elseif (CMAKE_SYSTEM_NAME MATCHES "Android")
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        if(CMAKE_SIZEOF_VOID_P MATCHES "8")
            set(CMAKE_PREFIX_PATH C:/Qt/6.8.3/android_arm64_v8a)
        endif()
    endif()
else()
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
        set(CMAKE_PREFIX_PATH C:/Qt/5.15.2/mingw81_64)
    elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "arm64")

    elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "arm")
        set(CMAKE_PREFIX_PATH C:/Qt/5.15.2/mingw81_64)
    elseif (CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64")
        set(SYSTEM_NAME arm64)
    else()
        set(SYSTEM_NAME win32)
        set(CMAKE_PREFIX_PATH C:/Qt/5.15.2/mingw81_64)
    endif()
endif()
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(LIB_SUFF d)
endif()
set(PLOT_LIB plot${LIB_SUFF})
message("CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH}")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui Widgets PrintSupport OpenGL)
find_package(Qt${QT_VERSION_MAJOR}  REQUIRED COMPONENTS Core Gui Widgets PrintSupport OpenGL)


set(QWindowKit_DIR ${CMAKE_INSTALL_PREFIX}/lib/cmake/QWindowKit)
find_package(QWindowKit COMPONENTS Core Widgets REQUIRED)


add_subdirectory(nodes)
add_subdirectory(qwindowkit)
add_subdirectory(elf)
# 添加子目录
add_subdirectory(plot)
add_subdirectory(plug)
add_subdirectory(testplot)

add_subdirectory(app)
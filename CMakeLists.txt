cmake_minimum_required(VERSION 3.16)
project(plot VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)


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



find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui Widgets PrintSupport)
find_package(Qt${QT_VERSION_MAJOR}  REQUIRED COMPONENTS Core Gui Widgets PrintSupport)

# 添加子目录
add_subdirectory(plot)
add_subdirectory(testplot)

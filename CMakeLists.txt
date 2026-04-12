cmake_minimum_required(VERSION 3.16)
project(plot VERSION 0.1 LANGUAGES CXX)
add_compile_options(
        $<$<CXX_COMPILER_ID:MSVC>:/utf-8>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-finput-charset=UTF-8>
)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O1")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O1")
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
# 设置运行时路径
if(WIN32)
    # 添加 Qt DLL 目录到运行时路径
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /LIBPATH:\"C:/Qt/5.15.2/msvc2019_64/bin\"")
    
    # 复制 Qt DLL 到输出目录（构建时自动复制）
    # 根据需要添加其他 Qt DLL
endif()

if(BUILD_DEBUG_POSTFIX_D)
    set(CMAKE_DEBUG_POSTFIX "d")
    set(CMAKE_RELEASE_POSTFIX "")
    set(CMAKE_RELWITHDEBINFO_POSTFIX "rd")
    set(CMAKE_MINSIZEREL_POSTFIX "s")
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
set(Protobuf_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/common/bus/protoc")
find_package(Protobuf REQUIRED)
#if (Protobuf_FOUND)
#    message(STATUS "Protobuf found: ${Protobuf_VERSION}")
#    message(STATUS "Protobuf include dir: ${Protobuf_INCLUDE_DIRS}")
#    message(STATUS "Protobuf library: ${Protobuf_LIBRARIES}")
#    message(STATUS "Protoc path: ${Protobuf_PROTOC_EXECUTABLE}")
#endif()
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui Widgets PrintSupport OpenGL Quick QuickWidgets Sql)
find_package(Qt${QT_VERSION_MAJOR}  REQUIRED COMPONENTS Core Gui Widgets PrintSupport OpenGL Quick QuickWidgets Sql)
#message(STATUS "OpenGL include dir: ${OPENGL_INCLUDE_DIR}")
#message(STATUS "OpenGL libraries : ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY}")
# 添加子目录


include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/common
        ${CMAKE_CURRENT_SOURCE_DIR}/common/bus/protoc/include
        ${CMAKE_CURRENT_SOURCE_DIR}/plug/page/plot
        ${CMAKE_CURRENT_SOURCE_DIR}/plug/io
        ${CMAKE_CURRENT_SOURCE_DIR}/QtPropertyBrowser
)

add_subdirectory(nodes)
add_subdirectory(qwindowkit)
add_subdirectory(elf)
add_subdirectory(ads)
add_subdirectory(QtPropertyBrowser)
add_subdirectory(demo)
# 添加子目录
add_subdirectory(plug/page/plot)
add_subdirectory(plug)
add_subdirectory(testplot)
#
add_subdirectory(app)

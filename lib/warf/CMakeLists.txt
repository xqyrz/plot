cmake_minimum_required(VERSION 3.10)

project(dwarfapp LANGUAGES CXX)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libdwarf)

add_library(${PROJECT_NAME} SHARED dwarfapp.cpp)

# libdwarf 的 CMake 目标名是 dwarf-static（BUILD_NON_SHARED 默认 ON）
target_link_libraries(${PROJECT_NAME} PRIVATE dwarf-static)

# libdwarf 的 include 不会自动传播到外层，需手动加头文件路径
target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/libdwarf/src/lib/libdwarf)
target_compile_options(${PROJECT_NAME} PRIVATE /utf-8)
# 链接静态库 libdwarf(dwarf-static)，必须定义 LIBDWARF_STATIC，
# 否则 DW_API 会展开成 dllimport，导致 __imp_dwarf_* 链接失败
target_compile_definitions(${PROJECT_NAME} PRIVATE LIBDWARF_STATIC)

# ---- 命令行验证程序（可选）： dwarfapp_test <file.axf> ----
# 直接编译 dwarfapp.cpp 并链接静态库，避免依赖 DLL 导入库
add_executable(dwarfapp_test main.cpp dwarfapp.cpp)
target_link_libraries(dwarfapp_test PRIVATE dwarf-static)
target_include_directories(dwarfapp_test PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/libdwarf/src/lib/libdwarf)
target_compile_options(dwarfapp_test PRIVATE /utf-8)
target_compile_definitions(dwarfapp_test PRIVATE LIBDWARF_STATIC)

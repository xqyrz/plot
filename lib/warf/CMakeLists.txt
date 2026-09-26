cmake_minimum_required(VERSION 3.10)
project(dwarfapp LANGUAGES CXX)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libdwarf)

# 构建 dwarfapp 动态库
add_library(${PROJECT_NAME} SHARED dwarfapp.cpp)

# 链接 libdwarf 静态目标 dwarf-static
target_link_libraries(${PROJECT_NAME} PRIVATE dwarf-static)

# 头文件搜索路径
target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/libdwarf/src/lib/libdwarf
)
target_include_directories(dwarfapp PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>     # 树内用
        $<INSTALL_INTERFACE:include>)                      # 安装后用
add_library(dwarfapp::dwarfapp ALIAS dwarfapp)
# 编译选项与宏
target_compile_options(${PROJECT_NAME} PRIVATE /utf-8)
target_compile_definitions(${PROJECT_NAME} PRIVATE LIBDWARF_STATIC)




# ===================== 【对外暴露头文件】=====================
# 注意：把对外的头文件（dwarfapp.h）设置为 PUBLIC，供外部使用者
# 假设你的对外头文件是 dwarfapp.h，放在当前目录
target_include_directories(${PROJECT_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)

# ===================== 【INSTALL 安装规则】=====================
# 1. 安装库目标，并导出到 dwarfappTargets
install(TARGETS ${PROJECT_NAME}
        EXPORT dwarfappTargets
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)

# 2. 安装对外头文件（dwarfapp.h）
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/dwarfapp.h
        DESTINATION include
)

# 3. 导出目标文件（供 find_package 使用）
install(EXPORT dwarfappTargets
        FILE dwarfappTargets.cmake
        NAMESPACE dwarfapp::
        DESTINATION lib/cmake/dwarfapp
)

# ===================== 【生成 Config 与版本文件】=====================
include(CMakePackageConfigHelpers)

# 版本文件，这里写一个版本号，你按需修改
set(DWARFAPP_VERSION "1.0.0")
write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/dwarfappConfigVersion.cmake"
        VERSION ${DWARFAPP_VERSION}
        COMPATIBILITY SameMajorVersion
)

# Config 文件
configure_package_config_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/dwarfappConfig.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/dwarfappConfig.cmake"
        INSTALL_DESTINATION lib/cmake/dwarfapp
)

# 安装 Config 文件
install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/dwarfappConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/dwarfappConfigVersion.cmake"
        DESTINATION lib/cmake/dwarfapp
)

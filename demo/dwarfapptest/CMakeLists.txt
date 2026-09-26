cmake_minimum_required(VERSION 3.16)
project(dwarfapp_test VERSION 0.1 LANGUAGES CXX)

# 与 dwarfapp 同属一个构建树（顶层 add_subdirectory(lib) 已建 dwarfapp 目标），
# 直接链接同树目标 dwarfapp，其 PUBLIC include 会带上 dwarfapp.h。
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE dwarfapp::dwarfapp)

# 构建后自动把 dwarfappd.dll 复制到 exe 同目录，避免运行时 0xC0000135 找不到 DLL
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:dwarfapp>"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>")

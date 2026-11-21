cmake_minimum_required(VERSION 3.16)
project(plotpage VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O1")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O1")
add_definitions(-DQCUSTOMPLOT_USE_OPENGL)

file(GLOB_RECURSE SRC_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.ui"
)
file(GLOB_RECURSE exclude_main "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
list(REMOVE_ITEM SRC_FILES ${exclude_main})
add_library(${PROJECT_NAME} SHARED
        ${PlugBase_SRC_FILES}
        ${PAGE_SRC_FILES}
        ${SRC_FILES}
        )

# 让本 DLL 导出 PlotView 等类（供 opencvTest 等目标直接链接使用）
target_compile_definitions(${PROJECT_NAME} PRIVATE
        PLOTPAGE_LIBRARY
        INTERFACEBASE_EXPORTS
        QCUSTOMPLOT_COMPILE_LIBRARY# 编译本 DLL 时，QCP 类按 dllexport
)

target_include_directories(${PROJECT_NAME}
        PUBLIC
        .   # 头文件所在目录
)
if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    set(OPENGL_LIB OpenGL::GL OpenGL::GLU)

endif()

target_link_libraries(${PROJECT_NAME}
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::PrintSupport
        Qt${QT_VERSION_MAJOR}::OpenGL
        ${OPENGL_LIB}
        mdb::mdb
)


if(WIN32)
    target_link_libraries(${PROJECT_NAME} opengl32 glu32)
endif()

install(TARGETS ${PROJECT_NAME}
        ARCHIVE DESTINATION lib     # 静态库 (.a / .lib)
        LIBRARY DESTINATION lib     # 共享库 (.so / .dll)
        RUNTIME DESTINATION plugins
)


add_executable(${PROJECT_NAME}Test main.cpp)
target_link_libraries(${PROJECT_NAME}Test
        ${PROJECT_NAME}
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Widgets
)
set_target_properties(${PROJECT_NAME}Test PROPERTIES
    VS_DEBUGGER_ENVIRONMENT "PATH=${QT_DLL_PATH};%PATH%"
)
project(opencvTest)
cmake_minimum_required(VERSION 3.16)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
file(GLOB_RECURSE SRC_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.ui"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.qrc"
)
add_executable(${PROJECT_NAME}
        ${SRC_FILES}
)
#find_package(qView REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Network
        ${OpenCV_LIBS}
        QtNodes
        qView
        plotpage
)

target_include_directories(${PROJECT_NAME} PRIVATE
        ${OpenCV_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# 本目标通过 plotpage.dll 的导入库使用 InterfaceBase，需声明为 dllimport
target_compile_definitions(${PROJECT_NAME} PRIVATE INTERFACEBASE_DLL_IMPORT)


if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(OPENCV_DLL "${OpenCV_ROOT}/x64/vc16/bin/opencv_world500d.dll")
else()
    set(OPENCV_DLL "${OpenCV_ROOT}/x64/vc16/bin/opencv_world500.dll")
endif()

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${OPENCV_DLL}"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/"
        # 运行时必须加载与导入库同版本的 plotpaged.dll，否则会出现
        # 0xC0000139 (STATUS_ENTRYPOINT_NOT_FOUND)：加载到旧副本里找不到 PlotView 等导出
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:plotpage>"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/rec"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/rec"
)



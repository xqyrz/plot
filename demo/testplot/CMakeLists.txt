cmake_minimum_required(VERSION 3.16)
set(APP_NAME testplot)


file(GLOB_RECURSE SRC_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.ui"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.qrc"
)

add_executable(${APP_NAME} ${SRC_FILES})

target_link_libraries(${APP_NAME}
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::PrintSupport
        ${PLOT_LIB}
)

target_compile_definitions(${APP_NAME}
        PRIVATE
        PROJECT_NAME="${APP_NAME}"
)
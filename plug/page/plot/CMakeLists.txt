cmake_minimum_required(VERSION 3.16)
set(PLOT_LIB plotpage)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O1")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O1")
add_definitions(-DQCUSTOMPLOT_USE_OPENGL)

file(GLOB_RECURSE SRC_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.ui"
)

add_library(${PLOT_LIB} SHARED ${SRC_FILES}
        )

target_include_directories(${PLOT_LIB}
        PUBLIC
        .   # 头文件所在目录
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

install(TARGETS ${PLOT_LIB}
        ARCHIVE DESTINATION lib     # 静态库 (.a / .lib)
        LIBRARY DESTINATION lib     # 共享库 (.so / .dll)
        RUNTIME DESTINATION plugins
)

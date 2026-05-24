project(testplot3d VERSION 0.1 LANGUAGES CXX)
set( CMAKE_AUTORCC ON )
add_executable(testplot3d WIN32
        main.cpp
        glwidget.cpp
        glwidget.h
)
# message(STATUS "CMAKE_INSTALL_PREFIX: ${CMAKE_INSTALL_PREFIX}/lib")
#set(qwtplot3d_DIR "F:/plot/install/lib/cmake/qwtplot3d")
#find_package(qwtplot3d REQUIRED)
find_package(OpenGL REQUIRED)
target_link_libraries(testplot3d
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Widgets
        qwtplot3d::qwtplot3d
        OpenGL::GL
        OpenGL::GLU
)
install(TARGETS testplot3d
        ARCHIVE DESTINATION bin     # 静态库 (.a / .lib)
        LIBRARY DESTINATION bin     # 共享库 (.so / .dll)
        RUNTIME DESTINATION bin
)

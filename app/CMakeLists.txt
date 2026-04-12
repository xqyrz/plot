cmake_minimum_required(VERSION 3.16)
set(APP_NAME app)
file(GLOB_RECURSE SRC_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.qrc"
)
#set(QWindowKit_DIR ${CMAKE_INSTALL_PREFIX}/lib/cmake/QWindowKit)
#find_package(QWindowKit COMPONENTS Core Widgets REQUIRED)
include_directories(${CMAKE_SOURCE_DIR}/shared ${CMAKE_SOURCE_DIR}/src )
#message("SRC_FILES ${SRC_FILES}")
add_executable(${APP_NAME} ${SRC_FILES}
        src/interface/manage.cpp
        src/interface/manage.h
        src/page/ioview.cpp
        src/page/ioview.h
        #        src/page/node/nodemodel.cpp
#        src/page/node/nodemodel.h
#        src/page/node/nodedata.cpp
#        src/page/node/nodedata.h
#        src/log/sflogger.hpp
)

target_link_libraries(${APP_NAME}
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Sql
        Qt${QT_VERSION_MAJOR}::PrintSupport
        QWindowKit::Core
        QWindowKit::Widgets
        qtadvanceddocking-qt${QT_VERSION_MAJOR}
        QtNodes
        ${PLOT_LIB}
        QtPropertyBrower
)
target_include_directories(${APP_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${IO_PATH}
        ${IOAPP_PATH}
)
target_compile_definitions(${APP_NAME}
        PRIVATE
        PROJECT_NAME="${APP_NAME}"
)

install(TARGETS ${APP_NAME}
        ARCHIVE DESTINATION bin     # 静态库 (.a / .lib)
        LIBRARY DESTINATION bin     # 共享库 (.so / .dll)
        RUNTIME DESTINATION bin
)

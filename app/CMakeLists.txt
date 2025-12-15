cmake_minimum_required(VERSION 3.16)
set(APP_NAME app)
file(GLOB_RECURSE SRC_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.qrc"
)
#set(QWindowKit_DIR ${CMAKE_INSTALL_PREFIX}/lib/cmake/QWindowKit)
#find_package(QWindowKit COMPONENTS Core Widgets REQUIRED)
include_directories(${CMAKE_SOURCE_DIR}/shared ${CMAKE_SOURCE_DIR}/src)

add_executable(${APP_NAME} ${SRC_FILES}
        src/page/maindock.cpp
        src/page/maindock.h)

target_link_libraries(${APP_NAME}
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::PrintSupport
        QWindowKit::Core
        QWindowKit::Widgets
        qtadvanceddocking-qt${QT_VERSION_MAJOR}
)
target_include_directories(${APP_NAME}
        PUBLIC
        ${IO_PATH}
        ${IOAPP_PATH}
)
target_compile_definitions(${APP_NAME}
        PRIVATE
        PROJECT_NAME="${APP_NAME}"
)

install(TARGETS ${ATCLIENT_LIB}
        ARCHIVE DESTINATION bin     # 静态库 (.a / .lib)
        LIBRARY DESTINATION lib     # 共享库 (.so / .dll)
        RUNTIME DESTINATION bin
)

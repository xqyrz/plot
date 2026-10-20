cmake_minimum_required(VERSION 3.16)
project(iowpage VERSION 0.1 LANGUAGES CXX)
file(GLOB_RECURSE SRC_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.ui"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.qrc"
)
# 插件CMakeLists.txt
# 编译时生成时间字符串
string(TIMESTAMP BUILD_TIMESTAMP "%Y-%m-%d %H:%M:%S")

# 生成metadata.json，里面增加build_time字段
configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/iowpage.in.json
        ${CMAKE_CURRENT_SOURCE_DIR}/iowpage.json
        @ONLY
)

list(FILTER SRC_FILES EXCLUDE REGEX "main\\.cpp$")
add_library(${PROJECT_NAME} SHARED
        ${PlugBase_SRC_FILES}
        ${PAGE_SRC_FILES}
        ${SRC_FILES}
)
#add_executable(${IOPAGE}
#                ${SRC_FILES}
#               main.c
#)
target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${IO_PATH}
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Widgets
        protobuf::libprotobuf
        #mdb::mdb
)




#if(WIN32)
#    target_link_libraries(${JLINKARM} ws2_32 mswsock)
#endif()
install(TARGETS ${PROJECT_NAME}
        ARCHIVE DESTINATION lib     # 静态库 (.a / .lib)
        LIBRARY DESTINATION lib     # 共享库 (.so / .dll)
        RUNTIME DESTINATION plugins
)




#add_executable(${PROJECT_NAME}test
#        ${SRC_FILES}
#        #${PlugBase_SRC_FILES_H}
#        #${IO_SRC_FILES_H}
#        #${IOAPP_SRC_FILES_H}
#        #${PAGE_SRC_FILES_H}
#        main.cpp
#)
#target_include_directories(${PROJECT_NAME}test
#        PRIVATE
#        ${IO_PATH}
#        ${CMAKE_CURRENT_SOURCE_DIR}
#)
#target_link_libraries(${PROJECT_NAME}test
#        Qt${QT_VERSION_MAJOR}::Core
#        Qt${QT_VERSION_MAJOR}::Widgets
#        protobuf::libprotobuf
#
#)
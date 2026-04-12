set(IOPAGE iowpage)
file(GLOB_RECURSE SRC_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.ui"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.qrc"


)
#add_library(${IOPAGE} SHARED
#        ${SRC_FILES}
#)
add_executable(${IOPAGE}
                ${SRC_FILES}
)
target_include_directories(${IOPAGE}
        PUBLIC
        ${IO_PATH}
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${IOPAGE}
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Widgets
        protobuf::libprotobuf
)
#if(WIN32)
#    target_link_libraries(${JLINKARM} ws2_32 mswsock)
#endif()
install(TARGETS ${IOPAGE}
        ARCHIVE DESTINATION lib     # 静态库 (.a / .lib)
        LIBRARY DESTINATION lib     # 共享库 (.so / .dll)
        RUNTIME DESTINATION plugins
)

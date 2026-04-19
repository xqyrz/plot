cmake_minimum_required(VERSION 3.16)
add_library(${IO_LIB} STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/iointerface.h
)


target_link_libraries(${IO_LIB}
        Qt${QT_VERSION_MAJOR}::Core
)
if(WIN32)
    target_link_libraries(${IO_LIB} ws2_32 mswsock)
endif()
install(TARGETS ${IO_LIB}
        ARCHIVE DESTINATION lib     # 静态库 (.a / .lib)
        LIBRARY DESTINATION lib     # 共享库 (.so / .dll)
        RUNTIME DESTINATION plugins
)

add_subdirectory(asio/tcpserver)
add_subdirectory(asio/tcpclient)
add_subdirectory(asio/udp)
add_subdirectory(asio/port)
add_subdirectory(jlink)

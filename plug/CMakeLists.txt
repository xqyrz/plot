
# 添加子目录
#add_subdirectory(io)
project(Plug)


set(IO_PATH ${CMAKE_CURRENT_SOURCE_DIR}/io)
set(ATCPSERVER_LIB atcpserver)
set(ATCLIENT_LIB atcpclient)
set(AUDP_LIB audp)
set(APORT_LIB aport)
set(JLINKARM ajlinkarm)

set(SELFIOAPP_LIB selfioapp)
set(VOFA_APP vofaapp)

set(IOAPP_PATH ${CMAKE_CURRENT_SOURCE_DIR}/ioapp)
MESSAGE("CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}")
include_directories(${CMAKE_CURRENT_SOURCE_DIR})


add_subdirectory(io/asio/tcpserver)
add_subdirectory(io/asio/tcpclient)
add_subdirectory(io/asio/udp)
add_subdirectory(io/asio/port)
add_subdirectory(io/jlink)


add_subdirectory(ioapp/selfapp)
add_subdirectory(ioapp/vofa)

add_subdirectory(testplug)
add_subdirectory(testmavlink)
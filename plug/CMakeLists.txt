
# 添加子目录
#add_subdirectory(io)
project(Plug)
file(GLOB Base_SRC_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)


set(IO_PATH ${CMAKE_CURRENT_SOURCE_DIR}/io)
set(IO_LIB io)
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

add_subdirectory(io)


add_subdirectory(ioapp)


add_subdirectory(page)


#add_subdirectory(testplug)
add_subdirectory(testmavlink)
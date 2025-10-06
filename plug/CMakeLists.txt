
# 添加子目录
#add_subdirectory(io)
project(Plug)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(LIB_SUFF d)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")

endif()
set(IO_PATH ${CMAKE_CURRENT_SOURCE_DIR}/io)
set(ATCPSERVER_LIB atcpserver${LIB_SUFF})
set(ATCLIENT_LIB atcpclient${LIB_SUFF})
set(AUDP_LIB audp${LIB_SUFF})


set(IOAPP_PATH ${CMAKE_CURRENT_SOURCE_DIR}/ioapp)
set(SELFIOAPP_LIB selfioapp${LIB_SUFF})



add_subdirectory(io/asio/tcpserver)
add_subdirectory(io/asio/tcpclient)
add_subdirectory(io/asio/udp)


add_subdirectory(ioapp/selfapp)

add_subdirectory(testplug)
add_subdirectory(testmavlink)
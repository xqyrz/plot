
# 添加子目录
#add_subdirectory(io)
project(Plug)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(ATCPSERVER_LIB atcpserverd)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(ATCPSERVER_LIB atcpserver)
endif()

set(IO_PATH ${CMAKE_CURRENT_SOURCE_DIR}/io)
add_subdirectory(io/asio/tcpserver)
add_subdirectory(testplug)
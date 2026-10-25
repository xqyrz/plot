cmake_minimum_required(VERSION 3.16)
set(CMAKE_FOLDER "${CMAKE_FOLDER}/io")

add_subdirectory(asio/tcpserver)
add_subdirectory(asio/tcpclient)
add_subdirectory(asio/udp)
add_subdirectory(asio/port)
add_subdirectory(jlink)

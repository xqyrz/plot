
# 添加子目录
#add_subdirectory(io)
project(Plug)
set(CMAKE_FOLDER "PLUG")
if(BUILD_DEBUG_POSTFIX_D)
    set(CMAKE_DEBUG_POSTFIX "d")
    set(CMAKE_RELEASE_POSTFIX "")
    set(CMAKE_RELWITHDEBINFO_POSTFIX "rd")
    set(CMAKE_MINSIZEREL_POSTFIX "s")
endif()


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
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${PLUG_INCLUDE_PATH}
)

add_subdirectory(io)


add_subdirectory(ioapp)


add_subdirectory(page)


#add_subdirectory(testplug)
#add_subdirectory(testmavlink)
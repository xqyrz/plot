cmake_minimum_required(VERSION 3.16)
set(APP_NAME testplug)
file(GLOB_RECURSE SRC_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)

add_executable(${APP_NAME} ${SRC_FILES}
)

target_link_libraries(${APP_NAME}
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::PrintSupport
        ${PLOT_LIB}

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

add_dependencies(${APP_NAME} ${ATCPSERVER_LIB})
add_dependencies(${APP_NAME} ${SELFIOAPP_LIB})
add_dependencies(${APP_NAME} ${ATCLIENT_LIB})
add_dependencies(${APP_NAME} ${AUDP_LIB})
add_dependencies(${APP_NAME} ${PLOT_LIB})
add_dependencies(${APP_NAME} ${JLINKARM})

install(TARGETS ${ATCLIENT_LIB}
        ARCHIVE DESTINATION bin     # 静态库 (.a / .lib)
        LIBRARY DESTINATION lib     # 共享库 (.so / .dll)
        RUNTIME DESTINATION bin
)
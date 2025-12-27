cmake_minimum_required(VERSION 3.16)
set(APP_NAME testmavlink)
file(GLOB_RECURSE SRC_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
        "${IOAPP_PATH}/mavlink/*.cpp"
        "${IOAPP_PATH}/mavlink/*.h"
        "${IOAPP_PATH}/mavlink/*.hpp"
)

add_executable(${APP_NAME} ${SRC_FILES}
)

target_link_libraries(${APP_NAME}
        Qt${QT_VERSION_MAJOR}::Core
)

target_compile_definitions(${APP_NAME}
        PRIVATE
        PROJECT_NAME="${APP_NAME}"
)

add_dependencies(${APP_NAME} ${ATCPSERVER_LIB})
add_dependencies(${APP_NAME} ${SELFIOAPP_LIB})

install(TARGETS ${APP_NAME}
        ARCHIVE DESTINATION bin     # 静态库 (.a / .lib)
        LIBRARY DESTINATION bin     # 共享库 (.so / .dll)
        RUNTIME DESTINATION bin
)

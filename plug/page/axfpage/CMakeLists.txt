cmake_minimum_required(VERSION 3.16)
project(axfpage VERSION 0.1 LANGUAGES CXX)

add_library(${PROJECT_NAME} SHARED
        ${Base_SRC_FILES}
        ${PAGE_SRC_FILES}
        axftree.h
        axftree.cpp
        axfmodel.h
        axfmodel.cpp
        axfpage.h
        axfpage.cpp
        Axfui.cpp
        Axfui.h
        Axfui.ui
)

target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${IO_PATH}
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Widgets
        dwarfapp::dwarfapp
)
#if(WIN32)
#    target_link_libraries(${JLINKARM} ws2_32 mswsock)
#endif()
install(TARGETS ${PROJECT_NAME}
        ARCHIVE DESTINATION lib     # 静态库 (.a / .lib)
        LIBRARY DESTINATION lib     # 共享库 (.so / .dll)
        RUNTIME DESTINATION plugins
)


add_executable(${PROJECT_NAME}test
        ${Base_SRC_FILES}
        ${PAGE_SRC_FILES}
        axftree.h
        axftree.cpp
        axfmodel.h
        axfmodel.cpp
        axfpage.h
        axfpage.cpp
        Axfui.cpp
        Axfui.h
        Axfui.ui
)
target_link_libraries(${PROJECT_NAME}test
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Widgets
        dwarfapp::dwarfapp
)
install(TARGETS ${PROJECT_NAME}test
        ARCHIVE DESTINATION bin     # 静态库 (.a / .lib)
        LIBRARY DESTINATION bin     # 共享库 (.so / .dll)
        RUNTIME DESTINATION bin
)
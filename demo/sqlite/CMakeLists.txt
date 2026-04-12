project(sqlite VERSION 0.1 LANGUAGES CXX)

add_executable(sqlite
        main.cpp
        dbm.cpp
        dbm.h
)
target_link_libraries(sqlite
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Sql
)

install(TARGETS sqlite
        ARCHIVE DESTINATION bin     # 静态库 (.a / .lib)
        LIBRARY DESTINATION bin     # 共享库 (.so / .dll)
        RUNTIME DESTINATION bin
)

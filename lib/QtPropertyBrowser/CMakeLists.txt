# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:



cmake_minimum_required(VERSION 3.16)

project(QtPropertyBrower VERSION 0.1 LANGUAGES CXX)

file(GLOB _IMPL_HDRS *.h)
file(GLOB _PUBLIC_HDRS Qt*)
add_library(${PROJECT_NAME} STATIC
        qtbuttonpropertybrowser.cpp
        qteditorfactory.cpp
        qtgroupboxpropertybrowser.cpp
        qtpropertybrowser.cpp
        qtpropertybrowserutils.cpp
        qtpropertymanager.cpp
        qttreepropertybrowser.cpp
        qtvariantproperty.cpp
  ${_UI_SRCS}
        qtpropertybrowser.qrc
  ${_IMPL_HDRS}
  )
if(MSVC)
set_target_properties(${PROJECT_NAME} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)

######################### Installation Stuff ###########################\
include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})
install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}Targets
        ARCHIVE DESTINATION lib     # 静态库 (.a / .lib)
        LIBRARY DESTINATION lib     # 共享库 (.so / .dll)
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
)

# 安装头文件到 include/QtPropertyBrowser 目录
install(FILES ${HEAD_FILES}
        DESTINATION include/${PROJECT_NAME}
)
install(EXPORT ${PROJECT_NAME}Targets
        FILE ${PROJECT_NAME}Targets.cmake
        NAMESPACE ${PROJECT_NAME}::
        DESTINATION ${INSTALL_CONFIGDIR}
)

include(CMakePackageConfigHelpers)


write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
        VERSION 1.0.0
        COMPATIBILITY AnyNewerVersion
)

# 关键：这里使用内置的简单模板，不需要你创建任何 .in 文件
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
        "include(\${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}Targets.cmake)\n"
)

install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
        DESTINATION ${INSTALL_CONFIGDIR}
)
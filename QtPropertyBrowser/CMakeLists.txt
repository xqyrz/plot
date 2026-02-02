# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:


file(GLOB _IMPL_HDRS *.h)
file(GLOB _PUBLIC_HDRS Qt*)


set(QtPropertyBrower_lib "QtPropertyBrower")

add_library(${QtPropertyBrower_lib}
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

target_link_libraries(${QtPropertyBrower_lib} Qt5::Widgets)

######################### Installation Stuff ###########################
install(TARGETS ${TARGET_NAME}
        ARCHIVE DESTINATION bin     # 静态库 (.a / .lib)
        LIBRARY DESTINATION bin     # 共享库 (.so / .dll)
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
)

# 安装头文件到 include/QtPropertyBrowser 目录
install(
        FILES
        ${_IMPL_HDRS}
        DESTINATION
        include/QtPropertyBrowser
)
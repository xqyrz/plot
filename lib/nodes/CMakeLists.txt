set(CPP_SOURCE_FILES
        src/AbstractGraphModel.cpp
        src/AbstractNodeGeometry.cpp
        src/BasicGraphicsScene.cpp
        src/ConnectionGraphicsObject.cpp
        src/ConnectionState.cpp
        src/ConnectionStyle.cpp
        src/DataFlowGraphModel.cpp
        src/DataFlowGraphicsScene.cpp
        src/DefaultConnectionPainter.cpp
        src/DefaultHorizontalNodeGeometry.cpp
        src/DefaultNodePainter.cpp
        src/DefaultVerticalNodeGeometry.cpp
        src/Definitions.cpp
        src/GraphicsView.cpp
        src/GraphicsViewStyle.cpp
        src/NodeConnectionInteraction.cpp
        src/NodeDelegateModel.cpp
        src/NodeDelegateModelRegistry.cpp
        src/NodeGraphicsObject.cpp
        src/NodeState.cpp
        src/NodeStyle.cpp
        src/StyleCollection.cpp
        src/UndoCommands.cpp
        src/locateNode.cpp
        resources/resources.qrc
)

set(HPP_HEADER_FILES
        include/QtNodes/internal/AbstractConnectionPainter.hpp
        include/QtNodes/internal/AbstractGraphModel.hpp
        include/QtNodes/internal/AbstractNodeGeometry.hpp
        include/QtNodes/internal/AbstractNodePainter.hpp
        include/QtNodes/internal/BasicGraphicsScene.hpp
        include/QtNodes/internal/Compiler.hpp
        include/QtNodes/internal/ConnectionGraphicsObject.hpp
        include/QtNodes/internal/ConnectionIdHash.hpp
        include/QtNodes/internal/ConnectionIdUtils.hpp
        include/QtNodes/internal/ConnectionState.hpp
        include/QtNodes/internal/ConnectionStyle.hpp
        include/QtNodes/internal/DataFlowGraphicsScene.hpp
        include/QtNodes/internal/DataFlowGraphModel.hpp
        include/QtNodes/internal/Definitions.hpp
        include/QtNodes/internal/Export.hpp
        include/QtNodes/internal/GraphicsView.hpp
        include/QtNodes/internal/GraphicsViewStyle.hpp
        include/QtNodes/internal/locateNode.hpp
        include/QtNodes/internal/NodeData.hpp
        include/QtNodes/internal/NodeDelegateModel.hpp
        include/QtNodes/internal/NodeDelegateModelRegistry.hpp
        include/QtNodes/internal/NodeGraphicsObject.hpp
        include/QtNodes/internal/NodeState.hpp
        include/QtNodes/internal/NodeStyle.hpp
        include/QtNodes/internal/OperatingSystem.hpp
        include/QtNodes/internal/QStringStdHash.hpp
        include/QtNodes/internal/QUuidStdHash.hpp
        include/QtNodes/internal/Serializable.hpp
        include/QtNodes/internal/Style.hpp
        include/QtNodes/internal/StyleCollection.hpp
        include/QtNodes/internal/DefaultConnectionPainter.hpp
        include/QtNodes/internal/DefaultHorizontalNodeGeometry.hpp
        include/QtNodes/internal/DefaultNodePainter.hpp
        include/QtNodes/internal/DefaultVerticalNodeGeometry.hpp
        include/QtNodes/internal/NodeConnectionInteraction.hpp
        include/QtNodes/internal/UndoCommands.hpp
        ../../app/main.cpp
)


set(DEFAULT_PREFIX "${CMAKE_SOURCE_DIR}/install")
set(CMAKE_INSTALL_PREFIX "${DEFAULT_PREFIX}"
        CACHE PATH "Installation directory" FORCE)

# If we want to give the option to build a static library,
# set BUILD_SHARED_LIBS option to OFF
add_library(QtNodes
        ${CPP_SOURCE_FILES}
        ${HPP_HEADER_FILES}
)

add_library(QtNodes::QtNodes ALIAS QtNodes)
# 5. 设置静态库属性
set_target_properties(QtNodes PROPERTIES
        POSITION_INDEPENDENT_CODE ON  # 允许链接到共享库
        CXX_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN ON
)

# 6. 静态库不需要导出宏
target_compile_definitions(QtNodes
        PUBLIC
        $<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:QT_NODES_STATIC>
)

target_include_directories(QtNodes
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/QtNodes/internal>
)

target_link_libraries(QtNodes
        PUBLIC
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::OpenGL
)

target_compile_definitions(QtNodes
        PUBLIC
        $<IF:$<BOOL:${BUILD_SHARED_LIBS}>, NODE_EDITOR_SHARED, NODE_EDITOR_STATIC>
        PRIVATE
        NODE_EDITOR_EXPORTS
        #NODE_DEBUG_DRAWING
        QT_NO_KEYWORDS
)


target_compile_options(QtNodes
        PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4 /wd4127 /EHsc /utf-8>
        $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra>
        $<$<CXX_COMPILER_ID:AppleClang>:-Wall -Wextra -Werror>
)
if(NOT "${CMAKE_CXX_SIMULATE_ID}" STREQUAL "MSVC")
    # Clang-Cl on MSVC identifies as "Clang" but behaves more like MSVC:
    target_compile_options(QtNodes
            PRIVATE
            $<$<CXX_COMPILER_ID:Clang>:-Wall -Wextra>
    )
endif()

if(QT_NODES_DEVELOPER_DEFAULTS)
    target_compile_features(QtNodes PUBLIC cxx_std_14)
    set_target_properties(QtNodes PROPERTIES CXX_EXTENSIONS OFF)
endif()


set_target_properties(QtNodes
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

###############
# Installation
##

include(GNUInstallDirs)

set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/QtNodes)

install(TARGETS QtNodes
        EXPORT QtNodesTargets
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY include
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT QtNodesTargets
        FILE QtNodesTargets.cmake
        NAMESPACE QtNodes::
        DESTINATION ${INSTALL_CONFIGDIR}
)

include(CMakePackageConfigHelpers)


configure_package_config_file(cmake/QtNodesConfig.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/QtNodesConfig.cmake
        INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/QtNodesConfig.cmake
        DESTINATION ${INSTALL_CONFIGDIR}
)

#add_subdirectory(nodesdemo)
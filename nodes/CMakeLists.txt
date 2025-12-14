set(CPP_SOURCE_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/AbstractGraphModel.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/AbstractNodeGeometry.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/BasicGraphicsScene.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ConnectionGraphicsObject.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ConnectionState.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ConnectionStyle.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/DataFlowGraphModel.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/DataFlowGraphicsScene.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/DefaultConnectionPainter.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/DefaultHorizontalNodeGeometry.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/DefaultNodePainter.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/DefaultVerticalNodeGeometry.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Definitions.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/GraphicsView.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/GraphicsViewStyle.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/NodeConnectionInteraction.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/NodeDelegateModel.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/NodeDelegateModelRegistry.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/NodeGraphicsObject.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/NodeState.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/NodeStyle.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/StyleCollection.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/UndoCommands.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/locateNode.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/resources/resources.qrc
)

set(HPP_HEADER_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/include/QtNodes/internal/AbstractConnectionPainter.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/QtNodes/internal/AbstractGraphModel.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/QtNodes/internal/AbstractNodeGeometry.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/QtNodes/internal/AbstractNodePainter.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/QtNodes/internal/BasicGraphicsScene.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/QtNodes/internal/Compiler.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/QtNodes/internal/ConnectionGraphicsObject.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/QtNodes/internal/ConnectionIdHash.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/QtNodes/internal/ConnectionIdUtils.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/QtNodes/internal/ConnectionState.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/QtNodes/internal/ConnectionStyle.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/QtNodes/internal/DataFlowGraphicsScene.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/QtNodes/internal/DataFlowGraphModel.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/QtNodes/internal/Definitions.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/QtNodes/internal/Export.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/QtNodes/internal/GraphicsView.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/QtNodes/internal/GraphicsViewStyle.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/QtNodes/internal/locateNode.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/QtNodes/internal/NodeData.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/QtNodes/internal/NodeDelegateModel.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/QtNodes/internal/NodeDelegateModelRegistry.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/QtNodes/internal/NodeGraphicsObject.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/QtNodes/internal/NodeState.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/QtNodes/internal/NodeStyle.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/QtNodes/internal/OperatingSystem.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/QtNodes/internal/QStringStdHash.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/QtNodes/internal/QUuidStdHash.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/QtNodes/internal/Serializable.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/QtNodes/internal/Style.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/QtNodes/internal/StyleCollection.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/QtNodes/internal/DefaultConnectionPainter.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/QtNodes/internal/DefaultHorizontalNodeGeometry.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/QtNodes/internal/DefaultNodePainter.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/QtNodes/internal/DefaultVerticalNodeGeometry.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/QtNodes/internal/NodeConnectionInteraction.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/QtNodes/internal/UndoCommands.hpp
        ../app/main.cpp
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

install(DIRECTORY include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT QtNodesTargets
        FILE QtNodesTargets.cmake
        NAMESPACE QtNodes::
        DESTINATION ${INSTALL_CONFIGDIR}
)

include(CMakePackageConfigHelpers)


configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/QtNodesConfig.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/QtNodesConfig.cmake
        INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/QtNodesConfig.cmake
        DESTINATION ${INSTALL_CONFIGDIR}
)

add_subdirectory(nodesdemo)
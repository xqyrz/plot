project(opencvTest)
file(GLOB_RECURSE SRC_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.ui"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.qrc"
)
add_executable(${PROJECT_NAME}
        ${SRC_FILES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})

target_include_directories(${PROJECT_NAME} PRIVATE ${OpenCV_INCLUDE_DIRS})


if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(OPENCV_DLL "${OpenCV_ROOT}/x64/vc16/bin/opencv_world500d.dll")
else()
    set(OPENCV_DLL "${OpenCV_ROOT}/x64/vc16/bin/opencv_world500.dll")
endif()

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${OPENCV_DLL}"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/rec"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/rec"
)



file(GLOB_RECURSE CPPS  ./*.cpp )
file(GLOB_RECURSE HPPS  ./*.hpp )

add_executable(nodes_demo ${CPPS} ${HPPS})

target_link_libraries(nodes_demo QtNodes)

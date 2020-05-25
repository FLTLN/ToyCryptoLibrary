add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/sources")

add_executable(perfs ${PERF_SOURCES})
target_link_libraries(perfs PUBLIC tcl)
add_dependencies(perfs tcl)

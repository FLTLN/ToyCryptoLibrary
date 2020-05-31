add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/sources")

add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests PUBLIC tcl)
add_dependencies(tests tcl)

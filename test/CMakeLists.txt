add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/sources")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/testlib")

add_library(ts STATIC ${TEST_LIB_SOURCES})
target_include_directories(ts PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/testlib)

add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests PUBLIC tcl ts)
add_dependencies(tests tcl ts)

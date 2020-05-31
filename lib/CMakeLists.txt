add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/include")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/sources")

# Target for main library.
add_library(tcl STATIC ${LIB_HEADERS} ${LIB_SOURCES})
target_include_directories(tcl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

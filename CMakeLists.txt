# Main CMake file

cmake_minimum_required(VERSION 3.10)

project("Toy Crypto Library" VERSION 0.1 LANGUAGES C CXX)

message (STATUS "CMAKE_OUTPUT_DIR ...................... " ${CMAKE_BINARY_DIR})
message (STATUS "CMAKE_GENERATOR ....................... " ${CMAKE_GENERATOR})
message (STATUS "CMAKE_C_COMPILER_ID ................... " ${CMAKE_C_COMPILER_ID})
message (STATUS "CMAKE_CXX_COMPILER_ID ................. " ${CMAKE_CXX_COMPILER_ID})

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/lib")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/test")


# Main CMake file.

cmake_minimum_required(VERSION 3.10)

project("Toy Crypto Library" VERSION 0.1 LANGUAGES C CXX)

# Flag for GCC that allow to use AES instructions.
set(CMAKE_C_FLAGS "-maes")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/lib")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/test")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/perf")


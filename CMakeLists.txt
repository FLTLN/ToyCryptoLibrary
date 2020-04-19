# Main CMake file

cmake_minimum_required(VERSION 3.10)

project("Toy Crypto Library")

include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(tcl sources/version.c include/tcl.h)

add_executable(t_version tests/t_version.cpp)
add_dependencies(t_version tcl)

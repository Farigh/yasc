# CMake version
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

# Project name
set(PROJECT_NAME "YASC")

# Declare project
project(${PROJECT_NAME} CXX)

# Compiler settings and options
include(config/GccCompileOptions.cmake)

# Set artifacts output location
set(CMAKE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../out)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIRECTORY}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIRECTORY}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_OUTPUT_DIRECTORY}/bin)

# Source dir
add_subdirectory(src)
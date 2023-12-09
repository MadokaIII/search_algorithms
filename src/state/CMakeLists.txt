cmake_minimum_required(VERSION 3.20)

# Create a static library
add_library(state STATIC state.c state.h)

# Specify where to look for header files for this library and its dependencies
target_include_directories(state PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
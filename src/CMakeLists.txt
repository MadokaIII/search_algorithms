cmake_minimum_required(VERSION 3.20)

# Add the executable SearchAlgorithms
add_executable(SearchAlgorithms main.c algorithms.c algorithms.h)

# Add subdirectories
add_subdirectory(state)

# main depends on state
target_link_libraries(SearchAlgorithms PRIVATE state)
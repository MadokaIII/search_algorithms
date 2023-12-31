cmake_minimum_required(VERSION 3.10)
project(SearchAlgorithms C)

# Doxygen setup
find_package(Doxygen)

# Set the C standard to C11
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_COMPILER "clang")

# Normal compiler flags
add_compile_options(-std=c18 -D_POSIX_C_SOURCE=200809L -Wall -Wextra -Werror -Wfatal-errors -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function -Wno-unused-result)

# Add compiler flags for sanitizers in Debug mode
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer -g -O0")
  set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fsanitize=address -fsanitize=undefined")
endif()

# Export Compile Commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src)

enable_testing()

add_test(NAME test_search COMMAND SearchAlgorithms 10 1 1)

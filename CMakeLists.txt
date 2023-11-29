cmake_minimum_required(VERSION 3.20)

project(SearchAlgorithms C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_COMPILER "clang")
add_compile_options(-std=c18 -D_POSIX_C_SOURCE=200809L -Wall -Wextra -Werror)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_compile_options(-g -O0 -fsanitize=address,undefined)
    add_link_options(-fsanitize=address,undefined)
endif()


add_subdirectory(src)


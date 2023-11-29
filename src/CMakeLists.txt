# Set the source directory
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Collect all source files
file(GLOB SRC "*.c")
file(GLOB HEADERS "*.h")

add_executable(SearchAlgorithms ${SRC} ${HEADERS})

cmake_minimum_required(VERSION 3.24.0)
project(drone-master VERSION 1.0)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
configure_file(app.info app.info)

add_subdirectory(extern)
add_subdirectory(src)
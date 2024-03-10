cmake_minimum_required(VERSION 3.24.0)
project(drone-master VERSION 1.0)

configure_file(app.info app.info)

set(resource_files fonts)
file(COPY ${resource_files} DESTINATION .)

add_subdirectory(extern)
add_subdirectory(src)
add_subdirectory(UI)
add_subdirectory(NetworkManager)

set(app_sources Application.h Application.cc ApplicationInfo.h ApplicationInfo.cc)
add_library(application ${app_sources})
target_link_libraries(application PUBLIC ui network_manager)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
add_executable(main main.cc)
target_link_libraries(main PRIVATE application)
add_subdirectory(UI)

set(app_sources Application.h Application.cc ApplicationInfo.h ApplicationInfo.cc)
add_library(application ${app_sources})
target_link_libraries(application PRIVATE ui glfw glad)
target_compile_features(application PUBLIC cxx_std_20)

add_executable(main main.cc)
target_link_libraries(main PRIVATE application)
# target_include_directories(main PRIVATE ${ASIO_INCLUDE_DIRECTORY})
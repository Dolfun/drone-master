add_subdirectory(UI)

add_library(application Application.h Application.cc)
target_link_libraries(application PRIVATE ui glfw glad)

add_executable(main main.cc)
target_link_libraries(main PRIVATE application)
target_compile_features(main PRIVATE cxx_std_20)
# target_include_directories(main PRIVATE ${ASIO_INCLUDE_DIRECTORY})
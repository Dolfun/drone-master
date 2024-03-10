set(ui_sources WindowManager.h WindowManager.cc UserInterface.h UserInterface.cc)

add_library(ui ${ui_sources})
target_link_libraries(ui PUBLIC imgui)
target_compile_features(ui PUBLIC cxx_std_20)
target_include_directories(ui PUBLIC .)

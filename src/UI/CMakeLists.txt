set(ui_sources WindowManager.cc UserInterface.cc)
set(ui_headers WindowManager.h UserInterface.h)

add_library(ui ${ui_sources} ${ui_headers})
target_link_libraries(ui PRIVATE imgui glad glfw)
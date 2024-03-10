set(imgui_sources
  imgui/imgui.cpp
  imgui/imgui_demo.cpp
  imgui/imgui_draw.cpp
  imgui/imgui_tables.cpp
  imgui/imgui_widgets.cpp
  imgui/backends/imgui_impl_glfw.cpp
  imgui/backends/imgui_impl_opengl3.cpp
  imgui/misc/cpp/imgui_stdlib.cpp
)

set(imgui_headers imgui imgui/backends imgui/misc/cpp)

add_library(imgui ${imgui_sources})
target_link_libraries(imgui PUBLIC glfw glad)
target_include_directories(imgui PUBLIC ${imgui_headers})
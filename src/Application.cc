#include "Application.h"
#include "logger.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <stdexcept>
#include <utility>
#include <format>
#include <map>

constexpr ImVec4 RED    (0.88f, 0.42f, 0.46f, 1.0f);
constexpr ImVec4 GREEN  (0.60f, 0.76f, 0.47f, 1.0f);
constexpr ImVec4 BLUE   (0.38f, 0.69f, 0.94f, 1.0f);
constexpr ImVec4 YELLOW (0.90f, 0.75f, 0.48f, 1.0f);
constexpr ImVec4 PURPLE (0.78f, 0.70f, 0.87f, 1.0f);
constexpr ImVec4 CYAN   (0.34f, 0.71f, 0.76f, 1.0f);
constexpr ImVec4 WHITE  (0.86f, 0.87f, 0.89f, 1.0f);
constexpr ImVec4 BLACK  (0.16f, 0.17f, 0.20f, 1.0f);

Application::Application(const ApplicationInfo& _info) : info(_info) {
  init_glfw();

  if (!gladLoadGL()) {
    throw std::runtime_error("Failed to initialize OpenGL context");
  }

  init_imgui();
}

Application::~Application() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwDestroyWindow(window);
  glfwTerminate();
}

void Application::init_glfw() {
  if (!glfwInit()) {
    throw std::runtime_error("failed to initialize glfw");
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_RESIZABLE , false);

  window = glfwCreateWindow(
    info.window_x, 
    info.window_y, 
    "drone-master", 
    info.fullscreen ? glfwGetPrimaryMonitor() : nullptr, 
    nullptr
  );
  if (!window) {
    throw std::runtime_error("failed to create window");
  }

  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  glfwSetWindowUserPointer(window, static_cast<void*>(this));
  glfwSetKeyCallback(window, key_callback);
}

void Application::init_imgui() {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  auto font_path = "fonts/" + info.font_name;
  io.Fonts->AddFontFromFileTTF(font_path.c_str(), 20.0f);

  ImGui::StyleColorsDark();
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init();
}

void Application::key_callback(GLFWwindow* window, int key, int, int action, int) {
  auto& self = *static_cast<Application*>(glfwGetWindowUserPointer(window));
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

void Application::run() {
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    render_ui();

    ImGui::Render();
    glViewport(0, 0, info.window_x, info.window_y);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
  }
}

void Application::render_ui() {
  render_websocket_ui();
  render_logger_ui();
}

void Application::render_websocket_ui() {
  ImGui::Begin("Websocket");
  ImGui::SetWindowSize(ImVec2(400, 200));

  static std::map<Websocket::status_t, const char*> status_str {
    { Websocket::status_t::connecting, "connecting" },
    { Websocket::status_t::open, "open" },
    { Websocket::status_t::closing, "closing" },
    { Websocket::status_t::closed, "closed" },
  };
  ImGui::Text("Status: %s", status_str[client.get_status()]);

  static std::string uri = info.websocket_uri.c_str();
  ImGui::InputText("uri", &uri);

  if (ImGui::Button("Connect")) {
    client.connect(uri);
  }
  ImGui::SameLine();
  if (ImGui::Button("Close")) {
    client.close();
  }

  ImGui::End();
}

void Application::render_logger_ui() {
  ImGui::Begin("Logger");
  ImGui::SetWindowSize(ImVec2(400, 300));

  static std::map<logger::level_t, std::pair<std::string, ImVec4>> level_info {
    { logger::level_t::info,  { "I", WHITE } },
    { logger::level_t::debug, { "D", GREEN } },
    { logger::level_t::error, { "E", RED } },
  };

  for (const auto& [id, level, tag, line] : logger()) {
    auto [level_str, color] = level_info[level];
    auto line_str = std::format("({}) {} [{}] -> {}\n", id, tag, level_str, line);
    ImGui::TextColored(color, "%s", line_str.c_str());
  }
  
  ImGui::End();
}
#pragma once
#include "ApplicationInfo.h"
#include "Websocket/Client.h"

struct GLFWwindow;

class Application {
public:
  Application(const ApplicationInfo&);
  ~Application();

  Application(const Application&) = delete;
  Application& operator=(const Application&) = delete;
  Application(Application&&) = default;
  Application& operator=(Application&&) = default;

  void run();

private:
  void init_glfw();
  void init_imgui();
  void render_ui();

  ApplicationInfo info;
  GLFWwindow* window;
};
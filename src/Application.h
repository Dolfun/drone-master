#pragma once
#include "ApplicationInfo.h"
#include "Websocket/Client.h"
#include "logger.h"

struct GLFWwindow;

class Application {
public:
  Application(const ApplicationInfo&);
  ~Application();

  Application(const Application&) = delete;
  Application& operator=(const Application&) = delete;
  Application(Application&&) = delete;
  Application& operator=(Application&&) = delete;

  void run();

private:
  void init_glfw();
  void init_imgui();
  void render_ui();
  void render_websocket_ui();
  void render_logger_ui();
  static void key_callback(GLFWwindow*, int, int, int, int);

  ApplicationInfo info;
  GLFWwindow* window;

  Websocket::Client client;
};
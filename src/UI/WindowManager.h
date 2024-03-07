#pragma once

struct GLFWwindow;

class WindowManager {
public:
  WindowManager(int window_x, int window_y, bool fullscreen = false);

  WindowManager(const WindowManager&) = delete;
  WindowManager& operator=(const WindowManager&) = delete;
  WindowManager(WindowManager&&) = default;
  WindowManager& operator=(WindowManager&&) = default;

  ~WindowManager();

  auto handle() { return window; }
  
private:
  GLFWwindow* window;
};
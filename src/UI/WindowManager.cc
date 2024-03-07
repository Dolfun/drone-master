#include "WindowManager.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <stdexcept>
#include <string>

WindowManager::WindowManager(int window_x, int window_y, bool fullscreen) {
  glfwSetErrorCallback([] (int error_code, const char* description) {
    auto error = "GLFW_Error " + std::to_string(error_code) + ": " + description + '\n';
    throw std::runtime_error(error);
  });
  if (!glfwInit()) std::terminate();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_RESIZABLE , false);

  window = glfwCreateWindow(
    window_x, 
    window_y, 
    "Drone Master", 
    fullscreen ? glfwGetPrimaryMonitor() : nullptr, 
    nullptr
  );
  if (window == nullptr) std::terminate();
  glfwMakeContextCurrent(window);

  int version = gladLoadGL();
  if (version == 0) {
    std::cerr << "Failed to initialize OpenGL context\n";
    std::terminate();
  }

  glfwSwapInterval(1);
}

WindowManager::~WindowManager() {
  glfwDestroyWindow(window);
  glfwTerminate();
}
#include "Application.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

void Application::run() {
  auto window = window_manager.handle();
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    int window_x, window_y;
    glfwGetFramebufferSize(window, &window_x, &window_y);
    glViewport(0, 0, window_x, window_y);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    user_interface.update();

    glfwSwapBuffers(window);
  }
}
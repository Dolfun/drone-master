#pragma once
#include "ApplicationInfo.h"
#include "UI/WindowManager.h"
#include "UI/UserInterface.h"
#include "Server.h"
#include <thread>

class Application {
public:
  Application(const ApplicationInfo&);

  Application(const Application&) = delete;
  Application& operator= (const Application&) = delete;
  Application(Application&&) = delete;
  Application& operator= (Application&&) = delete;

  ~Application();

  void run();

private:
  void io_context_run();

  WindowManager window_manager;
  UserInteface user_interface;
  asio::io_context io_context;
  std::jthread io_context_thread;
  Server server;
};
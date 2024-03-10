#pragma once
#include "ApplicationInfo.h"
#include "UI/WindowManager.h"
#include "UI/UserInterface.h"
#include "NetworkManager.h"

class Application {
public:
  Application(const ApplicationInfo& info)
    : window_manager(info.window_x, info.window_y, info.fullscreen),
      user_interface(window_manager.handle(), info.font_name) {}

  void run();

private:
  WindowManager window_manager;
  UserInteface user_interface;
  NetworkManager network_manager;
};
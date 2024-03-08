#pragma once
#include "ApplicationInfo.h"
#include "UI/WindowManager.h"
#include "UI/UserInterface.h"

class Application {
public:
  Application(const ApplicationInfo& info)
    : window_manager(info.window_x, info.window_y, info.fullscreen),
      user_interface(window_manager.handle()) {}

  void run();

private:
  WindowManager window_manager;
  UserInteface user_interface;
};
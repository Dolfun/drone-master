#pragma once
#include "UI/WindowManager.h"
#include "UI/UserInterface.h"

class Application {
public:
  Application() : window_manager(1280, 720), user_interface(window_manager.handle()) {}

  void run();

private:
  WindowManager window_manager;
  UserInteface user_interface;
};
#pragma once
#include "ApplicationInfo.h"
#include "UI/WindowManager.h"
#include "UI/UserInterface.h"

class Application {
public:
  Application(const ApplicationInfo&);

  void run();

private:
  WindowManager window_manager;
  UserInteface user_interface;
};
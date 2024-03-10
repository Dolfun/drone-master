#pragma once
#include <string>

struct GLFWwindow;

class UserInteface {
public:
  UserInteface(GLFWwindow*, std::string);

  UserInteface(const UserInteface&) = delete;
  UserInteface& operator=(const UserInteface&) = delete;
  UserInteface(UserInteface&&) = default;
  UserInteface& operator=(UserInteface&&) = default;
  
  ~UserInteface();

  void update();

private:
  std::string font_name;
};
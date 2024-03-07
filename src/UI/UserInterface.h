#pragma once

struct GLFWwindow;

class UserInteface {
public:
  UserInteface(GLFWwindow*);

  UserInteface(const UserInteface&) = delete;
  UserInteface& operator=(const UserInteface&) = delete;
  UserInteface(UserInteface&&) = default;
  UserInteface& operator=(UserInteface&&) = default;
  
  ~UserInteface();

  void update();
};
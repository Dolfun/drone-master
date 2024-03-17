#pragma once
#include <string>

struct ApplicationInfo {
  int window_x, window_y;
  bool fullscreen;
  std::string font_name;
  std::string websocket_uri;

  static ApplicationInfo parse_from_file(std::string path);
};
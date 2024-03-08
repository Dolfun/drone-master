#pragma once

struct ApplicationInfo {
  int window_x, window_y;
  bool fullscreen;

  static ApplicationInfo parse_from_file(const char* path);
};
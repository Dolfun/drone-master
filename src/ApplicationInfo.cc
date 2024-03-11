#include "ApplicationInfo.h"
#include <algorithm>
#include <fstream>
#include <map>

auto trim(const std::string& str) {
  auto pred = [] (char c) { return !std::isspace(c); };
  auto begin = std::find_if(str.begin(), str.end(), pred);
  auto end = std::find_if(str.rbegin(), str.rend(), pred).base();
  return std::string { begin, end };
}

auto lower(const std::string& str) {
  std::string result { str };
  std::transform(result.begin(), result.end(), result.begin(), [] (auto c) {
    return std::tolower(c);
  });
  return result;
}

auto parse_file_to_map(std::ifstream& file_stream) {
  std::string line;
  std::map<std::string, std::string> file;
  while (std::getline(file_stream, line)) {
    auto it = std::find(line.begin(), line.end(), '=');
    auto parameter = lower(trim(std::string(line.begin(), it)));
    auto value = trim(std::string(it + 1, line.end()));
    file[parameter] = value;
  }

  return file;
}

ApplicationInfo ApplicationInfo::parse_from_file(std::string path) {
  std::ifstream file_stream(path);
  auto info_file = parse_file_to_map(file_stream);

  ApplicationInfo info;
  info.window_x = std::stoi(info_file["window_x"]);
  info.window_y = std::stoi(info_file["window_y"]);
  info.fullscreen = (lower(info_file["fullscreen"]) == "true");
  info.font_name = info_file["font_name"];
  info.port_no = std::stoi(info_file["port_no"]);

  return info;
}
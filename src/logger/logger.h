#pragma once

#include <type_traits>
#include <concepts>
#include <vector>
#include <format>
#include <tuple>
#include <mutex>

class logger {
public:
  enum class level_t {
  info,
  debug,
  error,
  };

  using log_info = std::tuple<int, level_t, std::string, std::string>;

  logger() = default;
  logger(const std::string& _tag) : tag(_tag) {}

  auto begin()const {
    return logs.cbegin();
  }

  auto end() const {
    return logs.cend();
  }

  logger& operator[] (const level_t& l) {
    level = l;
    return *this;
  }

  template <typename... Args>
  logger& log(std::format_string<Args...> fmt, Args&&... args) {
    std::scoped_lock scoped_lock(mutex);
    logs.emplace_back(
      id++,
      level,
      tag,
      std::format(std::forward<decltype(fmt)>(fmt), std::forward<Args>(args)...)
    );
    return *this;
  }

private:
  

  static int id;
  static std::vector<log_info> logs;
  static std::mutex mutex;
  level_t level;
  std::string tag;
};
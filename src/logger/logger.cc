#include "logger.h"

int logger::id = 1000;
std::vector<logger::log_info> logger::logs;
std::mutex logger::mutex;
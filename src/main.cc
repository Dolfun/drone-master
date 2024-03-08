#include "Application.h"

int main() {
  auto app_info = ApplicationInfo::parse_from_file("app.info");
  Application app(app_info);

  app.run();
}
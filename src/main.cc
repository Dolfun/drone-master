#include "Application.h"
#include <exception>

int main() {

  try {
    auto app_info = ApplicationInfo::parse_from_file("app.info");
    Application app(app_info);
    app.run();
    
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
  
}
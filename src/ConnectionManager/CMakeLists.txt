set (nm_souces
  Server.h Server.cc
)
add_library(network_manager ${nm_souces})
target_link_libraries(network_manager PUBLIC asio)
target_include_directories(network_manager PUBLIC .)
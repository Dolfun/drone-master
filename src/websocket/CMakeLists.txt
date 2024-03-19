set(websocket_sources Client.cc Client.h)
add_library(websocket ${websocket_sources})
target_compile_features(websocket PUBLIC cxx_std_20)
target_link_libraries(websocket PUBLIC websocketpp asio logger)
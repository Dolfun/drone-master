add_library(websocketpp INTERFACE)
target_include_directories(websocketpp INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/websocketpp")
target_compile_features(websocketpp INTERFACE cxx_std_20)
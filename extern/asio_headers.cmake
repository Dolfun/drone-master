set(asio_include "${CMAKE_CURRENT_SOURCE_DIR}/asio/asio/include" CACHE INTERNAL "")
add_library(asio_headers INTERFACE)
target_compile_features(asio_headers INTERFACE cxx_std_20)
target_include_directories(asio_headers INTERFACE ${asio_include})
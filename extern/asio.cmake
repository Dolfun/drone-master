set(asio_sources asio/asio/src/asio.cpp)
set(asio_include asio/asio/include)

add_library(asio ${asio_sources})
target_compile_features(asio PUBLIC cxx_std_20)
target_include_directories(asio PUBLIC ${asio_include})
target_compile_definitions(asio PRIVATE ASIO_SEPARATE_COMPILATION)
add_library(logger logger.cc)
target_compile_features(logger PRIVATE cxx_std_20)
target_include_directories(logger INTERFACE .)
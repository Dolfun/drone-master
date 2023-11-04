add_executable(main)
target_compile_features(main PRIVATE cxx_std_20)
target_link_options(main PRIVATE -lws2_32 -lwsock32)
target_include_directories(main PRIVATE ${ASIO_INCLUDE_DIRECTORY})
target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/common)
target_sources(main PRIVATE
    main.cc
    application.h
    application.cc
    asio_server.h
    asio_server.cc
)
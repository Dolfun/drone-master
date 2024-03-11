#include "Server.h"
#include <iostream>

void Server::connect() {
  acceptor.async_accept([this] (std::error_code ec, tcp::socket socket) {
    if (ec) {
      connect();
      std::cerr << "asio: " + ec.message() << '\n';
    } else {
      session = std::make_unique<Session>(std::move(socket));
      std::cout << "Connected!" << std::endl;
    }
  });
}
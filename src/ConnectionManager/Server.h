#pragma once
#ifdef _WIN32
#include <SDKDDKVer.h>
#endif
#include "asio.hpp"

using asio::ip::tcp;

class Session {
public:
  Session(tcp::socket _socket) : socket(std::move(_socket)) {}
  
private:
  tcp::socket socket;
};

class Server {
public:
  Server(asio::io_context& io_context, short port_no)
    : acceptor (io_context, tcp::endpoint(tcp::v4(), port_no)) {
    connect();
  }

private:
  void connect();

  tcp::acceptor acceptor;
  std::unique_ptr<Session> session;
};
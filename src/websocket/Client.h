#pragma once

#ifdef _WIN32
#include <sdkddkver.h>
#endif
#include <asio.hpp>
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

#include <memory>
#include <string>
#include <thread>
#include <atomic>

namespace Websocket {
  
  using client_endpoint_t = websocketpp::client<websocketpp::config::asio_client>;

  enum class status_t {
    connecting,
    open,
    closing,
    closed,
  };

  class Client {
  public:
    Client();
    ~Client();

    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;
    Client(Client&&) = delete;
    Client& operator=(Client&&) = delete;


    void connect(std::string);
    void close(websocketpp::close::status::value code = websocketpp::close::status::normal);

    status_t get_status() { return status.load(); }

  private:
    client_endpoint_t endpoint;
    std::shared_ptr<std::thread> thread;
    websocketpp::connection_hdl connection_handle;
    std::atomic<status_t> status;
  };
}

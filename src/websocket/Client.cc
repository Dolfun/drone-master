#include "Client.h"
#include "logger.h"
#include <iostream>
#include <memory>

auto ws_logger = logger("websocket");

namespace Websocket {

  Client::Client() : status { status_t::closed } {
    endpoint.clear_access_channels(websocketpp::log::alevel::all);
    endpoint.clear_error_channels(websocketpp::log::alevel::all);
    endpoint.init_asio();
    endpoint.start_perpetual();

    thread = std::make_shared<std::thread>(&client_endpoint_t::run, &endpoint);
  }

  Client::~Client() {
    endpoint.stop_perpetual();
    if (status == status_t::open || status == status_t::connecting) {
      close(websocketpp::close::status::going_away);
    }
    thread->join();
  }

  void Client::connect(std::string uri) {
    if (status != status_t::closed) return;
    status = status_t::connecting;

    websocketpp::lib::error_code ec;
    auto connection = endpoint.get_connection(uri, ec);
    if (ec) {
      ws_logger[logger::level_t::error].log("connection initialization error: {}", ec.message());
      status = status_t::closed;
      return;
    }

    connection_handle = connection->get_handle();

    connection->set_open_handler([this] (websocketpp::connection_hdl) {
      status = status_t::open;
      ws_logger[logger::level_t::info].log("connection opened successfully");
    });

    connection->set_fail_handler([this] (websocketpp::connection_hdl hdl) {
      status = status_t::closed;
      auto connection = endpoint.get_con_from_hdl(hdl);
      ws_logger[logger::level_t::error].log("failed to connect: {}", connection->get_ec().message());
    });

    connection->set_close_handler([this] (websocketpp::connection_hdl hdl) {
      status = status_t::closed;
      auto connection = endpoint.get_con_from_hdl(hdl);
      ws_logger[logger::level_t::info]
        .log("connection closed ({}) : {}", connection->get_remote_close_reason(), connection->get_remote_close_code());
    });

    endpoint.connect(connection);
  }

  void Client::close(websocketpp::close::status::value code) {
    if (status != status_t::open) return;
    status = status_t::closing;

    websocketpp::lib::error_code ec;
    endpoint.close(connection_handle, code, "", ec);
    if (ec) {
      ws_logger[logger::level_t::error].log("error closing connection: {}", ec.message());
      status = status_t::open;
    }
  }
}
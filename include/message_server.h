#pragma once
#include "boost/asio.hpp"
#include "connection.h"
#include "channel_manager.h"
#include <functional>
namespace MessageBroker {

namespace asio = boost::asio;
using tcp = boost::asio::ip::tcp;

class MessageServer {
  unsigned short serverPort_;
  asio::io_context ioContext_;
  tcp::acceptor tcpAcceptor_;
  ChannelManager channelManager_;
  // handler
  std::function<void(Connection)> connectHandler_ = nullptr;
  std::function<void(Connection)> disconnectHandler_ = nullptr;

  void StartAccept();
  void HandleAccept(const boost::system::error_code& erc, tcp::socket peer);
public:
  MessageServer(unsigned short port);
  ~MessageServer();
  void OnConnect(std::function<void(Connection)> connectHandler);
  void OnDisconnect(std::function<void(Connection)> disconnectHandler);
  bool Start();
};
} // namespace MessageBroker

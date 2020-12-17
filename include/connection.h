#pragma once
#include "boost/asio.hpp"
#include "channel_manager.h"
#include <memory>
namespace MessageBroker {
using tcp = boost::asio::ip::tcp;
class Connection : public std::enable_shared_from_this<Connection> {
  tcp::socket socket_;
  boost::asio::io_context &ioContext_;
  ChannelManager &channelManager_;

public:
  Connection(boost::asio::io_context &ioContext,
             boost::asio::ip::tcp::socket &&socket,
             ChannelManager &channelManager);
  void HandleData();
};

} // namespace MessageBroker

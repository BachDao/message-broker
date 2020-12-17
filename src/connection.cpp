#include "connection.h"

namespace MessageBroker {
Connection::Connection(boost::asio::io_context &ioContext,
                       boost::asio::ip::tcp::socket &&socket,
                       ChannelManager &channelManager)
    : socket_(std::move(socket)), ioContext_(ioContext),
      channelManager_(channelManager) {}
void Connection::HandleData() {

}
} // namespace MessageBroker
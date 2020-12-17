#include "message_server.h"
namespace MessageBroker {
MessageServer::MessageServer(unsigned short port)
    : serverPort_(port), ioContext_(),
      tcpAcceptor_(ioContext_, tcp::endpoint(tcp::v4(), serverPort_)) {}
void MessageServer::OnConnect(std::function<void(Connection)> connectHandler) {
  connectHandler_ = std::move(connectHandler);
}
void MessageServer::OnDisconnect(
    std::function<void(Connection)> disconnectHandler) {
  disconnectHandler_ = std::move(disconnectHandler);
}
void MessageServer::HandleAccept(const boost::system::error_code &erc,
                                 tcp::socket peer) {
  if (!erc) {
    auto connection = std::make_shared<Connection>(ioContext_, std::move(peer),
                                                   channelManager_);
    connection->HandleData();
  } else {
    throw std::logic_error("handle new connection error");
  }
}
void MessageServer::StartAccept() {

  tcpAcceptor_.async_accept(
      [this](const boost::system::error_code &erc, tcp::socket peer) {
        HandleAccept(erc, std::move(peer));
      });
}
bool MessageServer::Start() {
  StartAccept();
  return true;
}
} // namespace MessageBroker
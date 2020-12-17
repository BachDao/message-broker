#include "message_parser.h"

namespace MessageBroker {
namespace detail {

std::span<byte> MessageParser::GetBuffer(size_t size) {
  return buff_.GetBuffer(size);
}
void MessageParser::Advance(size_t len) { buff_.WriteAdvance(len); }
std::tuple<bool, Piece> MessageParser::GetMessage() {
  auto buff = buff_.GetBytes();
  Piece p;
  auto success = p.ParseFromArray(buff.data(), buff.size());
  if (success) {
    buff_.ReadAdvance(p.ByteSizeLong());
  }
  return {success, p};
}

} // namespace detail
} // namespace MessageBroker
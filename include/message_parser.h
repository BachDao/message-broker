#pragma once
#include "message.pb.h"
#include "buffer.h"
#include <tuple>
namespace MessageBroker {
namespace detail {

// stateful message parser
class MessageParser {
  Buffer buff_;

public:
  std::span<byte> GetBuffer(size_t size);
  void Advance(size_t len);
  std::tuple<bool, Piece> GetMessage();
};
} // namespace detail
} // namespace MessageBroker
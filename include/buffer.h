#pragma once
#include <span>
#include <vector>
namespace MessageBroker {
namespace detail {
using byte = std::byte;


class Buffer {
  std::vector<byte> storage_;
  int runningIndex_ = 0;
  int start_ = 0;
  int end_ = 0; // past-the-last
  const size_t MAX_SIZE = 4096;

  size_t Capacity();
public:
  Buffer();
  std::span<byte> GetBuffer(size_t size);
  std::span<byte> GetBytes();
  void WriteAdvance(size_t size);
  void ReadAdvance(size_t size);
  size_t Size();
  void Relocate();
};
} // namespace detail
} // namespace MessageBroker

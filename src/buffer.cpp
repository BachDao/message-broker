#include "buffer.h"
#include <exception>

namespace MessageBroker {
namespace detail {

std::span<byte> Buffer::GetBuffer(size_t size) {
  auto cap = Capacity();
  if (size > cap) {
    throw std::overflow_error("cannot allocate enough memory");
  }
  if (cap < size) {
    Relocate();
  }
  runningIndex_ = size;
  return {storage_.data() + end_, static_cast<long>(size)};
}
size_t Buffer::Capacity() { return MAX_SIZE - end_; }
size_t Buffer::Size() { return end_ - start_; }
void Buffer::WriteAdvance(size_t size) {
  if (runningIndex_ == -1) {
    throw std::logic_error("invalid precondition");
  }
  if (end_ + size > runningIndex_) {
    throw std::length_error("invalid value of size");
  }
  end_ += size;
  runningIndex_ = -1;
  return;
}
std::span<byte> Buffer::GetBytes() {
  return std::span<byte>(storage_.data() + start_, end_ - start_);
}
void Buffer::ReadAdvance(size_t size) {
  if (size > end_ - start_) {
    throw std::length_error("invalid value of size");
  }
  start_ += size;
}
void Buffer::Relocate() {
  std::copy(storage_.begin() + start_, storage_.begin() + end_,
            storage_.begin());
}
Buffer::Buffer() { storage_.reserve(MAX_SIZE); }

} // namespace detail
} // namespace MessageBroker
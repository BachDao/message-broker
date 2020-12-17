#include "buffer.h"
#include "gtest/gtest.h"
#include <iostream>
using namespace MessageBroker::detail;

TEST(Buffer, GetWriteBuffer) {
  Buffer buf;
  auto writeBuf = buf.GetBuffer(512);
  EXPECT_EQ(writeBuf.size(), 512);
}

TEST(Buffer, SizeAfterWrite) {
  Buffer buf;
  auto writeBuf = buf.GetBuffer(512);
  buf.WriteAdvance(128);
  EXPECT_EQ(buf.Size(), 128);
}
TEST(Buffer, ContentAfterWrite) {
  Buffer buf;
  auto wb = buf.GetBuffer(512);
  for (size_t i = 0; i < wb.size(); i++) {
    wb[i] = static_cast<std::byte>(i);
  }
  buf.WriteAdvance(wb.size());
  auto content = buf.GetBytes();
  EXPECT_EQ(content.size(), 512);
  for (size_t i = 0; i < content.size(); i++) {
    EXPECT_EQ(content[i], static_cast<std::byte>(i));
  }
}
TEST(Buffer, WriteTwiceAndReadBack) {
  Buffer bf;
  auto wb = bf.GetBuffer(512);
  bf.WriteAdvance(128);
  bf.GetBuffer(512);
  bf.WriteAdvance(256);
  auto size = bf.Size();
  EXPECT_EQ(size, 384);
  bf.ReadAdvance(128);
  EXPECT_EQ(bf.Size(), 256);
}
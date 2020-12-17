#include "message_parser.h"
#include <gtest/gtest.h>


using namespace MessageBroker::detail;

TEST(Parser, TryParse)
{
    Piece p;
    p.set_channel("default");
    p.set_sender("client");
    p.set_content("hello");
    auto size = p.ByteSizeLong();
    byte tmpBuff[512];
    p.SerializeToArray(tmpBuff, 512);
    MessageParser parser;
    auto buff = parser.GetBuffer(512);
    std::memcpy(buff.data(), tmpBuff, size);
    parser.Advance(size);
    auto [success, message] = parser.GetMessage();
    EXPECT_TRUE(success);
    EXPECT_EQ(message.content(), "hello");
}
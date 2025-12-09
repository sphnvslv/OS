#include <gtest/gtest.h>
#include "message.h"

using namespace std;

// Тест создания сообщения
TEST(MessageTest, CreateEmptyMessage) {
    Message msg;
    EXPECT_TRUE(msg.isEmpty());
    EXPECT_EQ(msg.senderId, 0);
}

// Тест установки содержимого
TEST(MessageTest, SetContent) {
    Message msg;
    msg.setContent("Hello");

    EXPECT_FALSE(msg.isEmpty());
    EXPECT_STREQ(msg.getContent().c_str(), "Hello");
}

// Тест обрезки длинного сообщения
TEST(MessageTest, LongMessageTruncated) {
    Message msg;
    string longText = "This is a very long message that exceeds limit";
    msg.setContent(longText);

    EXPECT_EQ(msg.getContent().length(), Message::MAX_LENGTH);
}

// Тест конструктора с параметрами
TEST(MessageTest, ConstructorWithParams) {
    Message msg("Test", 5);

    EXPECT_STREQ(msg.getContent().c_str(), "Test");
    EXPECT_EQ(msg.senderId, 5);
    EXPECT_FALSE(msg.isEmpty());
}

// Тест максимальной длины
TEST(MessageTest, MaxLengthConstant) {
    EXPECT_EQ(Message::MAX_LENGTH, 20);
}
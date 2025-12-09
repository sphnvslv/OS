#include <gtest/gtest.h>
#include <fstream>
#include <filesystem>
#include "message.h"

// Объявление класса SharedFile (если он в .h файле)
#include "shared_file.h"

using namespace std;
namespace fs = filesystem;

class SharedFileTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Создаем временный файл для тестов
        testFilename = "test_shared_file.bin";
        // Удаляем если уже существует
        if (fs::exists(testFilename)) {
            fs::remove(testFilename);
        }
    }

    void TearDown() override {
        // Удаляем тестовый файл после каждого теста
        if (fs::exists(testFilename)) {
            fs::remove(testFilename);
        }
    }

    string testFilename;
};

// Тест создания файла
TEST_F(SharedFileTest, CreateFile) {
    {
        SharedFile file(testFilename, 10, true);
        EXPECT_TRUE(fs::exists(testFilename));
    }
    EXPECT_TRUE(fs::exists(testFilename));
}

// Тест записи и чтения сообщения
TEST_F(SharedFileTest, WriteAndReadMessage) {
    SharedFile file(testFilename, 10, true);

    Message msgToWrite("Hello World", 1);
    EXPECT_TRUE(file.write(msgToWrite));
    EXPECT_FALSE(file.isEmpty());

    Message msgToRead;
    EXPECT_TRUE(file.read(msgToRead));

    EXPECT_STREQ(msgToRead.getContent().c_str(), "Hello World");
    EXPECT_EQ(msgToRead.senderId, 1);
}

// Тест нескольких сообщений
TEST_F(SharedFileTest, MultipleMessages) {
    SharedFile file(testFilename, 5, true);

    // Пишем 3 сообщения
    for (int i = 0; i < 3; i++) {
        Message msg("Msg " + to_string(i), i);
        EXPECT_TRUE(file.write(msg));
    }

    EXPECT_EQ(file.getMessageCount(), 3);
    EXPECT_FALSE(file.isFull());
    EXPECT_FALSE(file.isEmpty());

    // Читаем их
    for (int i = 0; i < 3; i++) {
        Message msg;
        EXPECT_TRUE(file.read(msg));
        EXPECT_EQ(msg.senderId, i);
    }

    EXPECT_TRUE(file.isEmpty());
}

// Тест пустого файла
TEST_F(SharedFileTest, EmptyFile) {
    SharedFile file(testFilename, 5, true);

    EXPECT_TRUE(file.isEmpty());
    EXPECT_FALSE(file.isFull());
    EXPECT_EQ(file.getMessageCount(), 0);

    // Попытка чтения из пустого файла
    // Зависит от реализации - либо exception, либо false
}

// Тест полного буфера
TEST_F(SharedFileTest, FullBuffer) {
    SharedFile file(testFilename, 3, true);

    // Заполняем буфер
    for (int i = 0; i < 3; i++) {
        Message msg("Message", i);
        EXPECT_TRUE(file.write(msg));
    }

    EXPECT_TRUE(file.isFull());
    EXPECT_EQ(file.getMessageCount(), 3);

    // Освобождаем место
    Message msg;
    EXPECT_TRUE(file.read(msg));

    EXPECT_FALSE(file.isFull());
    EXPECT_EQ(file.getMessageCount(), 2);
}
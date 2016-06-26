//
// Created by juan on 17/06/16.
//

#include "include/messages_service_test.h"

TEST(MessageService, GetMessagesWhithNoMessage) {
    DataBase::getInstance()->open("/tmp/messagesService1");
    if (DataBase::getInstance()->is_open()) {
        MessagesService messagesService;
        std::vector<Message> messages = messagesService.getMessages("john", "doe");
        EXPECT_TRUE(messages.size() == 0);
        messages = messagesService.getMessages("doe", "john");
        EXPECT_TRUE(messages.size() == 0);
    } else {
        EXPECT_EQ(1, 0);
    }
}

TEST(MessageService, AddAndGetMessage) {
    DataBase::getInstance()->open("/tmp/messagesService2");
    if (DataBase::getInstance()->is_open()) {
        DataBase::getInstance()->remove(Constant::messagesPrefix + "ElthonJohn");
        DataBase::getInstance()->remove(Constant::messagesPrefix + "JohnElthon");
        MessagesService messagesService;
        std::vector<Message> messages = messagesService.getMessages("Elthon", "John");
        EXPECT_TRUE(messages.size() == 0);
        Message m("Elthon", "John", "content");
        messagesService.addMessage(m);
        messages = messagesService.getMessages("Elthon", "John");
        EXPECT_TRUE(messages.size() == 1);
        messages = messagesService.getMessages("John", "Elthon");
        EXPECT_TRUE(messages.size() == 1);
    } else {
        EXPECT_EQ(1, 0);
    }
}

TEST(MessageService, AddAndGetTwoMessages) {
    DataBase::getInstance()->open("/tmp/messagesService3");
    if (DataBase::getInstance()->is_open()) {
        DataBase::getInstance()->remove(Constant::messagesPrefix + "ElthonJohn");
        DataBase::getInstance()->remove(Constant::messagesPrefix + "JohnElthon");
        MessagesService messagesService;
        std::vector<Message> messages = messagesService.getMessages("Elthon", "John");
        EXPECT_TRUE(messages.size() == 0);
        Message message("Elthon", "John", "Hello");
        messagesService.addMessage(message);
        Message otherMessage("Elthon", "John", "nice to see you again");
        messagesService.addMessage(otherMessage);
        messages = messagesService.getMessages("Elthon", "John");
        EXPECT_TRUE(messages.size() == 2);
        messages = messagesService.getMessages("John", "Elthon");
        EXPECT_TRUE(messages.size() == 2);
    } else {
        EXPECT_EQ(1, 0);
    }
}

TEST(MessageService, AddConversation) {
    DataBase::getInstance()->open("/tmp/messagesService4");
    if (DataBase::getInstance()->is_open()) {
        DataBase::getInstance()->remove(Constant::messagesPrefix + "ElthonJohn");
        DataBase::getInstance()->remove(Constant::messagesPrefix + "JohnElthon");
        MessagesService messagesService;
        std::vector<Message> messages = messagesService.getMessages("Elthon", "John");
        EXPECT_TRUE(messages.size() == 0);
        Message message("Elthon", "John", "Hello");
        messagesService.addMessage(message);
        Message otherMessage("John", "Elthon", "hello my dear friend");
        messagesService.addMessage(otherMessage);
        messages = messagesService.getMessages("Elthon", "John");
        EXPECT_TRUE(messages.size() == 2);
        messages = messagesService.getMessages("John", "Elthon");
        EXPECT_TRUE(messages.size() == 2);
    } else {
        EXPECT_EQ(1, 0);
    }
}

TEST(MessageService, AddAndGetLastMessage) {

    DataBase::getInstance()->open("/tmp/messagesService5");
    if (DataBase::getInstance()->is_open()) {
        DataBase::getInstance()->remove(Constant::messagesPrefix + "ElthonJohn");
        DataBase::getInstance()->remove(Constant::messagesPrefix + "JohnElthon");
        MessagesService messagesService;
        std::vector<Message> messages = messagesService.getMessages("Elthon", "John");
        EXPECT_TRUE(messages.size() == 0);
        Message m("Elthon", "John", "content");
        messagesService.addMessage(m);
        Message message = messagesService.getLastMessage("Elthon", "John");
        EXPECT_TRUE(message.getContent().compare(m.getContent()) == 0);
        message = messagesService.getLastMessage("John", "Elthon");
        EXPECT_TRUE(message.getContent().compare("") == 0);
    } else {
        EXPECT_EQ(1, 0);
    }
}

TEST(MessageService, AddMessagesAndGetLastMessageAfterGetAll) {
    DataBase::getInstance()->open("/tmp/messagesService6");
    if (DataBase::getInstance()->is_open()) {
        DataBase::getInstance()->remove(Constant::messagesPrefix + "ElthonJohn");
        DataBase::getInstance()->remove(Constant::messagesPrefix + "JohnElthon");
        MessagesService messagesService;
        std::vector<Message> messages = messagesService.getMessages("Elthon", "John");
        EXPECT_TRUE(messages.size() == 0);
        Message firstMessage("Elthon", "John", "content");
        Message secondMessage("Elthon", "John", "secondContent");
        messagesService.addMessage(firstMessage);
        messagesService.addMessage(secondMessage);
        messages = messagesService.getMessages("Elthon", "John");
        EXPECT_TRUE(messages.size() == 2);
        Message message = messagesService.getLastMessage("Elthon", "John");
        EXPECT_TRUE(message.getContent().compare("") == 0);
        message = messagesService.getLastMessage("John", "Elthon");
        EXPECT_TRUE(message.getContent().compare("") == 0);
    } else {
        EXPECT_EQ(1, 0);
    }
}
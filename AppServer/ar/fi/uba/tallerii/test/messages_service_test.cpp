//
// Created by juan on 17/06/16.
//

#include "include/messages_service_test.h"
#include "RemoveDatabase.h"

TEST(MessageService, GetMessagesWhithNoMessage) {
    DataBase db("/tmp/messagesService1");
    if (db.is_open()) {
        MessagesService messagesService(db);
        std::vector<Message> messages = messagesService.getMessages("john", "doe");
        EXPECT_TRUE(messages.size() == 0);
        messages = messagesService.getMessages("doe", "john");
        EXPECT_TRUE(messages.size() == 0);
    } else {
        EXPECT_EQ(1, 0);
    }
}

TEST(MessageService, AddAndGetMessage) {
    removeDataBase("/tmp/messagesService2");
    DataBase db("/tmp/messagesService2");
    if (db.is_open()) {
        MessagesService messagesService(db);
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
    removeDataBase("/tmp/messagesService3");
    DataBase db("/tmp/messagesService3");
    if (db.is_open()) {
        MessagesService messagesService(db);
        std::vector<Message> messages = messagesService.getMessages("Elthon", "John");
        EXPECT_TRUE(messages.size() == 0);
        Message message("Elthon", "John", "Hello");
        messagesService.addMessage(message);
        Message otherMessage("Elthon", "John", "nice to see you again");
        messagesService.addMessage(otherMessage);
        messages = messagesService.getMessages("Elthon", "John");
        EXPECT_TRUE(messages.size() == 2);
        EXPECT_TRUE(messages.front().getSender().compare(message.getSender()) == 0);
        EXPECT_TRUE(messages.front().getReciever().compare(message.getReciever()) == 0);
        EXPECT_TRUE(messages.front().getContent().compare(message.getContent()) == 0);
        EXPECT_TRUE(messages.back().getSender().compare(otherMessage.getSender()) == 0);
        EXPECT_TRUE(messages.back().getReciever().compare(otherMessage.getReciever()) == 0);
        EXPECT_TRUE(messages.back().getContent().compare(otherMessage.getContent()) == 0);
        messages = messagesService.getMessages("John", "Elthon");
        EXPECT_TRUE(messages.size() == 2);
    } else {
        EXPECT_EQ(1, 0);
    }
}

TEST(MessageService, AddConversation) {
    removeDataBase("/tmp/messagesService4");
    DataBase db("/tmp/messagesService4");
    if (db.is_open()) {
        MessagesService messagesService(db);
        std::vector<Message> messages = messagesService.getMessages("Elthon", "John");
        EXPECT_TRUE(messages.size() == 0);
        Message message("Elthon", "John", "Hello");
        messagesService.addMessage(message);
        Message otherMessage("John", "Elthon", "hello my dear friend");
        messagesService.addMessage(otherMessage);
        messages = messagesService.getMessages("Elthon", "John");
        EXPECT_TRUE(messages.size() == 2);
        EXPECT_TRUE(messages.front().getSender().compare(message.getSender()) == 0);
        EXPECT_TRUE(messages.front().getReciever().compare(message.getReciever()) == 0);
        EXPECT_TRUE(messages.front().getContent().compare(message.getContent()) == 0);
        EXPECT_TRUE(messages.back().getSender().compare(otherMessage.getSender()) == 0);
        EXPECT_TRUE(messages.back().getReciever().compare(otherMessage.getReciever()) == 0);
        EXPECT_TRUE(messages.back().getContent().compare(otherMessage.getContent()) == 0);
        messages = messagesService.getMessages("John", "Elthon");
        EXPECT_TRUE(messages.size() == 2);
    } else {
        EXPECT_EQ(1, 0);
    }
}
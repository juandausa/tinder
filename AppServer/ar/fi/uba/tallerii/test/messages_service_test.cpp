//
// Created by juan on 17/06/16.
//

#include "include/messages_service_test.h"

TEST(MessageService, GetMessagesWhithNoMessage) {
    DataBase db("/tmp/messagesService1");
    if (db.is_open()) {
        MessagesService messagesService(db);
        std::vector<Message> messages = messagesService.getMessages("john", "doe");
        EXPECT_TRUE(messages.size() == 0);
    } else {
        EXPECT_EQ(1, 0);
    }
}
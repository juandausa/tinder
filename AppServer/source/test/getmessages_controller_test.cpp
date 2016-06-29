//
// Created by juan on 25/06/16.
//

#include "getmessages_controller_test.h"

TEST(GetMessagesController, GetEmptyMessageBody) {
    DataBase* db = DataBase::getInstance();
    if (db->open("/tmp/testaddmessagescontroller")) {
        GetMessagesController addMessagesController;
        EXPECT_EQ("{\"message\":\"\"}\n", addMessagesController.getEmptyMessageResponseBody());
    }
}

TEST(GetMessagesController, GetMessageBody) {
    DataBase* db = DataBase::getInstance();
    if (db->open("/tmp/testaddmessagescontroller2")) {
        GetMessagesController addMessagesController;
        Message message("33", "44", "hello");
        EXPECT_EQ("{\"message\":\"hello\"}\n", addMessagesController.getMessageResponseBody(message));
    }
}

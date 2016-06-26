//
// Created by juan on 25/06/16.
//

#include "addmessages_controller_test.h"

TEST(AddMessagesController, GetSuccessBody) {
    DataBase* db = DataBase::getInstance();
    if (db->open("/tmp/testaddmessagescontroller")) {
        AddMessagesController addMessagesController;
        EXPECT_EQ("{\"status_code\":200}\n", addMessagesController.getSucceedResponseBody());
    }
}

TEST(AddMessagesController, GetErrorBody) {
    DataBase* db = DataBase::getInstance();
    if (db->open("/tmp/testaddmessagescontroller2")) {
        AddMessagesController addMessagesController;
        EXPECT_EQ("{\"status_code\":500}\n", addMessagesController.getErrorResponseBody());
    }
}

TEST(AddMessagesController, GetEmptyBody) {
    DataBase* db = DataBase::getInstance();
    if (db->open("/tmp/testaddmessagescontroller3")) {
        AddMessagesController addMessagesController;
        EXPECT_EQ("{\"message\":\"\"}\n", addMessagesController.getEmptyMessageResponseBody());
    }
}

TEST(AddMessagesController, GetMessageBody) {
    DataBase* db = DataBase::getInstance();
    if (db->open("/tmp/testaddmessagescontroller4")) {
        AddMessagesController addMessagesController;
        EXPECT_EQ("{\"message\":\"content\"}\n", addMessagesController.getMessageResponseBody(Message("54","45","content")));
    }
}

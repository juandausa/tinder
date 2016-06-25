//
// Created by juan on 25/06/16.
//

#include "addlike_controller_test.h"

TEST(AddLikeController, GetUserToWithotUser) {
    DataBase* db = DataBase::getInstance();
    if (db->open("/tmp/testuserregistercontroller")) {
        UserService user_service;
        AddLikeController addLikeController;
        EXPECT_EQ("", addLikeController.getUserTo("{ \"to_user\": \"jose\" }"));
    }
}

TEST(AddLikeController, GetUserTo) {
    DataBase* db = DataBase::getInstance();
    if (db->open("/tmp/testuserregistercontroller")) {
        UserService user_service;
        AddLikeController addLikeController;
        EXPECT_EQ("jose", addLikeController.getUserTo("{ \"to_user_id\": \"jose\" }"));
    }
}

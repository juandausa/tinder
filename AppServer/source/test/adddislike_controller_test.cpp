//
// Created by juan on 25/06/16.
//

#include "adddislike_controller_test.h"

TEST(AddDislikeController, GetUserToWithotUser) {
    DataBase* db = DataBase::getInstance();
    if (db->open("/tmp/testuserregistercontroller")) {
        UserService user_service;
        AddDisLikeController addDisLikeController;
        EXPECT_EQ("", addDisLikeController.getUserTo("{ \"to_user\": \"jose\" }"));
    }
}

TEST(AddDisLikeController, GetUserTo) {
    DataBase* db = DataBase::getInstance();
    if (db->open("/tmp/testuserregistercontroller")) {
        UserService user_service;
        AddDisLikeController addDisLikeController;
        EXPECT_EQ("jose", addDisLikeController.getUserTo("{ \"to_user_id\": \"jose\" }"));
    }
}

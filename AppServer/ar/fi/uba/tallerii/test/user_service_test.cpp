//
// Created by juan on 08/04/16.
//

#include "include/user_service_test.h"
#include "DataBase.h"

TEST(UserService, IsUserRegisteredWithNoUsers) {
    DataBase db("/tmp/testuserservicedb");
    if (db.is_open()) {
        UserService user_service(db);
        EXPECT_FALSE(user_service.is_user_registered("UserJohnDoe"));
    } else {
        EXPECT_EQ(1, 0);
    }
}

TEST(UserService, IsUserRegisteredWithUserPreviouslyRegistered) {
    DataBase db("/tmp/testuserservicedb2");
    db.set("UserJoaneDoe", "value");
    if (db.is_open()) {
        UserService user_service(db);
        EXPECT_TRUE(user_service.is_user_registered("UserJoaneDoe"));
    } else {
        EXPECT_EQ(1, 0);
    }
}

TEST(UserService, GenerateTokenFromUsername) {
    DataBase db("/tmp/testuserservicedb3");
    if (db.is_open()) {
        UserService user_service(db);
        EXPECT_NE("", user_service.get_securiry_token("UserJoaneDoe"));
    } else {
        EXPECT_EQ(1, 0);
    }
}

TEST(UserService, GenerateTokenTwoTokensFromOneUsernameShoulReturnDifferentTokens) {
    DataBase db("/tmp/testuserservicedb4");
    if (db.is_open()) {
        UserService user_service(db);
        std::string token = user_service.get_securiry_token("UserJoaneDoe");
        for (unsigned int i = 0; i < 10; i++) {
            EXPECT_NE(token, user_service.get_securiry_token("UserJoaneDoe"));
        }
        EXPECT_NE(user_service.get_securiry_token("UserJoaneDoe"), user_service.get_securiry_token("UserJoaneDoe"));
    } else {
        EXPECT_EQ(1, 0);
    }
}

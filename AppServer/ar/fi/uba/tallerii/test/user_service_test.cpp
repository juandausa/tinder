//
// Created by juan on 08/04/16.
//

#include "include/user_service_test.h"
#include "DataBase.h"

TEST(UserService, IsUserRegisteredWithNoUsers) {
    DataBase db("/tmp/testuserservicedb");
    if (db.is_open()) {
        UserService user_service(db);
        EXPECT_FALSE(user_service.isUserRegistered("UserJohnDoe"));
    } else {
        EXPECT_EQ(1, 0);
    }
}

TEST(UserService, IsUserRegisteredWithUserPreviouslyRegistered) {
    DataBase db("/tmp/testuserservicedb2");
    db.set("UserJoaneDoe", "value");
    if (db.is_open()) {
        UserService user_service(db);
        EXPECT_TRUE(user_service.isUserRegistered("UserJoaneDoe"));
    } else {
        EXPECT_EQ(1, 0);
    }
}

TEST(UserService, GenerateTokenFromUsername) {
    DataBase db("/tmp/testuserservicedb3");
    if (db.is_open()) {
        UserService user_service(db);
        EXPECT_NE("", user_service.getSecurityToken("UserJoaneDoe"));
    } else {
        EXPECT_EQ(1, 0);
    }
}

TEST(UserService, GenerateDifferentTokensFromTwoUsernames) {
    DataBase db("/tmp/testuserservicedb3");
    if (db.is_open()) {
        UserService user_service(db);
        EXPECT_NE(user_service.getSecurityToken("UserJoaneDoes"), user_service.getSecurityToken("UserJoaneDoe"));
    } else {
        EXPECT_EQ(1, 0);
    }
}

TEST(UserService, GenerateTokenTwoTokensFromOneUsernameShoulReturnDifferentTokens) {
    DataBase db("/tmp/testuserservicedb4");
    if (db.is_open()) {
        UserService user_service(db);
        std::string token = user_service.getSecurityToken("UserJoaneDoe");
        for (unsigned int i = 0; i < 100; i++) {
            EXPECT_NE(token, user_service.getSecurityToken("UserJoaneDoe"));
        }
        EXPECT_NE(user_service.getSecurityToken("UserJoaneDoe"), user_service.getSecurityToken("UserJoaneDoe"));
    } else {
        EXPECT_EQ(1, 0);
    }
}

TEST(UserService, GenerateTokenAndValidateWithValidToken) {
    DataBase db("/tmp/testuserservicedb5");
    if (db.is_open()) {
        UserService user_service(db);
        std::string token = user_service.getSecurityToken("UserJoaneDoe");
        EXPECT_TRUE(user_service.isTokenValid("UserJoaneDoe", token));
    } else {
        EXPECT_EQ(1, 0);
    }
}

TEST(UserService, GenerateTokenAndValidateWithInvalidToken) {
    DataBase db("/tmp/testuserservicedb6");
    if (db.is_open()) {
        UserService user_service(db);
        std::string token = user_service.getSecurityToken("UserJoaneDoe");
        EXPECT_FALSE(user_service.isTokenValid("UserJoaneDoe", "invalidtoken"));
    } else {
        EXPECT_EQ(1, 0);
    }
}

TEST(UserService, ValidateNullToken) {
    DataBase db("/tmp/testuserservicedb6");
    if (db.is_open()) {
        UserService user_service(db);
        std::string token = user_service.getSecurityToken("UserJoaneDoe");
        EXPECT_FALSE(user_service.isTokenValid("UserJoaneDoe", ""));
    } else {
        EXPECT_EQ(1, 0);
    }
}

TEST(UserService, ValidateNullUser) {
    DataBase db("/tmp/testuserservicedb6");
    if (db.is_open()) {
        UserService user_service(db);
        std::string token = user_service.getSecurityToken("UserJoaneDoe");
        EXPECT_FALSE(user_service.isTokenValid("", token));
    } else {
        EXPECT_EQ(1, 0);
    }
}

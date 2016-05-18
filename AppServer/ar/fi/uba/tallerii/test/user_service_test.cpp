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
/*    DataBase db("/tmp/testuserservicedb2");
    db.set("UserJoaneDoe", "value");
    if (db.is_open()) {
        UserService user_service(db);
        EXPECT_TRUE(user_service.isUserRegistered("UserJoaneDoe"));
    } else {
        EXPECT_EQ(1, 0);
    }
*/
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

TEST(UserService, GetLikesWhithNoLike) {
    DataBase db("/tmp/testuserservicedb7");
    if (db.is_open()) {
        UserService user_service(db);
        std::vector<std::string> likes = user_service.getLikes("JohnDoe");
        EXPECT_TRUE(likes.size() == 0);
    } else {
        EXPECT_EQ(1, 0);
    }
}

TEST(UserService, AddLikeReturnTrue) {
    DataBase db("/tmp/testuserservicedb8");
    if (db.is_open()) {
        UserService user_service(db);
        std::vector<std::string> likes = user_service.getLikes("JohnDoe");
        EXPECT_TRUE(user_service.addLike("JohnDoe", "Josi"));
    } else {
        EXPECT_EQ(1, 0);
    }
}

TEST(UserService, AddLikeReturnFalseIfDbIsClose) {
    DataBase db("/tmp/testuserservicedb9");
    if (db.is_open()) {
        UserService user_service(db);
        db.~DataBase();
        std::vector<std::string> likes = user_service.getLikes("JohnDoe");
        EXPECT_FALSE(user_service.addLike("JohnDoe", "Josi"));
    } else {
        EXPECT_EQ(1, 0);
    }
}

TEST(UserService, AddLikeShouldAddLikeToTheUser) {
    removeDataBase("/tmp/testuserservicedb10");
    DataBase db("/tmp/testuserservicedb10");
    if (db.is_open()) {
        UserService user_service(db);
        std::vector<std::string> likes = user_service.getLikes("JohnDoe");
        EXPECT_TRUE(likes.size() == 0);
        user_service.addLike("JohnDoe", "Josi");
        likes = user_service.getLikes("JohnDoe");
        EXPECT_TRUE(likes.size() == 1);
    } else {
        EXPECT_EQ(1, 0);
    }
}

TEST(UserService, AddSeveralLikesShouldAddLikesToTheUser) {
    removeDataBase("/tmp/testuserservicedb11");
    DataBase db("/tmp/testuserservicedb11");
    if (db.is_open()) {
        UserService user_service(db);
        std::vector<std::string> likes = user_service.getLikes("JohnDoe");
        EXPECT_TRUE(likes.size() == 0);
        user_service.addLike("JohnDoe", "Josi");
        user_service.addLike("JohnDoe", "Carmen");
        user_service.addLike("JohnDoe", "Lara");
        likes = user_service.getLikes("JohnDoe");
        EXPECT_TRUE(likes.size() == 3);
    } else {
        EXPECT_EQ(1, 0);
    }
}

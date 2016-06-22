//
// Created by juan on 08/04/16.
//

#include "include/user_service_test.h"
#include "DataBase.h"
#include <iostream>
TEST(UserService, IsUserRegisteredWithNoUsers) {
    DataBase* db = DataBase::getInstance();
    if (db->open("/tmp/testuserservicedb")) {
        UserService user_service;
        EXPECT_FALSE(user_service.isUserRegistered("UserJohnDoe"));
    } else {
        EXPECT_EQ(1, 0);
    }

}

TEST(UserService, GenerateTokenFromUsername) {
    DataBase* db = DataBase::getInstance();
    if (db->open("/tmp/testuserservicedb1")){
        UserService user_service;
        EXPECT_NE("", user_service.getSecurityToken("UserJoaneDoe"));
    } else {
        EXPECT_EQ(1, 0);
    }

}

TEST(UserService, GenerateDifferentTokensFromTwoUsernames) {
    DataBase* db = DataBase::getInstance();
    if (db->open("/tmp/testuserservicedb3")){
        UserService user_service;
        EXPECT_NE(user_service.getSecurityToken("UserJoaneDoes"), user_service.getSecurityToken("UserJoaneDoe"));
    } else {
        EXPECT_EQ(1, 0);
    }

}

TEST(UserService, GenerateTokenTwoTokensFromOneUsernameShoulReturnDifferentTokens) {
    DataBase* db = DataBase::getInstance();
    if (db->open("/tmp/testuserservicedb4")){
        UserService user_service;
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
    DataBase* db = DataBase::getInstance();
    if (db->open("/tmp/testuserservicedb5")){
        UserService user_service;
        std::string token = user_service.getSecurityToken("UserJoaneDoe");
        EXPECT_TRUE(user_service.isTokenValid("UserJoaneDoe", token));
    } else {
        EXPECT_EQ(1, 0);
    }

}

TEST(UserService, GenerateTokenAndValidateWithInvalidToken) {
    DataBase* db = DataBase::getInstance();
    if (db->open("/tmp/testuserservicedb6")){
        UserService user_service;
        std::string token = user_service.getSecurityToken("UserJoaneDoe");
        EXPECT_FALSE(user_service.isTokenValid("UserJoaneDoe", "invalidtoken"));
    } else {
        EXPECT_EQ(1, 0);
    }

}

TEST(UserService, ValidateNullToken) {
    DataBase* db = DataBase::getInstance();
    if (db->open("/tmp/testuserservicedb7")){
        UserService user_service;
        std::string token = user_service.getSecurityToken("UserJoaneDoe");
        EXPECT_FALSE(user_service.isTokenValid("UserJoaneDoe", ""));
    } else {
        EXPECT_EQ(1, 0);
    }

}

TEST(UserService, ValidateNullUser) {
    DataBase* db = DataBase::getInstance();
    if (db->open("/tmp/testuserservicedb8")){
        UserService user_service;
        std::string token = user_service.getSecurityToken("UserJoaneDoe");
        EXPECT_FALSE(user_service.isTokenValid("", token));
    } else {
        EXPECT_EQ(1, 0);
    }

}

TEST(UserService, GetLikesWhithNoLike) {
    removeDataBase("/tmp/testuserservicedb9");
    DataBase* db = DataBase::getInstance();
    if (db->open("/tmp/testuserservicedb9")){
        UserService user_service;
        std::vector<std::string> likes = user_service.getLikes("JohnDoe");
        EXPECT_TRUE(likes.size() == 0);
    } else {
        EXPECT_EQ(1, 0);
    }

}

TEST(UserService, AddLikeReturnTrue) {
    DataBase* db = DataBase::getInstance();
    if (db->open("/tmp/testuserservicedb10")){
        UserService user_service;
        std::vector<std::string> likes = user_service.getLikes("JohnDoe");
        EXPECT_TRUE(user_service.addLike("JohnDoe", "Josi"));
    } else {
        EXPECT_EQ(1, 0);
    }

}

TEST(UserService, AddLikeReturnFalseIfDbIsClose) {
    DataBase* db = DataBase::getInstance();
    if (db->open("/tmp/testuserservicedb11")){
        UserService user_service;
        db->close();
        std::vector<std::string> likes = user_service.getLikes("JohnDoe");
        EXPECT_FALSE(user_service.addLike("JohnDoe", "Josi"));
    } else {
        EXPECT_EQ(1, 0);
    }

}

TEST(UserService, AddLikeShouldAddLikeToTheUser) {
    removeDataBase("/tmp/testuserservicedb12");
    DataBase* db = DataBase::getInstance();
    if (db->open("/tmp/testuserservicedb12")){
        UserService user_service;
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
    removeDataBase("/tmp/testuserservicedb13");
    DataBase* db = DataBase::getInstance();
    if (db->open("/tmp/testuserservicedb13")){
        UserService user_service;
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

TEST(UserService, AddSameLikeTwiceShouldAddLikeOnce) {
    removeDataBase("/tmp/testuserservicedb14");
    DataBase* db = DataBase::getInstance();
    if (db->open("/tmp/testuserservicedb14")){
        UserService user_service;
        std::vector<std::string> likes = user_service.getLikes("JohnDoe");
        EXPECT_TRUE(likes.size() == 0);
        user_service.addLike("JohnDoe", "Josi");
        likes = user_service.getLikes("JohnDoe");
        EXPECT_TRUE(likes.size() == 1);
        user_service.addLike("JohnDoe", "Josi");
        likes = user_service.getLikes("JohnDoe");
        EXPECT_TRUE(likes.size() == 1);
    } else {
        EXPECT_EQ(1, 0);
    }

}

TEST(UserService, HasLikeAfterAddShouldReturnTrue) {
    removeDataBase("/tmp/testuserservicedb15");
    DataBase* db = DataBase::getInstance();
    if (db->open("/tmp/testuserservicedb15")){
        UserService user_service;
        std::vector<std::string> likes = user_service.getLikes("JohnDoe");
        EXPECT_TRUE(likes.size() == 0);
        user_service.addLike("JohnDoe", "Josi");
        likes = user_service.getLikes("JohnDoe");
        EXPECT_TRUE(user_service.hasLike("JohnDoe", "Josi"));
    } else {
        EXPECT_EQ(1, 0);
    }

}

TEST(UserService, HasLikeBeforeAddShouldReturnFalse) {
    removeDataBase("/tmp/testuserservicedb16");
    DataBase* db = DataBase::getInstance();
    if (db->open("/tmp/testuserservicedb16")){
        UserService user_service;
        EXPECT_FALSE(user_service.hasLike("JohnDoe", "Josi"));
    } else {
        EXPECT_EQ(1, 0);
    }

}

TEST(UserService, AddLikeBetweenUsersShouldAddMatch) {
    removeDataBase("/tmp/testuserservicedb18");
    DataBase* db = DataBase::getInstance();
    if (db->open("/tmp/testuserservicedb18")){
        UserService user_service;
        user_service.addLike("JohnDoe", "Josi");
        EXPECT_TRUE(user_service.hasLike("JohnDoe", "Josi"));
        user_service.addLike("Josi", "JohnDoe");
        EXPECT_TRUE(user_service.hasLike("Josi", "JohnDoe"));
        EXPECT_TRUE(user_service.hasMatch("Josi", "JohnDoe"));
        EXPECT_TRUE(user_service.hasMatch("JohnDoe", "Josi"));
    } else {
        EXPECT_EQ(1, 0);
    }

}

TEST(UserService, AddLikeUserShouldNotAddMatch) {
    removeDataBase("/tmp/testuserservicedb19");
    DataBase* db = DataBase::getInstance();
    if (db->open("/tmp/testuserservicedb19")){
        UserService user_service;
        user_service.addLike("JohnDoe", "Josi");
        EXPECT_TRUE(user_service.hasLike("JohnDoe", "Josi"));
        EXPECT_FALSE(user_service.hasMatch("Josi", "JohnDoe"));
        EXPECT_FALSE(user_service.hasMatch("JohnDoe", "Josi"));
    } else {
        EXPECT_EQ(1, 0);
    }

}

TEST(UserService, AddDislikeShouldAddLikeToTheUser) {
    removeDataBase("/tmp/testuserservicedb20");
    DataBase* db = DataBase::getInstance();
    if (db->open("/tmp/testuserservicedb20")){
        UserService user_service;
        std::vector<std::string> dislikes = user_service.getDislikes("JohnDoe");
        EXPECT_TRUE(dislikes.size() == 0);
        user_service.addDislike("JohnDoe", "Josi");
        dislikes = user_service.getDislikes("JohnDoe");
        EXPECT_TRUE(dislikes.size() == 1);
    } else {
        EXPECT_EQ(1, 0);
    }

}

TEST(UserService, AddSeveralDislikesShouldAddDislikesToTheUser) {
    removeDataBase("/tmp/testuserservicedb21");
    DataBase* db = DataBase::getInstance();
    if (db->open("/tmp/testuserservicedb21")){
        UserService user_service;
        std::vector<std::string> dislikes = user_service.getDislikes("JohnDoe");
        EXPECT_TRUE(dislikes.size() == 0);
        user_service.addDislike("JohnDoe", "Josi");
        user_service.addDislike("JohnDoe", "Carmen");
        user_service.addDislike("JohnDoe", "Lara");
        dislikes = user_service.getDislikes("JohnDoe");
        EXPECT_TRUE(dislikes.size() == 3);
    } else {
        EXPECT_EQ(1, 0);
    }

}

TEST(UserService, AddSameDislikeTwiceShouldAddDislikeOnce) {
    removeDataBase("/tmp/testuserservicedb22");
    DataBase* db = DataBase::getInstance();
    if (db->open("/tmp/testuserservicedb22")){
        UserService user_service;
        std::vector<std::string> dislikes = user_service.getDislikes("JohnDoe");
        EXPECT_TRUE(dislikes.size() == 0);
        user_service.addDislike("JohnDoe", "Josi");
        dislikes = user_service.getDislikes("JohnDoe");
        EXPECT_TRUE(dislikes.size() == 1);
        user_service.addDislike("JohnDoe", "Josi");
        dislikes = user_service.getDislikes("JohnDoe");
        EXPECT_TRUE(dislikes.size() == 1);
    } else {
        EXPECT_EQ(1, 0);
    }

}

TEST(UserService, HasDislikeAfterAddDislikeShouldReturnTrue) {
    removeDataBase("/tmp/testuserservicedb23");
    DataBase* db = DataBase::getInstance();
    if (db->open("/tmp/testuserservicedb23")){
        UserService user_service;
        std::vector<std::string> dislikes = user_service.getDislikes("JohnDoe");
        EXPECT_TRUE(dislikes.size() == 0);
        user_service.addDislike("JohnDoe", "Josi");
        dislikes = user_service.getDislikes("JohnDoe");
        EXPECT_TRUE(user_service.hasDislike("JohnDoe", "Josi"));
    } else {
        EXPECT_EQ(1, 0);
    }

}

TEST(UserService, HasDislikeBeforeAddDislikeShouldReturnFalse) {
    removeDataBase("/tmp/testuserservicedb24");
    DataBase* db = DataBase::getInstance();
    if (db->open("/tmp/testuserservicedb24")){
        UserService user_service;
        EXPECT_FALSE(user_service.hasDislike("JohnDoe", "Josi"));
    } else {
        EXPECT_EQ(1, 0);
    }

}
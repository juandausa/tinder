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
    removeDataBase("/tmp/testuserservicedb12");
    DataBase db("/tmp/testuserservicedb12");
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

TEST(UserService, AddSameLikeTwiceShouldAddLikeOnce) {
    removeDataBase("/tmp/testuserservicedb13");
    DataBase db("/tmp/testuserservicedb13");
    if (db.is_open()) {
        UserService user_service(db);
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
    removeDataBase("/tmp/testuserservicedb14");
    DataBase db("/tmp/testuserservicedb14");
    if (db.is_open()) {
        UserService user_service(db);
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
    removeDataBase("/tmp/testuserservicedb15");
    DataBase db("/tmp/testuserservicedb15");
    if (db.is_open()) {
        UserService user_service(db);
        EXPECT_FALSE(user_service.hasLike("JohnDoe", "Josi"));
    } else {
        EXPECT_EQ(1, 0);
    }
}

TEST(UserService, AddLikeBetweenUsersShouldAddMatch) {
    removeDataBase("/tmp/testuserservicedb16");
    DataBase db("/tmp/testuserservicedb16");
    if (db.is_open()) {
        UserService user_service(db);
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
    removeDataBase("/tmp/testuserservicedb17");
    DataBase db("/tmp/testuserservicedb17");
    if (db.is_open()) {
        UserService user_service(db);
        user_service.addLike("JohnDoe", "Josi");
        EXPECT_TRUE(user_service.hasLike("JohnDoe", "Josi"));
        EXPECT_FALSE(user_service.hasMatch("Josi", "JohnDoe"));
        EXPECT_FALSE(user_service.hasMatch("JohnDoe", "Josi"));
    } else {
        EXPECT_EQ(1, 0);
    }
}

TEST(UserService, AddDislikeShouldAddLikeToTheUser) {
    removeDataBase("/tmp/testuserservicedb18");
    DataBase db("/tmp/testuserservicedb18");
    if (db.is_open()) {
        UserService user_service(db);
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
    removeDataBase("/tmp/testuserservicedb19");
    DataBase db("/tmp/testuserservicedb19");
    if (db.is_open()) {
        UserService user_service(db);
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
    removeDataBase("/tmp/testuserservicedb20");
    DataBase db("/tmp/testuserservicedb20");
    if (db.is_open()) {
        UserService user_service(db);
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
    removeDataBase("/tmp/testuserservicedb21");
    DataBase db("/tmp/testuserservicedb21");
    if (db.is_open()) {
        UserService user_service(db);
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
    removeDataBase("/tmp/testuserservicedb22");
    DataBase db("/tmp/testuserservicedb22");
    if (db.is_open()) {
        UserService user_service(db);
        EXPECT_FALSE(user_service.hasDislike("JohnDoe", "Josi"));
    } else {
        EXPECT_EQ(1, 0);
    }
}
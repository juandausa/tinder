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

TEST(UserService, IsUserRegisteredWithUserPreviouslyRegister) {
    DataBase db("/tmp/testuserservicedb2");
    db.set("UserJoaneDoe", "value");
    if (db.is_open()) {
        UserService user_service(db);
        EXPECT_TRUE(user_service.is_user_registered("UserJoaneDoe"));
    } else {
        EXPECT_EQ(1, 0);
    }
}

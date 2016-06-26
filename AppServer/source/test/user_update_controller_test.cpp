//
// Created by juan on 21/06/16.
//

#include "user_update_controller_test.h"

TEST(UserUpdateController, CreateBodyForNotExistingUser) {
    DataBase* db = DataBase::getInstance();
    if (db->open("/tmp/testuserupdatecontrollerdb")) {
        UserService user_service;
        UpdateUserInfoController userInfoController;
        std::string body = userInfoController.makeBodyUserInfoForUpdate("{ \"user_id\": \"idausa\",\"name\": \"Nacho Dausa\",\"birthday\": \"02/07/1985\",\"gender\": \"male\",\"alias\": \"idausa\",\"email\": \"idausa@usuario.com\",\"photo_profile\": \"\",\"interests\": {\"music\": [],\"movies\": [],\"likes\": [],\"television\": [],\"games\": [],\"books\": []},\"location\": {\"latitude\": 11.45356,\"longitude\": 46.51119}}", "-500", "347");
        EXPECT_EQ(body.compare(""), 0);
    }
}

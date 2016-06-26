//
// Created by juan on 21/06/16.
//

#include "user_register_controller_test.h"

TEST(UserRegisterController, CreateBody) {
    DataBase* db = DataBase::getInstance();
    if (db->open("/tmp/testuserregistercontroller1")) {
        UserService user_service;
        UserRegisterController userRegisterController;
        Json::Value root;
        Json::Reader reader;
        bool parsingSuccessful = reader.parse("{ \"user_id\": \"idausa\",\"name\": \"Nacho Dausa\",\"birthday\": \"02/07/1985\",\"gender\": \"male\",\"alias\": \"idausa\",\"email\": \"idausa@usuario.com\",\"photo_profile\": \"\",\"interests\": {\"music\": [],\"movies\": [],\"likes\": [],\"television\": [],\"games\": [],\"books\": []},\"location\": {\"latitude\": 11.45356,\"longitude\": 46.51119}}", root, true);
        if (parsingSuccessful) {
            Json::Value body = userRegisterController.makeBodyForRegistrationPost(root, "idausa");
            EXPECT_FALSE(body.empty());
        }
    }
}


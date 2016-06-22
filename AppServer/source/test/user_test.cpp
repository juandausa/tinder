//
// Created by juan on 05/04/16.
//

#include "include/user_test.h"


TEST(User, ConstructorWithoutParams) {
    EXPECT_NO_THROW(User user);
}

TEST(User, ConstructorWithParams) {
    Json::Value root;
    Json::Reader reader;
    if (reader.parse("{ \"user_id\": \"idausa\",\"name\": \"Nacho Dausa\",\"birthday\": \"02/07/1985\",\"gender\": \"male\",\"alias\": \"idausa\",\"email\": \"idausa@usuario.com\",\"photo_profile\": \"\",\"interests\": {\"music\": [\"music1\", \"music2\"],\"movies\": [\"movie1\", \"movie2\"],\"likes\": [\"like1\", \"like2\"],\"television\": [\"tv1\", \"tv2\"],\"games\": [\"game1\", \"game2\"],\"books\": [\"book1\", \"book2\"],\"gender\": \"male\"},\"location\": {\"latitude\": 11.45356,\"longitude\": 46.51119}}", root, true)) {
        EXPECT_NO_THROW(User user(root));
    }
}


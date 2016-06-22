//
// Created by juan on 21/06/16.
//

#include "matches_controller_test.h"

TEST(MatchesController, CreateBody) {
    DataBase *db = DataBase::getInstance();
    if (db->open("/tmp/testmatchescontroller")) {
        MatchesController matchesController;
        std::string userId = "34";
        db->set(userId, userId);
        std::string body = matchesController.makeBodyForShowMatchesResponse(userId);
        EXPECT_FALSE(body.length() == 0);
    }
}
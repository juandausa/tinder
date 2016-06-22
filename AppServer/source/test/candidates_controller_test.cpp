//
// Created by juan on 21/06/16.
//

#include "include/candidates_controller_test.h"

TEST(CandidatesController, Create) {
    DataBase *db = DataBase::getInstance();
    if (db->open("/tmp/testcandidatescontroller")) {
        GetCandidatesController getCandidatesController;
        std::string body = getCandidatesController.makeBodyForUserInfoResponse("43",
                                                                               "{\"user\": {\"id\": 1,\"name\": \"usuario\",\"alias\": \"not a user\",\"email\": \"usuario @usuario.com\",\"sex\": \"male\",\"age\": 30,\"photo_profile\": \"\",\"interests\": [{\"category\": \"music/band\",\"value\": \"michael jackson\"}, {\"category\": \"music/band\",\"value\": \"pearl jam\"}, {\"category\": \"outdoors\",\"value\": \"running\"}],\"location\": {\"latitude\": 121.45356,\"longitude\": 46.51119}},\"metadata\": {\"version\": \"0.1\"}}");
        EXPECT_FALSE(body.length() == 0);
    }
}
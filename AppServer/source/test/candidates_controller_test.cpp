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

TEST(CandidatesController, GetGenderOfInterest) {
    DataBase *db = DataBase::getInstance();
    if (db->open("/tmp/testcandidatescontroller2")) {
        GetCandidatesController getCandidatesController;
        Json::Reader reader;
        Json::Value interests;
        std::string json = "[{\"category\": \"music/band\",\"value\": \"michael jackson\"}, {\"category\": \"music/band\",\"value\": \"pearl jam\"}, {\"category\": \"outdoors\",\"value\": \"running\"}]";
        reader.parse(json, interests, true);
        EXPECT_EQ("male|female", getCandidatesController.genderOfMyPreference(interests));
    } else {
        EXPECT_EQ(0, 1);
    }
}

TEST(CandidatesController, IsInMyArrayOfInterestsShouldReturnFalse) {
    DataBase *db = DataBase::getInstance();
    if (db->open("/tmp/testcandidatescontroller4")) {
        GetCandidatesController getCandidatesController;
        Json::Reader reader;
        Json::Value interests, music;
        std::string jsonInterests = "[{\"category\": \"music/band\",\"value\": \"michael jackson\"}, {\"category\": \"music/band\",\"value\": \"pearl jam\"}, {\"category\": \"outdoors\",\"value\": \"running\"}]";
        std::string jsonMusicInterest = "[{\"category\": \"music/band\",\"value\": \"Madona\"}]";
        reader.parse(jsonInterests, interests, true);
        reader.parse(jsonMusicInterest, music, true);
        EXPECT_FALSE(getCandidatesController.isInMyArrayOfInterest(music, interests));
    } else {
        EXPECT_EQ(0, 1);
    }
}

TEST(CandidatesController, UserCountOfRequest) {
    DataBase *db = DataBase::getInstance();
    if (db->open("/tmp/testcandidatescontroller5")) {
        db->set("43", "657");
        time_t rawtime;
        time(&rawtime);
        std::string date = ctime(&rawtime);
        date = date.substr(0, date.size() - 14);
        db->set(date + "43", "1");
        GetCandidatesController getCandidatesController;
        EXPECT_FALSE(getCandidatesController.exceedsCandidatesCountPerDay("43"));
    } else {
        EXPECT_EQ(0, 1);
    }
}

TEST(CandidatesController, UserCheckPreviousMatch) {
    DataBase *db = DataBase::getInstance();
    if (db->open("/tmp/testcandidatescontroller6")) {
        GetCandidatesController getCandidatesController;
        EXPECT_FALSE(getCandidatesController.hasUserPreviousMatch("33", "44"));
    } else {
        EXPECT_EQ(0, 1);
    }
}
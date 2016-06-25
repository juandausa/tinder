//
// Created by juan on 21/06/16.
//

#include "matches_service_test.h"

TEST(MatchesService, GetPhoto) {
    DataBase *db = DataBase::getInstance();
    if (db->open("/tmp/testmatchesservice1")) {
        MatchesService matchesService;
        EXPECT_NE("", matchesService.getMatchPhoto("http://www.clarin.com/static/CLAClarinV3/images/logo.png"));
    }
}
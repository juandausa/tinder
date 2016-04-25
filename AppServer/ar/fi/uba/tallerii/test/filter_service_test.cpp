//
// Created by juan on 25/04/16.
//

#include "filter_service_test.h"

TEST(FilterTest, GetFiltersWithoutPreviousUpdate) {
    DataBase db("/tmp/testfilterservicedb");
    if (db.is_open()) {
        FilterService filter_service(db);
        std::string filters = filter_service.get_filters("UserJoaneDoe");
        EXPECT_EQ(filters, "");
    } else {
        EXPECT_EQ(1, 0);
    }
}

TEST(FilterTest, UpdateFilters) {
    DataBase db("/tmp/testfilterservicedb2");
    if (db.is_open()) {
        FilterService filter_service(db);
        EXPECT_TRUE(filter_service.update_filters("UserJoaneDoe", "Some random text."));
    } else {
        EXPECT_EQ(1, 0);
    }
}


TEST(FilterTest, UpdateAndGetFilters) {
    std::string filters = "Some random text. Bla Bla";
    DataBase db("/tmp/testfilterservicedb4");
    if (db.is_open()) {
        FilterService filter_service(db);
        EXPECT_TRUE(filter_service.update_filters("UserJoaneDoe", filters));
        EXPECT_EQ(filter_service.get_filters("UserJoaneDoe"), filters);
    } else {
        EXPECT_EQ(1, 0);
    }
}

TEST(FilterTest, UpdateAndGetFiltersWrongValueExpected) {
    std::string filters = "Some random text. Bla Bla";
    DataBase db("/tmp/testfilterservicedb4");
    if (db.is_open()) {
        FilterService filter_service(db);
        EXPECT_TRUE(filter_service.update_filters("UserJoaneDoe", filters));
        EXPECT_NE(filter_service.get_filters("UserJoaneDoe"), filters + "other");
    } else {
        EXPECT_EQ(1, 0);
    }
}
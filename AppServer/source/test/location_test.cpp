//
// Created by juan on 05/04/16.
//

#include "include/location_test.h"


TEST(Location, ConstructorWithoutParams) {
    Location location;
    EXPECT_LE(location.getLatitude(), 0);
    EXPECT_LE(location.getLongitude(), 0);
}

TEST(Location, ConstructorWithParams) {
    Location location(1,1);
    EXPECT_LE(location.getLatitude(), 1);
    EXPECT_LE(location.getLongitude(), 1);
}

TEST(Location, Setters) {
    Location location;
    location.setLatitude(1);
    location.setLongitude(2);
    EXPECT_LT(location.getLatitude(), 1.1);
    EXPECT_LT(location.getLongitude(), 2.1);
    EXPECT_GT(location.getLatitude(), 0.9);
    EXPECT_GT(location.getLongitude(), 1.9);
}
//
// Created by juan on 22/04/16.
//

#include "include/md5_test.h"
#include <string>

TEST(MD5, GetHashFromString) {
    EXPECT_NE(md5("grape"), "");
}

TEST(MD5, GetSameHashFromString) {
    std::string first_hash, second_hash;
    first_hash = md5("this is a test");
    second_hash = md5("this is a test");
    EXPECT_EQ(first_hash, second_hash);
}

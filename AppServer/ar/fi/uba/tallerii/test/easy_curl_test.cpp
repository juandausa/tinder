//
// Copyright 2016 FiUBA
//

#include "include/easy_curl_test.h"

TEST(EasyCurl, GetNotExistingSiteShouldNotWork) {
    EasyCurl curl("www.claringrillaargentina.com.ar");
    EXPECT_FALSE(curl.Perform());
}

TEST(EasyCurl, GetExistingSite) {
    EasyCurl curl("www.google.com");
    EXPECT_TRUE(curl.Perform());
}

TEST(EasyCurl, GetContentOfExistingSite) {
    EasyCurl curl("www.google.com");
    std::string content = curl.StringPerform();
    EXPECT_TRUE(content.length() != 0);
}
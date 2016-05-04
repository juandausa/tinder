//
// Created by juan on 04/05/16.
//

#include "include/easy_curl_test.h"

TEST(EasyCurl, GetNotExistingSiteReturnFalse) {
    /*CurlWrapper curl_wrapper;
    curl_wrapper.set_post_url("www.claringrillaargentina.com.ar");
    curl_wrapper.set_post_data("");
    EXPECT_FALSE(curl_wrapper.perform_request());
    curl_wrapper.clean();
    curl_global_cleanup();*/
    EasyCurl curl("www.claringrillaargentina.com.ar");
    EXPECT_FALSE(curl.Perform());
}
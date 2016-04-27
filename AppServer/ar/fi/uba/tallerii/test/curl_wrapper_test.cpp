//
// Created by juan on 27/04/16.
//

#include "include/curl_wrapper_test.h"

TEST(CurlWrapper, PostNotExistingSiteReturnFalse) {
    CurlWrapper curl_wrapper;
    curl_wrapper.set_post_url("www.claringrillaargentina.com.ar");
    curl_wrapper.set_post_data("");
    EXPECT_FALSE(curl_wrapper.perform_request());
    curl_wrapper.clean();
}
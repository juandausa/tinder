//
// Created by juan on 27/04/16.
//

#include "include/curl_wrapper_test.h"

TEST(CurlWrapper, PostNotExistingSiteReturnFalse) {
    CurlWrapper curl_wrapper;
    std::string buffer;
    curl_wrapper.set_post_url("www.claringrillaargentina.com.ar");
    curl_wrapper.set_post_data("", buffer);
    EXPECT_FALSE(curl_wrapper.perform_request());
    curl_wrapper.clean();
    curl_global_cleanup();
}
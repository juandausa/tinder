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

TEST(CurlWrapper, PutContentOnExistingSiteReturnContent) {
    CurlWrapper curlWrapper = CurlWrapper();
    std::string url = "http://jsonplaceholder.typicode.com/posts/1";
    std::string readBuffer;
    curlWrapper.set_post_url(url);
    curlWrapper.set_put_data("{ \"id\": \"1\", \"title\": \"foo\", \"body\": \"bar\", \"userId\": \"1\" }", readBuffer);
    bool res = curlWrapper.perform_request();
    EXPECT_TRUE(res);
    EXPECT_NE("{}", readBuffer.c_str());
    curlWrapper.clean();
    curl_global_cleanup();
}
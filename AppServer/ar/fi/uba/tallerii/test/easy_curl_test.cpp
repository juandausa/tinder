//
// Copyright 2016 FiUBA
//

#include "include/easy_curl_test.h"

TEST(EasyCurl, GetOnNotExistingSiteShouldNotWork) {
    EasyCurl curl("www.claringrillaargentina.com.ar");
    EXPECT_FALSE(curl.Perform());
}

TEST(EasyCurl, GetContentOfExistingSite) {
    EasyCurl curl("www.google.com");
    std::string content = curl.StringPerform();
    EXPECT_TRUE(content.length() != 0);
}

TEST(EasyCurl, GetContentOfExistingSiteReturnContent) {
    EasyCurl curl("http://www.example.com");
    std::string content = curl.StringPerform();
    EXPECT_EQ("<!doctype html><html><head>    <title>Example Domain</title>    <meta charset=\"utf-8\" />    <meta http-equiv=\"Content-type\" content=\"text/html; charset=utf-8\" />    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\" />    <style type=\"text/css\">    body {        background-color: #f0f0f2;        margin: 0;        padding: 0;        font-family: \"Open Sans\", \"Helvetica Neue\", Helvetica, Arial, sans-serif;            }    div {        width: 600px;        margin: 5em auto;        padding: 50px;        background-color: #fff;        border-radius: 1em;    }    a:link, a:visited {        color: #38488f;        text-decoration: none;    }    @media (max-width: 700px) {        body {            background-color: #fff;        }        div {            width: auto;            margin: 0 auto;            border-radius: 0;            padding: 1em;        }    }    </style>    </head><body><div>    <h1>Example Domain</h1>    <p>This domain is established to be used for illustrative examples in documents. You may use this    domain in examples without prior coordination or asking for permission.</p>    <p><a href=\"http://www.iana.org/domains/example\">More information...</a></p></div></body></html>", content);
}

TEST(EasyCurl, PostOnExistingSite) {
    EasyCurl curl("http://jsonplaceholder.typicode.com/posts");
    curl.SetParms("");
    std::string content = curl.StringPerform();
    EXPECT_TRUE(content.length() != 0);
}

TEST(EasyCurl, PostOnExistingSiteReturnContent) {
    EasyCurl curl("http://jsonplaceholder.typicode.com/posts");
    curl.SetParms("");
    std::string content = curl.StringPerform();
    EXPECT_EQ("{  \"id\": 101}", content);
}

TEST(EasyCurl, PutOnExistingSiteReturnContent) {
    EasyCurl curl("http://jsonplaceholder.typicode.com/posts/1");
    curl.SetParms("");
    curl.ForcePut();
    std::string content = curl.StringPerform();
    EXPECT_EQ("{  \"id\": 1}", content);
}

TEST(EasyCurl, PutContentOnExistingSiteReturnContent) {
    EasyCurl curl("http://jsonplaceholder.typicode.com/posts/1");
    curl.SetParms("{ \"id\": \"1\", \"title\": \"foo\", \"body\": \"bar\", \"userId\": \"1\" }");
    curl.ForcePut();
    std::string content = curl.StringPerform();
    EXPECT_EQ("{  \"{ \\\"id\\\": \\\"1\\\", \\\"title\\\": \\\"foo\\\", \\\"body\\\": \\\"bar\\\", \\\"userId\\\": \\\"1\\\" }\": \"\",  \"id\": 1}", content);
}
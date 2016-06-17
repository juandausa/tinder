//
// Copyright 2016 FiUBA
//

#include "include/response_test.h"

TEST(Response, TestSetAndGetCode) {
    struct mg_connection nc;
    int code = 200;
    Response response(&nc);
    response.SetCode(code);
    EXPECT_EQ(code, response.GetCode());
}

TEST(Response, TestSetWrongCodeAndGet) {
    struct mg_connection nc;
    int code = 1200;
    Response response(&nc);
    response.SetCode(code);
    EXPECT_NE(code, response.GetCode());
}

TEST(Response, TestSetWrongCodeAndGetDefaultCode) {
    struct mg_connection nc;
    int code = 1200;
    Response response(&nc);
    response.SetCode(code);
    EXPECT_EQ(DEFAUTLRESPONSE, response.GetCode());
}

TEST(Response, TestSetAndGetBody) {
    struct mg_connection nc;
    std::string body("This is a body");
    Response response(&nc);
    response.SetBody(body);
    EXPECT_EQ(body, response.GetBody());
}

TEST(Response, TestGetHeadersBeforeSet) {
    struct mg_connection nc;
    Response response(&nc);
    EXPECT_TRUE(response.GetHeaders().empty());
}

TEST(Response, TestSetAndGetHeaders) {
    struct mg_connection nc;
    Response response(&nc);
    std::pair<std::string, std::string> header("key", "value");
    response.AddHeader(header.first, header.second);
    EXPECT_EQ(header, response.GetHeaders()[0]);
}

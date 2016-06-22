//
// Copyright 2016 FiUBA
//

#include "include/request_test.h"

TEST(Request, TestCreateRequest) {
    struct mg_connection nc;
    int code = 200;
    Response response(&nc);
    response.SetCode(code);
    Request request(response);
    request.getBody();
    request.getMethod();
    request.getUrl();
    request.handleOperation();
    request.getResourceId();
    EXPECT_EQ("", request.getBody());
}

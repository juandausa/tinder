//
// Created by juan on 25/06/16.
//

#include "request_test.h"
#include <Mongoose.h>

TEST(Request, Constructor) {
    mg_connection conn;
    Response response(&conn);
    Request request(response);
    EXPECT_EQ("", request.getBody());
    EXPECT_EQ("", request.getMethod());
    EXPECT_EQ("", request.getResourceId());
    EXPECT_EQ("", request.getUrl());
}

TEST(Request, HandleOp) {
    mg_connection conn;
    Response response(&conn);
    Request request(response);
    EXPECT_NO_THROW(request.handleOperation());
}
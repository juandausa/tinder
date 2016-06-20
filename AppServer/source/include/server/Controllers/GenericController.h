//
// Created by agu on 27/04/16.
//

#ifndef TINDER_GENERIC_CONTROLLER_H
#define TINDER_GENERIC_CONTROLLER_H

#include "Mongoose.h"
#include <string>
#include <jsoncpp/json/json.h>
#include "CurlWrapper.h"
#include "Constant.h"
#include "Request.h"
#include "Response.h"


class Request;
class GenericController{
public:
    void operation(Request &request, Response &response);
protected:
    CurlWrapper curlWrapper;
    Json::Reader reader;
    Json::FastWriter fastWriter;      
};

#endif //TINDER_GENERIC_CONTROLLER_H

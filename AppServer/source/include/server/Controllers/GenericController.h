//
// Created by agu on 27/04/16.
//

#ifndef TINDER_GENERIC_CONTROLLER_H
#define TINDER_GENERIC_CONTROLLER_H

#include <string>
#include <jsoncpp/json/json.h>
#include "CurlWrapper.h"
#include "Constant.h"
#include "Request.h"
#include "Response.h"
#include "Log.h"
#include "Converter.h"

class Request;
class GenericController{
public:
	GenericController();
	virtual ~GenericController();
    virtual void operation(Request &request, Response &response);
protected:
    Log* log;
    CurlWrapper curlWrapper;
    Json::Reader reader;
    Json::FastWriter fastWriter;      
    std::string getErrorResponseBody();
	std::string getSucceedResponseBody();
};

#endif //TINDER_GENERIC_CONTROLLER_H

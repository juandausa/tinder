//
// Created by agu on 27/04/16.
//

#ifndef TINDER_REQUEST_H
#define TINDER_REQUEST_H

#include "Mongoose.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "Response.h"
#include "GenericController.h"

class GenericController;
class Request {
public:
    Request(Response &response);
    ~Request();
    void parse(struct http_message *hm);
    std::string getUrl();
    std::string getResourceId();
    std::string getMethod();
    std::string getBody();
    
    void handleOperation();
    void execute();

private:
    Response response;
    std::string uri;
    std::string resourceId;
    std::string method;
    std::string body;
    GenericController *genericController;

    bool isUserLoginRequest();
    bool isUserRegisterRequest();
    bool isUserInfoRequest();
    bool isUserUpdateRequest();
    bool isFiltersGetRequest();
    bool isFiltersPostRequest();
    bool isCandidatesGetRequest();
    bool isMatchesGetRequest();
    bool isAddLikeRequest();
    bool isAddDislikeRequest();
    bool isAddMessagesRequest();
    bool isGetMessagesRequest();
};


#endif //TINDER_REQUEST_H

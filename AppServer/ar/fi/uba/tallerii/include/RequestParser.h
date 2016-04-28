//
// Created by agu on 27/04/16.
//

#ifndef TINDER_REQUESTPARSER_H
#define TINDER_REQUESTPARSER_H

#include "Mongoose.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

class RequestParser {
public:
    void parse(struct http_message *hm);
    std::string getUrl();
    std::string getResourceId();
    std::string getMethod();
    std::string getBody();

    bool isUserLoginRequest();
    bool isUserRegisterRequest();
    bool isUserInfoRequest();
    bool isUserUpdateRequest();
    bool isFiltersGetRequest();
    bool isFiltersPostRequest();
    bool isCandidatesGetRequest();
    bool isMatchesGetRequest();
private:
    std::string uri;
    std::string resourceId;
    std::string method;
    std::string body;
};


#endif //TINDER_REQUESTPARSER_H

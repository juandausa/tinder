//
// Created by juan on 05/04/16.
//

#ifndef TINDER_USERCONTROLLER_H
#define TINDER_USERCONTROLLER_H
#include <jsoncpp/json/json.h>
#include <glog/logging.h>
#include "Mongoose.h"
#include "Response.h"
#include "DataBase.h"
#include "UserService.h"
#include "CurlWrapper.h"

class UserController {
public:
    UserController(UserService user_service);
    virtual void handleLogin(struct mg_connection *nc, struct http_message *hm, Response response);
    virtual void handleRegistration(struct mg_connection *nc, struct http_message *hm, Response response);
    virtual void handleGetUserInfo(struct mg_connection *nc, struct http_message *hm, Response response);
    virtual void handleUpdateUserInfo(struct mg_connection *nc, struct http_message *hm, Response response);
    virtual void handleShowCandidates(struct mg_connection *nc, struct http_message *hm, Response response, std::string userId);
    virtual void handleGetMatches(struct mg_connection *nc, struct http_message *hm, Response response);
private:
    UserService userService;
    std::string fakeResponseForUserInfo(const std::string userId);
    std::string fakeResponseForUserMatches();
    Json::Value makeBodyForLoginResponse(const std::string userId);
    Json::Value makeBodyForRegistrationPost(const Json::Value root);
    Json::Value makeBodyForShowCandidatesResponse();
    void postInterests(const Json::Value root);
};


#endif //TINDER_USERCONTROLLER_H

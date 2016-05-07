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
#include "EasyCurl.h"
#include "Constant.h"
#include <RequestParser.h>
class UserController {
public:
    UserController(UserService user_service);
    virtual void handleLogin(RequestParser requestParser,Response response);
    virtual void handleRegistration(RequestParser requestParser, Response response);
    virtual void handleGetUserInfo(RequestParser requestParser, Response response);
    virtual void handleUpdateUserInfo(RequestParser requestParser, Response response);
    virtual void handleShowCandidates(RequestParser requestParser, Response response);
    virtual void handleGetMatches(RequestParser requestParser, Response response);
private:
    UserService userService;
    std::string fakeResponseForUserMatches();
    Json::Value makeBodyForLoginResponse(const std::string userId);
    Json::Value makeBodyForRegistrationPost(const Json::Value root);
    Json::Value makeBodyForShowCandidatesResponse();
    void postInterests(const Json::Value root);
};


#endif //TINDER_USERCONTROLLER_H

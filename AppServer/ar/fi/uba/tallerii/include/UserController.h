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
#include "CandidatesService.h"

class UserController {
public:
    UserController(UserService user_service);
    virtual void handleLogin(RequestParser requestParser,Response response);
    virtual void handleRegistration(RequestParser requestParser, Response response);
    virtual std::string handleGetUserInfo(RequestParser requestParser, Response response, bool send);
    virtual void handleUpdateUserInfo(RequestParser requestParser, Response response);
    virtual void handleGetCandidates(RequestParser requestParser, Response response);
    virtual void handleGetMatches(RequestParser requestParser, Response response);
    virtual void handleAddLike(RequestParser requestParser, Response response);
    virtual void handleAddDislike(RequestParser requestParser, Response response);

private:
    UserService userService;
    Json::Reader reader;
    Json::FastWriter fastWriter;
    std::string fakeResponseForUserMatches();
    Json::Value makeBodyAndTokenForLoginResponse(const std::string userId);
    Json::Value makeBodyAndTokenForRegistrationResponse(const std::string userId);
    Json::Value makeBodyForRegistrationPost(const Json::Value root);
    std::string makeBodyForUserInfoResponse(const std::string appUserId, const std::string userInfo);
    std::string makeBodyUserInfoForUpdate(const std::string info, const std::string userId);
    Json::Value makeBodyForShowCandidatesResponse(const std::string genderOfInterest, Json::Value myArrayOfInterests);
    bool isInMyArrayOfInterest(Json::Value interest, Json::Value myArrayOfInterests);
    void postInterests(const Json::Value root);
    std::string getUserTo(const std::string body);
};


#endif //TINDER_USERCONTROLLER_H

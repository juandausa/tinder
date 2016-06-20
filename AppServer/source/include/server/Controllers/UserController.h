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
#include "Constant.h"
#include <RequestParser.h>
#include "CandidatesService.h"

class UserController {
public:
    UserController(UserService user_service);
    void setUrl(std::string url);
    void handleLogin(RequestParser requestParser,Response response);
    void handleRegistration(RequestParser requestParser, Response response);
    std::string handleGetUserInfo(RequestParser requestParser, Response response, bool send);
    void handleUpdateUserInfo(RequestParser requestParser, Response response);
    void handleGetCandidates(RequestParser requestParser, Response response);
    void handleGetMatches(RequestParser requestParser, Response response);
    void handleAddLike(RequestParser requestParser, Response response);
    void handleAddDislike(RequestParser requestParser, Response response);

private:
    CurlWrapper curlWrapper;
    UserService userService;
    Json::Reader reader;
    Json::FastWriter fastWriter;
    std::string fakeResponseForUserMatches();
    Json::Value makeBodyAndTokenForLoginResponse(const std::string userId);
    Json::Value makeBodyAndTokenForRegistrationResponse(const std::string userId);
    Json::Value makeBodyForRegistrationPost(const Json::Value root);
    std::string makeBodyForUserInfoResponse(const std::string appUserId, const std::string userInfo);
    std::string makeBodyUserInfoForUpdate(const std::string info, const std::string userId);
    Json::Value makeBodyForShowCandidatesResponse(Json::Value userData, const std::string genderOfInterest, Json::Value myArrayOfInterests);
    bool isInMyArrayOfInterest(Json::Value interest, Json::Value myArrayOfInterests);
    void postInterests(const Json::Value root);
    std::string getUserTo(const std::string body);
};


#endif //TINDER_USERCONTROLLER_H

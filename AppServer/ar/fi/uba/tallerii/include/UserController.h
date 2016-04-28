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
    virtual void handle_login(struct mg_connection *nc, struct http_message *hm, Response response);
    virtual void handle_registration(struct mg_connection *nc, struct http_message *hm, Response response);
    virtual void handle_get_user_info(struct mg_connection *nc, struct http_message *hm, Response response);
    virtual void handle_update_user_info(struct mg_connection *nc, struct http_message *hm, Response response);
    virtual void handle_get_matches(struct mg_connection *nc, struct http_message *hm, Response response);
private:
    UserService userService;
    Json::Value makeBodyForLoginResponse(const std::string userId);
    Json::Value makeBodyForRegistrationPost(const Json::Value root);
    void postInterests(Json::Value root);
    std::string fakeResponseForUserInfo(std::string userId);
    std::string fakeResponseForUserMatches();
};


#endif //TINDER_USERCONTROLLER_H

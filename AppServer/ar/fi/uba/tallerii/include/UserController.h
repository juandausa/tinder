//
// Created by juan on 05/04/16.
//

#ifndef TINDER_USERCONTROLLER_H
#define TINDER_USERCONTROLLER_H
#include "Mongoose.h"
#include "Response.h"
#include "DataBase.h"
#include "UserService.h"

class UserController {
public:
    UserController(UserService user_service);
    void handle_login(struct mg_connection *nc, struct http_message *hm, Response response);
    void handle_registration(struct mg_connection *nc, struct http_message *hm, Response response);
private:
    std::string make_body(std::string user_id);
    bool is_user_registered(std::string user_id);
    UserService user_service;
};


#endif //TINDER_USERCONTROLLER_H

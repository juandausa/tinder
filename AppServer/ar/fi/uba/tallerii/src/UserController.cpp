//
// Copyright 2016 FiUBA
//

#include "UserController.h"
#include "UserService.h"
#include "Response.h"
#include "DataBase.h"
#include <glog/logging.h>
#include <string>

UserController :: UserController(UserService user_service) : user_service(user_service) {
}

void UserController :: handle_login(struct mg_connection *nc, struct http_message *hm, Response response) {
    char user_id[255];
    mg_get_http_var(&hm->query_string, "userId", user_id, sizeof(user_id));
    LOG(INFO) << "Proccesing login for user: " << user_id << ".";
    if (this->user_service.is_user_registered(user_id)) {
        response.SetCode(200);
        response.SetBody(this->make_body(user_id));
        response.Send();
        LOG(INFO) << "Login succeeded for user: " << user_id << ".";
    } else {
        response.SetCode(304);
        response.SetBody(this->make_body(user_id));
        response.Send();
        LOG(INFO) << "Login failed for user: " << user_id << ".";
    }
}

void UserController :: handle_registration(struct mg_connection *nc, struct http_message *hm, Response response) {

}

std::string UserController :: make_body(std::string user_id) {
    std::string body("{ \"user\": { \"userId\" : \"");
    body.append(user_id).append("\" } }");
    return body;
}

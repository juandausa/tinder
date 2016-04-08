//
// Copyright 2016 FiUBA
//

#include "UserController.h"
#include "Response.h"
#include <glog/logging.h>
#include <string>

UserController :: UserController() {
}

void UserController :: handle_login(struct mg_connection *nc, struct http_message *hm, Response response) {
    char user_id[255];
    mg_get_http_var(&hm->query_string, "userId", user_id, sizeof(user_id));
    LOG(INFO) << "Proccesing login for user: " << user_id << ".";
    response.SetCode(200);
    response.SetBody(this->make_body(user_id));
    response.Send();
    LOG(INFO) << "Login succeeded for user: " << user_id << ".";
}

std::string UserController :: make_body(std::string user_id) {
    std::string body("{ \"user\": { \"userId\" : \"");
    body.append(user_id).append("\" } }");
    return body;
}

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

/* Private methods declarion */
std::string make_body_for_login_response(const std::string user_id, const std::string token);
/* End private methods */

void UserController :: handle_login(struct mg_connection *nc, struct http_message *hm, Response response) {
    char user_id[255];
    mg_get_http_var(&hm->query_string, "userId", user_id, sizeof(user_id));
    LOG(INFO) << "Proccesing login for user: '" << user_id << "'";
    if (this->user_service.is_user_registered(user_id)) {
        response.SetCode(200);
        std::string token = user_service.get_securiry_token(user_id);
        response.SetBody(make_body_for_login_response(user_id, token));
        response.Send();
        LOG(INFO) << "Login succeeded for user: '" << user_id << "'";
    } else {
        response.SetCode(304);
        response.Send();
        LOG(INFO) << "Login failed for user: '" << user_id << "'";
    }
}

void UserController :: handle_registration(struct mg_connection *nc, struct http_message *hm, Response response) {
    char user_id[255];
    char name[255];
    char birthday[255];
    char alias[255];
    char email[255];
    char photo_profile[255];
    // TODO(jasmina): ver como manejar estas estructuras:
    // char interests[255];
    // char location[255];
    mg_get_http_var(&hm->body, "userId", user_id, sizeof(user_id));
    mg_get_http_var(&hm->body, "name", name, sizeof(name));
    mg_get_http_var(&hm->body, "birthday", birthday, sizeof(birthday));
    mg_get_http_var(&hm->body, "alias", alias, sizeof(alias));
    mg_get_http_var(&hm->body, "email", email, sizeof(email));
    mg_get_http_var(&hm->body, "photo_profile", photo_profile, sizeof(photo_profile));
    LOG(INFO) << "Proccesing registration for user: " << user_id << " ; name: " << name
            << " ; birthday: " << birthday <<" ;alias: " <<alias <<"; email: " << email
            << " ; photo_profile: " << photo_profile;
    if (this->user_service.register_user(user_id, name, birthday, alias, email, photo_profile)) {
        response.SetCode(200);
        response.Send();
        LOG(INFO) << "Registration succeeded for user: " << user_id << ".";
    } else {
        response.SetCode(500);
        response.Send();
        LOG(INFO) << "Registration failed for user: " << user_id << ".";
    }
}

std::string make_body_for_login_response(const std::string user_id, const std::string token) {
    std::string body("{ \"user\": { \"userId\" : \"");
    body.append(user_id).append("\" , \"token\" : \"");
    body.append(token).append("\" } }");
    return body;
}
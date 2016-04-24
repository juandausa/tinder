//
// Copyright 2016 FiUBA
//

#include "SecurityManager.h"
#include <glog/logging.h>
#include <iostream>
#include <string>
#include "UserService.h"
#include "Response.h"
#include "Constant.h"
#include "Mongoose.h"

SecurityManager::SecurityManager(UserService user_service) : user_service(user_service) {
    this->secure_paths.push_back("/filters");
}

void SecurityManager::filter_request(struct mg_connection *nc, struct http_message *hm, Response response) {
    LOG(INFO) << "Apliying security filter for any path";
    for (std::string &path : this->secure_paths) {
        if ((mg_vcmp(&hm->uri, path.c_str()) == 0)) {
            LOG(INFO) << "Apliying security filter for path: '" << path <<"'";
            char user_id[255], token[255];
            mg_get_http_var(&hm->query_string, "userId", user_id, sizeof(user_id));
            mg_get_http_var(&hm->query_string, "token", token, sizeof(token));
            if (this->user_service.is_token_valid(user_id, token)) {
                LOG(INFO) << "User '" << user_id << "' has been authorized";
                return;
            } else {
                LOG(INFO) << "User '" << user_id << "' has not been authorized";
                /*response.SetCode(401);
                response.SetBody("{ \"error\": \"401 Unauthorized\" }");
                response.Send();*/
            }
        }
    }
}

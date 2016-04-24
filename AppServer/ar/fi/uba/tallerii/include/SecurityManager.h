//
// Copyright 2016 FiUBA
//

#ifndef TINDER_SECURITYMANAGER_H
#define TINDER_SECURITYMANAGER_H

#include "UserService.h"
#include "Response.h"

class SecurityManager {
public:
    SecurityManager(UserService user_service);
    void filter_request(struct mg_connection *nc, struct http_message *hm, Response response);
private:
    UserService user_service;
    std::vector<std::string> secure_paths;
};


#endif //TINDER_SECURITYMANAGER_H

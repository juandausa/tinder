//
// Copyright 2016 FiUBA
//

#include "UserService.h"
#include <glog/logging.h>
#include <string>
#include "RandomTextGenerator.h"
#include "DataBase.h"
#include "MD5.h"
#include "RandomTextGenerator.h"
#include "Constant.h"

UserService::UserService(DataBase &db) : database(&db) {
}

bool UserService::isUserRegistered(const std::string userId) {
    LOG(INFO) << "Checking whether the user '" << userId << "' is registered";
    std::string value;
    return (userId == "1");

//    if (this->database->is_open()) {
//        return this->database->get(userId, &value);
//    }

//    LOG(WARNING) << "The database is closed.";
//    return false;
}

bool UserService::registerUser(const std::string user_id, const std::string name,
                                const std::string birthday, const std::string alias,
                                const std::string email, const std::string photo_profile) {
    // TODO(jasmina): enviar request con curl a SharedServer
    return true;
}

std::string UserService::getSecurityToken(const std::string userId) {
    LOG(INFO) << "Generating security token for user: '" << userId <<"'";
    RandomTextGenerator rnd;
    std::string random_string = rnd.generate(Constant::random_characters_quantity);
    std::string token = md5(userId + random_string);
    if (this->database->is_open()) {
        this->database->set(Constant::security_token_prefix + userId, token);
    } else {
        LOG(WARNING) << "The database is closed.";
    }

    return token;
}

bool UserService::isTokenValid(const std::string userId, const std::string token) {
    LOG(INFO) << "Checking whether the security token '" << token << "' for user '" << userId << "' is valid";
    if (userId.compare("") == 0 || token.compare("") == 0) {
        return false;
    }

    std::string retrieved_token;
    if (this->database->is_open()) {
        this->database->get(Constant::security_token_prefix + userId, &retrieved_token);
    } else {
        LOG(WARNING) << "The database is closed.";
    }

    return token.compare(retrieved_token) == 0;
}

std::string UserService::getExternalUserId(std::string userId) {
    return "0";
}

UserService::~UserService() {
}

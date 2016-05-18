//
// Copyright 2016 FiUBA
//

#include "UserService.h"
#include <string>


UserService::UserService(DataBase &db) : database(&db) {
}

bool UserService::isUserRegistered(const std::string userId) {
    LOG(INFO) << "Checking whether the user '" << userId << "' is registered";
    std::string value;
    if (this->database->is_open()) {
        return this->database->get(Constant::security_token_prefix + userId, &value);
    }
//
    LOG(WARNING) << "The database is closed.";
    return false;
}

bool UserService::registerUser(const std::string appUserId, const std::string sharedUserId) {
    if (this->database->is_open()) {
        return this->database->set(appUserId, sharedUserId) && this->database->set(sharedUserId, appUserId);
    }
    return false;
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
    std::string sharedUserId;
    if (this->database->is_open()) {
        this->database->get(userId, &sharedUserId);
    } else {
        LOG(WARNING) << "The database is closed.";
    }
    return sharedUserId;
}

std::string UserService::getAppUserId(std::string sharedUserId) {
    std::string appUserId;
    if (this->database->is_open()) {
        this->database->get(sharedUserId, &appUserId);
    } else {
        LOG(WARNING) << "The database is closed.";
    }
    return appUserId;
}

bool UserService::addLike(const std::string fromUserId, const std::string toUserId) {
    return true;
}

std::vector<std::string> UserService::getLikes(const std::string userId) {
    return std::vector<std::string>();
}

std::vector<std::string> UserService::getMatches(const std::string userId) {
    return std::vector<std::string>();
}

UserService::~UserService() {
}

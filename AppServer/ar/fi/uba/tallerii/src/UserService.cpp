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

UserService :: UserService(DataBase & db) : database(&db) {
}

bool UserService :: is_user_registered(const std::string user_id) {
    LOG(INFO) << "Checking whether the user " << user_id << " is registered";
    std::string value;
    if (this->database->is_open()) {
        return this->database->get(user_id, &value);
    }

    LOG(WARNING) << "The database is closed.";
    return false;
}

bool UserService :: register_user(const std::string user_id, const std::string name,
                                  const std::string birthday, const std::string alias,
                                  const std::string email, const std::string photo_profile) {
    // TODO(jasmina): enviar request con curl a SharedServer
    return true;
}

std::string UserService :: get_securiry_token(const std::string user_id) {
    LOG(INFO) << "Generating security token for user: " << user_id;
    RandomTextGenerator rnd;
    std::string random_string = rnd.generate();
    std::string token = md5(user_id + random_string);
    if (this->database->is_open()) {
        this->database->set(Constant :: security_token_prefix + user_id, token);
    } else {
        LOG(WARNING) << "The database is closed.";
    }

    return token;
}

bool UserService ::is_token_valid(const std::string user_id, const std::string token) {
    std::string retrieved_token;
    if (this->database->is_open()) {
        this->database->get(Constant :: security_token_prefix + user_id, &retrieved_token);
    } else {
        LOG(WARNING) << "The database is closed.";
    }

    return token.compare(retrieved_token) == 0;
}

UserService ::~UserService() {
}

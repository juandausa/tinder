//
// Copyright 2016 FiUBA
//

#include <string>
#include <RandomTextGenerator.h>
#include "UserService.h"
#include "DataBase.h"
#include "MD5.h"
#include "RandomTextGenerator.h"

UserService :: UserService(DataBase & db) : database(&db) {
}

bool UserService :: is_user_registered(const std::string user_id) {
    std::string value;
    if (this->database->is_open()) {
        return this->database->get(user_id, &value);
    }
    return false;
}

bool UserService :: register_user(const std::string user_id, const std::string name,
                                  const std::string birthday, const std::string alias,
                                  const std::string email, const std::string photo_profile) {
    // TODO(jasmina): enviar request con curl a SharedServer
    return true;
}

std::string UserService :: get_securiry_token(std::string username) {
    RandomTextGenerator rnd;
    std::string random_string = rnd.generate();
    return md5(username.append(random_string));
}

bool UserService ::is_token_valid(std::string username, std::string token) {
    return true;
}

UserService ::~UserService() {
}

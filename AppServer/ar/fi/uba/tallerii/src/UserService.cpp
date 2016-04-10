//
// Copyright 2016 FiUBA
//

#include <string>
#include "UserService.h"
#include "DataBase.h"

UserService :: UserService(DataBase & db) : database(&db) {
}

bool UserService :: is_user_registered(const std::string user_id) {
    std::string value;
    if (this->database->is_open()) {
        return this->database->get(user_id, &value);
    }
    return false;
}

UserService ::~UserService() {
}

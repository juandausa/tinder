//
// Created by juan on 08/04/16.
//

#include <string>
#include "UserService.h"
#include "DataBase.h"

UserService :: UserService(DataBase database) : database(database) {
}


bool UserService :: is_user_registered(std::string user_id) {
    std::string value;
    return this->database.get(user_id, &value);
}
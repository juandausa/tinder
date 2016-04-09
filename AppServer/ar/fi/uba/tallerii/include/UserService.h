//
// Created by juan on 08/04/16.
//

#ifndef TINDER_USERSERVICE_H
#define TINDER_USERSERVICE_H
#include <string>
#include "DataBase.h"

class UserService {
public:
    UserService(DataBase database);
    bool is_user_registered(std::string user_id);
private:
    DataBase database;
};


#endif //TINDER_USERSERVICE_H

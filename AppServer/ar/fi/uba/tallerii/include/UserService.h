//
// Created by juan on 08/04/16.
//

#ifndef TINDER_USERSERVICE_H
#define TINDER_USERSERVICE_H
#include <string>
#include "DataBase.h"

class UserService {
public:
    UserService(DataBase & db);
    ~UserService();
    bool is_user_registered(const std::string user_id);
    bool register_user(const std::string user_id, const std::string name,
                       const std::string birthday, const std::string alias,
                       const std::string email, const std::string photo_profile);
private:
    DataBase* database;
};


#endif //TINDER_USERSERVICE_H

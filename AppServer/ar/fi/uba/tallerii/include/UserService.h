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
    bool isUserRegistered(const std::string userId);
    bool registerUser(const std::string userId, const std::string name,
                       const std::string birthday, const std::string alias,
                       const std::string email, const std::string photoProfile);
    std::string getSecurityToken(const std::string userName);
    bool isTokenValid(const std::string userName, const std::string token);
    std::string getExternalUserId(std::string userId);
private:
    DataBase* database;
};

#endif //TINDER_USERSERVICE_H

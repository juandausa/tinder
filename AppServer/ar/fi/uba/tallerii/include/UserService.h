//
// Created by juan on 08/04/16.
//

#ifndef TINDER_USERSERVICE_H
#define TINDER_USERSERVICE_H
#include <string>
#include "DataBase.h"
#include <glog/logging.h>
#include <string>
#include "RandomTextGenerator.h"
#include "DataBase.h"
#include "MD5.h"
#include "RandomTextGenerator.h"
#include "Constant.h"

class UserService {
public:
    UserService(DataBase & db);
    ~UserService();
    bool isUserRegistered(const std::string userId);
    bool registerUser(const std::string userId, const std::string token);
    std::string getSecurityToken(const std::string userName);
    bool isTokenValid(const std::string userName, const std::string token);
    std::string getExternalUserId(std::string userId);
    std::string getAppUserId(std::string sharedUserId);
    std::vector<std::string> getLikes(const std::string userId);
    bool addLike(const std::string fromUserId, const std::string toUserId);
    std::vector<std::string> getMatches(const std::string userId);

private:
    DataBase* database;
};

#endif //TINDER_USERSERVICE_H

//
// Created by juan on 08/04/16.
//

#ifndef TINDER_USERSERVICE_H
#define TINDER_USERSERVICE_H
#include <string>
#include "DataBase.h"
#include <glog/logging.h>
#include <string>
#include <algorithm>
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
    std::string getCountLikes(const std::string userId);
    std::vector<std::string> getDislikes(const std::string userId);
    std::vector<std::string> getMatches(const std::string userId);
    bool addLike(const std::string fromUserId, const std::string toUserId);
    bool hasLike(const std::string fromUserId, const std::string toUserId);
    bool addDislike(const std::string fromUserId, const std::string toUserId);
    bool hasDislike(const std::string fromUserId, const std::string toUserId);
    bool hasMatch(const std::string fromUserId, const std::string toUserId);
    bool setDiscoveringDistance(const std::string appUserId, const std::string discoveringDistance);

private:
    DataBase* database;
    bool addMatch(const std::string fromUserId, const std::string toUserId);
};

#endif //TINDER_USERSERVICE_H

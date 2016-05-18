//
// Copyright 2016 FiUBA
//

#include "UserService.h"
#include <string>
#include <vector>


UserService::UserService(DataBase &db) : database(&db) {
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }

    return elems;
}

std::string convertInString(std::vector<std::string> vector) {
    std::string out("");
    if (vector.size() != 0) {
        out.append(vector[0]);
        for (size_t i = 1; i < vector.size(); i++) {
            out += Constant::likes_separator;
            // Because likes_separator is a char.
            out.append(vector[i]);
        }
    }

    return out;
}

std::vector<std::string> convertInVector(std::string in) {
    std::vector<std::string> out = split(in, Constant::likes_separator);

    return out;
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
    if (this->database->is_open()) {
        std::string previousLikes("");
        this->database->get(Constant::likes_prefix + fromUserId, &previousLikes);
        if (previousLikes.length() != 0) {
            previousLikes += Constant::likes_separator;
            // Because likes_separator is a char.
            previousLikes.append(toUserId);
            return this->database->set(Constant::likes_prefix + fromUserId, previousLikes);
        } else {
            return this->database->set(Constant::likes_prefix + fromUserId, toUserId);
        }
    } else {
        LOG(WARNING) << "The database is closed.";
        return false;
    }

    return true;
}

std::vector<std::string> UserService::getLikes(const std::string userId) {
    std::string like;
    this->database->get(Constant::likes_prefix + userId, &like);
    if (like.length() != 0) {
        return convertInVector(like);
    }

    std::vector<std::string> likes;
    return likes;
}

std::vector<std::string> UserService::getMatches(const std::string userId) {
    return std::vector<std::string>();
}

UserService::~UserService() {
}

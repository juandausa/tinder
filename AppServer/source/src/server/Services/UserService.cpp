//
// Copyright 2016 FiUBA
//

#include "UserService.h"
#include <string>
#include <vector>

UserService::UserService(){
    this->database = DataBase::getInstance();
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
        LOG(WARNING) << "Getting external user Id. The database is closed.";
    }
    return sharedUserId;
}

std::string UserService::getAppUserId(std::string sharedUserId) {
    std::string appUserId;
    if (this->database->is_open()) {
        this->database->get(sharedUserId, &appUserId);
    } else {
        LOG(WARNING) << "Getting user Id. The database is closed.";
    }
    return appUserId;
}

bool UserService::hasLike(std::string fromUserId, std::string toUserId) {
    std::vector<std::string> likes = this->getLikes(fromUserId);
    if (std::find(likes.begin(), likes.end(), toUserId) != likes.end()) {
        return true;
    }

    return false;
}

bool UserService::hasMatch(std::string fromUserId, std::string toUserId) {
    std::vector<std::string> matches = this->getMatches(fromUserId);
    if (std::find(matches.begin(), matches.end(), toUserId) != matches.end()) {
        return true;
    }

    return false;
}

bool UserService::addLike(const std::string fromUserId, const std::string toUserId) {
    if (this->database->is_open()) {
        if (!this->hasLike(fromUserId, toUserId)) {
            std::string previousLikes("");
            this->database->get(Constant::likes_prefix + fromUserId, &previousLikes);
            bool result;
            if (previousLikes.length() != 0) {
                previousLikes += Constant::likes_separator;
                // Because likes_separator is a char.
                previousLikes.append(toUserId);
                result = this->database->set(Constant::likes_prefix + fromUserId, previousLikes);
            } else {
                result = this->database->set(Constant::likes_prefix + fromUserId, toUserId);
            }
            if (result && this->hasLike(toUserId, fromUserId)) {
                return this->addMatch(fromUserId, toUserId) && this->addMatch(toUserId, fromUserId);
            }

            return result;
        }

        return true;
    } else {
        LOG(WARNING) << "Adding like. The database is closed.";
        return false;
    }
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
    std::string match;
    this->database->get(Constant::matches_prefix + userId, &match);
    if (match.length() != 0) {
        return convertInVector(match);
    }

    std::vector<std::string> matches;
    return matches;
}

bool UserService::addMatch(const std::string fromUserId, const std::string toUserId) {
    if (this->database->is_open()) {
        if (!this->hasMatch(fromUserId, toUserId)) {
            std::string previousMatches("");
            this->database->get(Constant::matches_prefix + fromUserId, &previousMatches);
            bool result;
            if (previousMatches.length() != 0) {
                previousMatches += Constant::likes_separator;
                // Because likes_separator is a char.
                previousMatches.append(toUserId);
                result = this->database->set(Constant::matches_prefix + fromUserId, previousMatches);
            } else {
                result = this->database->set(Constant::matches_prefix + fromUserId, toUserId);
            }

            return result;
        }

        return true;
    } else {
        LOG(WARNING) << "Adding match. The database is closed.";
        return false;
    }
}

std::vector<std::string> UserService::getDislikes(const std::string userId) {
    std::string dislikes;
    this->database->get(Constant::dislikes_prefix + userId, &dislikes);
    if (dislikes.length() != 0) {
        return convertInVector(dislikes);
    }

    std::vector<std::string> emptyVector;
    return emptyVector;
}

bool UserService::addDislike(const std::string fromUserId, const std::string toUserId) {
    if (this->database->is_open()) {
        if (!this->hasDislike(fromUserId, toUserId)) {
            std::string previousDislikes("");
            this->database->get(Constant::dislikes_prefix + fromUserId, &previousDislikes);
            bool result;
            if (previousDislikes.length() != 0) {
                previousDislikes += Constant::likes_separator;
                // Because likes_separator is a char.
                previousDislikes.append(toUserId);
                result = this->database->set(Constant::dislikes_prefix + fromUserId, previousDislikes);
            } else {
                result = this->database->set(Constant::dislikes_prefix + fromUserId, toUserId);
            }

            return result;
        }

        return true;
    } else {
        LOG(WARNING) << "Adding dislike. The database is closed.";
        return false;
    }
}

bool UserService::hasDislike(const std::string fromUserId, const std::string toUserId) {
    std::vector<std::string> dislikes = this->getDislikes(fromUserId);
    if (std::find(dislikes.begin(), dislikes.end(), toUserId) != dislikes.end()) {
        return true;
    }

    return false;
}

UserService::~UserService() {
}

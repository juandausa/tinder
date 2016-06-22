//
// Copyright 2016 FiUBA
//

#include "AddLikeController.h"
#include <string>

void AddLikeController::operation(Request &request, Response &response) {
    std::string fromUserId = request.getResourceId();
    std::string toUserId = this->getUserTo(request.getBody());
    LOG(INFO) << "Adding like from user: '" << fromUserId << "' to user: '" << toUserId << "'";
    if ((fromUserId.length() == 0) || (toUserId.length() == 0)) {
        response.SetCode(500);
        response.SetBody("Bad Request, no fromUserId or toUserId detected.");
        LOG(WARNING) << "Bad request for addLike. User: '" << fromUserId << "' or user: '" << toUserId << "'";
    } else if ((!userService.isUserRegistered(fromUserId)) || (!userService.isUserRegistered(toUserId))) {
        response.SetCode(500);
        response.SetBody(
                "Bad Request, fromUserId '" + fromUserId + "' or toUserId '" + toUserId + " is not registered.");
        LOG(WARNING) << "Error for addLike. User: '" << fromUserId << "' or user: '" << toUserId <<
        "' is not registered";
    } else {
        if (this->userService.addLike(fromUserId, toUserId)) {
            response.SetCode(200);
            LOG(INFO) << "Like from user: '" << fromUserId << "' to user: '" << toUserId << "' added";
        } else {
            response.SetCode(500);
            response.SetBody("Error for addLike, error on save.");
            LOG(WARNING) << "Error for addLike, error on save. From user: '" << fromUserId << "' to user: '" <<
            toUserId << "'";
        }
    }

    response.Send();
}


std::string AddLikeController::getUserTo(const std::string body) {
    Json::Value userInfo;
    bool parsingSuccessful = reader.parse(body, userInfo, true);
    if (!parsingSuccessful) {
        return "";
    }

    return userInfo.get("to_user_id", "").asString();
}

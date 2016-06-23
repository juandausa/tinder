//
// Copyright 2016 FiUBA
//

#include "AddDisLikeController.h"
#include <string>

void AddDisLikeController::operation(Request &request, Response &response) {
    std::string fromUserId = request.getResourceId();
    std::string toUserId = this->getUserTo(request.getBody());
    LOG(INFO) << "Adding dislike from user: '" << fromUserId << "' to user: '" << toUserId << "'";

    if ((fromUserId.length() == 0) || (toUserId.length() == 0)) {
        response.SetCode(500);
        response.SetBody("Bad Request, no fromUserId or toUserId detected.");
        LOG(WARNING) << "Bad request for addDislike. User: '" << fromUserId << "' or user: '" << toUserId << "'";
    } else if ((!userService.isUserRegistered(fromUserId)) || (!userService.isUserRegistered(toUserId))) {
        response.SetCode(500);
        response.SetBody(
                "Bad Request, fromUserId '" + fromUserId + "' or toUserId '" + toUserId + " is not registered.");
        LOG(WARNING) << "Error for addDislike. User: '" << fromUserId << "' or user: '" << toUserId <<
        "' is not registered";
    } else {
        if (this->userService.addDislike(fromUserId, toUserId)) {
            response.SetCode(200);
            response.SetBody(getSucceedResponseBody());
            LOG(INFO) << "Dislike from user: '" << fromUserId << "' to user: '" << toUserId << "' added";
        } else {
            response.SetCode(500);
            response.SetBody("Error for addDislike, error on save.");
            LOG(WARNING) << "Error for addDislike, error on save. From user: '" << fromUserId << "' to user: '" <<
            toUserId << "'";
        }
    }

    response.Send();
}


std::string AddDisLikeController::getUserTo(const std::string body) {
    Json::Value userInfo;
    bool parsingSuccessful = reader.parse(body, userInfo, true);
    if (!parsingSuccessful) {
        return "";
    }

    return userInfo.get("to_user_id", "").asString();
}

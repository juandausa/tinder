//
// Copyright 2016 FiUBA
//

#include "UserLoginController.h"
#include <string>

void UserLoginController::operation(Request &request, Response &response) {
    log->writeAndPrintLog("UserLoginController", Log::INFO);
    std::string userId = request.getResourceId();
    log->writeAndPrintLog(std::string("Proccesing login for user: ' ") + userId + std::string("'"), Log::INFO);
    if (this->userService.isUserRegistered(userId)) {
        response.SetCode(200);
        Json::Value event = this->makeBodyAndTokenForLoginResponse(userId);
        std::string data = fastWriter.write(event);
        response.SetBody(data);
        response.Send();
        log->writeAndPrintLog(std::string("Login succeeded for user: ' ") + userId + std::string("'"), Log::INFO);
    } else {
        response.SetCode(304);
        response.Send();
        log->writeAndPrintLog(std::string("Login failed for user: ' ") + userId + std::string("'"), Log::WARNING);
    }
}

Json::Value UserLoginController::makeBodyAndTokenForLoginResponse(const std::string userId) {
    Json::Value event;
    std::string token = this->userService.getSecurityToken(userId);
    event["user"]["token"] = token;
    return event;
}

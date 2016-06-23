//
// Copyright 2016 FiUBA
//

#include "MatchesController.h"
#include "Converter.h"
#include <string>
#include <vector>

void MatchesController::operation(Request &request, Response &response) {
    std::string userId = request.getResourceId();
    LOG(INFO) << "Proccesing show matches for user: '" << userId << "'";
    if (!this->userService.isUserRegistered(userId)) {
        response.SetCode(500);
        response.SetBody(this->getErrorResponseBody());
        response.Send();
        LOG(INFO) << "Show matches has returned no users for user: '" << userId << "'";
        return;
    }

    response.SetCode(200);
    response.SetBody(this->makeBodyForShowMatchesResponse(userId));
    response.Send();
}

std::string MatchesController::makeBodyForShowMatchesResponse(std::string userId) {
    Json::Value result;
    Json::Value matches;
    result["matches"] = Json::arrayValue;
    std::string readBuffer;

    Json::Value users = this->getUsersFromSharedServer();
    for (unsigned int i = 0; i < users.size(); i++) {
        Json::Value user = users[i]["user"];
        std::string sharedUserId = Converter::intToString(user.get("id", "").asInt());
        std::string appUserId = this->userService.getAppUserId(sharedUserId);
        std::cout << "CHECK FOR MATCH WITH: " << appUserId << std::endl;
        if (!this->userService.hasMatch(userId, appUserId)) {
            continue;
        }
        user["user_id"] = appUserId;
        user["messages"] = this->getMessages(userId, appUserId);
        user["age"] = Converter::calculateAge(user.get("birthday", "").asString());
        user.removeMember("id");
        user.removeMember("location");
        // LIBERAR ESTA MEMORIA
        std::string photoBase64 = this->matchesService.getMatchPhoto((users[i]["user"].get("photo_profile", "")).asString());
        user["photo_profile"] = photoBase64;
        matches.append(user);
    }

    if (matches.size() > 0) {
        result["matches"] = matches;
    }

    return this->fastWriter.write(result);
}

Json::Value MatchesController::getUsersFromSharedServer() {
    std::string readBuffer;
    Json::Value root;
    CurlWrapper curlWrapper = CurlWrapper();
    std::string url = Constant::getUsersUrl;
    curlWrapper.set_post_url(url);
    curlWrapper.set_get_buffer(readBuffer);
    if (curlWrapper.perform_request()) {
        if (reader.parse(readBuffer, root, true)) {
            return root["users"];
        }
    }

    Json::Value empty;
    return empty;
}

Json::Value MatchesController::getMessages(std::string sender, std::string reciever) {
    Json::Value convertedMessages = Json::arrayValue;
    std::vector<Message> messages = this->messagesService.getMessages(sender, reciever);
    if (messages.size() == 0) {
        return convertedMessages;
    }

    for (size_t i = 0; i < messages.size(); i++) {
        Json::Value message;
        if (messages[i].getSender().compare(sender) == 0) {
            message["0"] = messages[i].getContent();
        } else {
            message["1"] = messages[i].getContent();
        }

        convertedMessages.append(message);
    }

    return convertedMessages;
}




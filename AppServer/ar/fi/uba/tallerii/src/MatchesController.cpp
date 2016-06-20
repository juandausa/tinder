//
// Copyright 2016 FiUBA
//

#include "MatchesController.h"
#include "CurlWrapper.h"
#include <string>

MatchesController::MatchesController(MatchesService matches_service, UserService user_service,
                                     MessagesService messages_service) :
        matchesService(matches_service), userService(user_service), messagesService(messages_service) {
}

void MatchesController::handleGetMatches(RequestParser requestParser, Response response) {
    /*
     * Pedir todos los usuarios.
     * Filtrar los matcheados
     * Agregarle la lista de mensajes
     */

    std::string userId = requestParser.getResourceId();
    LOG(INFO) << "Proccesing show matches for user: '" << userId << "'";
    /*if (!this->userService.isUserRegistered(userId)) {
        response.SetCode(500);
        response.SetBody(this->getErrorResponseBody());
        response.Send();
        LOG(INFO) << "Show matches has returned no users for user: '" << userId<< "'";
        return;
    }*/

    response.SetCode(200);
    response.SetBody(this->makeBodyForShowMatchesResponse(userId));
    response.Send();
}

std::string MatchesController::getErrorResponseBody() {
    Json::Value errorResponse;
    errorResponse["matches"] = Json::arrayValue;
    return this->fastWriter.write(errorResponse);
}

std::string MatchesController::intToString(int value) {
    std::ostringstream oss;
    // Works just like cout
    oss << value;
    // Return the underlying string
    return oss.str();
}

std::string MatchesController::makeBodyForShowMatchesResponse(std::string userId) {
    Json::Value result;
    Json::Value matches;
    result["matches"] = Json::arrayValue;
    std::string readBuffer;

    Json::Value users = this->getUsersFromSharedServer();
    for (unsigned int i = 0; i < users.size(); i++) {
        Json::Value user = users[i]["user"];
        std::string sharedUserId = intToString(user.get("id", "").asInt());
        std::string appUserId = this->userService.getAppUserId(sharedUserId);
        user["userId"] = appUserId;
        user["messages"] = this->getMessages(userId, appUserId);
        user.removeMember("id");
        user.removeMember("location");
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



//
// Copyright 2016 FiUBA
//

#include "GetMessagesController.h"
#include <string>


void GetMessagesController::operation(Request &request, Response &response) {
    LOG(INFO) << "Getting messages from user: '" << request.getResourceId() << "'";
    Message message = this->getMessageFromRequest(request);
    std::string sender = message.getSender();
    std::string reciever = message.getReciever();
    if ((sender.length() == 0) || (reciever.length() == 0)) {
        response.SetCode(500);
        response.SetBody(this->getErrorResponseBody());
        LOG(WARNING) << "Bad Request, no sender or reciever detected. Sender: '" << sender << "' or reciever: '" <<
        reciever << "'";
    } else if ((!userService.isUserRegistered(sender)) || (!userService.isUserRegistered(reciever))) {
        response.SetCode(500);
        response.SetBody(this->getErrorResponseBody());
        LOG(WARNING) << "Error for getMessage. User: '" << sender << "' or user: '" << reciever <<
        "' is not registered";
    } else {
        Message lastMessage = this->messagesService.getLastMessage(sender, reciever);
        if (lastMessage.getContent().length() == 0) {
            response.SetCode(200);
            response.SetBody(this->getEmptyMessageResponseBody());
            LOG(INFO) << "No last message between user: '" << sender << "' and user: '" << reciever << "'.";
        } else {
            response.SetCode(200);
            response.SetBody(this->getMessageResponseBody(lastMessage));
            LOG(WARNING) << "Error for getMessage, error on load. From user: '" << sender << "' to user: '" <<
            reciever << "'";
        }
    }

    response.Send();
}

Message GetMessagesController::getMessageFromRequest(Request &request) {
    Json::Value message;
    bool parsingSuccessful = this->reader.parse(request.getBody(), message, true);
    if (!parsingSuccessful) {
        Message emptyMessage;
        return emptyMessage;
    }

    Message result(request.getResourceId(), message.get("to_user_id", "").asString(),
                   message.get("message", "").asString());
    return result;
}


std::string GetMessagesController::getErrorResponseBody() {
    Json::Value errorResponse;
    errorResponse["status_code"] = 500;
    return this->fastWriter.write(errorResponse);
}

std::string GetMessagesController::getSucceedResponseBody() {
    Json::Value succeedResponse;
    succeedResponse["status_code"] = 200;
    return this->fastWriter.write(succeedResponse);
}

std::string GetMessagesController::getEmptyMessageResponseBody() {
    Json::Value succeedResponse;
    succeedResponse["message"] = "";
    return this->fastWriter.write(succeedResponse);
}

std::string GetMessagesController::getMessageResponseBody(Message message) {
    Json::Value messageResponse;
    messageResponse["message"] = message.getContent();
    return this->fastWriter.write(messageResponse);
}

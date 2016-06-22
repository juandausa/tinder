//
// Copyright 2016 FiUBA
//

#include "AddMessagesController.h"
#include <string>

void AddMessagesController::operation(Request &request, Response &response) {
    LOG(INFO) << "Adding message from user: '" << request.getResourceId() << "'";
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
        LOG(WARNING) << "Error for addMessage. User: '" << sender << "' or user: '" << reciever <<
        "' is not registered";
    } else {
        if (this->messagesService.addMessage(message)) {
            response.SetCode(200);
            response.SetBody(this->getSucceedResponseBody());
            LOG(INFO) << "Message from user: '" << sender << "' to user: '" << reciever << "' added";
        } else {
            response.SetCode(500);
            response.SetBody(this->getErrorResponseBody());
            LOG(WARNING) << "Error for addMessage, error on save. From user: '" << sender << "' to user: '" <<
            reciever << "'";
        }
    }

    response.Send();
}

Message AddMessagesController::getMessageFromRequest(Request &request) {
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


std::string AddMessagesController::getErrorResponseBody() {
    Json::Value errorResponse;
    errorResponse["status_code"] = 500;
    return this->fastWriter.write(errorResponse);
}

std::string AddMessagesController::getSucceedResponseBody() {
    Json::Value succeedResponse;
    succeedResponse["status_code"] = 200;
    return this->fastWriter.write(succeedResponse);
}

std::string AddMessagesController::getEmptyMessageResponseBody() {
    Json::Value succeedResponse;
    succeedResponse["message"] = "";
    return this->fastWriter.write(succeedResponse);
}

std::string AddMessagesController::getMessageResponseBody(Message message) {
    Json::Value messageResponse;
    messageResponse["message"] = message.getContent();
    return this->fastWriter.write(messageResponse);
}

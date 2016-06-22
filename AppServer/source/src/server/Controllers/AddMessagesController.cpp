//
// Copyright 2016 FiUBA
//

#include "AddMessagesController.h"
#include <string>

void AddMessagesController::operation(Request &request, Response &response) {
    log->writeAndPrintLog(std::string("Adding message from user: '") + request.getResourceId()
                                  + std::string("'"), Log::INFO);

    Message message = this->getMessageFromRequest(request);

    std::string sender = message.getSender();
    std::string reciever = message.getReciever();
    if ((sender.length() == 0) || (reciever.length() == 0)) {
        response.SetCode(500);
        response.SetBody(this->getErrorResponseBody());
        log->writeAndPrintLog(std::string("Bad Request, no sender or reciever detected. Sender: '") + request.getResourceId()
                                  + std::string("' or reciever: '") + reciever + std::string("'"), Log::WARNING);
    } else if ((!userService.isUserRegistered(sender)) || (!userService.isUserRegistered(reciever))) {
        response.SetCode(500);
        response.SetBody(this->getErrorResponseBody());
        log->writeAndPrintLog(std::string("Error for addMessage. User: '") + sender
                                  + std::string("' or user: '") + reciever + std::string("' is not registered"), Log::WARNING);
    } else {
        if (this->messagesService.addMessage(message)) {
            response.SetCode(200);
            response.SetBody(this->getSucceedResponseBody());
            log->writeAndPrintLog(std::string("Message from user: '") + sender
                                  + std::string("' to user: '") + reciever + std::string("' added"), Log::INFO);
        } else {
            response.SetCode(500);
            response.SetBody(this->getErrorResponseBody());
            log->writeAndPrintLog(std::string("Error for addMessage, error on save. From user: '") + sender
                                  + std::string("' to user: '") + reciever + std::string("'"), Log::WARNING);
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
    log->writeAndPrintLog(message.get("message", "").asString(), Log::INFO);
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

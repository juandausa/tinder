//
// Copyright 2016 FiUBA
//

#include "MessagesController.h"
#include <string>

MessagesController::MessagesController(MessagesService messages_service, UserService user_service) :
        messagesService(messages_service), userService(user_service) {
}

Message MessagesController::getMessageFromRequest(RequestParser request) {
    Json::Value message;
    bool parsingSuccessful = this->reader.parse(request.getBody(), message, true);
    if (!parsingSuccessful) {
        Message emptyMessage;
        return emptyMessage;
    }

    Message result(request.getResourceId(), message.get("to_user_id", "").asString(), message.get("message", "").asString());
    return result;
}

void MessagesController::handleAddMessage(RequestParser requestParser, Response response) {
    LOG(INFO) << "Adding message from user: '" << requestParser.getResourceId() << "'";
    Message message = this->getMessageFromRequest(requestParser);
    std::string sender = message.getSender();
    std::string reciever = message.getReciever();
    if ((sender.length() == 0) || (reciever.length() == 0)) {
        response.SetCode(500);
        response.SetBody("Bad Request, no sender or reciever detected.");
        LOG(WARNING) << "Bad Request, no sender or reciever detected. Sender: '" << sender << "' or user: '" <<
        reciever << "'";
    } else if ((!userService.isUserRegistered(sender)) || (!userService.isUserRegistered(reciever))) {
        response.SetCode(500);
        response.SetBody(
                "Bad Request, sender '" + sender + "' or reciever '" + reciever + " is not registered.");
        LOG(WARNING) << "Error for addLike. User: '" << sender << "' or user: '" << reciever <<
        "' is not registered";
    } else {
        if (this->messagesService.addMessage(message)) {
            response.SetCode(200);
            LOG(INFO) << "Message from user: '" << sender << "' to user: '" << reciever << "' added";
        } else {
            response.SetCode(500);
            response.SetBody("Error for addMessage, error on save.");
            LOG(WARNING) << "Error for addMessage, error on save. From user: '" << sender << "' to user: '" <<
            reciever << "'";
        }
    }

    response.Send();
}

void MessagesController::handleGetMessages(RequestParser requestParser, Response response) {
    response.SetCode(200);
    response.SetBody("RECIBIDO");
    response.Send();
}

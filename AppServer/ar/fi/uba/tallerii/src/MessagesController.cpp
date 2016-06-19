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
        response.SetBody(this->getErrorResponseBody());
        LOG(WARNING) << "Bad Request, no sender or reciever detected. Sender: '" << sender << "' or user: '" <<
        reciever << "'";
    } else if ((!userService.isUserRegistered(sender)) || (!userService.isUserRegistered(reciever))) {
        response.SetCode(500);
        response.SetBody(this->getErrorResponseBody());
        LOG(WARNING) << "Error for addLike. User: '" << sender << "' or user: '" << reciever <<
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

void MessagesController::handleGetMessages(RequestParser requestParser, Response response) {
    response.SetCode(200);
    response.SetBody(this->getSucceedResponseBody());
    response.Send();
    /*OK:
		{message: “ESTO ES UN MENSAJE”}
	Error:
		{message: “”}
     */
}

std::string MessagesController::getErrorResponseBody() {
    Json::Value errorResponse;
    errorResponse["status_code"] = 500;
    return this->fastWriter.write(errorResponse);
}

std::string MessagesController::getSucceedResponseBody() {
    Json::Value succeedResponse;
    succeedResponse["status_code"] = 200;
    return this->fastWriter.write(succeedResponse);
}

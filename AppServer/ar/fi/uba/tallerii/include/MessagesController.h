//
// Copyright 2016 FiUBA
//

#ifndef TINDER_MESSAGESCONTROLLER_H
#define TINDER_MESSAGESCONTROLLER_H

#include "MessagesService.h"
#include "UserService.h"
#include "RequestParser.h"
#include "Response.h"
#include "Message.h"
#include <jsoncpp/json/json.h>
#include <string>

class MessagesController {
public:
    MessagesController(MessagesService messages_service, UserService user_service);
    virtual void handleAddMessage(RequestParser requestParser, Response response);
    virtual void handleGetMessages(RequestParser requestParser, Response response);

private:
    MessagesService messagesService;
    UserService userService;
    Json::Reader reader;
    Json::FastWriter fastWriter;
    Message getMessageFromRequest(RequestParser request);
    std::string getErrorResponseBody();
    std::string getSucceedResponseBody();
};


#endif //TINDER_MESSAGESCONTROLLER_H

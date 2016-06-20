//
// Copyright 2016 FiUBA
//

#ifndef TINDER_ADD_MESSAGES_CONTROLLER_H
#define TINDER_ADD_MESSAGES_CONTROLLER_H

#include "GenericController.h"
#include "MessagesService.h"
#include "UserService.h"
#include "Message.h"

class AddMessagesController: public GenericController {
	
public:
    void operation(Request &request, Response &response);
private:
    MessagesService messagesService;
    UserService userService;
	Message getMessageFromRequest(Request &request);
    std::string getErrorResponseBody();
    std::string getSucceedResponseBody();
    std::string getEmptyMessageResponseBody();
    std::string getMessageResponseBody(Message message);
};

#endif //TINDER_ADD_MESSAGES_CONTROLLER_H

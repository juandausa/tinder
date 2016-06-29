//
// Copyright 2016 FiUBA
//

#ifndef TINDER_GET_MESSAGES_CONTROLLER_H
#define TINDER_GET_MESSAGES_CONTROLLER_H

#include "GenericController.h"
#include "MessagesService.h"
#include "UserService.h"
#include "Message.h"

class GetMessagesController: public GenericController {
	
public:
    void operation(Request &request, Response &response);
	std::string getEmptyMessageResponseBody();
	std::string getMessageResponseBody(Message message);
private:
    MessagesService messagesService;
    UserService userService;
	Message getMessageFromRequest(Request &request);
    std::string getErrorResponseBody();
    std::string getSucceedResponseBody();
};

#endif //TINDER_GET_MESSAGES_CONTROLLER_H

//
// Copyright 2016 FiUBA
//

#ifndef TINDER_MESSAGESCONTROLLER_H
#define TINDER_MESSAGESCONTROLLER_H
#include "MessagesService.h"
#include "UserService.h"
#include "RequestParser.h"
#include "Response.h"

class MessagesController {
public:
    MessagesController(MessagesService messages_service, UserService user_service);
private:
    MessagesService messagesService;
    UserService userService;
};


#endif //TINDER_MESSAGESCONTROLLER_H

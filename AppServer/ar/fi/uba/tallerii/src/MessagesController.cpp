//
// Copyright 2016 FiUBA
//

#include "MessagesController.h"
#include <string>

MessagesController::MessagesController(MessagesService messages_service, UserService user_service) :
        messagesService(messages_service), userService(user_service) {
}

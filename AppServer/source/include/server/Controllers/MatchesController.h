//
//

#ifndef TINDER_MATCHCONTROLLER_H
#define TINDER_MATCHCONTROLLER_H

#include "GenericController.h"
#include "MatchesService.h"
#include "UserService.h"
#include "MessagesService.h"

class MatchesController: public GenericController {

public:
    void operation(Request &request, Response &response);
    std::string makeBodyForShowMatchesResponse(std::string userId);

private:
    MatchesService matchesService;
    UserService userService;
    MessagesService messagesService;
    Json::Value getUsersFromSharedServer();
    Json::Value getMessages(std::string userId, std::string appUserId);
    
};


#endif //TINDER_MATCHCONTROLLER_H

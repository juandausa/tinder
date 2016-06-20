//
// Copyright 2016 FiUBA
//

#ifndef TINDER_MATCHCONTROLLER_H
#define TINDER_MATCHCONTROLLER_H
#include "MatchesService.h"
#include "UserService.h"
#include "MessagesService.h"
#include "RequestParser.h"
#include "Response.h"
#include <jsoncpp/json/json.h>
#include <string>

class MatchesController {
public:
    MatchesController(MatchesService matches_service, UserService user_service, MessagesService messagesService);
    virtual void handleGetMatches(RequestParser requestParser, Response response);
private:
    MatchesService matchesService;
    UserService userService;
    MessagesService messagesService;
    Json::Reader reader;
    Json::FastWriter fastWriter;
    std::string getErrorResponseBody();
    std::string makeBodyForShowMatchesResponse(std::string userId);
    Json::Value getUsersFromSharedServer();
    Json::Value getMessages(std::string userId, std::string appUserId);
};

#endif //TINDER_MATCHCONTROLLER_H

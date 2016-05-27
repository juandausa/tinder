//
// Copyright 2016 FiUBA
//

#ifndef TINDER_MATCHCONTROLLER_H
#define TINDER_MATCHCONTROLLER_H
#include "MatchService.h"
#include "UserService.h"
#include "RequestParser.h"
#include "Response.h"

class MatchController {
public:
    MatchController(MatchService match_service, UserService user_service);
    virtual void handleGetCandidates(RequestParser requestParser, Response response);
private:
    MatchService matchService;
    UserService userService;
};


#endif //TINDER_MATCHCONTROLLER_H

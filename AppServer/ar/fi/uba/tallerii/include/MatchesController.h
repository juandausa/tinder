//
// Copyright 2016 FiUBA
//

#ifndef TINDER_MATCHCONTROLLER_H
#define TINDER_MATCHCONTROLLER_H
#include "MatchesService.h"
#include "UserService.h"
#include "RequestParser.h"
#include "Response.h"

class MatchesController {
public:
    MatchesController(MatchesService matches_service, UserService user_service);
    virtual void handleGetCandidates(RequestParser requestParser, Response response);
private:
    MatchesService matchesService;
    UserService userService;
};


#endif //TINDER_MATCHCONTROLLER_H

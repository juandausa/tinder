//
// Copyright 2016 FiUBA
//

#ifndef TINDER_MATCHCONTROLLER_H
#define TINDER_MATCHCONTROLLER_H
#include "MatchesService.h"
#include "UserService.h"
#include "Request.h"
#include "Response.h"

class MatchesController {
public:
    MatchesController(MatchesService matches_service, UserService user_service);
    void handleGetCandidates(Request Request, Response response);
private:
    MatchesService matchesService;
    UserService userService;
};


#endif //TINDER_MATCHCONTROLLER_H

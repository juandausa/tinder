//
// Created by juan on 26/05/16.
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
    virtual void handle_get_candidates(RequestParser requestParser, Response response);
private:
    MatchService match_service;
    UserService user_service;
};


#endif //TINDER_MATCHCONTROLLER_H

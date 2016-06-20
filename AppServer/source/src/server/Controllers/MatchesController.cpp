//
// Copyright 2016 FiUBA
//

#include "MatchesController.h"
#include <string>

MatchesController ::MatchesController(MatchesService matches_service, UserService user_service) :
        matchesService(matches_service), userService(user_service) {
}

void MatchesController :: handleGetCandidates(Request Request, Response response) {
//    std::string userId = Request.getResourceId();
//    LOG(INFO) << "Proccesing show candidates for user: '" << userId << "'";
//    if (this->userService.isUserRegistered(userId)) {
//        response.SetCode(200);
//        response.SetBody("{ \"response\": \"DummyUserRegistered\" }");
//        response.Send();
//        LOG(INFO) << "Show Candidates succeeded for user: '" << userId<< "'";
//    } else {
//        response.SetCode(400);
//        response.SetBody("{ \"response\": \"DummyUserNotRegistered\" }");
//        response.Send();
//        LOG(INFO) << "Show Candidates failed for user: '" << userId<< "'";
//    }
}


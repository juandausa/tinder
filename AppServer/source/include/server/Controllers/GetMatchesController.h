//
//

#ifndef TINDER_GET_MATCHES_CONTROLLER_H
#define TINDER_GET_MATCHES_CONTROLLER_H

#include "GenericController.h"
#include "UserService.h"
class GetMatchesController: public GenericController {

public:
    void operation(Request &request, Response &response);

private:
    UserService userService;
    std::string fakeResponseForUserMatches();
};


#endif //TINDER_GET_MATCHES_CONTROLLER_H

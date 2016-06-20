//
//

#ifndef TINDER_USER_REGISTER_CONTROLLER_H
#define TINDER_USER_REGISTER_CONTROLLER_H

#include "GenericController.h"
#include "UserService.h"
class UserRegisterController: public GenericController {

public:
    void operation(Request &request, Response &response);

private:
    UserService userService;
    Json::Value makeBodyAndTokenForRegistrationResponse(const std::string userId);
    Json::Value makeBodyForRegistrationPost(const Json::Value root);
    void postInterests(Json::Value root);
    
};


#endif //TINDER_USER_REGISTER_CONTROLLER_H

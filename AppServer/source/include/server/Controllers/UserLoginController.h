//
//

#ifndef TINDER_USER_LOGIN_CONTROLLER_H
#define TINDER_USER_LOGIN_CONTROLLER_H

#include "Response.h"
#include "Request.h"
#include "GenericController.h"
#include "UserService.h"
class UserLoginController: public GenericController {

public:
    void operation(Request &request,Response &response);

private:
    UserService userService;
    Json::Value makeBodyAndTokenForLoginResponse(const std::string userId);
};


#endif //TINDER_USER_LOGIN_CONTROLLER_H

//
//

#ifndef TINDER_USER_REGISTER_CONTROLLER_H
#define TINDER_USER_REGISTER_CONTROLLER_H

#include "GenericController.h"
#include "UserService.h"
#include <thread>

class UserRegisterController: public GenericController {
public:
	UserRegisterController();
	~UserRegisterController();
    void operation(Request &request, Response &response);
	Json::Value makeBodyForRegistrationPost(const Json::Value root);

private:
    UserService userService;
    std::thread* postInterestsThread;
    Json::Value makeBodyAndTokenForRegistrationResponse(const std::string userId);
    void postInterests(Json::Value root);

};


#endif //TINDER_USER_REGISTER_CONTROLLER_H

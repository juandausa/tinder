//
//

#ifndef TINDER_USER_REGISTER_CONTROLLER_H
#define TINDER_USER_REGISTER_CONTROLLER_H

#include "GenericController.h"
#include "UserService.h"
#include "PhotoService.h"
#include <thread>

class UserRegisterController: public GenericController {
public:
	UserRegisterController();
	~UserRegisterController();
    void operation(Request &request, Response &response);
	Json::Value makeBodyForRegistrationPost(const Json::Value root);
    Json::Value makeBodyAndTokenForRegistrationResponse(const std::string userId);
private:
    UserService userService;
    std::thread* postInterestsThread;
    void postInterests(Json::Value root);
};


#endif //TINDER_USER_REGISTER_CONTROLLER_H

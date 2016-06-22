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

private:
    UserService userService;
    std::thread* postInterestsThread;
    Json::Value makeBodyAndTokenForRegistrationResponse(const std::string userId);
    Json::Value makeBodyForRegistrationPost(const Json::Value root, std::string appUserId);
    void postInterests(Json::Value root);
    
};


#endif //TINDER_USER_REGISTER_CONTROLLER_H

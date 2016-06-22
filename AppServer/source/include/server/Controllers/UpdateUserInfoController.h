//
//

#ifndef TINDER_UPDATE_USER_INFO_CONTROLLER_H
#define TINDER_UPDATE_USER_INFO_CONTROLLER_H

#include "GenericController.h"
#include "UserService.h"
class UpdateUserInfoController: public GenericController {

public:
    void operation(Request &request, Response &response);
    std::string makeBodyUserInfoForUpdate(const std::string appUserId, const std::string userInfo);
    Json::Value makeBodyForRegistrationPost(Json::Value root);

private:
    UserService userService;
};


#endif //TINDER_UPDATE_USER_INFO_CONTROLLER_H

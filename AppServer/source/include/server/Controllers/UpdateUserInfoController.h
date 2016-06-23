//
//

#ifndef TINDER_UPDATE_USER_INFO_CONTROLLER_H
#define TINDER_UPDATE_USER_INFO_CONTROLLER_H

#include "GenericController.h"
#include "UserService.h"
class UpdateUserInfoController: public GenericController {

public:
    void operation(Request &request, Response &response);
    std::string makeBodyUserInfoForUpdate(const std::string info, const std::string userInfo,
                                          const std::string appUserId);
    void makeBodyForRegistrationPost(const Json::Value &root, std::string appUserId, Json::Value &userData, int userId);

private:
    UserService userService;
};


#endif //TINDER_UPDATE_USER_INFO_CONTROLLER_H

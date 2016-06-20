//
//

#ifndef TINDER_GET_USER_INFO_CONTROLLER_H
#define TINDER_GET_USER_INFO_CONTROLLER_H

#include "GenericController.h"
#include "UserService.h"
class GetUserInfoController: public GenericController {

public:
    void operation(Request &request, Response &response);

private:
    UserService userService;
    std::string makeBodyForUserInfoResponse(const std::string appUserId, const std::string userInfo);
    
};


#endif //TINDER_GET_USER_INFO_CONTROLLER_H
